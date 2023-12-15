#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#define _POSIX_SOURCE
#include <stdio.h>
#undef _POSIX_SOURCE
#include <unistd.h>

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		printf("Необходимо указать имя файла\n");
		return 1;
	}

	char* first_file_pathname = argv[1];
	char* second_file_pathname = argv[2];
	
	if (checkPermission(first_file_pathname, second_file_pathname) == -1)
		return 1;
	
	FILE* file1 = fopen(first_file_pathname, "r");
	if (file1 == NULL)
	{
		printf("Ошибка открытия файла\n");
		return 1;
	}

	FILE* file2 = fopen(second_file_pathname, "w");
	if (file2 == NULL)
	{
		printf("Ошибка открытия файла\n");
		return 1;
	}

	copy(file1, file2);
	
	if (ferror(file1)) {
        perror("Fail to read src file");
        closeFile(file1, file2);
        return 1;
    }
	
	closeFile(file1, file2);

	return 0;
}

void copy(FILE* copy_from_file, FILE* copy_to_file) {
	int ch;
	while ((ch = getc(copy_from_file)) != EOF) {
		if(putc(ch, copy_to_file) == EOF) // On success, fputc() returns the value c that it wrote to stream. On failure, it returns EOF
		{
			printf("Произошла ошибка при записи");
			return;
		}
	}
}

int closeFile(FILE* file1, FILE* file2)
{
	int result1 = fclose(file1);
	int result2 = fclose(file2);
	if (result1 == EOF || result2 == EOF)
	{
		printf("При закрытии поток произошла ошибка");
		return -1;
	}
	return 0;
}

// Если ошибка, возвращает -1, иначе - 0.
int checkPermission(char* file1, char* file2)
{
	int first_file_can_be_read = access(file1, R_OK);
	int second_file_can_be_edited = access(file2, W_OK);

	if (first_file_can_be_read == -1) 
	{
		printf("Нет доступа на чтение первого файла\n");
		return -1;
	}

	if (second_file_can_be_edited == -1)
	{
		printf("Нет доступа на запись второго файла\n");
		return -1;
	}
	return 0;
}
