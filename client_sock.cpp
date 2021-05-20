#include "client_sock.hpp"


client_sock::client_sock(const std::string& ip, const uint16_t& port)
{
    m_client_fd = socket(AF_INET, SOCK_STREAM, 0); // AM DEFINIT DESCRIPTORUL DE FISIER PENTRU SOCKET , PENTRU A MA CONECTA LA
                                                   // SERVER
    this->ConnectToServer(ip, port);               // MA VOI CONECTA AUTOMAT DIRECT LA SERVER
}
void client_sock::ConnectToServer(const std::string& ip, const uint16_t& port)
{
    SetPort(port);
    server_addr.sin_family = AF_INET; // SETEZ FAMILIA NET (FAPTUL CA VOI FOLOSI IPv4)
    if(inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr) < 0) // INCERC CONECTAREA CATRE SERVER
    {
        fprintf(stderr, "Can not connect to server!\n");
    }
    is_connected = connect(m_client_fd, (sockaddr *)&server_addr, sizeof(server_addr)) < 0 ? false : true; // RETIN DACA SUNT 
    //CONECTAT
}


void client_sock::SetPort(const uint16_t& port)
{
    server_addr.sin_port = htons(port); //SETEZ PORTUL LA CARE MA VOI CONECTA IN STRUCTURA HINT
}

void client_sock::WriteToServer(const std::string& msg)
{
    memset(&m_buffer, 0, sizeof(m_buffer)); //CURAT BUFFER-UL INAINTE DE A SCRIE CATRE SERVER 
    strcpy(m_buffer, msg.c_str()); //VOI PASA ARGUMENTUL MESAJ IN BUFFER
    uint16_t len = strlen(m_buffer); //RETIN LUNGIMEA BUFFER-ULUI 
    m_buffer[ len + 1] = '\n'; // LINIE NOUA LA FINAL DE BUFFER PENTRU A FI CITIT CUM TREBUIE DE CATRE SERVER
    send(m_client_fd, m_buffer, sizeof(m_buffer), 0);//TRIMIT CE AM IN BUFFER 
    memset(&m_buffer, 0, sizeof(m_buffer));//CURAT BUFFER-UL DIN NOU
}

    

const std::string client_sock::ReadFromServer()
{
    memset(&m_buffer, 0, sizeof(m_buffer)); //CURAT BUFFER-UL INAINTE DE A CITI IN EL DATE DE LA SERVER
    recv(m_client_fd, m_buffer, strlen(m_buffer), 0); //VOI RECEPTIONA DATE DE LA SERVER
    return std::string(m_buffer);
}



// AICI VOI INCHIDE SOCKET-UL PENTRU CLIENT 

client_sock::~client_sock()
{
    close(m_client_fd);
}

void client_sock::Raise() const
{
    
}


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
