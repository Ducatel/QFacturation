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

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include<QtSql>
#include<QString>
#include<QDir>

/**
 * Class qui permet de gerer un client
 * @author David Ducatel
 */
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
        bool updateEntry();
        bool createEntry();

};

#endif // CUSTOMER_H
