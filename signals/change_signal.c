/* 
    Программа с пользовательской обработкой сигнала SIGINT 
*/
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

/* Функция my_handler */ 
void my_handler(int nsig)
{ 
    printf("\nReceive signal %d, CTRL-C pressed\n", nsig);
}

int main()
{
    pid_t pid;
    printf("My PID: %d\n", getpid());

    (void)signal(SIGINT, my_handler);
    
    int i =0;
    while(1)
    {
        i++;
    }
    return 0;
}