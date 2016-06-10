/*
 * Рябцев Владимир Дмитриевич. БИВ141
 * Фильтр 1
 * Разработать фильтр, заключающий в скобки каждое встречающееся во входном тексте число.
 */

#include <stdio.h>
#include <string.h>

#define MAXLEN 512

/*
 * эта функция возвращает 1, если символ является числом, или 0
 * с - символ, который надо проверить
 */
int isDigit(char c)
{
    return ((c >= '0' && c <= '9') ? 1 : 0);
}

/*
 * эта функция возвращает количество чисел в строке 'str' (возвращает int)
 * 'str' - строка (указатель), в которой надо посчитать количество чисел
 */
int countOfNumbers(char *str)
{
    int len = strlen(str), count = 0, i = 0;
    while(i < len)
    {
        if (isDigit(str[i]))
        {
            count++;
            int j;
            for (j = i+1; j < len && isDigit(str[j]); j++);
            i = j;
        }
        else
            i++;
    }
    return count;
}

/*
 * эта функция конвертирует строку 'str' в 'newStr' (заключает все числа в скобки)
 * 'str' - строка (указатель), которую нужно конвертировать (исходная)
 * 'newStr' - строка (указатель), в которой будет сохранена измененная строка
 */
void convertString(char *str, char *newStr)
{
    int len = strlen(str);
    int i = 0, j = 0, wasBeen = 0;;

    for(i = 0; i < len; i++)
    {
        if(isDigit(str[i]))
        {
            if (!wasBeen)
            {
                newStr[j] = '(';
                j++;
                newStr[j] = str[i];
                j++;
                wasBeen = 1;
            }
            else
            {
                if (i + 1 < len && isDigit(str[i + 1]))
                {
                    newStr[j] = str[i];
                    j++;
                }
                else
                {
                    newStr[j] = str[i];
                    j++;
                    newStr[j] = ')';
                    j++;
                    wasBeen = 0;
                }
            }
        }
        else
        {
            if (wasBeen)
            {
                newStr[j] = ')';
                j++;
                wasBeen = 0;
            }
            newStr[j] = str[i];
            j++;
        }
    }
    if (isDigit(newStr[j-1]))
    {
        newStr[j] = ')';
        j++;
    }
    newStr[j] = '\0';
}

int main(int argc, char *argv[])
{
    char str[MAXLEN], ch;
    int i = 0;

    // getchar() - считывает символ из стандартного потока
    ch = getchar();
    while(ch != '\n' && ch != EOF && i < MAXLEN)
    {
        str[i++] = ch;
        ch = getchar();
    }
    str[i] = '\0';

    // создаем новую строку, учитывая ее размер
    char strNew[strlen(str) + 2 * countOfNumbers(str)];

    // заключаем в кавычки все наши числа и записываем в строку strNew
    convertString(str, strNew);

    // выводим новую строку
    printf("%s\n", strNew);

    return 0;
}
