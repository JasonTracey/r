
#include <unordered_set>
#include <string>
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
    Location home = new Location(name='Home')
    Location forest = new Location(name='Forest')
    Species human = new Species(name='Human')
    Unit jason = new Unit()
    jason->go_to(forest)
}