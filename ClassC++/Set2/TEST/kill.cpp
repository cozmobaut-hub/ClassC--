#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <cstdint>

int main() {
    void* ptr = mmap(reinterpret_cast<void*>(0x64f3eebb42b0), 4096,
                     PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_FIXED, -1, 0);
    if (ptr == MAP_FAILED) {
        std::cout << "Failed: address unavailable\n";
        return 1;
    }
    // Use *(int*)ptr = 42; then munmap(ptr, 4096);
    return 0;
}
