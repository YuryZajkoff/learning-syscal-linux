/* 
    Сигналы SIGUSR1 и SIGUSR2. Использование сигналов для синхронизации процессов 
*/
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int i = 0, cnt = 0; /* Счетчик числа обработок сигнала */

 
void my_handler(int nsig)
{
    i++;
    cnt++;
}

int main(void)
{
    pid_t pid;

    signal(SIGUSR1, my_handler);

    if ( ( pid = fork() ) < 0)
    {
        printf("Ошибка системного вызова fork()\n");
        exit(-1);
    }
    else if (pid == 0)
    {
        while (1)
        {
            if (i)
            {
                i--;
                printf("Потомок занял 'ресурс'\n");
                /* Какая-то работа процесса */
                printf("Потомок освободил 'ресурс'\n\n");
                kill(getppid(), SIGUSR1);
                if (cnt >= 2) exit(1);
            }
        }
    }
    else
    {
        i++;
        while (1)
        {
            if (i)
            {
                i--;
                printf("Родитель занял 'ресурс'\n");
                /* Какая-то работа процесса */
                printf("Родитель освободил 'ресурс'\n\n");
                kill(pid, SIGUSR1);
                if (cnt >= 2) exit(1);
            }
        }
    }
    return 0;
}