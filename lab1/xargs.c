#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

#define MAXN 1024

int
main(int argc, char *argv[]){
  if (argc < 2) {
    fprintf(2, "exec xargs failed!!");
    exit(1);
  }
  
  char *argvs[MAXARG];
  int index = 0;
  for (int i = 1; i < argc; i++) {
    argvs[index++] = argv[i];
  }
  int n;
  char buf[MAXN] = {"\0"};
  while ((n = read(0, buf, MAXN)) > 0) {
    char tmp[MAXN] = {"\0"};
    argvs[index] = tmp;
    for (int i = 0; i < strlen(buf); i++) {
      if (buf[i] == '\n') {
        if (fork() == 0) {
	  exec(argv[1], argvs);
	}
	wait(0);
      } else {
        tmp[i] = buf[i];
      }
    }
  }
  exit(0);
}
