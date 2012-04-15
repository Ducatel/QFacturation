#ifndef CUSTOMER_H
#define CUSTOMER_H

#include<QtSql>
#include<QString>
#include<QDir>

class Customer
{
    public:
        Customer();
        Customer(int identifiant);

        QString name;
        QString adress;
        QString adress2;
        QString city;
        QString country;
        QString email;
        QString phone;
        int postalCode;

        int getId();
        bool save();

    private:
        int id;

};

#endif // CUSTOMER_H
