/* Прогон программы с использованием fork() */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main()
{
   /*
      fork порождает еще один процесс с тем же кодом, что и у родителя, 
      относительно того, где был вызвов fork, те все что ниже этого вызова.
      Если это родитель, то форк возвращает pid ребенка, если же это сын, то 
      fork возвращает 0 
   */
   pid_t pid_f = fork();
   if (pid_f < 0)
   {
      printf("Error call function fork();\n");
      return -1;
   }

   printf("\n\nBegin work\n");
   
   // Одинаковое поведение "родителя" и "сына"
   for (int i = 0; i < 10; i++)
   {
      printf("%d ", i);
   }
   printf("\n");

   // Разное поведение "родителя" и "сына"
   if (pid_f < 0)
   {
      printf("Error call function fork();\n");
      exit(-1);
   }
   else if (pid_f == 0) 
   {
      printf("child (pid=%d)\n", getpid());
   } 
   else 
   {
      printf("parent (pid=%d, child's pid=%d)\n", getpid(), pid_f);
   }
   
   fprintf(stderr, "Press <Enter> to exit...");
   getchar();

   return 0;
}