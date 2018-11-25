//
// Created by Ilya on 25/11/2018.
//

#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#include <SFML/Network.hpp>


class Server {
public:

    Server();

    ~Server();

    void createServer(void);
    void getInfo(void);

    std::vector<std::unique_ptr<sf::TcpSocket>> socket;

private:

    sf::Mutex globalMutex;

    const unsigned short PORT = 5000;

    void sendInput(void);

    std::string msgSend;
    bool quit = false;

};


#endif //SERVER_SERVER_H
