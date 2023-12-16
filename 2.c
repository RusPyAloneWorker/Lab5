#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) 
{
    if (argc < 2) 
    {
        printf("Необходимо указать имя файла\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "w");
    if (file == NULL) 
    {
        printf("Ошибка открытия файла\n");
        return 1;
    }
    
    int ch;
    while ((ch = getc(stdin)) != EOF) 
    {
        // Завершаем программу, если нажата комбинация клавиш Ctrl-F
        if (ch == 6 || ch == 3) {
            break;
        }

 		if(fputc(ch, file) == EOF) {
 			perror("Fail to write in file\n");
 			exit(EXIT_FAILURE);
 		}
    	}

	if(fclose(file) == EOF) {
 		perror("Fail to close file \n");
 		exit(EXIT_FAILURE);
	}

    return 1;
}
