/* Написание, компиляция и запуск программы с распечаткой значений переменных среды и аргументов командной строки */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

extern char** environ;	/* Environment itself */

int main(int argc, char** argv[])
{
   
   for (int i = 0; environ[i] != NULL; i++)
	{
		printf("'%s'\n", environ[i]);
	}
   printf("\n\n");

   if (argc <= 1)
   {
      fprintf (stderr, "environ: Too few arguments\n");
      exit (1);
   }

   for (int i = 0; i < argc; i++)
   {
      printf("%d: '%s'\n", i, argv[i]);
   }
   

   fprintf(stderr, "Press <Enter> to exit...");
   getchar();

   return 0;
}