#include <string>

auto main(int argc, char* argv[]) -> int{
    auto to_pid std::stoi(argv[1]);
    auto use_signo = std::stoi(argv[2]);

    kill(to_pid, use_signo);

    return 0;
}