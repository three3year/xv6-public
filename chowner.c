#include "types.h"
#include "stat.h"
#include "user.h"
int
main(int argc, char *argv[])
{
    if(argc < 5) {
	printf(1,"Usage: Specify filename and ownerid, Ex.: chowner filename ownerid\n");
       exit();
}
    int fd;
    char * path = argv[1];
    struct stat st;
    if((fd = open(path, 0)) < 0) {
        printf(2, "chowner: cannot open %s\n", path);
        exit();
    }
    if(fstat(fd, &st) < 0) {
        printf(2, "chowner: cannot stat %s\n", path);
        close(fd);
        exit();
    }
    close(fd);
    if(strcmp(argv[2],"root") == 0)
	chown(path, 99);
    else if(strcmp(argv[2],"test1") == 0)
	chown(path, 87);
    else if(strcmp(argv[2],"test2") == 0)
	chown(path, 33);
    else
	printf(2, "chowner: don't have this account %s\n", argv[2]);
    exit();
}
