#include <iostream>
#include <unistd.h>
#include <memory>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <string.h>
#include <netinet/in.h>
using namespace std;


int main()
{
    auto sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock < 0)
    { 
        std::cout<<"sock < 0"<<std::endl;
        return 0;
    };
    sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(sockaddr_in));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(8800);
    int bind_res = 0;
    if(bind_res = bind(sock, reinterpret_cast<const sockaddr*>(&servaddr), sizeof(sockaddr_in)) < 0)
    {
        std::cout<<"bind error:"<<bind_res<<std::endl;
        return 0;
    }
    if(listen(sock, 5) < 0)
    {
        std::cout<<"listen error:"<<std::endl;
        return 0;
    }
    sockaddr_in client;
    int len = sizeof(sockaddr);
    while(1)
    {
        auto sock_client = accept(sock,  reinterpret_cast<sockaddr*>(&client), (socklen_t*)&len);
        std::cout<<"new client:"<<sock_client<<std::endl;
        sleep(4);
        close(sock_client);
    }
    //close(sock);
    
}
