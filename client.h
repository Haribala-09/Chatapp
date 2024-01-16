#ifndef CLIENT_H
#define CLIENT_H
#include <arpa/inet.h>
#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>
#include <thread>

class client_soc
{
public:
    client_soc(int por);
    char r_buff[1024];
    struct sockaddr_in serv_addr;
    std::thread t2;
    void connect_();
    void close_();
    int soc_fd;
};

#endif // CLIENT_H
