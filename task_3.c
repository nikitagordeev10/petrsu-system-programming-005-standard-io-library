/**
 * task_2.c — программа копирования файлов с использованием потоковых фунций fopen(), fread(), fwrite(), fclose().
 * Программа должна получать три аргумента командной строки, первый аргумент - файл, откуда копировать, второй аргумент - файл, куда копировать, третий аргумент - размер блока.
 * Измерить время работы программы при чтении блоками по 1 байт, 1 Кб, 1 Мб, st_blksize из результата stat().
 * 
 * Ход работы:
 * 1) Добавьте отключение буферизации в программу. 
 * 2) Сделайте выводы по результатам измерений в пп.2,3.
 * 
 * Copyright (c) <2022> <Гордеев Никита>
 *
 * This code is licensed under a MIT-style license.
 */


#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

#define B 1
#define K 1024
#define M 1024*1024

void file_copying (const char *argv1, const char *argv2, const int BUFSIZE);

int main(int argc, char **argv)
{
    if (argc != 3) {
        printf("Недостаточно аргументов\n");
        printf("Первый аргумент - файл, откуда копировать, второй аргумент - файл, куда копировать\n");
        exit(EXIT_FAILURE);
    }

    /* Проверяем, можно ли получить сведения о файле через lstat */
    struct stat buf;
    if (lstat(argv[1], &buf) < 0) {
        printf("Ошибка lstat!\n");
        exit(EXIT_FAILURE);
    }

    /* Запускаем копирование несколькими блоками с подсчётом времени для каждого */
    file_copying(argv[1], argv[2], B);
    file_copying(argv[1], argv[2], K);
    file_copying(argv[1], argv[2], M);
    file_copying(argv[1], argv[2], buf.st_blksize);
    
    /* Успешное завершение программы */
    return 0;
}

void file_copying (const char *argv1, const char *argv2, const int BUFSIZE)
{
    FILE *f1, *f2;    
    
    /* Первый аргумент - файл, откуда копировать */
    if ((f1 = fopen(argv1, "r")) == NULL) {
        printf("Первый файл недоступен\n");
        exit(EXIT_FAILURE);
    }

    /* Второй аргумент - файл, куда копировать */
    if ((f2 = fopen(argv2, "w")) == NULL) {
        printf("Второй файл недоступен\n");
        exit(EXIT_FAILURE);
    }

    /* Отключаем буферизацию */
    setbuf(f1, NULL);
    setbuf(f2, NULL);

    /* Чтение из первого файла и запись во второй файл */
    time_t time_start = time(NULL);
    int status;
    char buf[BUFSIZE];
    while ((status = fread(buf, sizeof(char), BUFSIZE, f1)) > 0) {
        if (fwrite(buf, sizeof(char), status, f2) != status) {
            printf("Ошибка записи во второй файл!\n");
            exit(EXIT_FAILURE);
        }
    }
    time_t time_end = time(NULL);

    /* Проверка закрытия первого файла */
    if (fclose(f1) == EOF) {
        printf("Ошибка закрытия первого файла!\n");
        exit(EXIT_FAILURE);
    }

    /* Проверка закрытия второго файла */
    if (fclose(f2) == EOF) {
        printf("Ошибка закрытия второго файла!\n");
        exit(EXIT_FAILURE);
    }

    printf("Время работы программы при размере буфера в %d байт: %ld секунд\n", BUFSIZE, time_end - time_start);
}

/* Материалы:
 * У. Ричард Стивенс, Стивен А. Раго Листинг 5.3. Вывод сведений о буферизации для различных потоков ввода/вывода // UNIX. Профессиональное программирование. - 2018. - С. 217-219.
 * У. Ричард Стивенс, Стивен А. Раго Листинг 8.17. Вывод учетной информации из системного файла учетных данных // UNIX. Профессиональное программирование. - 2018. - С. 334-335.
 * У. Ричард Стивенс, Стивен А. Раго Листинг 15.5. Функции popen и pclose // UNIX. Профессиональное программирование. - 2018. - С. 625-626.
 */

/* Вывод по результатам измерений:
 * Программа с отключенной буферизацией работает намного медленнее, это хорошо заметно при чтениями блоками, равными 1 байт.
 */

/* 
 * К сожалению, буферизация — это тот самый аспект стандартной библиотеки ввода/вывода, который более всего смущает программистов.
 * (c) 5.4. Буферизация // Электронная библиотека RuLit URL: https://www.rulit.me/data/programs/resources/pdf/UNIX-Professionalnoe-programmirovanie_RuLit_Me_609965.pdf (дата обращения: 06.11.2022).
 */
