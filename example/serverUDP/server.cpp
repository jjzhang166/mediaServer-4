#include <bits/stdc++.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
void WriteError(std::string msg)
{
    std::cout << msg << std::endl;
    exit(-1);
}
const int MSG_LEN=1<<10;
int main()
{
    struct sockaddr_in addr;
    int sock_fd;
    int ret;
    char msg[MSG_LEN]={0};
    sock_fd=socket(PF_INET,SOCK_RAW,0);
    if(sock_fd<0)
        WriteError("Failed to socket!");
    
}