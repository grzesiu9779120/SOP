#include <string>

auto main(int argc, char* argv[]) -> int{
    auto to_pid std::stoi(argv[1]);
    auto use_signo = std::stoi(argv[2]);

    union sigval {
        int sival_int =2;
        void *sival_ptr;
    }

    sigqueue(to_pid, use_signo, sigval);

    return 0;
}