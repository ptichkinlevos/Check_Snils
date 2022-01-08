#include <iostream>
#include <QtSql>
#include "windows.h"
#include "functions.h"
#include "generator.cpp"

using namespace std;

int main()
{
    SetConsoleCP(1251); //Обработка русских символов при вводе
    SetConsoleOutputCP(1251); //Обработка русских символов при выводе
    string answer; //Строка answer - содержащая ответ: Да или Нет на вопрос в строке main.cpp (13)
    cout<<"Хотите проверить СНИЛС самостоятельно ?: ";
    cin>>answer;
    cin.ignore(INT_MAX, '\n'); //Очищаем cin от переменной answer
    if(answer=="Нет")
    {
        srand(time(0));
        call_generator(); //Генерируем СНИЛСы в базу данных
        {
            QSqlDatabase db=connect_database(); //Подключаемся к БД
            db.open(); //Открываем БД
            QSqlQuery query(QSqlDatabase::database("Connect_1")); //Создаём запрос query, относящийся к соединению с именем Connect_1
            query.exec("SELECT * FROM data"); //Выполняем запрос SELECT для таблицы data, выводящий все строки и столбцы
            while (query.next()) //Пока не достигнута последняя запись в БД. Начальное позиция 1 запись в БД
            {
                QString record=query.value("snils").toString(); //Записываем в record значение столбца snils
                autocheck_snils(record); //Выполняем автопроверку СНИЛСа
            }
            db.close(); //Закрываем БД
        }
        QSqlDatabase::removeDatabase("Connect_1"); //Разрываем соединение Connect_1 с БД
    }
    if(answer=="Да")
    {
        manualcheck_snils(); //Выполняем ручную проверку СНИЛСА
    }
    system("pause");
    return 0;
}
