#include <stdio.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    if (argc < 2) 
    {
    	printf("Нет пути к директории");
    	return 1;
    }

    // Открываем каталоги
    DIR * dir = opendir(argv[1]);
    if (dir == NULL) {
        printf("Произошла ошибка при открытии директории: %s\n", argv[1]);
        return 1;
    }
    
    DIR * dir1 = opendir(".");
    if (dir1 == NULL) {
        printf("Произошла ошибка при открытии директории: %s\n", ".");
        return 1;
    }

    print(dir);
    printf("------\n");
    print(dir1);

    // Закрываем каталог
    if (closedir(dir) == -1)
    {
    	printf("Прoизошла ошибка при закрытии директории\n");
    }
    
    if (closedir(dir1) == -1)
    {
    	printf("Прoизошла ошибка при закрытии директории\n");
    }

    return 0;
}

void print(DIR *dir)
{
    struct dirent *entry;
    // Выводим содержимое каталога
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) // string comprasion. Одинаковы => 0
        	continue;
        printf("%s [%d]\n", entry->d_name, entry->d_reclen);
    }
}
