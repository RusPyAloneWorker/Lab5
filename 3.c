#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	//--------- Проверка Валидности -----------//
	if (argc < 3)
	{
		printf("Необходимо указать имя файла\n");
		return 1;
	}

	int N = atoi(argv[2]);
	FILE* file = fopen(argv[1], "r");
	if (file == NULL)
	{
		printf("Ошибка открытия файла\n");
		return 1;
	}

	printLines(file, N);

	return 0;
}

void printLines(FILE* file, int N)
{
	int _count = 0;
	int ch;
	while (1)
	{
		ch = getc(file);
		if (ch == '\n') // Говорят, что \n может не сработать
		{
			_count++;
			//rintf("It's symbol: %d", ch); // ch == '\n' || ch == 13 || 124
		}
		
		if (_count == N) 
		{
			char user_input = getc(stdin);
			if (user_input != NULL)
				_count = 0;
			else
				break;
		}

		if (ch == EOF) {
			break;
		}

		putc(ch, stdout);
	}
}
