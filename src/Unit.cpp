#include "Unit.h"
#include "Location.h"
#include "Species.h"


// Constructors
Unit::Unit(std::string name, Species* species, Location* location) 
        : name_(name), species_(species) {
    go_to(location);
}

// Methods 
void Unit::go_to(Location* location) {
    if (location_) location_->exit(this);
    location_ = location;
    location_->enter(this);
}
void Unit::harvest(Resource* r) {
    
}
void Unit::deposit(Resource* r) {

}

move

a_supp = 3
b_supp = 199
amnt = 6
a.remove(amnt)
//a supp -> 0, ret 3
b.add(amnt-a.remove)
//b supp -> 1, ret 2
a.add(berries, b.add(berries, amnt-a.remove(berriesm amnt)))