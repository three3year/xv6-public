#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"
#include "x86.h"

char*
strcpy(char *s, char *t)
{
  char *os;

  os = s;
  while((*s++ = *t++) != 0)
    ;
  return os;
}

int
strcmp(const char *p, const char *q)
{
  while(*p && *p == *q)
    p++, q++;
  return (uchar)*p - (uchar)*q;
}

uint
strlen(char *s)
{
  int n;

  for(n = 0; s[n]; n++)
    ;
  return n;
}

void*
memset(void *dst, int c, uint n)
{
  stosb(dst, c, n);
  return dst;
}

char*
strchr(const char *s, char c)
{
  for(; *s; s++)
    if(*s == c)
      return (char*)s;
  return 0;
}

char*
gets(char *buf, int max)
{
  int i, cc;
  char c;

  for(i=0; i+1 < max; ){
    cc = read(0, &c, 1);
    if(cc < 1)
      break;
    buf[i++] = c;
    if(c == '\n' || c == '\r')
      break;
  }
  buf[i] = '\0';
  return buf;
}

int
stat(char *n, struct stat *st)
{
  int fd;
  int r;

  fd = open(n, O_RDONLY);
  if(fd < 0)
    return -1;
  r = fstat(fd, st);
  close(fd);
  return r;
}

int
atoi(const char *s)
{
  int n;

  n = 0;
  while('0' <= *s && *s <= '9')
    n = n*10 + *s++ - '0';
  return n;
}

void*
memmove(void *vdst, void *vsrc, int n)
{
  char *dst, *src;
  
  dst = vdst;
  src = vsrc;
  while(n-- > 0)
    *dst++ = *src++;
  return vdst;
}
int getuser()
{
	return 87;
}
int getgroup()
{
	return 1;
}
int chkSta(char* userO,char* userG,int owner,int group,int mode,char st)
{
  int nowUser = stoi(userO);
  int nowGroup = stoi(userG);
  if(st == 'r')
  {
    if(owner == nowUser){
	if(mode&0x400){
	    return 0;
	}
    }
    else if(group == nowGroup){
	if(mode&0x40){
	    return 0;
    	}
    }
    else{
	if(mode&0x4){
	    return 0;
	}
    }
  }
  if(st == 'w')
  {
    if(owner == nowUser){
	if(mode&0x200){
	    return 0;
	}
    }
    else if(group == nowGroup){
	if(mode&0x20){
	    return 0;
    	}
    }
    else{
	if(mode&0x2){
	    return 0;
	}
    }
  }
return -1;
}

short stoi(char* input)
{
	short out = 0;
	int i;
	for(i = 0;input[i];i++)
	;
	for(int j = i-1;j>=0;j--)
		out += ctoi(input[j]) * mutiple(i-j-1);
	return out;
}
short ctoi(char input)
{
	return input-48;
}
short mutiple(int input)
{
	short out = 1;
	while(input>0)
	{
		out *= 10;
		input--;	
	}
	return out;

}
uint xint(uint x)
{
  int y;
  uchar *a = (uchar*)&y;
  a[0] = x;
  a[1] = x >> 8;
  a[2] = x >> 16;
  a[3] = x >> 24;
  return y;
}
