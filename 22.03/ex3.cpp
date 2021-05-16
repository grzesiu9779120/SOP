#include <unistd.h>
#include <string>
#include <vector>

auto execute(std::vector<std::string>  args) -> int
{
    auto argv = std::vector<char*>{};
    for (auto const& each : args) {
        argv.push_back(const_cast<char*>(each.c_str());
    }
    argv.push_back(nullptr);

    auto env = std::vector<char*>{};
    env.push_back(nullptr);

    execve(argv[0], argv.data(), env.data());
    perror("execve");
    exit(EXIT_FAILURE);
}

auto main(int argc, char* argv[]) -> int{
    auto args = std::vector<std::string>{};
    for (auto i-1; i<argc; ++i){
        args.push_back(argv[i]);
    }

    execute(args);
    return 0;
}