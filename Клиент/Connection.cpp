/**
 * @file Connection.cpp
 */
#include "Connection.h"
#include "Hash.h"
/// Получение пароля и логина
void Connection::GetLoginPassword()
{
    //Открытие файла с логином и паролем
    ifstream fa(auth_file);

    if(!fa.is_open()) {

        fa.close();

        throw error_proj("Ошибка отрытия файла для аутентификации!");

    }

    string line;

    if(fa.peek() == EOF) {

        fa.close();

        throw error_proj("Ошибка отрытия файла для аутентификации! Файл пуст!");

    }

    getline(fa, line);

    int k = line.find(" ");

    string u = line.substr(0, k);

    string p = line.erase(0, k+1);

    username = u;

    pswd = p;
}
/**
* @brief Взаимодействие с сервером.
* @param str1 адрес сервера.
* @param str2 порт сервера.
* @throw error_proj при возникновении ошибки.
*/
int Connection::Connect_to_server(string str1, string str2)
{
    GetLoginPassword();
    // Открытие файла с векторами
    ifstream f(original_file, ios::binary);

    if(!f.is_open()) {

        f.close();

        throw error_proj("Ошибка отрытия файла с векторами!");

    }
    // Открытие файла для результатов
    ofstream fout(result_file,ios::binary | ios::app);

    if (!fout.is_open()) {

        fout.close();

        throw error_proj("Файл для результата не может быть открыт или создан!");

    }

    try {

        ip_addr = stoi(str1);

    } catch (...) {

        throw error_proj("Не возможно получить адрес!");

    }

    try {

        port = stoi(str2);

    } catch (...) {

        throw error_proj("Не возможно получить порт!");

    }

    char buf[1024];

    int bytes_read;

    int s;

    struct sockaddr_in addr;

    s = socket(AF_INET, SOCK_STREAM, 0);

    if(s < 0) {

        throw error_proj("Ошибка создания сокета!");

    }

    addr.sin_family = AF_INET;

    addr.sin_port = htons(port);

    addr.sin_addr.s_addr = htonl(ip_addr);

    if(connect(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {

        throw error_proj("Ошибка подключения к серверу!");

    }
    // Отправка логина
    strcpy(buf,username.c_str());

    send(s, buf, username.length(), 0);

    // Принимаем строку с SALT или ошибку ERR
    bytes_read = recv(s, buf, sizeof(buf), 0);

    buf[bytes_read] = '\0';

    string s1 = string(buf);
    cout << "Мы получаем ответ: " << s1 << endl;

    if (s1 == "") {

        close(s);

        throw error_proj("Ошибка идентификации!");
    }

    // Вычисление хэша-кода от SALT+PASSWORD
    string s2 = s1 + pswd;

    s2 = MD5_hash(s2);

    // Отправка хэша-кода от SALT+PASSWORD
    strcpy(buf,s2.c_str());

    send(s, buf, s2.length(), 0);

    // Получение ответа об аутентификации
    bytes_read = recv(s, buf, sizeof(buf), 0);

    buf[bytes_read] = '\0';

    string s3 = string(buf);
    cout << "Мы получаем ответ: "<< s3<< endl; 
    if (s3 == "") {

        close(s);

        throw error_proj("Ошибка аутентификации!");
    }

    uint32_t n,m;

    uint16_t v;

    // Получение количества векторов
    f.read((char*)&n, sizeof(n));
    
    fout.write((char*)&n, sizeof(n));

    // Отправка количества векторов
    send(s, &n, sizeof(uint32_t), 0);

    for(int i =0; i<n; i++) {

        // Получение размера векторов
        f.read((char*)&m, sizeof(m));

        uint16_t array[m]= {0};

        for(int j=0; j<m; j++) {

            f.read((char*)&v, sizeof(v));

            array[j] = v;
        }

        // Отправка размера векторов
        send(s, &m, sizeof(uint32_t), 0);
        // Отправка чисел в векторах
        send(s, &array, sizeof(array), 0);

        uint16_t sum=0;

        // Получение суммы
        recv(s, &sum, sizeof(sum), 0);

        fout.write((char*)&sum, sizeof(sum));

    }

    f.close();

    fout.close();

    cout << "Результат сохранен в файле: " << result_file << endl;

    close(s);

    return 0;
}
