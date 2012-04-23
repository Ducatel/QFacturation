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

#ifndef DOCUMENT_H
#define DOCUMENT_H

#include<QtSql>
#include<QString>
#include<QDir>
#include<QDate>

#define qDebug(msg) qDebug() << Q_FUNC_INFO << msg

#include "product.h"
#include "productdocument.h"

/**
 * Class qui gere un document (devis ou facture)
 * @author David Ducatel
 */
class Document
{
    public:
        Document();
        Document(int identifiant);
        int getId();
        QString getDateInString();
        QDate getDate();
        bool remove();
        bool save();
        double getTotalPrice();
        bool addProduct(int idProduct,int quantity,QString reduction);


        enum DocTypeEnum{
            Facture=0,
            Devis=1
        };

        enum PaymentEnum{
            Cheque=0,
            Especes=1,
            Virement=2
        };

        int idCustomer;
        DocTypeEnum docType;
        PaymentEnum payment;
        double tva;


    private:
        int id;
        QDate date;
        bool updateEntry();
        bool createEntry();


};

#endif // DOCUMENT_H
