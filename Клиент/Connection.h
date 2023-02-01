/** 
* @file Connection.h
* @author Нефедова В.А.
* @version 1.0
* @date 31.01.2023
* @copyright ИБСТ ПГУ
* @brief Заголовочный файл для модуля Connection
*/
#pragma once
#include <sys/types.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fstream>
#include <vector>
#include <string>
#include <locale>
#include <codecvt>
using namespace std;

/** 
* @brief Класс для подключения к серверу
* @param ip_addr адрес сервера
* @param port порт сервера
* @param original_file имя файла с векторами
* @param result_file имя файла для записи результатов
* @param auth_file имя файла, в котором храняться логины и пароли клиентов
* @param username логин клиента
* @param pswd пароль клиента
*/

class Connection
{
public:
    int ip_addr;
    int port;
    string original_file;
    string result_file;
    string auth_file;
    string username;
    string pswd;
    int Connect_to_server(string str1, string str2);
    void GetLoginPassword();

};

//!Класс для обработки исключений
class error_proj: public std::invalid_argument
{
public:
    explicit error_proj (const std::string& what_arg):
        std::invalid_argument(what_arg) {}
    explicit error_proj (const char* what_arg):
        std::invalid_argument(what_arg) {}
};
