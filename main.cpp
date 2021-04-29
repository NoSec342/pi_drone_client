#include <iostream>
#include "client_sock.hpp"
#include <unistd.h>
#include <stdio.h>
#include <termios.h>


// O FUNCTIE PENTRU A CITI IN TIMP REAL DE LA TASTATURA TASTELE APASATE 

char GetKeystroke()
{
    char buf = 0;
    struct termios term = {0}; 
    fflush(stdout); 
    if(tcgetattr(STDIN_FILENO, &term) < 0)
    {
        fprintf( stderr , "tcsetattr()");
    }
    term.c_lflag &= ~ICANON;
    term.c_lflag &= ~ECHO;
    term.c_cc[VMIN] = 1;
    term.c_cc[VTIME] = 0;
    if(tcsetattr(STDIN_FILENO, TCSANOW, &term) < 0)
    {
        fprintf(stderr, "tcsetattr ICANON");
    }
    if(read(STDIN_FILENO, &buf, 1) < 0)
    {
        fprintf(stderr, "Can not read!\n");
    }
    term.c_lflag |= ICANON;
    term.c_lflag |= ECHO;
    if(tcsetattr(STDIN_FILENO, TCSADRAIN, &term) < 0)
        fprintf(stderr, "tcsetattr ~ICANON");
    return buf;

}

int main(int argc, char **argv) {
    
    const uint8_t FORWARD = 8, BACKWARDS = 9, LEFT = 7, RIGHT = 0, ROTATE_LEFT = 2, ROTATE_RIGHT = 3, MOTOR_POWER1 = 12, MOTOR_POWER2 = 13, MOTOR_POWER3 = 14,  MOTOR_POWER4 = 30;
    
    uint16_t port = argc > 1 ? atoi(argv[1]) : 54000;
    std::cout << port << std::endl;
    std::string ip = argc > 2 ? std::string(argv[2]) : "127.0.0.1";
    client_sock Client(ip ,port);
        while(true)
        {
            
            uint8_t msg;
            char rd = GetKeystroke();
            switch(rd)
            {
                case 'w':
                    Client.WriteToServer(std::to_string(FORWARD));
                    break;
                case 'a':
                    Client.WriteToServer(std::to_string(LEFT));
                    break;
                case 's':
                    Client.WriteToServer(std::to_string(BACKWARDS));
                    break;
                case 'd':
                    Client.WriteToServer(std::to_string(RIGHT));
                    break;
                case 'e':
                    Client.WriteToServer(std::to_string(ROTATE_RIGHT));
                    break;
                case 'q':
                    Client.WriteToServer(std::to_string(ROTATE_LEFT));
                    break;
                case ' ':
                    Client.WriteToServer(std::to_string(MOTOR_POWER1));
                    break;
                default:
                    
                    break;
            }
            
            std::cout << rd << std::endl;
        }
    return 0;
}
