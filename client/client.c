#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> // open() arguments
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//------
struct message
{
    char privfifo[15]; // им€ частного именованного канала
    char data[100]; // информаци€, котора€ будет передана
};

#define PUBLIC "public" // им€ общедоступного именованного программного канала
#define LINESIZE 512
//------

int main(int argc, char *argv[]) // Фnamed pipeФ client.c
{
    struct message msg;
    int n, fdpub, fdpriv;
    char line[LINESIZE];

    /*
     * синтезируем им€ личного программного канала (privfifo) и
     * создаем этот канал с правами чтени€ и записи дл€ всех процессов
     *
     * вывод записываетс€ в msg.privfifo
     * getpid() - возвращает идентификатор текущего процесса
     */
    sprintf(msg.privfifo, "Fifo%d", getpid());

    /*
     * создание особого FIFO-файла с правом на чтение и запись дл€ всех процессов (0666)
     * константа S_IFIFO означает файл типа именованного канала
     */
    if (mkfifo(msg.privfifo, S_IFIFO|0666) == -1)
    {
        // запись ошибки в поток ошибок
        perror(msg.privfifo);
        exit(1);
    }


    /*
     * общедоступный именованный канал (создаетс€ перед запуском сервера %mkfifo public)
     * открываетс€ на запись, и в него записываютс€ имена личного канала и требуемого файла
     *
     * преобразование пути к файлу в файловый дескриптор
     * флаг открывает файл только дл€ записи
     */
    if ((fdpub = open(PUBLIC, O_WRONLY)) == -1)
    {
        perror(PUBLIC);
        exit(2);
    }

    // читаем строку с клавиатуры
    char ch;
    int i = 0;

    // getchar() - считывает символ из стандартного потока
    ch = getchar();
    while(ch != '\n' && ch != EOF && i < 100)
    {
        msg.data[i++] = ch;
        ch = getchar();
    }
    msg.data[i] = '\0';

    // записывает в файл с дескриптором fdpub
    write(fdpub, (char*)&msg, sizeof(msg));

    // личный именованный канал открываетс€ дл€ чтени€
    if ((fdpriv = open (msg.privfifo, O_RDONLY)) == -1)// вывод ошибки, если есть
    {
        perror(msg.privfifo);
        exit(3);
    }

    // выводим данные, полученные из личного канала
    while((n = read(fdpriv, line, strlen(line))) > 0)
        write(1, line, n);

    // закрываем личный именованный канал
    close(fdpriv);

    // удал€ет им€ из файловой системы
    unlink(msg.privfifo);

    return 0;
}
