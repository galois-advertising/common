#include <iostream>
#include <sys/socket.h>
#include <netinet/tcp.h>
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
    close(sock);
    
}
