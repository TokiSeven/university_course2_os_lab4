#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // it needs for: fork, pipe, read, write, close, etc.

#define R 0 //it is stdin
#define W 1 //it is stdout

int main(void)
{
    int pid;
    int p[2], q[2];
    FILE *fp, *fq;
    char *str;
    int ch;

    // ��������� ����������� ������� p � q
    pipe(p);
    pipe(q);

    /* p[R], q[R] - ����� ������� ��� ������ */
    /* p[W], q[W] - ����� ������� ��� ������ */

    switch(pid = fork())
    {

    case -1: // ���� ��� ������ fork()
        printf("Error when fork() was been called\n");
        exit(1);

    case 0: // �������
        /*
         * ������ �� p[R]
         * ����� � q[W]
         * p[W] � q[R]  - �������
         * �����. ���� � p[R] - ��������
         * �����. ����� � q[W] - ��������
         */

        // ����� p
        close(p[W]);
        close(R);
        dup(p[R]);
        close(p[R]);

        // ����� q
        close(q[R]);
        close(W);
        dup(q[W]);
        close(q[W]);

        /* ������ �����. ����� �  q[W] - ��������  */
        /* ������ ������� ����������� ��������� filter_1 */

        // ������ �������
        execl("./filter_1", "filter_1", 0);
        exit(1);

    default: // ������
        /*
         * ����� ������ P ������������� ���
         * ������ � �����
         */
        close(p[R]);
        close(q[W]);

        // fp - ��������� ����� � �������� ������������
        fp = fdopen(p[W], "w");

        // ch - ������� ������
        ch = getchar();
        while(ch != '\n' && ch != '\0' && ch != EOF)
        {
            // putc - ���������� ������ � ����� ������ fp
            putc(ch, fp);
            ch = getchar();
        }
        putc('\n', fp);

        // fclose - ������� ����� (fp) � ��������� �������� ����������
        fclose(fp);

        /*
         * ������ ���������� ���� ����������
         * �� ������ Q
         */
        fq = fdopen(q[R], "r");

        // ������ �� �������� ������ fq
        fgets(str, 511, fq);
        printf("%s", str);
        fclose(fq);
        exit(0);
    }

    return 0;
}
