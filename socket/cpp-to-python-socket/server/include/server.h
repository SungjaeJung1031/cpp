// server.h header file for C++ UDP
#ifndef SERVER_H
#define SERVER_H


#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <system_error>
#include <string>
#include <iostream>
#include <cstdint>

#include <sys/socket.h> 
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h> 
#include <netinet/ip.h> /* superset of previous */

#include "udp_buffer.h"

#include "server_decl.h"

//#pragma comment (lib, "ws2_32")

// class WSASession
// {
//   public:
//       /**
//        * @brief Construct a new WSASession object
//        * @details 
//        */
//       WSASession();
//       ~WSASession();

//   private:
//     UDP_DATA_T data;
// };

class UdpSocket
{
  public:
    /**
     * @brief Construct a new UDPSocket object
     * @details Create a socket
     */
    UdpSocket();

    /**
     * @brief Destroy the UDPSocket object
     * @details Close a socket
     */
    ~UdpSocket();

    void UdpBind(void);
    void UdpLitsen(void);
    void UdpAccept(void);
    void UdpSend(void);


  private:
    int32_t s32MasterSocketFd_;
    int32_t s32NewMasterSocketFd_;
    sockaddr_in stSockAddrInServer_;
    sockaddr_in stSockAddrInClient_;
    uint32_t u32SzStSockAddrInClient_;
    UDP_BUFFER_T stUdpBuffer_;
};

#endif // SERVER_H