#ifndef __CLIENT_SOCK__
#define __CLIENT_SOCK__
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>

// AICI VOI DEFINI FUNCTIILE DE CONECTARE CATRE DRONA

class client_sock
{
private:
    int8_t m_client_fd;
    sockaddr_in server_addr;
    uint16_t m_port;
    char m_buffer[4096];
    
public:
    
    bool is_connected;
    
    client_sock(const std::string& ip, const uint16_t& port);
    ~client_sock();
    virtual void SetPort(const uint16_t& fa_port);
    virtual void ConnectToServer(const std::string& ip, const uint16_t& port);
    virtual void WriteToServer(const std::string& fa_msg);
    virtual const std::string ReadFromServer();
    virtual void Raise() const;

};

// AM REDEFINIT NISTE OPERATORI PENTRU A-MI FACE TREABA MAI USOARA

std::ostream& operator<<(std::ostream& stream, client_sock& client);

std::istream& operator>>(std::istream& stream, client_sock& client);


#endif
