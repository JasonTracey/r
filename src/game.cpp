#include <iostream>
#include "Location.h"
#include "Unit.h"
#include "Resource.h"
#include "Species.h"

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
    Resource berry("Berry");
    forest.add_resource(&berry, 200);

    std::cout << suse.name() << " is at " << suse.location()->name() << '\n';
    
    suse.go_to(&forest);
    std::cout << suse.name() << " goes to " << forest.name() << '\n';
    std::cout << suse.name() << " is at " << suse.location()->name() << '\n';
    suse.location()->print_stocks();
    std::cout << berry.name() << " at " << forest.name() << " grow! \n";
    forest.add_resource(&berry, 10);
    suse.location()->print_stocks();
    
    
}