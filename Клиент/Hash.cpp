/**
 * @file Hash.cpp
 */
#include "Hash.h"

std::string MD5_hash(std::string msg)
{
    using namespace CryptoPP;

    // Создаем объект-"хэширователь" для MD5
    Weak::MD5 hash;

    // куда запишем результат
    std::string digest;

    // создаем цепочку преобразования
    StringSource(msg, true,             // источник-стока
                 new HashFilter(hash,       // фильтр-"хеширователь"
                                new HexEncoder(     // кодировщик в строку цифр
                                //new Base64Encoder
                                    new StringSink(digest))));  // строка-приемник
    // выводим сообщение и его хэш
    return digest;
}
