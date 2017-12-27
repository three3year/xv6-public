#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];

void
cat(int fd)
{
  int n;

  while((n = read(fd, buf, sizeof(buf))) > 0)
    write(1, buf, n);
  if(n < 0){
    printf(1, "cat: read error\n");
    exit();
  }
}

int
main(int argc, char *argv[])
{
  int fd, i;
  struct stat st;
  if(argc <4){
    cat(0);
    exit();
  }

  for(i = 1; i < argc-2; i++){
    if((fd = open(argv[i], 0)) < 0){
      printf(1, "cat: cannot open %s\n", argv[i]);
      exit();
    }
    if(fstat(fd, &st) < 0) {
        printf(2, "cat: cannot stat %s\n", argv[i]);
        close(fd);
        exit();
    }
    if(chkSta(argv[argc-2],argv[argc-1],st.ownerid,st.groupid,st.mode,'r') < 0) {
	write(1, "cat: cannot read\n", 17);
    }
    else {
	cat(fd);
    }
    close(fd);
  }
  exit();
}
