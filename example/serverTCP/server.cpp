#include <bits/stdc++.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
void WriteError(std::string msg)
{
    std::cout << msg << std::endl;
    exit(-1);
}
const int CONST_PORT = 8111;
const int Qlen = 10;
const int MSG_LEN = 1 << 10;
int main(int argc, char **argv)
{
    int ret = -1;
    int on = 1;
    int sock_fd;
    char in_buff[MSG_LEN] = {0};
    struct sockaddr_in server_addr;
    struct sockaddr_in clnt_addr;
    sock_fd = socket(PF_INET, SOCK_STREAM, 0);
    if (sock_fd == -1)
        WriteError("Failed to create socket!");
    ret = setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    if (ret == -1)
        WriteError("Failed to set socket options!");
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = CONST_PORT;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    bzero(&(server_addr.sin_zero), 8);
    ret = bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
    if (ret == -1)
        WriteError("Failed to bind socket!");
    ret = listen(sock_fd, Qlen);
    if (ret == -1)
        WriteError("Failed to listen socket!");
    for (;;)
    {
        unsigned int clnt_len = sizeof(clnt_addr);
        int accept_fd = accept(sock_fd, (struct sockaddr *)&clnt_addr, &clnt_len);
        if (accept_fd == -1)
            WriteError("Failed to accept socket!");
        for (;;)
        {
            ret = recv(accept_fd, in_buff, MSG_LEN, 0);
            if (ret == 0)
                break;
            std::cout << "recv from clnt: " << in_buff << std::endl;
            send(accept_fd, in_buff, MSG_LEN, 0);
        }
        close(accept_fd);
    }
    close(sock_fd);
}
