#include "header.h"
#include <queue>
#include <cstring>
using namespace std;

class client
{

public:
    int id;
    int sock_fd;
    client(int s, int i) : sock_fd(s), id(i)
    {

        int flags = fcntl(sock_fd, F_GETFL, 0);
        if (flags == -1)
        {
            perror("Error getting socket flags");
            exit(-1);
        }

        if (fcntl(sock_fd, F_SETFL, flags | O_NONBLOCK) == -1)
        {
            perror("Error setting non-blocking mode");
            exit(-1);
        }
    };

    bool operator==(const client &other)
    {
        if (&other == this)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool operator!=(const client &other)
    {
        if (*this == other)
        {
            return false;
        }
        return true;
    }
};

class message
{
    int SIZE = 256;

public:
    int id;
    char *content;
    message(int i, char con[]) : id(i), content(con){};
};

class server_sock
{
    queue<message> reply;
    struct sockaddr_in addr;
    int sock_fd;
    vector<client> clients;

public:
    bool stop_ = false;
    void clean()
    {
        for (auto &x : this->clients)
        {
            close(x.sock_fd);
        }
    }
    void close_connection()
    {
        close(sock_fd);
    }
    static int idgen;
    server_sock()
    {

        sock_fd = socket(AF_INET, SOCK_STREAM, 0);
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = INADDR_ANY;
        addr.sin_port = htons(8081);

        bind(sock_fd, (struct sockaddr *)&addr, sizeof(addr));
    }
    void listenloop()
    {
//        int curr = sock_fd;

        int result;
        int m = sizeof(addr);
            // Set up a timeval struct for the timeout
        struct timeval timeout;
        timeout.tv_sec = 1;  // 1 second timeout
        timeout.tv_usec = 0;
        int res;
        // Set up a file descriptor set for select()
        fd_set readSet;
        FD_ZERO(&readSet);
        FD_SET(sock_fd, &readSet);
        //      int flags = fcntl(sock_fd, F_GETFL, 0);
        // fcntl(sock_fd, F_SETFL, flags | O_NONBLOCK);

        listen(sock_fd, 30);
        do
        {


            // // Use select() with a timeout to check for new connections
            //     res = select(curr , &readSet, NULL, NULL, &timeout);
            // if (res == -1) {
            //     perror("Error in select()");
            //     break;  // Exit the loop on error
            // } else if (res == 0) {
            //     cout<<clients.size()<<endl;
            //     // Timeout occurred, no new connections
            //     continue;
            // }
            //     curr++;
            result = accept(sock_fd, NULL,
                            NULL);
            clients.push_back(client(result, server_sock::idgen++));
        } while (!stop_);
    }
    void read_write()
    {
        char buff[256];
        int result;
        while (!stop_)
        {

            for (auto &x : clients)
            {
                result = recv(x.sock_fd, buff, 256, 0);
                if (result == 0)
                {

                    clients.erase(remove(clients.begin(), clients.end(), x));
                    cout << "hey!" << clients.size() << endl;
                    continue;
                }
                if (result == -1)
                {
                    continue;
                }
                char *tmp = new char[strlen(buff) + 1];
                strcpy(tmp, buff);
                cout << "w_r: " << tmp[0] << "," << endl;
                reply.push(message(x.id, tmp));
            }
            SLEEP
        }
    }
    void deliver()
    {
        while (!stop_)
        {
            if (reply.empty())
            {
                SLEEP
                    continue;
            }
            // cout << reply.front().id << " : " << reply.front().content << endl;
            for(auto &cli :clients)
            {
                if(reply.front().id!=cli.id)
                {
                    send(cli.sock_fd,reply.front().content,256,0);
                }
            }
            delete[] reply.front().content;
            reply.pop();
        }
    }
};
int server_sock::idgen;
//int main()
//{
//    server_sock myserver;
//    server_sock::idgen = 1545;
//    thread t1 = thread([&myserver]()
//                       { myserver.listenloop(); });
//    thread t2 = thread([&myserver]()
//                       { myserver.read_write(); });
//    thread t3 = thread([&myserver]()
//                       { myserver.deliver(); });
//    int n;
//    do
//    {
//        cin >> n;

//    }while (n!=0);


//    myserver.stop_ = true;
//    myserver.clean();
//    myserver.close_connection();
//    cout<<".."<<endl;
//    t1.join();
//    t2.join();
//    t3.join();


//}
