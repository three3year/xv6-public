#include "types.h"
#include "user.h"
#include "stat.h"
#include "fcntl.h"


int
main(int argc, char *argv[])
{
    int fd;
    struct stat st;
    if(argc<5){
	printf(1,"Usage: Specify filename and input, Ex.: writeD filename input...\n");
	exit();
}

    fd = open(argv[1], O_RDWR);
    if(fd < 0) {
        printf(1, "writeD: cannot open %s\n", argv[1]);
	exit();
    }

    if(fstat(fd, &st) < 0) {
        printf(1, "writeD: cannot stat %s\n", argv[1]);
        close(fd);
        exit();
    } 

    if(chkSta(argv[argc-2],argv[argc-1],st.ownerid,st.groupid,st.mode,'w') < 0) {
	printf(1, "writeD: cannot write %s\n", argv[1]);
	close(fd);
        exit();
    }
    
    for(int i = 2;i<argc-2;i++){
    	if(write(fd, argv[i], sizeof(argv[i])) != sizeof(argv[i])){
            printf(1, "error: write to backup file failed\n");
            exit();
    	}
    }

    printf(1, "write ok\n");
    close(fd);

    exit();
}


