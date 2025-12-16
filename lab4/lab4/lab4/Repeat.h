#pragma once
#include <vector>
#include <string>

template <typename T, int N>
class Repeat {
public:
    typedef T ValueType;

    T operator()(const T& value) const {
        T result = value;
        for (int i = 1; i < N; ++i) {
            result = result + value;
        }
        return result;
    }
};