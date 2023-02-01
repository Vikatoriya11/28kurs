/** 
* @file Hash.h
* @author Нефедова В.А.
* @version 1.0
* @date 31.01.2023
* @copyright ИБСТ ПГУ
* @brief Заголовочный файл для модуля Hash
*/
#include <iostream>
#include <vector>
#include <cryptopp/hex.h>
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <cryptopp/md5.h>

std::string MD5_hash(std::string msg);
