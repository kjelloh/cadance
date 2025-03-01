#include "cadance.h"
#include <vector>
#include <string>

int main() {
    cadance();

    std::vector<std::string> vec;
    vec.push_back("test_package");

    cadance_print_vector(vec);
}
