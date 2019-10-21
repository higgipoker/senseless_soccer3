#pragma once
#include <memory>
//
//
//
template <typename T>
using UnqPtr = std::unique_ptr<T>;
//
//
//
template <typename T>
using SharedPtr = std::shared_ptr<T>;
