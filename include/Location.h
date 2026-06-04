#pragma once

#include <unordered_set>
#include <string>

class Unit;
class Location {    
    public:
        // Constructors
        Location(std::string name);

        // Destructor
        ~Location() = default;

        // Methods
        void enter(Unit* unit);
        void exit(Unit* unit);
        
        std::string name() {return name_;};
        std::unordered_set<Unit*> units() {return units_;};
    private:
        std::string name_;
        std::unordered_set<Unit*> units_;
};

