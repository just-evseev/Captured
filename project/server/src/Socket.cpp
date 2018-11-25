//
// Created by tsv on 05.11.18.
//

#include <netinet/in.h>
#include "Socket.h"
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <cstring>


Socket::Socket() {
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        puts("error");
    }
}

Socket::~Socket() {
    std::cout << "Close server" << std::endl;
    close(fd);
}

void Socket::bind(unsigned short port) {
    sockaddr_in serv_addr{};

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port);

    /* Bind */
    if (::bind(this->fd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) {
        puts("error");
    }
}

void Socket::listen() {
    if (::listen(this->fd, 10) < 0) {
        puts("error");
    }
}

//ClientSocket Socket::accept() {
//    int cli_fd = ::accept(this->fd, nullptr, nullptr);
//    if (cli_fd < 0) {
//        throw_errno_str();
//    }
//
//    return ClientSocket(cli_fd);
//}
