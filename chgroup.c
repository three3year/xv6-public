#include "types.h"
#include "stat.h"
#include "user.h"
int
main(int argc, char *argv[])
{
    if(argc < 5) { 
	 printf(1,"Usage: Specify filename and groupid, Ex.: chgroup filename groupid\n");
      exit();
}
    int fd;
    char * path = argv[1];
    struct stat st;
    if((fd = open(path, 0)) < 0) {
        printf(2, "chgroup: cannot open %s\n", path);
        exit();
    }
    if(fstat(fd, &st) < 0) {
        printf(2, "chgroup: cannot stat %s\n", path);
        close(fd);
        exit();
    }
    close(fd);
    if(strcmp(argv[2],"0") == 0)
	chgup(path,0);
    else if(strcmp(argv[2],"1") == 0)
	chgup(path,1);
    else if(strcmp(argv[2],"2") == 0)
	chgup(path,2);
    else
	printf(2, "chgroup: don't have this group %s\n", argv[2]);
    exit();
}
