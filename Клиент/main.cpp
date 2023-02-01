#include <iostream>
#include <string>
#include <getopt.h>
#include "Connection.h"
using namespace std;
/** 
* @file main.cpp
* @brief Главный модуль программы для получения параметров от пользователя
* @param rez переменная для работы с параметрами командной строки
* @param optarg переменная для получения парметров командной строки
*/
int main (int argc, char *argv[])
{

    const char* short_options = "hi:p::o:r:a::";

    const struct option long_options[] = {
        { "help", no_argument, NULL, 'h' },
        { "ip", required_argument, NULL, 'i' },
        { "port", optional_argument, NULL, 'p' },
        { "original_file", required_argument, NULL, 'o' },
        { "result_file", required_argument, NULL, 'r' },
        { "auth", optional_argument, NULL, 'a' },
        { NULL, 0, NULL, 0 }
    };

    int rez;
    int option_index;

    string s1 = "1 парметр -h или --help для справки";
    string s2 = "2 параметр -i или --ip сетевой адрес сервера обязательный";
    string s3 = "3 параметр -p или --port порт серевера необязательный";
    string s4 = "4 параметр -o или --original_file файл с векторами обязательный";
    string s5 = "5 параметр -r или --result_file файл с результатами обязательный";
    string s6 = "6 параметр -a или --auth файл с логином и паролем необязательный";
	
	//! Взаимодействие с пользователем через командную строку
    Connection Interface;

    if(argc == 1) {
        cout << "Программа-клиент" << endl;
        cout << s1 << endl;
        cout << s2 << endl;
        cout << s3 << endl;
        cout << s4 << endl;
        cout << s5 << endl;
        cout << s6 << endl;
        return 1;
    }
    string str1;
    string str2;
    while ((rez=getopt_long(argc,argv,short_options,
                            long_options,&option_index))!=-1) {

        switch(rez) {
        case 'h': {
            cout << "Программа-клиент" << endl;
            cout << s1 << endl;
            cout << s2 << endl;
            cout << s3 << endl;
            cout << s4 << endl;
            cout << s5 << endl;
            cout << s6 << endl;
            return 1;
        };
        case 'i': {
            if (optarg==NULL) {
                cout << s2 << endl;
                return 2;
            } else {
                str1 = string(optarg);
            }
            break;
        };

        case 'p': {
            if (optarg!=NULL) {
                str2 = string(optarg);
            } else {
                str2 = "33333";
            }
            break;
        };
        case 'o': {
            if (optarg==NULL) {
                cout << s4 << endl;
                return 3;
            } else {
                Interface.original_file = string(optarg);
            }
            break;
        };

        case 'r': {
            if (optarg==NULL) {
                cout << s5 << endl;
                return 4;
            } else {
                Interface.result_file = string(optarg);
            }
            break;
        };

        case 'a': {
            if (optarg!=NULL) {
                Interface.auth_file = string(optarg);
            } else {
                Interface.auth_file =string("./config/vclient.conf");
            }
            break;
        };

        case '?':
        default: {
            cout << "Таких опций нет" << endl;
            return 5;
        };
        };
    };



    Interface.Connect_to_server(str1, str2);


    return 0;
};
