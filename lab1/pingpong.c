#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int pipe1_fd[2];
  int pipe2_fd[2];
  char buf[8];
  pipe(pipe1_fd);
  pipe(pipe2_fd);
  if (fork() == 0) {
    close(pipe1_fd[1]);
    read(pipe1_fd[0], buf, 4);
    close(pipe1_fd[0]);
    printf("%d: received %s\n", getpid(), buf);
    close(pipe2_fd[0]);
    write(pipe2_fd[1], "pong", strlen("pong"));
    close(pipe2_fd[1]);
    exit(0);
  } else {
    close(pipe1_fd[0]);
    write(pipe1_fd[1], "ping", strlen("ping"));
    close(pipe1_fd[1]);
    wait(0);
    close(pipe2_fd[1]);
    read(pipe2_fd[0], buf, 4);
    close(pipe2_fd[0]);
    printf("%d: received %s\n", getpid(), buf);
    exit(0);
  }
}
