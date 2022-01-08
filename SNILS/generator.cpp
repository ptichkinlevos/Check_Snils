#include <iostream>
#include "functions.h"

using namespace std;

void recordcheck_in_db(char *snils) //Функция записи полученного СНИЛСа в БД, где snils - сгенерированный СНИЛС
{
    {
        QSqlDatabase db=connect_database(); //Подключаемся к БД
        db.open(); //Открываем БД
        {
            QSqlQuery query(QSqlDatabase::database("Connect_1")); //Создаём запрос query, относящийся к соединению с именем Connect_1
            QVariant value; //Строка, которая будет отправлена в БД
            string h; //Строка h, содержащая СНИЛС
            h.append(snils); //Переписываем snils в h
            value=QString::fromStdString(h); //Переписываем h в value
            query.prepare("INSERT INTO data (snils) VALUES (?)"); //Обращаемся к столбцу snils таблцы data
            query.addBindValue(value); //Вставляем в свободное значение столбца значение переменной value
            query.exec(); //Подтверждаем операцию
        }
        db.close(); //Закрываем работу с запросами в БД
    }
    QSqlDatabase::removeDatabase("Connect_1"); //Разрываем соединение Connect_1 с БД
}

void generate_snils_ss() //Функция, для генерации СНИЛСов, которые покрывают тесты к функциям check_ss, count_ss
{
    for(int k=0;k!=12;) //Выполняем цикл пока k!=12, где k - счётчик количества СНИЛСов
    {
        char symbols[]="0123456789"; //Массив для генерации рандомной цифры
        char snils[14]; //Массив, содержащий СНИЛС
        char *point=snils; //Указатель на СНИЛС
        for (int i=0;i<12;i++) //Генерируем первые 12 символов для СНИЛСА
        {
            if(i==3||i==7) //Расстановка дефисов в СНИЛСе
            {
                snils[i]='-';
                continue;
            }
            if(i==11) //Расстановка пробела в СНИЛСе
            {
                snils[i]=' ';
                continue;
            }
            snils[i]=symbols[rand()%10]; //Генерация рандомной цифры
        }
        int S=0; //Объявим сумму S равную нулю
        for(int i=0,p=9;i<14;i++) //Цикл для подсчёта суммы первых 9 цифр СНИЛСА, где p - номер позиции цифры (исходная позиция = 9)
        {
            if(snils[i]!='-'&&i<11) //Если элемент массива не дефис и его номер меньше 11
            {
                S=S+((snils[i]-'0')*p); //Умножение цифры на позицию, где snils[i]-'0' - преобразования символа в цифру
                p--;
            }
        }
        if(S<100&&k<2) //Записываем в БД 2 СНИЛСа с правильно посчитанной КС
        {
            snils[12]=S/10+'0';
            snils[13]=S%10+'0';
            point[14]='\0'; //Закрываем массив snils завершающим нулём
            recordcheck_in_db(snils);
            k++;
            continue;
        }
        if(S<100&&k<4) //Записываем в БД 2 СНИЛСа с неправильно посчитанной КС
        {
            do
            {
                snils[12]=symbols[rand()%10];
                snils[13]=symbols[rand()%10];
            }
            while((S/10+'0')==snils[12]&&(S%10+'0')==snils[13]); //Генерируем рандомную КС до тех пор пока она равна правильной
            point[14]='\0';
            recordcheck_in_db(snils);
            k++;
            continue;
        }
        if(S==100&&k==4) //Записываем в БД 1 СНИЛС с правильно посчитанной КС
        {
            snils[12]='0';
            snils[13]='0';
            point[14]='\0';
            recordcheck_in_db(snils);
            k++;
            continue;
        }
        if(S==100&&k==5) //Записываем в БД 1 СНИЛС с неправильно посчитанной КС
        {
            do
            {
                snils[12]=symbols[rand()%10];
                snils[13]=symbols[rand()%10];
            }
            while(snils[12]=='0'&&snils[13]=='0'); //Генерируем рандомную КС до тех пор пока она равна правильной (00)
            point[14]='\0';
            recordcheck_in_db(snils);
            k++;
            continue;
        }
        if(S==101&&k==6) //Записываем в БД 1 СНИЛС с правильно посчитанной КС
        {
            snils[12]='0';
            snils[13]='0';
            point[14]='\0';
            recordcheck_in_db(snils);
            k++;
            continue;
        }
        if(S==101&&k==7) //Записываем в БД 1 СНИЛС с неправильно посчитанной КС
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
        if(S>101&&k==8&&k!=10) //Записываем в БД 2 СНИЛСа с правильно посчитанной КС
        {
            do
            {
                S=S%101; //Берём остаток от деления на первичной суммы на 101
            }
            while(S>101); //Берём остаток деления S на 101 пока этот остаток больше 101
            if(S==100||S==101) //Если остаток равен 101 или 100 то КС равна 00
            {
                snils[12]='0';
                snils[13]='0';
            }
            if(S<100) //Если остаток меньше 100 то КС равна этому остатку
            {
                snils[12]=S/10+'0';
                snils[13]=S%10+'0';
            }
            point[14]='\0';
            recordcheck_in_db(snils);
            k++;
            continue;
        }
        if(S>101&&k==10&&k!=12) //Записываем в БД 2 СНИЛСа с неправильно посчитанной КС
        {
            do
            {
                S=S%101; //Берём остаток от деления на первичной суммы на 101
            }
            while(S>101); //Берём остаток деления S на 101 пока этот остаток больше 101
            do
            {
                snils[12]=symbols[rand()%10];
                snils[13]=symbols[rand()%10];
            }
            while((snils[12]==S/10+'0'&&snils[13]==S%10+'0')||(snils[12]=='0'&&snils[13]=='0'));
            //Генерируем случайную КС до тех пор пока она равна правильной в ситуации, когда КС < 100 или КС = 100, 101
            point[14]='\0';
            recordcheck_in_db(snils);
            k++;
            continue;
        }
    }
}

void generate_snils_in() //Функция, для генерации СНИЛСов, которые покрывают тесты к функции check_in
{
    {
        char symbols[]="0123456789";
        char snils[14];
        char *point=snils;
        for (int i=0;i<13;i++) //Генерируем 13 символов СНИЛСа
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
        for (int i=0;i<14;i++) //Генерируем все 14 символов СНИЛСа, где вместо пробела будет дефис
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
        for (int i=0;i<14;i++) //Генерируем все 14 символов СНИЛСа, где все символы это цифры
        {
            snils[i]=symbols[rand()%10];
        }
        point[14]='\0';
        recordcheck_in_db(snils);
    }
    {
        char symbols[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"; //Английский алфавит с маленькой и большой буквы
        char snils[14];
        char *point=snils;
        for (int i=0;i<14;i++) //Генерируем 14 рандомных английских букв
        {
            snils[i]=symbols[rand()%52];
        }
        point[14]='\0';
        recordcheck_in_db(snils);
    }
}

void call_generator() //Функция, вызывающая другие функции
{
    generate_snils_ss();
    generate_snils_in();
}
