
#include "Error.h"
Error::Error() {
    has_error = false;
    type = SUCCESS;
    msg = "";
}

Error::Error(ErrorType t, const std::string& message) {
    has_error = true;
    type = t;
    msg = message;
}

Error::Error(ErrorType t) {
    has_error = (t != SUCCESS);
    type = t;
    msg = defaultMessage(t);
}

bool Error::getHasError() const { return has_error; }
ErrorType Error::getType() const { return type; }
std::string Error::getMessage() const { return msg; }

std::string Error::defaultMessage(ErrorType t) {
    switch (t) {
    case ERR_INVALID_ARG_COUNT:
        return "Blad: Niepoprawna liczba argumentow.";
    case ERR_DIVISION_BY_ZERO:
        return "Blad: Dzielenie przez zero.";
    case ERR_UNDEFINED_VARIABLE:
        return "Blad: Uzyto niepoprawnej wartości zmiennej.";
    case ERR_EMPTY_TREE:
        return "Blad: Drzewo jest puste.";
    case ERR_UNKNOWN_CMD:
        return "Blad:Nieznana komenda";
    default:
        return "";
    }
}

