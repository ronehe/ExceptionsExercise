#pragma once
#include <exception>
#include <functional>

template<typename T>
class Validator {
public:
	T operator()(std::function<void()>);
};

template <typename T>
T Validator<T>::operator()(std::function<void()> func) {
    T ans;
    auto ansIsStupid = true;
    while (ansIsStupid) {
        try {
            func();
        }
        catch (std::exception& e) {
            m_istr.clear();
            continue;
        }
        return ans;
    }
}