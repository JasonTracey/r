#pragma once

#include <string>
#include <unordered_map>

class Species;
class Location;
class Resource;

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

        void go_to(Location* location);
        void harvest(Resource* r);
        void deposit(Resource* r);

        // Variables
    private:
        // Methods

        // Variables
        std::string name_;
        Species* species_;
        Location* location_ = nullptr;
        std::unordered_map<Resource*, int> bag_;
        std::unordered_map<Resource*, int> bag_capacity_;
        int harvest_rate = 1;
        int deposit_rate = 5;

};