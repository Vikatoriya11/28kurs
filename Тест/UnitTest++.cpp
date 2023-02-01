#include <UnitTest++/UnitTest++.h>
#include "Connection.h"
using namespace std;

struct Test {
    Connection * p;
    Test()
    {
        p = new Connection();
    }
    ~Test()
    {
        delete p;
    }
};

SUITE(Connect_to_server)
{
    TEST_FIXTURE(Test, NormalTest) {
        //1 Удачный сценарий
        p->original_file = "/home/stud/Клиент/vector.bin";
        p->result_file = "/home/stud/Клиент/res.bin";
        p->auth_file = "/home/stud/Клиент/config/vclient.conf";
        p->Connect_to_server("2130706433", "33333");
        CHECK(true);
    }

    TEST_FIXTURE(Test, InvalidServerAddress) {
        //2 Неверный ip
        p->original_file = "/home/stud/Клиент/vector.bin";
        p->result_file = "/home/stud/Клиент/res.bin";
        p->auth_file = "/home/stud/Клиент/config/vclient.conf";
        CHECK_THROW(p->Connect_to_server("2215024", "33333"), error_proj);

    }

    TEST_FIXTURE(Test, InvalidServerPort) {
        //3 Неверный порт
        p->original_file = "/home/stud/Клиент/vector.bin";
        p->result_file = "/home/stud/Клиент/res.bin";
        p->auth_file = "/home/stud/Клиент/config/vclient.conf";
        CHECK_THROW(p->Connect_to_server("2130706433", "33000"), error_proj);

    }


    TEST_FIXTURE(Test, InvalidLogin) {
        //4 Введен неправильный логин
        p->original_file = "/home/stud/Клиент/vector.bin";
        p->result_file = "/home/stud/Клиент/res.bin";
        p->auth_file = "/home/stud/Клиент/config/login.conf";
        CHECK_THROW(p->Connect_to_server("2130706433", "33333"), error_proj);

    }


    TEST_FIXTURE(Test, InvalidPassword) {
        //5 Введен неправильный пароль
        p->original_file = "/home/stud/Клиент/vector.bin";
        p->result_file = "/home/stud/Клиент/res.bin";
        p->auth_file = "/home/stud/Клиент/config/pswd.conf";
        CHECK_THROW(p->Connect_to_server("2130706433", "33333"), error_proj);

    }


    TEST_FIXTURE(Test, InvalidFileOriginal) {
        //6 Ошибка открытия файла с векторами
        p->original_file = "/home/stud/Клиент/vector.txt";
        p->result_file = "/home/stud/Клиент/res.bin";
        p->auth_file = "/home/stud/Клиент/config/vclient.conf";
        CHECK_THROW(p->Connect_to_server("2130706433", "33333"), error_proj);

    }


    TEST_FIXTURE(Test, InvalidFileRes) {
        //7 Ошибка открытия файла для записи суммы
        p->original_file = "/home/stud/Клиент/vector.bin";
        p->result_file = "/home/stud/Клиент/12/res.bin";
        p->auth_file = "/home/stud/Клиент/config/vclient.conf";
        CHECK_THROW(p->Connect_to_server("2130706433", "33333"), error_proj);

    }

    TEST_FIXTURE(Test, WrongIpAddressEntered) {
        //8 Неверно введен ip-адрес
        p->original_file = "/home/stud/Клиент/vector.bin";
        p->result_file = "/home/stud/Клиент/res.bin";
        p->auth_file = "/home/stud/Клиент/config/vclient.conf";
        CHECK_THROW(p->Connect_to_server("string", "33333"), error_proj);

    }

    TEST_FIXTURE(Test, WrongPortEntered) {
        //9 Неверно введен port
        p->original_file = "/home/stud/Клиент/vector.bin";
        p->result_file = "/home/stud/Клиент/res.bin";
        p->auth_file = "/home/stud/Клиент/config/vclient.conf";
        CHECK_THROW(p->Connect_to_server("2130706433", "string"), error_proj);

    }
    TEST_FIXTURE(Test, AuthError) {
        //10 Ошибка открытия файла авторизации
        p->original_file = "/home/stud/Клиент/vector.bin";
        p->result_file = "/home/stud/Клиент/res.bin";
        p->auth_file = "/home/stud/Клиент/config/1.conf";
        CHECK_THROW(p->Connect_to_server("2130706433", "33333"), error_proj);

    }

}

int main(int argc, char **argv)
{
    return UnitTest::RunAllTests();
}
