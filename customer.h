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

#include <QString>
#include <QDir>
#include <QList>
#include <QVariant>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>

#define qDebug(msg) qDebug() << Q_FUNC_INFO << msg


/**
 * Class qui permet de gerer un client
 * @author David Ducatel
 */
class Customer
{
    public:
        Customer();
        Customer(int identifiant);
        static QList<Customer> getAllCustomer();

        QString m_name;
        QString m_adress;
        QString m_adress2;
        QString m_city;
        QString m_country;
        QString m_email;
        QString m_phone;
        int m_postalCode;

        int getId();
        bool save();

    private:
        int id;
        bool updateEntry();
        bool createEntry();

};

#endif // CUSTOMER_H
