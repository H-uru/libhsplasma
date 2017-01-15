#include <cstdint>
#include <cstddef>

void overloaded(uint16_t) { }
void overloaded(uint32_t) { }
void overloaded(uint64_t) { }
void overloaded(size_t) { }

int main(int, char**) {
    size_t x = 5;
    overloaded(x);
    return 0;
}
