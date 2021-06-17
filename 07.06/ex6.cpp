#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

pid_t cpid;

void handler(int i){
    kill(cpid, i);
}

auto main(int argc, char *argv[]) -> int {
    cpid = fork();
    if (cpid == -1){
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (cpid== 0) {
        execvp(argv[1], argv+1);
        perror("execve");
        exit(EXIT_FAILURE);
    }

    struct sigaction act{};
    act.sa_handler = handler;

    sigaction(SIGTERM, &act, nullptr);

    signal(SIGINT, SIG_IGN);
    int status = 0;
    waitpid(cpid, &status, 0);

    if (WIFEXITED(status)) {
        std::cout << "Child PID is " << cpid << "proccess, status: " << WEXITSTATUS(status) << "\n";
    }

    if (WIFSIGNALED(status)) {
        std::cout << "Procces: " << cpid << " killed by signal: " << WTERMSIG(status) << "\n" << strsignal(WTERMSIG(status)) << "\n";
    }

    return 0;
}