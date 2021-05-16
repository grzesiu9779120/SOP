#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <array>
#include <string>


auto cat_to_stdout(std::string const path) -> void
{
    auto const in_fd = open(path.c_str(), 0_RDONLY);
    if(in_fd == -1){
        return;
    }

    std::array<char,4000> buf{0};
    while(true){
        auto const bytes_in = read(int_fd, buf.data(), buf.size());
        if( bytes_in == -1){
            break; //error
        }
        if (bytes_in == 0){
            break; end of file
        }

        write(1,buf.data(), bytes_in);
        //dokończyć

        close(in_fd);
    }

}

auto main(int argc, char* argv[]) ->int
{

for(auto i = int(1); i<argc; ++i){
   cat_to_stdout(argv[i]);
    }

    return 0;
}