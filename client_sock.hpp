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
    void SetPort(const uint16_t& fa_port);
    void ConnectToServer(const std::string& ip, const uint16_t& port);
    void WriteToServer(const std::string& fa_msg);
    const std::string ReadFromServer();
    
};

std::ostream& operator<<(std::ostream& stream, client_sock& client)
{
    stream << client.ReadFromServer();
    return stream;
}

std::istream& operator>>(std::istream& stream, client_sock& client)
{
    std::string msg;
    stream >> msg;
    client.WriteToServer(msg);
    return stream;
}


#endif
