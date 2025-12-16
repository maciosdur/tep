#include <iostream>
#include <string>
#include <vector>
#include <cassert>

template<typename T, unsigned N>
struct Repeat {
    typedef T ValueType;  

    T operator()(const T& value) const {
        T result = T();  
        for(unsigned i = 0; i < N; ++i) {
            result = result + value;
        }
        return result;
    }
};

template <class Funct>
struct Mapper { 
    std::vector<typename Funct::ValueType>& operator()(std::vector<typename Funct::ValueType>& vec) const {
        Funct funct;

        for (auto& el : vec) {
            el = funct(el);  
        }

        return vec;
    } 
};


int main()
{
    Mapper< Repeat<int, 3> > map_int;
    Mapper< Repeat<std::string, 2> > map_str;
    std::vector<int> vec_int;
    for(int i = 1; i <= 5; ++i){ vec_int.push_back(i); };
    map_int(vec_int);
    for (auto& c : vec_int) std::cout << c << " ";
        std::cout << std::endl;
    // test dla int
    {
        static const int res[] = {3,6,9,12,15};
        std::vector<int> test(res, res + 5);
        assert(test == vec_int);
    }
        std::vector<std::string> vec_str;
        vec_str.push_back("foo"); vec_str.push_back("bar");
        map_str(vec_str);
        for (auto& s : vec_str) std::cout << s << " ";
        std::cout << std::endl;
    // test dla str
    {
        static const char* res[] = {"foofoo", "barbar"};
        std::vector<std::string> test(res, res + 2);
        assert(test == vec_str);
    }
    return 0;
}

//g++ test2.cpp -o Tester2
