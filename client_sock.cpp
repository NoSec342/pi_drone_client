#include "client_sock.hpp"
client_sock::client_sock(const std::string& ip, const uint16_t& port)
{
    m_client_fd = socket(AF_INET, SOCK_STREAM, 0);
    this->ConnectToServer(ip, port);
}
void client_sock::ConnectToServer(const std::string& ip, const uint16_t& port)
{
    SetPort(port);
    server_addr.sin_family = AF_INET;
    if(inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr) < 0)
    {
        fprintf(stderr, "Can not connect to server!\n");
    }
    is_connected = connect(m_client_fd, (sockaddr *)&server_addr, sizeof(server_addr)) < 0 ? false : true;
}


void client_sock::SetPort(const uint16_t& port)
{
    server_addr.sin_port = htons(port);
}

void client_sock::WriteToServer(const std::string& msg)
{
    memset(&m_buffer, 0, sizeof(m_buffer));
    strcpy(m_buffer, msg.c_str());
    uint16_t len = strlen(m_buffer);
    m_buffer[ len + 1] = '\n';
    send(m_client_fd, m_buffer, sizeof(m_buffer), 0);
    memset(&m_buffer, 0, sizeof(m_buffer));
}

const std::string client_sock::ReadFromServer()
{
    memset(&m_buffer, 0, sizeof(m_buffer));
    recv(m_client_fd, m_buffer, strlen(m_buffer), 0);
    return std::string(m_buffer);
}

client_sock::~client_sock()
{
    close(m_client_fd);
}

