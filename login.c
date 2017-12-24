#include "types.h"
#include "user.h"
#include "stat.h"
#include "fcntl.h"
#define MAXLEN 30
char *argv[] = { "sh",  0};

struct account
{
	char name[MAXLEN];
	char uid[MAXLEN];
	char homePath[MAXLEN];
	char groupIdList[MAXLEN];
	
};

struct account nowAccount;


char* getGroupIdList()
{
	return nowAccount.groupIdList;
}

char* getHomePath()
{
	return nowAccount.homePath;
}

char* getUid()
{
	return nowAccount.uid;
}

char* getName()
{
	return nowAccount.name;
}

int checkpasswd(int fd, char *user, char *passwd){
  int i, n, c, l, t;
  char ipasswd[MAXLEN];
  char iuser[MAXLEN];
  char iuid[MAXLEN];
  char ihomePath[MAXLEN];
  char igroupIdList[MAXLEN];
  char buf[1024];
  l = c = 0;
  //chop the \n
  if(user[strlen(user)-1]  == '\n'){
  	user[strlen(user)-1]  = 0;	
  }
  if(passwd[strlen(passwd)-1]  == '\n'){
  	passwd[strlen(passwd)-1]  = 0;	
  }

  while((n = read(fd, buf, sizeof(buf))) > 0){
    for(i=0; i<n;) {
      if(l == 0){	
      	while(i < n && buf[i] != ':' )iuser[c++] = buf[i++];
      	if(i == n) break; 
      	iuser[c] = '\0';
      	i++;
      }
      while(i <n && buf[i] != ':')ipasswd[l++] = buf[i++];
      if(i == n) break;
      ipasswd[l] = '\0';
	  i++;
	  
	  l = 0;
	  while(i <n && buf[i] != ':')iuid[l++] = buf[i++];
      if(i == n) break;
      iuid[l] = '\0';
	  i++;
	  
	  l = 0;
	  while(i <n && buf[i] != ':')ihomePath[l++] = buf[i++];
      if(i == n) break;
      ihomePath[l] = '\0';
	  i++;
	  
	  l = 0;
	  while(i <n && buf[i] != ':')igroupIdList[l++] = buf[i++];
      if(i == n) break;
      igroupIdList[l] = '\0';
	  
      c = 0;
      l = 0;
     //printf(1,"%s::%s\n", user,iuser);
     //printf(1,"%s::%s\n", passwd,ipasswd);
      if(!strcmp(user,iuser) && !strcmp(passwd,ipasswd)){
      	char * dirToCreate = "/home/";
      	strcpy(dirToCreate + strlen(dirToCreate), user);
      	//printf(1,"%s\n", dirToCreate);
      	mkdir(dirToCreate);
		
		t = 0;
		while(user[t] != '\0')
		{
			nowAccount.name[t] = user[t];
			t = t + 1;
		}
		nowAccount.name[t] = '\0';
		
		t = 0;
		while(iuid[t] != '\0')
		{
			nowAccount.uid[t] = iuid[t];
			t = t + 1;
		}
		nowAccount.uid[t] = '\0';
      		
		t = 0;
		while(ihomePath[t] != '\0')
		{
			nowAccount.homePath[t] = ihomePath[t];
			t = t + 1;
		}
		nowAccount.homePath[t] = '\0';
			
		t = 0;
		while(igroupIdList[t] != '\0')
		{
			nowAccount.groupIdList[t] = igroupIdList[t];
			t = t + 1;
		}
		nowAccount.groupIdList[t] = '\0';
				
      	return 1;
      }
      while(i <n && buf[i++] != '\n');

    }
  }
  return 0; 
}

int main(void){
	//int pid, wpid, fd;
	int pid, fd;
	int loggedIn = 1;
	mkdir("/home/");
	while(loggedIn){
		printf(1,"Username: ");
		char * username = gets("username", MAXLEN);
		printf(1,"Password: ");
		char * password = gets("password", MAXLEN);
		//printf(1,"%s, %s\n",username, password);
		dup(0);  // stdout
		dup(0);  // stderr
		//printf(1, "init: starting sh\n");
		if((fd = open("/shadow", O_RDONLY)) < 0){
		printf(1, "login: cannot open %s\n", argv[1]);
			exit();
		}
		if(checkpasswd(fd,username,password)){
			loggedIn = 0;
			printf(1,"Welcome back %s\n", username);
			pid = fork();
			if(pid < 0){
			  printf(1, "login: fork failed\n");
			  exit();
			}
			if(pid == 0){
				char * uname[] = {username};
			  exec("sh", uname);
			  printf(1, "login: exec sh failed\n");
			  exit();
			}
		}
		else{
			printf(1,"wrong username or password\n");
		}
		close(fd);
		/*while((wpid=wait()) >= 0 && wpid != pid)
		  printf(1, "zombie!\n"); 
			*/
	}
	
	wait();
	exit();
	//Unreachable line but I like to place it there
	return 0;
}











