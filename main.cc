#include "cnpy_mmap.h"
int main() {
    auto arr = cnpy::npy_load("data.npy");
    auto vec = arr.data<int64_t>();
    std::cout << "vec: ";
    for (size_t i = 0; i < arr.num_vals; i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
}
