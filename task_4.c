/**
 * task_4.c — программа, в которой посимвольно с использованием фунции fgetc() читается указанный в командной строке файл, 
 * прочитанные символы выводятся в поток stdout, разделенные пробелами 
 * (например, для содержимого файла "Hello, world!" должно получиться "H e l l o , w o r l d ! "). 
 * Убедитесь, что, если файл содержит кириллицу в UTF-8, то результат получается некорректный.
 * 
 * Copyright (c) <2022> <Гордеев Никита>
 *
 * This code is licensed under a MIT-style license.
 */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv)
{  
    FILE *f1;
    char ch;
    
    /* Проверка открытия файла */
    if ((f1 = fopen(argv[1], "r")) == NULL) {
        printf("Первый файл недоступен\n");
	    exit(EXIT_FAILURE);
    }

    // Посимвольное чтение указанного в командной строке файла
    while ((ch = fgetc(f1)) != EOF) {
        // Вывод прочитанных символов разделенных пробелами в поток stdout
        if (ch != '\n')
            printf("%c ", ch);
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


/* Материалы:
 * 5.6. Чтение из потока и запись в поток // UNIX. Профессиональное программирование. 3-е URL: https://www.rulit.me/data/programs/resources/pdf/UNIX-Professionalnoe-programmirovanie_RuLit_Me_609965.pdf (дата обращения: 06.11.2022). 
 * Листинг 5.2. Копирование данных со стандартного ввода на стандартный вывод с помощью функций fgets и fputs // UNIX. Профессиональное программирование. 3-е изд URL: https://www.rulit.me/data/programs/resources/pdf/UNIX-Professionalnoe-programmirovanie_RuLit_Me_609965.pdf (дата обращения: 06.11.2022).
 */