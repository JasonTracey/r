#include <numeric>
#include "Stockpile.h"


Stockpile::Stockpile(unsigned int capacity, Contents contents) : 
    capacity_(capacity), contents_(contents) {}

unsigned int Stockpile::used_space() const {
    return std::accumulate(
        contents_.begin(),
        contents_.end(),
        0u,
        [](unsigned int sum, const auto& pair){return sum + pair.second;}
    );
}
unsigned int Stockpile::available_space() const {
    return capacity_ - used_space();
}
unsigned int Stockpile::resource_count(Resource* resource) const {
    auto it = contents_.find(resource);
    return it != contents_.end() ? it->second : 0u;
}
unsigned int Stockpile::add(Resource* resource, unsigned int amount) {
    unsigned int delta = std::min(available_space(), amount);
    contents_[resource] += delta;
    return amount-delta;
}
unsigned int Stockpile::remove(Resource* resource, unsigned int amount) {
    unsigned int supply = resource_count(resource);
    unsigned int delta = std::min(supply, amount);
    if (delta == supply) {
        contents_.erase(resource);
    } else {
        contents_[resource] -= delta;
    }
    return amount-delta;
}