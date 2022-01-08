#include <iostream>
#include "functions.h"

using namespace std;

void recordcheck_in_db(char *snils) //������� ������ ����������� ������ � ��, ��� snils - ��������������� �����
{
    {
        QSqlDatabase db=connect_database(); //������������ � ��
        db.open(); //��������� ��
        {
            QSqlQuery query(QSqlDatabase::database("Connect_1")); //������ ������ query, ����������� � ���������� � ������ Connect_1
            QVariant value; //������, ������� ����� ���������� � ��
            string h; //������ h, ���������� �����
            h.append(snils); //������������ snils � h
            value=QString::fromStdString(h); //������������ h � value
            query.prepare("INSERT INTO data (snils) VALUES (?)"); //���������� � ������� snils ������ data
            query.addBindValue(value); //��������� � ��������� �������� ������� �������� ���������� value
            query.exec(); //������������ ��������
        }
        db.close(); //��������� ������ � ��������� � ��
    }
    QSqlDatabase::removeDatabase("Connect_1"); //��������� ���������� Connect_1 � ��
}

void generate_snils_ss() //�������, ��� ��������� �������, ������� ��������� ����� � �������� check_ss, count_ss
{
    for(int k=0;k!=12;) //��������� ���� ���� k!=12, ��� k - ������� ���������� �������
    {
        char symbols[]="0123456789"; //������ ��� ��������� ��������� �����
        char snils[14]; //������, ���������� �����
        char *point=snils; //��������� �� �����
        for (int i=0;i<12;i++) //���������� ������ 12 �������� ��� ������
        {
            if(i==3||i==7) //����������� ������� � ������
            {
                snils[i]='-';
                continue;
            }
            if(i==11) //����������� ������� � ������
            {
                snils[i]=' ';
                continue;
            }
            snils[i]=symbols[rand()%10]; //��������� ��������� �����
        }
        int S=0; //������� ����� S ������ ����
        for(int i=0,p=9;i<14;i++) //���� ��� �������� ����� ������ 9 ���� ������, ��� p - ����� ������� ����� (�������� ������� = 9)
        {
            if(snils[i]!='-'&&i<11) //���� ������� ������� �� ����� � ��� ����� ������ 11
            {
                S=S+((snils[i]-'0')*p); //��������� ����� �� �������, ��� snils[i]-'0' - �������������� ������� � �����
                p--;
            }
        }
        if(S<100&&k<2) //���������� � �� 2 ������ � ��������� ����������� ��
        {
            snils[12]=S/10+'0';
            snils[13]=S%10+'0';
            point[14]='\0'; //��������� ������ snils ����������� ����
            recordcheck_in_db(snils);
            k++;
            continue;
        }
        if(S<100&&k<4) //���������� � �� 2 ������ � ����������� ����������� ��
        {
            do
            {
                snils[12]=symbols[rand()%10];
                snils[13]=symbols[rand()%10];
            }
            while((S/10+'0')==snils[12]&&(S%10+'0')==snils[13]); //���������� ��������� �� �� ��� ��� ���� ��� ����� ����������
            point[14]='\0';
            recordcheck_in_db(snils);
            k++;
            continue;
        }
        if(S==100&&k==4) //���������� � �� 1 ����� � ��������� ����������� ��
        {
            snils[12]='0';
            snils[13]='0';
            point[14]='\0';
            recordcheck_in_db(snils);
            k++;
            continue;
        }
        if(S==100&&k==5) //���������� � �� 1 ����� � ����������� ����������� ��
        {
            do
            {
                snils[12]=symbols[rand()%10];
                snils[13]=symbols[rand()%10];
            }
            while(snils[12]=='0'&&snils[13]=='0'); //���������� ��������� �� �� ��� ��� ���� ��� ����� ���������� (00)
            point[14]='\0';
            recordcheck_in_db(snils);
            k++;
            continue;
        }
        if(S==101&&k==6) //���������� � �� 1 ����� � ��������� ����������� ��
        {
            snils[12]='0';
            snils[13]='0';
            point[14]='\0';
            recordcheck_in_db(snils);
            k++;
            continue;
        }
        if(S==101&&k==7) //���������� � �� 1 ����� � ����������� ����������� ��
        {
            do
            {
                snils[12]=symbols[rand()%10];
                snils[13]=symbols[rand()%10];
            }
            while(snils[12]=='0'&&snils[13]=='0');
            point[14]='\0';
            recordcheck_in_db(snils);
            k++;
            continue;
        }
        if(S>101&&k==8&&k!=10) //���������� � �� 2 ������ � ��������� ����������� ��
        {
            do
            {
                S=S%101; //���� ������� �� ������� �� ��������� ����� �� 101
            }
            while(S>101); //���� ������� ������� S �� 101 ���� ���� ������� ������ 101
            if(S==100||S==101) //���� ������� ����� 101 ��� 100 �� �� ����� 00
            {
                snils[12]='0';
                snils[13]='0';
            }
            if(S<100) //���� ������� ������ 100 �� �� ����� ����� �������
            {
                snils[12]=S/10+'0';
                snils[13]=S%10+'0';
            }
            point[14]='\0';
            recordcheck_in_db(snils);
            k++;
            continue;
        }
        if(S>101&&k==10&&k!=12) //���������� � �� 2 ������ � ����������� ����������� ��
        {
            do
            {
                S=S%101; //���� ������� �� ������� �� ��������� ����� �� 101
            }
            while(S>101); //���� ������� ������� S �� 101 ���� ���� ������� ������ 101
            do
            {
                snils[12]=symbols[rand()%10];
                snils[13]=symbols[rand()%10];
            }
            while((snils[12]==S/10+'0'&&snils[13]==S%10+'0')||(snils[12]=='0'&&snils[13]=='0'));
            //���������� ��������� �� �� ��� ��� ���� ��� ����� ���������� � ��������, ����� �� < 100 ��� �� = 100, 101
            point[14]='\0';
            recordcheck_in_db(snils);
            k++;
            continue;
        }
    }
}

void generate_snils_in() //�������, ��� ��������� �������, ������� ��������� ����� � ������� check_in
{
    {
        char symbols[]="0123456789";
        char snils[14];
        char *point=snils;
        for (int i=0;i<13;i++) //���������� 13 �������� ������
        {
            if(i==3||i==7)
            {
                snils[i]='-';
                continue;
            }
            if(i==11)
            {
                snils[i]=' ';
                continue;
            }
            snils[i]=symbols[rand()%10];
        }
        point[13]='\0';
        recordcheck_in_db(snils);
    }
    {
        char symbols[]="0123456789";
        char snils[14];
        char *point=snils;
        for (int i=0;i<14;i++) //���������� ��� 14 �������� ������, ��� ������ ������� ����� �����
        {
            if(i==3||i==7)
            {
                snils[i]='-';
                continue;
            }
            if(i==11)
            {
                snils[i]='-';
                continue;
            }
            snils[i]=symbols[rand()%10];
        }
        point[14]='\0';
        recordcheck_in_db(snils);
    }
    {
        char symbols[]="0123456789";
        char snils[14];
        char *point=snils;
        for (int i=0;i<14;i++) //���������� ��� 14 �������� ������, ��� ��� ������� ��� �����
        {
            snils[i]=symbols[rand()%10];
        }
        point[14]='\0';
        recordcheck_in_db(snils);
    }
    {
        char symbols[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"; //���������� ������� � ��������� � ������� �����
        char snils[14];
        char *point=snils;
        for (int i=0;i<14;i++) //���������� 14 ��������� ���������� ����
        {
            snils[i]=symbols[rand()%52];
        }
        point[14]='\0';
        recordcheck_in_db(snils);
    }
}

void call_generator() //�������, ���������� ������ �������
{
    generate_snils_ss();
    generate_snils_in();
}
