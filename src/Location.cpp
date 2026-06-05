#include "Location.h"
#include "Unit.h"
#include "Resource.h"
#include <iostream>

// Constructors
Location::Location(std::string name) : name_(name) {};

// Methods
void Location::enter(Unit* unit) {units_.insert(unit);}
void Location::exit(Unit* unit) {units_.erase(unit);}
int Location::resource_count(Resource* resource) const {
    auto it = resources_.find(resource);
    return it != resources_.end() ? it->second : 0;
}
void Location::add_resource(Resource* resource, int quantity) {
    resources_[resource] += quantity;
}

void Location::print_stocks() const {
    std::cout<<name_<<" stocks: \n";
    for (const auto& [r, q] : resources_)
        std::cout<<"    "<<r->name()<<'['<<q<<"]\n";
}