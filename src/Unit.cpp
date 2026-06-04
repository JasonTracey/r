#include "Unit.h"
#include "Location.h"

Species::Species(std::string name) : name_(name) {};

// Constructors
Unit::Unit(std::string name, Species* species, Location* location) 
        : name_(name), species_(species) {
    go_to(location);
};

// 
void Unit::go_to(Location* location) {
    if (location_) location_->exit(this);
    location_ = location;
    location_->enter(this);
};