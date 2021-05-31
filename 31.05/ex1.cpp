#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <signal.h>
auto main(int argc, char* argv[]) -> int
{
    auto cpid = fork();
    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (cpid == 0) {
        execvp(argv[1], argv + 1);
        perror("execve");
        exit(EXIT_FAILURE);
    }

    signal(SIGINT,STG_IGN);
    int status = 0;
    waitpid(cpid, &status, 0);

    if (WIFEXITED(status)) {
        printf("Child PID is %d, status=%d\n", cpid, WEXITSTATUS(status));
    }

    if(WIFSIGNALED(status)){
        std::cout<<"Process: "<<cpid<<" killed by signal" << WEXITSTATUS(status) << "\n";
    }

    if(WIFSIGNALED(status)){
        std::cout<<"Process: " <<cpid << " killed by signal" << WTERMSIG(status) << "\n"
        << strsignal(WTERMSIG(status)) << "\n";
    }
    return 0;
}