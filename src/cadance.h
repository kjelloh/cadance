#pragma once

#include <vector>
#include <string>


#ifdef _WIN32
  #define CADANCE_EXPORT __declspec(dllexport)
#else
  #define CADANCE_EXPORT
#endif

CADANCE_EXPORT void cadance();
CADANCE_EXPORT void cadance_print_vector(const std::vector<std::string> &strings);
