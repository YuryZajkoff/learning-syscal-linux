/*
    Прогон программы, игнорирующей сигнал SIGINT и SIGQUIT
*/
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main()
{
    pid_t pid;
    printf("My PID: %d\n", getpid());
     
    (void)signal(SIGINT, SIG_IGN);
    (void)signal(SIGQUIT, SIG_IGN);

    int i = 0;
    while(1)
    {
        i++;
    }
    return 0;
}