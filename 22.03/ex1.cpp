#include <unistd.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

auto main() -> int
{
    int* ap = reinterpret_cast<int*>(0xdeadbeef);
    std::cout<< *ap;
    return 0;
}
