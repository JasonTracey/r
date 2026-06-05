#pragma once

#include <string>

class Species;
class Location;

class Unit {
    public:
        // Constructors
        Unit(std::string name, Species* species, Location* location);

        // Destructor
        ~Unit() = default;

        // Methods
        Species* species() const {return species_;}
        Location* location() const {return location_;}
        std::string name() const {return name_;}

        void go_to(Location* l);

        // Variables
    private:
        // Methods

        // Variables
        std::string name_;
        Species* species_;
        Location* location_ = nullptr;

};