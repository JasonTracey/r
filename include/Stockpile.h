#pragma once
#include <unordered_map>

// Pre
class Resource;

// Class
class Stockpile {
    public:
        using Contents = std::unordered_map<Resource*, unsigned int>;

        Stockpile(unsigned int capacity = 200, Contents contents = {});
        ~Stockpile() = default;

        // Getter methods

        unsigned int capacity() const {
            return capacity_;
        }
        const Contents& contents() const {
            return contents_;
        }

        // Helper methods

        unsigned int used_space() const;
        unsigned int available_space() const;
        unsigned int resource_count(Resource* resource) const;
        
        // Adds resource to stockpile, returns overflow else 0
        unsigned int add(Resource* resource, unsigned int amount);
        // Removes resource from a stockpile, returns successfully removed
        unsigned int remove(Resource* resource, unsigned int amount);
        // consider whitelist blacklist for resources
    private:
        Contents contents_;
        unsigned int capacity_;
};
