#ifndef _KERNEL_PROC_H
#define  _KERNEL_PROC_H

#include <stdint.h>

typedef uint32_t, pid_t;


struct message
{
  char *description;
  struct message* nextMessage;
  struct message* previousMessage;
};

typedef struct message message;

struct messageQueue
{
    message* first;
    message* last;
    uint32_t len;
};




struct process
{
  pid_t pid;
  char *stdin;
  char *stdout;
  char *stderr;
  messageQueue msgQueue;
};


typedef struct process process_t;

process_t initialize_process(pid_t pid, char *stdin, char *stdout, char *stderr);



#endif
