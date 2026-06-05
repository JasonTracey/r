#pragma

#include <string>

class Species {
    public:
        Species(std::string name);

        std::string name() const {return name_;}
    private:
        std::string name_;
};
