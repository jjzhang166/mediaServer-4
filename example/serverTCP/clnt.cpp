#include <sys/socket.h>
#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
void WriteError(std::string msg)
{
    std::cout << msg << std::endl;
    exit(-1);
}
const int CONST_PORT = 8111;
const int MSG_LEN = 1 << 10;
void readline(char *buff)
{
    char ch;
    char *s = buff;
    while ((ch = getchar()) != '\n')
        *s++ = ch;
    *s = '\0';
}
int main(int argc, char **argv)
{
    int sock_fd;
    int ret;
    char send_msg[MSG_LEN] = {0};
    char recv_msg[MSG_LEN] = {0};
    struct sockaddr_in server_addr;
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0)
        WriteError("Failed to create socket!");
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = CONST_PORT;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    ret = connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (ret < 0)
        WriteError("Failed to connect server!");
    for (;;)
    {
        readline(send_msg);
        if (strcmp(send_msg, "quit") == 0)
            break;
        ret = send(sock_fd, send_msg, MSG_LEN, 0);
        if (ret < 0)
            WriteError("Faile to send msg!");
        ret = recv(sock_fd, recv_msg, MSG_LEN, 0);
        recv_msg[ret] = '\0';
        std::cout << "send to server: " << recv_msg << std::endl;
    }
    close(sock_fd);
}
