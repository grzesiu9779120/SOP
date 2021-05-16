#include <iostream>

auto main(int argc, char* argv[]) -> int{
    for(auto i = int(1); i<argc; ++i){
    std::cout << argv[i];
    }
    std::cout << "\n";
    
    return 0;
}