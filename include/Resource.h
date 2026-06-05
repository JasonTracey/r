#pragma once
#include <string>

class Resource {
    public:
        // Constructor
        Resource(std::string name);
        // Destructor
        ~Resource() = default;
        
        // Method
        std::string name() const {return name_;};
    private:
        std::string name_;
};
