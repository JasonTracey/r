#pragma once

#include <string>


class Location;

class Species {
    public:
        std::string name;
};

class Unit {
    public:
        // Constructors
        Unit(std::string name, Location* location, Species* species);

        // Destructor
        ~Unit() = default;

        // Methods
        Species* species() const {return species_;};
        Location* location() const {return location_;};
        std::string name() const {return name_;};

        void go_to(Location* l);

        // Variables
    private:
        // Methods

        // Variables
        std::string name_;
        Species* species_;
        Location* location_ = nullptr;

};