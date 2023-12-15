#include <stdio.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    DIR *dir;
    struct dirent *entry;
    char* path;

    if (argc < 2) 
        path = ".";
    else
    	path = argv[1];

    // Открываем каталог
    dir = opendir(path);
    if (dir == NULL) {
        printf("Произошла ошибка при открытии директории: %s\n", path);
        return 1;
    }

    // Выводим содержимое каталога
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) // string comprasion. Одинаковы => 0
        	continue;
        printf("%s [%d]\n", entry->d_name, entry->d_reclen);
    }

    // Закрываем каталог
    if (closedir(dir) == -1)
    {
    	printf("Прoизошла ошибка при закрытии файла\n");
    }

    return 0;
}
