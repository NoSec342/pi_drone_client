#include <iostream>
#include "client_sock.hpp"
int main(int argc, char **argv) {
    uint16_t port = argc > 1 ? atoi(argv[1]) : 54000;
    std::cout << port << std::endl;
    std::string ip = argc > 2 ? std::string(argv[2]) : "127.0.0.1";
    client_sock Client(ip ,port);
        while(true)
        {
            char buffer[4096]; 
            std::cin.getline(buffer, 4096);  
            Client.WriteToServer(std::string(buffer) + "\n");
            if(strstr( buffer , "exit"))
            {
                return 0;
            }
        }
    return 0;
}
