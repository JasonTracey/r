#include "Location.h"
#include "Unit.h"
#include <iostream>

void Location::enter(Unit* unit) {units.insert(unit);}
void Location::exit(Unit* unit) {units.erase(unit);}
void Location::print_name() {std::cout << name;}