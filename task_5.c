/**
 * task_5.c — программа, в которой посимвольно с использованием фунции fgetc() читается указанный в командной строке файл, 
 * прочитанные символы выводятся в поток stdout, разделенные пробелами 
 * (например, для содержимого файла "Hello, world!" должно получиться "H e l l o , w o r l d ! "). 
 * Используйте функцию fgetwc(). 
 * Убедитесь, что программа корректно работает, если файл содержит символы в UTF-8.
 * 
 * Copyright (c) <2022> <Гордеев Никита>
 *
 * This code is licensed under a MIT-style license.
 */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <errno.h>


int main(int argc, char **argv)
{  
    FILE *f1;
    wint_t ch;
    
    /* Устанавливаем локаль */
    setlocale(LC_ALL, "en_US.utf8");

    /* Проверка на наличие аргументов */
    if (argc < 2) {
        fprintf(stderr, "Введите имя файла\n");
        exit(EXIT_FAILURE);
    }

    /* Проверка открытия файла */
    if ((f1 = fopen(argv[1], "r")) == NULL) {
        printf("Первый файл недоступен\n");
	    exit(EXIT_FAILURE);
    }

    // Посимвольное чтение указанного в командной строке файла
    while ((ch = fgetwc(f1)) != WEOF) {
        // Вывод прочитанных символов разделенных пробелами в поток stdout
        if (ch != '\n')
            printf("%lc ", ch);
        else
            printf("\n");
    }
    printf("\n");

    /* Проверка закрытия файла */    
    if (fclose(f1) == EOF) {
        printf("Ошибка закрытия!\n");
	    exit(EXIT_FAILURE);    
    }
    return 0;
}


/* 
 * Материалы:
 * cppreference.com // fgetwc, getwc URL: https://en.cppreference.com/w/c/io/fgetwc (дата обращения: 07.11.2022).
 * Чтение кириллицы из консоли // Cyberforum URL: https://www.cyberforum.ru/c-beginners/thread669614.html (дата обращения: 06.11.2022).
 * Reading UTF-8 from stdin using fgets() on Windows // stackoverflow URL: https://stackoverflow.com/questions/38160929/reading-utf-8-from-stdin-using-fgets-on-windows (дата обращения: 06.11.2022).
 * Работа с файлами в си ввод и вывод в файл в си // itrobo.ru URL: http://itrobo.ru/programmirovanie/osnovy-si/rabota-s-failami-v-si-vvod-i-vyvod-v-fai.html (дата обращения: 06.11.2022).
 * wchar_t vs wint_t // stackoverflow URL: https://stackoverflow.com/questions/1081456/wchar-t-vs-wint-t (дата обращения: 06.11.2022).
 */