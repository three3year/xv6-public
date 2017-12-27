#include "types.h"
#include "user.h"
#include "fcntl.h"

int
main(int argc, char *argv[])
{
    int fd;
    if(argc < 3 || argc > 5){
    	printf(1,"Usage: Specify filename, Ex.: createfile filename\n");
    	exit();
    }

    fd = open(argv[1], O_CREATE);
    if(fd >= 0) {
        printf(1, "ok: create %s file succeed\n",argv[1]);
    } else {
        printf(1, "error: create %s file failed\n",argv[1]);
        exit();
    }
    
    close(fd);

    exit();
}

