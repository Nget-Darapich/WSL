#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid;

    // Create a child process
    pid = fork();

    if (pid < 0) {
        // Fork failed
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child process: PID = %d\n", getpid());

        // Execute 'ls' command using exec
        execlp("/bin/ls", "ls", "-l", (char *)NULL);

        // If exec returns, it means it failed
        perror("execlp failed");
        exit(1);
    } else {
        // Parent process
        printf("Parent process: PID = %d\n", getpid());
        printf("Child process ID = %d\n", pid);

        // Wait for child to complete
        wait(NULL);
        printf("Child process completed\n");
    }

    return 0;
}
