#include <stdarg.h>

#define _LOOSE_KERNEL_NAMES 1

#define NULL ((void *) 0)

#define	WIFSTOPPED(status)	(((status) & 0xff) == 0x7f)
#define	WIFSIGNALED(status)	(!WIFSTOPPED(status) && !WIFEXITED(status))
#define	WEXITSTATUS(status)	(((status) & 0xff00) >> 8)
#define	WTERMSIG(status)	((status) & 0x7f)
#define	WSTOPSIG(status)	WEXITSTATUS(status)
#define	WIFEXITED(status)	(WTERMSIG(status) == 0)

#define MS_MGC_VAL 0xc0ed0000
#define MS_RDONLY	 1	/* Mount read-only */

#define isspace(a) (a == ' ' || a == '\t')

extern char ** _environ;

extern int errno;

/* Aieee, gcc 2.95+ creates a stub for posix_types.h on i386 which brings
   glibc headers in and thus makes __FD_SET etc. not defined with 2.3+ kernels. */
#define _FEATURES_H 1
#include <linux/socket.h>
#include <linux/types.h>
#include <linux/time.h>
#include <linux/if.h>
#include <linux/un.h>
#include <linux/loop.h>
#include <linux/net.h>
#include <asm/posix_types.h>
#include <asm/termios.h>
#include <asm/ioctls.h>
#include <asm/unistd.h>
#include <asm/fcntl.h>
#include <asm/signal.h>

#ifndef MINILIBC_INTERNAL

#define X_OK	1
#define W_OK	2
#define R_OK	4

#define S_IFBLK 0x6000

static inline _syscall5(int,mount,const char *,spec,const char *,dir,const char *,type,unsigned long,rwflag,const void *,data);
static inline _syscall5(int,_newselect,int,n,fd_set *,rd,fd_set *,wr,fd_set *,ex,struct timeval *,timeval);
static inline _syscall4(int,wait4,pid_t,pid,int *,status,int,opts,void *,rusage)
static inline _syscall3(int,write,int,fd,const char *,buf,unsigned long,count)
static inline _syscall3(int,mknod,const char *,path,int,mode,int,dev)
static inline _syscall3(int,reboot,int,magic,int,magic_too,int,flag)
static inline _syscall3(int,execve,const char *,fn,void *,argv,void *,envp)
static inline _syscall3(int,read,int,fd,const char *,buf,unsigned long,count)
static inline _syscall3(int,open,const char *,fn,int,flags,mode_t,mode)
static inline _syscall2(int,access,const char *,fn,int,flags)
static inline _syscall3(int,ioctl,int,fd,int,request,void *,argp)
static inline _syscall2(int,dup2,int,one,int,two)
static inline _syscall2(int,pivot_root,const char *,one,const char *,two)
static inline _syscall2(int,kill,pid_t,pid,int,sig)
static inline _syscall2(int,symlink,const char *,a,const char *,b)
static inline _syscall2(int,chmod,const char * ,path,mode_t,mode)
static inline _syscall2(int,sethostname,const char *,name,int,len)
static inline _syscall2(int,setdomainname,const char *,name,int,len)
static inline _syscall2(int,setpgid,int,name,int,len)
static inline _syscall2(int,signal,int,num,void *,len)
static inline _syscall1(int,umount,const char *,dir)
static inline _syscall1(int,unlink,const char *,fn)
static inline _syscall1(int,close,int,fd)
static inline _syscall1(int,swapoff,const char *,fn)
static inline _syscall0(int,getpid)
static inline _syscall0(int,getppid)
static inline _syscall0(int,sync)
#ifdef __sparc__
/* Nonstandard fork calling convention :( */
static inline int fork(void) {
  int __res;
  __asm__ __volatile__ (
    "mov %0, %%g1\n\t"
    "t 0x10\n\t"
    "bcc 1f\n\t"
    "dec %%o1\n\t"
    "sethi %%hi(%2), %%g1\n\t"
    "st %%o0, [%%g1 + %%lo(%2)]\n\t"
    "b 2f\n\t"
    "mov -1, %0\n\t"
    "1:\n\t"
    "and %%o0, %%o1, %0\n\t"
    "2:\n\t"
    : "=r" (__res)
    : "0" (__NR_fork), "i" (&errno)
    : "g1", "o0", "cc");
  return __res;
}
#else
static inline _syscall0(int,fork)
#endif
static inline _syscall0(pid_t,setsid)
static inline _syscall3(int,syslog,int, type, char *, buf, int, len);
#else
static inline _syscall5(int,_newselect,int,n,fd_set *,rd,fd_set *,wr,fd_set *,ex,struct timeval *,timeval);
static inline _syscall3(int,write,int,fd,const char *,buf,unsigned long,count)
static inline _syscall2(int,socketcall,int,code,unsigned long *, args)
#define __NR__do_exit __NR_exit
extern inline _syscall1(int,_do_exit,int,exitcode)
#endif

#define select _newselect

extern int errno;

inline int socket(int a, int b, int c);
inline int bind(int a, void * b, int c);
inline int listen(int a, int b);
inline int accept(int a, void * addr, void * addr2);
int strlen(const char * string);
char * strcpy(char * dst, const char * src);
void * memcpy(void * dst, const void * src, size_t count);
void * memset(void * dst, int ch, size_t count);
void sleep(int secs);
int strcmp(const char * a, const char * b);
int strncmp(const char * a, const char * b, int len);
void printint(int i);
void printf(char * fmt, ...);
char * strchr(const char * str, int ch);
char * strncpy(char * dst, const char * src, int len);
void exit(int rc);
int atoi(const char * str);
