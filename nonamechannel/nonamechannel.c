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

    // установка программных каналов p и q
    pipe(p);
    pipe(q);

    /* p[R], q[R] - концы каналов для чтения */
    /* p[W], q[W] - концы каналов для записи */

    switch(pid = fork())
    {

    case -1: // сбой при вызове fork()
        printf("Error when fork() was been called\n");
        exit(1);

    case 0: // потомок
        /*
         * читает из p[R]
         * пишет в q[W]
         * p[W] и q[R]  - закрыты
         * станд. ввод и p[R] - синонимы
         * станд. вывод и q[W] - синонимы
         */

        // канал p
        close(p[W]);
        close(R);
        dup(p[R]);
        close(p[R]);

        // канал q
        close(q[R]);
        close(W);
        dup(q[W]);
        close(q[W]);

        /* Теперь станд. вывод и  q[W] - синонимы  */
        /* Запуск внешней независимой программы filter_1 */

        // запуск фильтра
        execl("./filter_1", "filter_1", 0);
        exit(1);

    default: // предок
        /*
         * Конец канала P преобразуется для
         * записи в поток
         */
        close(p[R]);
        close(q[W]);

        // fp - связывает поток с файловым дескриптором
        fp = fdopen(p[W], "w");

        // ch - текущий символ
        ch = getchar();
        while(ch != '\n' && ch != '\0' && ch != EOF)
        {
            // putc - записывает символ в поток вывода fp
            putc(ch, fp);
            ch = getchar();
        }
        putc('\n', fp);

        // fclose - очищает канал (fp) и закрывает файловый дескриптор
        fclose(fp);

        /*
         * Теперь подключаем ввод результата
         * из канала Q
         */
        fq = fdopen(q[R], "r");

        // читает из входного потока fq
        fgets(str, 511, fq);
        printf("%s", str);
        fclose(fq);
        exit(0);
    }

    return 0;
}
