
#pragma once
#include <string>

enum ErrorType {
    SUCCESS = 0,
    ERR_INVALID_ARG_COUNT,
    ERR_DIVISION_BY_ZERO,
    ERR_UNDEFINED_VARIABLE,
    ERR_EMPTY_TREE,
    ERR_UNKNOWN_CMD
};

class Error {
private:
    bool has_error;
    ErrorType type;
    std::string msg;

public:
    Error(); 
    Error(ErrorType t); 
    Error(ErrorType t, const std::string& message);

    bool getHasError() const;
    ErrorType getType() const;
    std::string getMessage() const;
    static std::string defaultMessage(ErrorType t);
};

