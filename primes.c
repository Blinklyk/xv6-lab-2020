#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void
mapping(int n, int fd[]) {
  close(n);
  dup(fd[n]);
  close(fd[0]);
  close(fd[1]);
}

void
primes() {
  int first, next;
  int fd[2];
  if (read(0, &first, sizeof(int))){
    printf("prime %d\n", first);
    pipe(fd);
    if (fork() == 0) {
      mapping(1, fd);
      while (read(0, &next, sizeof(int))) {
        if (next % first != 0) {
	  write(1, &next, sizeof(int));
	}
      }
    } else {
      wait(0);
      mapping(0, fd);
      primes();
    }
  }
}

int
main(int argc, char *argv[])
{
  int fd[2];
  pipe(fd);
  if (fork() == 0) {
    mapping(1, fd);
    for (int i = 2; i <= 35; i++) {
      write(1, &i, sizeof(int));
    }
  } else {
    wait(0);  
    mapping(0, fd);
    primes();
  }
  exit(0);
}
