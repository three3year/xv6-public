#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];

void
wc(int fd, char *name)
{
  int i, n;
  int l, w, c, inword;

  l = w = c = 0;
  inword = 0;
  while((n = read(fd, buf, sizeof(buf))) > 0){
    for(i=0; i<n; i++){
      c++;
      if(buf[i] == '\n')
        l++;
      if(strchr(" \r\t\n\v", buf[i]))
        inword = 0;
      else if(!inword){
        w++;
        inword = 1;
      }
    }
  }
  if(n < 0){
    printf(1, "wc: read error\n");
    exit();
  }
  printf(1, "%d %d %d %s\n", l, w, c, name);
}

int
main(int argc, char *argv[])
{
  int fd, i;
struct stat st;

  if(argc <= 3){
    wc(0, "");
    exit();
  }

  for(i = 1; i < argc-2; i++){
    if((fd = open(argv[i], 0)) < 0){
      printf(1, "wc: cannot open %s\n", argv[i]);
      exit();
    }
    if(stat(argv[i],&st)<0)
    { 
	printf(1, "wc: cannot stat %s\n", argv[i]);
	exit();
    }
    if(chkSta(argv[argc-2],argv[argc-1],st.ownerid,st.groupid,st.mode,'r') < 0)
    { 
	printf(1, "wc: cannot read %s\n", argv[i]);
	exit();
    }
    wc(fd, argv[i]);
    close(fd);
  }
  exit();
}
