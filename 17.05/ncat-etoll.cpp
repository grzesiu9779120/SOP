#include <arpa/inet.h>
#include <endian.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>
#include <set>
#include <string>
#include <sys/epoll.h>
#include <vector>


auto main(int argc, char* argv[]) -> int
{
    auto addres = argv[1];
    auto port   = static_cast<uint16_t>(std::stoi(argv[2]));
    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port   = htobe16(port);
    inet_pton(addr.sin_family, addres, &addr.sin_addr);
    auto sock = socket(AF_INET, SOCK_STREAM, 0);

    if (bind(sock, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == -1) {
        perror("test");
        shutdown(sock, SHUT_RDWR);
        close(sock);
        return 1;
    }
    listen(sock, 0);

    auto clients = std::set<int>{};
    auto epi = epoll_create1(0);

    {
        epoll_event ev;
        ev.events = EPOLLIN;
        ev.data.fd = sock;
        epoll_ctl(epi, EPOLL_CTL_ADD, sock, &ev);
    }

    while (true) {
        auto events = std::vector<epoll_event>(clients.size()+1);
        auto const nfds = epoll_wait(epi, events.data(), events.size(), 10);
        for (auto i = 0; i <nfds; ++i){
            if (events[i].data.fd ==sock){
                auto client = accept(sock, nullptr, nullptr);
                clients.insert(client);
                epoll_event ev;
                ev.events = EPOLLIN;
                ev.data.fd = client;
                epoll_ctl(epi, EPOLL_CTL_ADD, client, &ev);
            }
            else{
                auto client = events[i].data.fd;
                std::cout << client << std::endl;
                char buffer[1024];
                memset(&buffer, 0, sizeof(buffer));
                auto s = read(client, buffer, sizeof(buffer));
                if (s <= 1) {
                    shutdown(client, SHUT_RDWR);
                    close(client);
                    clients.erase(clients.find(client));
                    continue;
                }
                std::cout << buffer << "\n";  
                }
        }
    }



    shutdown(sock, SHUT_RDWR);
    return 0;
}