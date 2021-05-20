#include <iostream>
#include "client_sock.hpp"
#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include <thread>

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
    
    const char FORWARD = '3', BACKWARDS = '4', LEFT = '1', RIGHT = '2', ROTATE_LEFT = '5', ROTATE_RIGHT = 6, MOTOR_POWER1 = 8,  POWER_DOWN = 7;
    
    uint16_t port = argc > 1 ? atoi(argv[1]) : 54000;
    std::cout << port << std::endl;
    std::string ip = argc > 2 ? std::string(argv[2]) : "192.168.0.1";
    client_sock Client(ip ,port);
    
//     std::thread recv_err([&]{
//         while(true)
//         {
//             std::string buffer;
//             buffer = Client.ReadFromServer();
//             if(!buffer.empty())
//             {
//                     fprintf(stdout, "Received; %s", buffer.c_str());
//             }
//             buffer.clear();
//         }
//         
//     });
//     recv_err.detach();
    
    
        while(true)
        {
            char rd = GetKeystroke();
            switch(rd)
            {
                case 'w':
                {
                    std::thread thd([&]
                    {
                        Client.WriteToServer(std::to_string(FORWARD));
                    });
                    thd.detach();
                    break;
                }    
                case 'a':
                {
                    std::thread thd([&]
                    {
                        Client.WriteToServer(std::to_string(LEFT));
                    });
                    thd.detach();
                    break;
                }  
                case 's':
                {
                    std::thread thd([&]
                    {
                        Client.WriteToServer(std::to_string(BACKWARDS));
                    });
                    thd.detach();
                    break;
                }  
                case 'd':
                {
                    std::thread thd([&]
                    {
                        Client.WriteToServer(std::to_string(RIGHT));
                    });
                    thd.detach();
                    break;
                }  
                case 'e':
                {
                    std::thread thd([&]
                    {
                        Client.WriteToServer(std::to_string(ROTATE_RIGHT));
                    });
                    thd.detach();
                    break;
                };
                case 'q':
                {
                    std::thread thd([&]
                    {
                        Client.WriteToServer(std::to_string(ROTATE_LEFT));
                    });
                    thd.detach();
                    break;
                }
                case ' ':
                {
                    std::thread thd([&]
                    {
                        Client.WriteToServer(std::to_string(MOTOR_POWER1));
                    });
                    thd.detach();
                    break;
                }
                case 'x':
                {
                    std::thread thd([&]
                    {
                        Client.WriteToServer(std::to_string(POWER_DOWN));
                        
                    });
                    thd.detach();
                    break;
                }
                default:
                    fprintf(stderr, "%c not found!\n", rd);
                    break;
            }
            
            std::cout << rd << std::endl;
        }
    return 0;
}
