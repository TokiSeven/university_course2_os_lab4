/*
 * ������ �������� ����������. ���141
 * ������ 1
 * ����������� ������, ����������� � ������ ������ ������������� �� ������� ������ �����.
 */

#include <stdio.h>
#include <string.h>

#define MAXLEN 512

/*
 * ��� ������� ���������� 1, ���� ������ �������� ������, ��� 0
 * � - ������, ������� ���� ���������
 */
int isDigit(char c)
{
    return ((c >= '0' && c <= '9') ? 1 : 0);
}

/*
 * ��� ������� ���������� ���������� ����� � ������ 'str' (���������� int)
 * 'str' - ������ (���������), � ������� ���� ��������� ���������� �����
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
 * ��� ������� ������������ ������ 'str' � 'newStr' (��������� ��� ����� � ������)
 * 'str' - ������ (���������), ������� ����� �������������� (��������)
 * 'newStr' - ������ (���������), � ������� ����� ��������� ���������� ������
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

    // getchar() - ��������� ������ �� ������������ ������
    ch = getchar();
    while(ch != '\n' && ch != EOF && i < MAXLEN)
    {
        str[i++] = ch;
        ch = getchar();
    }
    str[i] = '\0';

    // ������� ����� ������, �������� �� ������
    char strNew[strlen(str) + 2 * countOfNumbers(str)];

    // ��������� � ������� ��� ���� ����� � ���������� � ������ strNew
    convertString(str, strNew);

    // ������� ����� ������
    printf("%s\n", strNew);

    return 0;
}
