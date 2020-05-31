#pragma once
#include <vector>
namespace Senseless{
//
//
//
template <class T>
std::vector<T> join_vectors(const std::vector<T> &_v1, const std::vector<T> &_v2) {
    std::vector<T> v3;
    v3.reserve(_v1.size() + _v2.size());
    v3.insert(v3.end(), _v1.begin(), _v1.end());
    v3.insert(v3.end(), _v2.begin(), _v2.end());
    return v3;
}
}
