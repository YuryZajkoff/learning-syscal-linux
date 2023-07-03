/*
    Восстановление предыдущей реакции на сигнал
*/
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int i = 0; /* Счетчик числа обработок сигнала */
void (*p)(int); /* Указатель, в который будет занесен адрес предыдущего обработчика сигнала */ 
 
void my_handler(int nsig)
{
    printf("\nReceive signal %d, CTRL-C pressed\n", nsig); 
    i = i+1;
    /* После 3-й обработки возвращаем первоначальную реакцию на сигнал */
    if(i == 3) (void)signal(SIGINT, p);
}
int main(void)
{
    pid_t pid;
    printf("My PID: %d\n", getpid());
    /* Выставляем свою реакцию процесса на сигнал SIGINT, запоминая адрес предыдущего обработчика */
    /* функция/системный вызов signal возвращает указатель на старый способ обработки сигнала*/ 
    p = signal(SIGINT, my_handler);

    int j = 0;
    while(1)
    {
        j++;
    }
    return 0;
}


