/*
 * ������ �������� ����������. ���141
 * ������ 1
 * ����������� ������, ��������� ������ ����� �� ������.
 */

#include <stdio.h>

#define MAXLEN 512

int main(int argc, char *argv[])
{
    char str[MAXLEN], ch;
    int i = 0;

    // getchar() - ��������� ������ �� ������������ ������
    ch = getchar();
    while(ch != '\n' && ch != EOF && i < MAXLEN)
    {
        if (ch <= '0' || ch >= '9')
            str[i++] = ch;�
        ch = getchar();
    }
    str[i] = '\0';

    // ����� ������ �� �����
    printf("%s\n", str);

    return 0;
}
