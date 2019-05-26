#include <sys/wait.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <stdio.h> 
int main(void) 
{ 
pid_t pids[10]; 
int i; 
for (i = 9;  i >= 0;  --i)  { 
pids[i] = fork() ; 
if (pids[i] == 0)  { 
                        printf("Child PID is %ld\n", (long)  getpid() ) ; 
sleep((i+1) *30) ; 
_exit(0) ; 
} 
} 
for (i = 9;  i >= 0;  --i) { 
                printf("Parent PID is %ld\n", (long)  getpid() ) ; 
                waitpid(pids[i], NULL, 0) ; 
        } 
return 0; 
} 