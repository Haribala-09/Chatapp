#ifndef HEADER_H
#define HEADER_H
#include <iostream>
#include <sys/socket.h>
#include <fcntl.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <vector>
#include <thread>
#include <chrono>
#include <arpa/inet.h>
#include<algorithm>
#include<string.h>
#include<unistd.h>
#define SLEEP this_thread::sleep_for(chrono::milliseconds(100));
#endif //HEADER_H
