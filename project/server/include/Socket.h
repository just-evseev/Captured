//
// Created by tsv on 05.11.18.
//

#ifndef FTP_SERVER_SOCKET_H
#define FTP_SERVER_SOCKET_H


#include <string>
//#include "ClientSocket.h"
#include "util.h"

class Socket {
public:
    Socket();

    virtual ~Socket();

    void bind(unsigned short port);

    void listen();

//    ClientSocket accept();

private:
    int fd;
};


#endif //FTP_SERVER_SOCKET_H
