#ifndef PRODUCT_H
#define PRODUCT_H

#include<QtSql>
#include<QString>
#include<QDir>

/**
 * Class qui permet de gerer un produit
 * @author David Ducatel
 */
class Product
{
    public:
        Product();
        Product(int identifiant);

        QString name;
        QString description;
        double price;

        int getId();
        bool save();
    private:
        int id;
        bool updateEntry();
        bool createEntry();

};

#endif // PRODUCT_H
