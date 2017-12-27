#include "types.h"
#include "stat.h"
#include "user.h"
int
main(int argc, char *argv[])
{
    if(argc < 6){ 
	printf(1,"Usage: Specify change and range and filename, Ex.: chmod change range filename\n");	
	exit();
}
    int fd;
    struct stat st;
    char * path = argv[3];
    if((fd = open(path, 0)) < 0) {
        printf(2, "chmod: cannot open %s\n", path);
        exit();
    }
    if(fstat(fd, &st) < 0) {
        printf(2, "chmod: cannot stat %s\n", path);
        close(fd);
        exit();
    }

    int mode = st.mode;
    close(fd);

    if((stoi(argv[4]) != st.ownerid)&&(99 != stoi(argv[4]))){
        printf(2, "chmod: cannot change permissions %s\n", path);
        exit();
    }

    if(strcmp(argv[2], "u") == 0 ){
      if(strcmp(argv[1], "-x") == 0 && (0x100&mode)) {
          chmod(path, 0x100 ^ mode);
      } else if(strcmp(argv[1], "+x") == 0 && !(0x100&mode)) {
          chmod(path, 0x100 ^ mode);
      }
      if(strcmp(argv[1], "-w") == 0 && (0x200&mode)) {
          chmod(path, 0x200 ^ mode);
      } else if(strcmp(argv[1], "+w") == 0 && !(0x200&mode)) {
          chmod(path, 0x200 ^ mode);
      }
      if(strcmp(argv[1], "-r") == 0 && (0x400&mode)) {
          chmod(path, 0x400 ^ mode);
      } else if(strcmp(argv[1], "+r") == 0 && !(0x400&mode)) {
          chmod(path, 0x400 ^ mode);
      }

    }
    else if(strcmp(argv[2], "g") == 0 ){
      if(strcmp(argv[1], "-x") == 0 && (0x10&mode)) {
          chmod(path, 0x10 ^ mode);
      } else if(strcmp(argv[1], "+x") == 0 && !(0x10&mode)) {
          chmod(path, 0x10 ^ mode);
      }
      if(strcmp(argv[1], "-w") == 0 && (0x20&mode)) {
          chmod(path, 0x20 ^ mode);
      } else if(strcmp(argv[1], "+w") == 0 && !(0x20&mode)) {
          chmod(path, 0x20 ^ mode);
      }
      if(strcmp(argv[1], "-r") == 0 && (0x40&st.mode)) {
          chmod(path, 0x40 ^ st.mode);
      } else if(strcmp(argv[1], "+r") == 0 && !(0x40&mode)) {
          chmod(path, 0x40 ^ mode);
      }

    }
    else if(strcmp(argv[2], "o") == 0 ){
      if(strcmp(argv[1], "-x") == 0 && (0x1&mode)) {
          chmod(path, 0x1 ^ mode);
      } else if(strcmp(argv[1], "+x") == 0 && !(0x1&mode)) {
          chmod(path, 0x1 ^ mode);
      }
      if(strcmp(argv[1], "-w") == 0 && (0x2&mode)) {
          chmod(path, 0x2 ^ mode);
      } else if(strcmp(argv[1], "+w") == 0 && !(0x2&mode)) {
          chmod(path, 0x2 ^ mode);
      }
      if(strcmp(argv[1], "-r") == 0 && (0x4&st.mode)) {
          chmod(path, 0x4 ^ st.mode);
      } else if(strcmp(argv[1], "+r") == 0 && !(0x4&st.mode)) {
          chmod(path, 0x4 ^ mode);
      }

    }
    /*else if(strcmp(argv[2], "a") == 0)
    {
	uint reg = 0x00000000;
	if(strcmp(argv[1], "+x") == 0) {
	  if(!(0x1&mode)){
            reg += 1;
	  }
	  if(!(0x10&mode)){
            reg += 10;
	  }
	  if(!(0x100&mode)){
            reg += 100;
	  }
      	}
	else if(strcmp(argv[1], "-x") == 0) {
	  if((0x1&mode)){
            reg += 1;
	  }
	  if((0x10&mode)){
            reg += 10;
	  }
	  if((0x100&mode)){
            reg += 100;
	  }
      	}
	if(strcmp(argv[1], "+w") == 0) {
	  if(!(0x2&mode)){
            reg += 2;
	  }
	  if(!(0x20&mode)){
            reg += 20;
	  }
	  if(!(0x200&mode)){
            reg += 200;
	  }
      	}
	else  if(strcmp(argv[1], "-w") == 0) {
	  if((0x2&mode)){
            reg += 2;
	  }
	  if((0x20&mode)){
            reg += 20;
	  }
	  if((0x200&mode)){
            reg += 200;
	  }
      	}
	if(strcmp(argv[1], "+r") == 0) {
	  if(!(0x4&mode)){
            reg += 4;
	  }
	  if(!(0x40&mode)){
            reg += 40;
	  }
	  if(!(0x400&mode)){
            reg += 400;
	  }
      	} 
	else if(strcmp(argv[1], "-r") == 0) {
	  if((0x4&mode)){
            reg += 4;
	  }
	  if((0x40&mode)){
            reg += 40;
	  }
	  if((0x400&mode)){
            reg += 400;
	  }
      	} 
	printf(2,"%d",reg);
	chmod(path,xint(reg)^mode);
    }*/
    else
    {
	printf(2, "chmod: wrong range %s\n", path);
        exit();
    }
    exit();
}
