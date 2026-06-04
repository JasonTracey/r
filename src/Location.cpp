#include "Location.h"
#include "Unit.h"
#include <iostream>

// Constructors
Location::Location(std::string name) : name_(name) {};

void Location::enter(Unit* unit) {units_.insert(unit);}
void Location::exit(Unit* unit) {units_.erase(unit);}