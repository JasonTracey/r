#pragma once

#include <unordered_set>
#include <string>

class Unit;
class Location {    
    public:
        std::string name;

        void enter(Unit* unit);
        void exit(Unit* unit);
        void print_name();
    private:
        std::unordered_set<Unit*> units;
};

