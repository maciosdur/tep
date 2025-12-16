#pragma once
#include <string>

class CError {
public:
    CError(const std::string& sDescription)
        : s_description(sDescription) {}

    CError(const CError& other)
        : s_description(other.s_description) {}

    std::string sGetDescription() const {
        return s_description;
    }

private:
    std::string s_description;
};
