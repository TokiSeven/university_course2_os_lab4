/*
 * Рябцев Владимир Дмитриевич. БИВ141
 * Фильтр 1
 * Разработать фильтр, удаляющий каждую цифру из строки.
 */

#include <stdio.h>

#define MAXLEN 512

int main(int argc, char *argv[])
{
    char str[MAXLEN], ch;
    int i = 0;

    // getchar() - считывает символ из стандартного потока
    ch = getchar();
    while(ch != '\n' && ch != EOF && i < MAXLEN)
    {
        if (ch <= '0' || ch >= '9')
            str[i++] = ch;ё
        ch = getchar();
    }
    str[i] = '\0';

    // вывод строки на экран
    printf("%s\n", str);

    return 0;
}
