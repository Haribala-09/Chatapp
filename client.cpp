//    Q_OBJECT
//signals:
//    void textReceived(const QString &text);
#include"client.h"
client_soc::client_soc(int por)
{

    if ((soc_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        exit(-1);
    }
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8081);
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
            std::cout << "\nInvalid address Address not supported \n";
            exit(-1);
    }
 }
void client_soc::connect_()
{

    if ((::connect(soc_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))) < 0)
    {
        std::cout << "\nConnection Failed \n";
        exit(-1);
    }
}
void client_soc::close_()
{
    close(soc_fd);
}
//    void sendd()
//    {
//        while (true)
//        {
//            std::cout << "\nEnter message :";
//            std::cin.getline(w_buff, sizeof(w_buff));
//            // std::cout << "u entrd: " << w_buff << std::endl;
//        }
//    }
//    void receive()
//    {
//        int val = 0;
//        while (true)
//        {
//            val = read(soc_fd, r_buff, 1024 - 1);
//            r_buff[val] = '\0';
//        }
//    }
// int main(int argc, char const *argv[])
// {
// 	client_soc xxx(8081);
// 	xxx.connect_();
// 	std::thread t1([&xxx]()
// 				   { xxx.sendd(); });
// 	std::thread t2([&xxx]()
// 				   { xxx.receive(); });
// 	t1.join();
// 	t2.join();
// }
//class client_soc : public QObject
//{
//    Q_OBJECT

//public:
//    int soc_fd;
//    char r_buff[1024];
//    struct sockaddr_in serv_addr;
//    std::thread t2;

//signals:
//    void messageReceived(const QString &message);

//public:
//    client_soc(int por);
//    ~client_soc();

//    void connect_();
//    void receive();
//    void close_();
//    void startReceiving();
//    void stopReceiving();
//};
//client_soc::client_soc(int por)
//{
//    if ((soc_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
//    {
//        printf("\n Socket creation error \n");
//        exit(-1);
//    }
//    memset(&serv_addr, 0, sizeof(serv_addr));
//    serv_addr.sin_family = AF_INET;
//    serv_addr.sin_port = htons(por);
//    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
//    {
//        std::cout << "\nInvalid address Address not supported \n";
//        exit(-1);
//    }
//}

//client_soc::~client_soc()
//{
//    close(soc_fd);
//}

//void client_soc::connect_()
//{
//    if ((::connect(soc_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))) < 0)
//    {
//        std::cout << "\nConnection Failed \n";
//        exit(-1);
//    }
//}

//void client_soc::receive()
//{
//    int val = 0;
//    while (true)
//    {
//        val = read(soc_fd, r_buff, 1024 - 1);
//        r_buff[val] = '\0';

//        // Emit the signal with the received message
//        emit messageReceived(QString::fromStdString(r_buff));
//    }
//}

//void client_soc::close_()
//{
//    close(soc_fd);
//}

//void client_soc::startReceiving()
//{
//    t2 = std::thread(&client_soc::receive, this);
//}

//void client_soc::stopReceiving()
//{
//    if (t2.joinable())
//    {
//        t2.join();
//    }
//}
