#include <iostream>
#include <QtSql>
#include "windows.h"
#include "functions.h"
#include "generator.cpp"

using namespace std;

int main()
{
    SetConsoleCP(1251); //��������� ������� �������� ��� �����
    SetConsoleOutputCP(1251); //��������� ������� �������� ��� ������
    string answer; //������ answer - ���������� �����: �� ��� ��� �� ������ � ������ main.cpp (13)
    cout<<"������ ��������� ����� �������������� ?: ";
    cin>>answer;
    cin.ignore(INT_MAX, '\n'); //������� cin �� ���������� answer
    if(answer=="���")
    {
        srand(time(0));
        call_generator(); //���������� ������ � ���� ������
        {
            QSqlDatabase db=connect_database(); //������������ � ��
            db.open(); //��������� ��
            QSqlQuery query(QSqlDatabase::database("Connect_1")); //������ ������ query, ����������� � ���������� � ������ Connect_1
            query.exec("SELECT * FROM data"); //��������� ������ SELECT ��� ������� data, ��������� ��� ������ � �������
            while (query.next()) //���� �� ���������� ��������� ������ � ��. ��������� ������� 1 ������ � ��
            {
                QString record=query.value("snils").toString(); //���������� � record �������� ������� snils
                autocheck_snils(record); //��������� ������������ ������
            }
            db.close(); //��������� ��
        }
        QSqlDatabase::removeDatabase("Connect_1"); //��������� ���������� Connect_1 � ��
    }
    if(answer=="��")
    {
        manualcheck_snils(); //��������� ������ �������� ������
    }
    system("pause");
    return 0;
}
