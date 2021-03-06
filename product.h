/**
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see http://www.gnu.org/licenses
 */

#ifndef PRODUCT_H
#define PRODUCT_H

#include<QtSql>
#include<QString>
#include<QDir>

#define qDebug(msg) qDebug() << Q_FUNC_INFO << msg

#include "document.h"
/**
 * Class qui permet de gerer un produit
 * @author David Ducatel
 */
class Product
{
    public:
        Product();
        Product(int identifiant);
        static QList<Product> getAllProduct();

        QString name;
        QString description;
        double price;

        int getId();
        bool save();
        void updateDocumentPrice();
    private:
        int id;
        bool updateEntry();
        bool createEntry();

};

#endif // PRODUCT_H
