#include "server.h"


// WSASession::WSASession()
// {
//     int ret = WSAStartup(MAKEWORD(2, 2), &data);
//     if (ret != 0)
//     throw std::system_error(WSAGetLastError(), std::system_category(), "WSAStartup Failed");
// }


// WSASession::~WSASession()
// {
//     WSACleanup();
// }


UdpSocket::UdpSocket()
{
    s32MasterSocketFd_ = socket(AF_INET, SOCK_STREAM, IPPROTO_UDP);
    
    if (s32MasterSocketFd_ < 0)
    {
        std::cout << "SERVER >> [ERROR] Failed to create a socket" << std::endl;
    }
    else
    {
        std::cout << "SERVER >> Successfully to create a socket" << std::endl;
    }
}


UdpSocket::~UdpSocket()
{
    close(s32MasterSocketFd_);
}


void UdpSocket::UdpBind(void)
{
    stSockAddrInServer_.sin_family = AF_INET;
    stSockAddrInServer_.sin_addr.s_addr = htonl(INADDR_ANY);
    stSockAddrInServer_.sin_port = htons(PORT_NUM);

    int s32SocketBindStat = bind(s32MasterSocketFd_, reinterpret_cast<struct sockaddr *>(&stSockAddrInServer_), sizeof(stSockAddrInServer_));
    if (s32SocketBindStat < 0)
    {
        std::cout << "SERVER >> [ERROR] Failed to bind a socket" << std::endl;
    }
    else
    {
        std::cout << "SERVER >> Successfully bind a socket" << std::endl;
    }
}


void UdpSocket::UdpLitsen(void)
{
    if (listen(s32MasterSocketFd_, MAX_PENDING_CONNECTIONS) < 0) //Specify 3 as maximum pending connections for master socket
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    // The accept() call actually accepts an incoming connection
    u32SzStSockAddrInClient_ = sizeof(stSockAddrInClient_);
}

void UdpSocket::UdpAccept(void)
{
     // This accept() function will write the connecting client's address info 
     // into the the address structure and the size of that structure is clilen.
     // The accept() returns a new socket file descriptor for the accepted connection.
     // So, the original socket file descriptor can continue to be used 
     // for accepting new connections while the new socker file descriptor is used for
     // communicating with the connected client.
     s32NewMasterSocketFd_ = accept(s32MasterSocketFd_, 
                 (struct sockaddr *) &stSockAddrInClient_, &u32SzStSockAddrInClient_);
     if (s32NewMasterSocketFd_ < 0)
     {
         std::cout << "SERVER >> [ERROR] Failed to accept" << std::endl;
     }
     else
     {
         std::cout << "SERVER >> Successfully aceept" << std::endl;
         std::cout << "SERVER >> Got connection: address(" 
                   << inet_ntoa(stSockAddrInClient_.sin_addr) 
                   << ") / port ("
                   << ntohs(stSockAddrInClient_.sin_port)
                   << ")"
                   << std::endl;
     }

     stUdpBuffer_.id = 0;
}

void UdpSocket::UdpSend(void)
{
    stUdpBuffer_.x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    stUdpBuffer_.y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
     // This send() function sends the 13 bytes of the string to the new socket
     send(s32NewMasterSocketFd_, reinterpret_cast<const void*>(&stUdpBuffer_), sizeof(stUdpBuffer_), 0);
}
