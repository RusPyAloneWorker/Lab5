#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc < 3) 
    {
    	printf("Нет нужных аргументов!!\n");
    	return 1;
    }
    
    FILE *file = fopen(argv[2], "a");
    if (file == NULL) 
    {
        printf("Ошибка открытия файла\n");
        return 1;
    }
	
	get_data(argv[1], file);
	
	if (fclose(file) == -1)
    {
    	printf("Прoизошла ошибка при закрытии файла\n");
    }

    return 0;
}


void get_data(char* dir_path, FILE *file)
{
	char* biggest_file;
	int files_count = 0;
	long biggest_size = 0;
	long dir_size = 0;
	char path[250];
	char new_dir[250];
    struct dirent *entry;
    
    if (realpath(dir_path, path) == NULL)  // Абсолютный путь 
    {
        printf("Ошибка при получении абсолютного пути.\n");
        return 1;
    }
	
	DIR* dir = opendir(dir_path);
	if (dir == NULL) {
        printf("Произошла ошибка при открытии директории: %s\n", dir_path);
        return 1;
    }

	// Выводим содержимое каталога
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        	continue;
        	
		sprintf(new_dir,"%s/%s", path, entry->d_name);
		printf("%s \n", new_dir);  // Абсолютный путь до этого файла
       	
       	struct stat fileStat;
        // Получаем инфу о файле/директории	
        if (stat(new_dir, &fileStat) == -1) {
            printf("Не получилось получить данные: %s\n", new_dir);
            continue;
        }
        
        if (S_ISDIR(fileStat.st_mode)) // Если это вложенная директория
        { 
        	printf("DIR");
    		get_data(new_dir, file); // Рекурсия
    		dir_size += fileStat.st_size;
        } 
        else // Файл
        {
        	if (fileStat.st_size > biggest_size)
        	{
        		biggest_file = entry->d_name;
        		biggest_size = fileStat.st_size;
        	}
        	dir_size += fileStat.st_size;
        	files_count++;
        }
    }
    
	fprintf(file, 
		"Directory %s. Total Size: %lld bytes; Files count: %d; Biggest file: %s [%d bytes] \n", 
		path, dir_size, files_count, biggest_file, biggest_size);
    
    // Закрываем каталог
    if (closedir(dir) == -1)
    {
    	printf("Прoизошла ошибка при закрытии директории\n");
    }
}
