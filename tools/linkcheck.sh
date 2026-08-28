#!/bin/sh
# Diagnose link failures by inspecting object files directly.
#
# collect2.exe on MSYS2/MinGW discards ld's stderr, so a link failure arrives
# as a bare "ld returned 1 exit status" with no detail. These two queries
# recover what ld would have told you:
#   1. symbols wanted by some object but defined by none  -> undefined reference
#   2. symbols defined strongly by more than one object   -> multiple definition
#
# Usage: make linkcheck

OBJDIR="${1:-build}"
T="${TMPDIR:-/tmp}/linkcheck.$$"

ls "$OBJDIR"/*.o >/dev/null 2>&1 || { echo "no .o files in $OBJDIR/ - run 'make' first"; exit 1; }

# --- 1. undefined ------------------------------------------------------------
# Anything still undefined after checking every object. C runtime and libstdc++
# names are expected here (they come from libraries at link time), so filter the
# common ones out.
NOISE='^std::|^__|^operator|^_|GLIBCXX|typeinfo|vtable|thunk|Unwind'
CRT='^(mem|str|log|exp|pow|sqrt|floor|ceil|trunc|round|fabs|fmod|next|abort|free|malloc|calloc|realloc|printf|puts|putchar|towupper|towlower|iswctype)'

nm -C -u "$OBJDIR"/*.o 2>/dev/null | sed -n 's/^ *U //p' | sort -u > "$T.undef"
nm -C --defined-only "$OBJDIR"/*.o 2>/dev/null | sed -n 's/^[0-9a-f]* [A-Za-z] //p' | sort -u > "$T.def"

echo "=== 1. Wanted, but defined nowhere  (undefined reference) ==="
comm -23 "$T.undef" "$T.def" | grep -vE "$NOISE" | grep -viE "$CRT" | sed 's/^/  /' > "$T.missing"
if [ -s "$T.missing" ]; then
    cat "$T.missing"
    echo
    echo "  -> declared but never defined. Check:"
    echo "     - is the .cpp listed in SRC?"
    echo "     - do the .h and .cpp signatures match EXACTLY (int vs unsigned counts)?"
else
    echo "  (none)"
fi

# --- 2. duplicated -----------------------------------------------------------
# Inline functions and template instantiations are legitimately emitted into
# every object that uses them; the linker merges them. On PE/COFF those live in
# COMDAT sections named ".text$<mangled>", while a real strong definition sits
# in plain ".text". So: collect the COMDAT names per object and subtract them.
: > "$T.pairs"
for f in "$OBJDIR"/*.o; do
    obj=$(basename "$f")
    nm "$f" 2>/dev/null | sed -n 's/.*\.text\$//p' | sort -u > "$T.comdat"
    nm "$f" 2>/dev/null | sed -n 's/^[0-9a-f]* [TDB] //p' | sort -u > "$T.strong"
    comm -23 "$T.strong" "$T.comdat" | sed "s|\$|	$obj|" >> "$T.pairs"
done

echo
echo "=== 2. Defined in more than one object  (multiple definition) ==="
sort "$T.pairs" | awk -F'\t' '
    { if ($1 == prev) { list = list " " $2; n++ }
      else { if (n > 1) print prev "\t" list; prev = $1; list = $2; n = 1 } }
    END { if (n > 1) print prev "\t" list }
' > "$T.dup"
if [ -s "$T.dup" ]; then
    while IFS="	" read -r sym objs; do
        printf '  %s\n      in: %s\n' "$(echo "$sym" | c++filt)" "$objs"
    done < "$T.dup"
    echo
    echo "  -> defined more than once. Check:"
    echo "     - a free function DEFINED in a header needs 'inline'"
    echo "     - or it is defined in two .cpp files"
else
    echo "  (none)"
fi

rm -f "$T".*
