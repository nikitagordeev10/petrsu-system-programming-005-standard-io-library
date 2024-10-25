/**
 * task_6.c — программа для определения количества символов в строке UTF-8. 
 * Строка передается как аргумент командной строки.
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

int strlen_utf8(char *s);

int main(int argc, char **argv)
{  
    /* Устанавливаем локаль */
    setlocale(LC_ALL, "en_US.utf8");

    /* Проверка на наличие аргументов */
    if (argc != 2) {
        fprintf(stderr, "Введите строку\n");
        exit(EXIT_FAILURE);
    }

    /* определение количества символов в строке UTF-8 */
    printf("Количество симолов в строке: %d\n", strlen_utf8(argv[1]));
    return 0;
}

int strlen_utf8(char *s) 
{
  int i = 0; // позиция в строке
  int j = 0; // количество символов

  while (s[i]) 
  {
    if ((s[i] & 0xc0) != 0x80) { // битовая маска
        j++; // количество символов
    }
    i++; // позиция в строке
  }
  return j; // количество символов
}

/* 
 * Материалы:
 * 5.13. Временные файлы // UNIX. Профессиональное программирование. 3-е изд URL: https://www.rulit.me/data/programs/resources/pdf/UNIX-Professionalnoe-programmirovanie_RuLit_Me_609965.pdf (дата обращения: 07.11.2022).
 * Getting the actual length of a UTF-8 encoded std::string? // stackoverflow URL: https://stackoverflow.com/questions/4063146/getting-the-actual-length-of-a-utf-8-encoded-stdstring (дата обращения: 07.11.2022).
 * UTF-8 & Unicode, what's with 0xC0 and 0x80? // stackoverflow URL: https://stackoverflow.com/questions/3911536/utf-8-unicode-whats-with-0xc0-and-0x80 (дата обращения: 07.11.2022).
 */