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
    char privfifo[15]; // ��� �������� ������������ ������
    char data[100]; // ����������, ������� ����� ��������
};

#define PUBLIC "public" // ��� �������������� ������������ ������������ ������
#define LINESIZE 512
//------

int main(int argc, char *argv[]) // �named pipe� client.c
{
    struct message msg;
    int n, fdpub, fdpriv;
    char line[LINESIZE];

    /*
     * ����������� ��� ������� ������������ ������ (privfifo) �
     * ������� ���� ����� � ������� ������ � ������ ��� ���� ���������
     *
     * ����� ������������ � msg.privfifo
     * getpid() - ���������� ������������� �������� ��������
     */
    sprintf(msg.privfifo, "Fifo%d", getpid());

    /*
     * �������� ������� FIFO-����� � ������ �� ������ � ������ ��� ���� ��������� (0666)
     * ��������� S_IFIFO �������� ���� ���� ������������ ������
     */
    if (mkfifo(msg.privfifo, S_IFIFO|0666) == -1)
    {
        // ������ ������ � ����� ������
        perror(msg.privfifo);
        exit(1);
    }


    /*
     * ������������� ����������� ����� (��������� ����� �������� ������� %mkfifo public)
     * ����������� �� ������, � � ���� ������������ ����� ������� ������ � ���������� �����
     *
     * �������������� ���� � ����� � �������� ����������
     * ���� ��������� ���� ������ ��� ������
     */
    if ((fdpub = open(PUBLIC, O_WRONLY)) == -1)
    {
        perror(PUBLIC);
        exit(2);
    }

    // ������ ������ � ����������
    char ch;
    int i = 0;

    // getchar() - ��������� ������ �� ������������ ������
    ch = getchar();
    while(ch != '\n' && ch != EOF && i < 100)
    {
        msg.data[i++] = ch;
        ch = getchar();
    }
    msg.data[i] = '\0';

    // ���������� � ���� � ������������ fdpub
    write(fdpub, (char*)&msg, sizeof(msg));

    // ������ ����������� ����� ����������� ��� ������
    if ((fdpriv = open (msg.privfifo, O_RDONLY)) == -1)// ����� ������, ���� ����
    {
        perror(msg.privfifo);
        exit(3);
    }

    // ������� ������, ���������� �� ������� ������
    while((n = read(fdpriv, line, strlen(line))) > 0)
        write(1, line, n);

    // ��������� ������ ����������� �����
    close(fdpriv);

    // ������� ��� �� �������� �������
    unlink(msg.privfifo);

    return 0;
}
