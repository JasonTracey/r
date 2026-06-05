#pragma once

#include <unordered_set>
#include <unordered_map>
#include <string>

class Unit;
class Resource;
class Location {    
    public:
        // Constructors
        Location(std::string name);

        // Destructor
        ~Location() = default;

        // Methods
        void enter(Unit* unit);
        void exit(Unit* unit);
        
        std::string name() const {return name_;}
        const std::unordered_set<Unit*>& units() const {return units_;}
        const std::unordered_map<Resource*, int>& resources() const {
            return resources_;
        }
        int resource_count(Resource* resource) const;
        
        void add_resource(Resource* resource, int quantity);
        void print_stocks() const;
    private:
        std::string name_;
        std::unordered_set<Unit*> units_;
        std::unordered_map<Resource*, int> resources_;
};

