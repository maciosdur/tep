#pragma once
#include <vector>

template <typename T, typename E>
class CResult {
public:
    CResult(const T& cValue) {
        pc_value = new T(cValue);
    }
    CResult(E* pcError) {
        pc_value = NULL;
        v_errors.push_back(pcError);
    }
    CResult(std::vector<E*>& vErrors) {
        pc_value = NULL;
        for (size_t i = 0; i < vErrors.size(); i++)
            v_errors.push_back(vErrors[i]);
    }

    CResult(const CResult<T, E>& cOther) {
        if (cOther.pc_value != NULL)
            pc_value = new T(*(cOther.pc_value));
        else
            pc_value = NULL;

        for (size_t i = 0; i < cOther.v_errors.size(); i++)
            v_errors.push_back(cOther.v_errors[i]);
    }

    ~CResult() {
        if (pc_value != NULL) delete pc_value;

        for (size_t i = 0; i < v_errors.size(); i++)
            delete v_errors[i];
    }

    static CResult<T, E> cOk(const T& cValue) {
        return CResult<T, E>(cValue);
    }

    static CResult<T, E> cFail(E* pcError) {
        return CResult<T, E>(pcError);
    }

    static CResult<T, E> cFail(std::vector<E*>& vErrors) {
        return CResult<T, E>(vErrors);
    }

    CResult<T, E>& operator=(const CResult<T, E>& cOther) {
        if (this == &cOther) return *this;

        if (pc_value != NULL) delete pc_value;
        for (size_t i = 0; i < v_errors.size(); i++)
            delete v_errors[i];

        v_errors.clear();

        if (cOther.pc_value != NULL)
            pc_value = new T(*(cOther.pc_value));
        else
            pc_value = NULL;

        for (size_t i = 0; i < cOther.v_errors.size(); i++)
            v_errors.push_back(cOther.v_errors[i]);

        return *this;
    }

    bool bIsSuccess() const {
    return v_errors.empty();
    }

    T cGetValue() const {
        return *pc_value;
    }

    std::vector<E*>& vGetErrors() const {
        return const_cast<std::vector<E*>&>(v_errors);
    }

private:
    T* pc_value;
    std::vector<E*> v_errors;
};



//3

template <typename E>
class CResult<void, E> {
public:
    CResult() {}
    CResult(E* pcError) { v_errors.push_back(pcError); }
    CResult(std::vector<E*>& vErrors) { v_errors = vErrors; }
    CResult(const CResult<void, E>& cOther) { v_errors = cOther.v_errors; }
    ~CResult() { for (auto e : v_errors) delete e; }

    static CResult<void, E> cOk() { return CResult<void, E>(); }
    static CResult<void, E> cFail(E* pcError) { return CResult<void, E>(pcError); }
    static CResult<void, E> cFail(std::vector<E*>& vErrors) { return CResult<void, E>(vErrors); }

    CResult<void, E>& operator=(const CResult<void, E>& cOther) {
        if (this != &cOther) {
            for (auto e : v_errors) delete e;
            v_errors = cOther.v_errors;
        }
        return *this;
    }

    bool bIsSuccess() const { return v_errors.empty(); }

    std::vector<E*>& vGetErrors() { return v_errors; }
    const std::vector<E*>& vGetErrors() const { return v_errors; }

private:
    std::vector<E*> v_errors;
};

