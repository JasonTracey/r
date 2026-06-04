
#include <unordered_set>
#include <string>
#include <iostream>
#include "Location.h"
#include "Unit.h"

// class Name {
//     private:
//         std::string name;
//     public:
//         void display() {std::cout << name;}
//         void update(std::string n) {name = n;}
// }

int main () {
    //
    Location home("Home");
    Location forest("Forest");
    Species human("Human");
    Unit suse("Susannah", &human, &home);
    
    std::cout << suse.name() << " is at " << suse.location()->name() << '\n';
    
    suse.go_to(&forest);
    std::cout << suse.name() << " goes to " << forest.name() << '\n';
    std::cout << suse.name() << " is at " << suse.location()->name() << '\n';
    
}