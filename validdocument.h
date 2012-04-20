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

#ifndef VALIDDOCUMENT_H
#define VALIDDOCUMENT_H
#include <QtSql>
#include <QDate>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QDomDocument>
#include <QDomElement>
#include <QList>
#include <QVariant>

#include "document.h"
#include "customer.h"
#include "productdocument.h"
#include "product.h"

#define qDebug(msg) qDebug() << Q_FUNC_INFO << msg

/**
 * Class qui gere les document valider
 * @author David Ducatel
 */
class ValidDocument
{
    public:
        ValidDocument(Document d);
        ValidDocument(int identifiant);

        bool save();
        int getId();
        void print();
        bool transform(Document::PaymentEnum typePayment);

        QDate date;
        double price;
        Document::DocTypeEnum docType;
        Document::PaymentEnum payment;
        QString view;
        int idCustomer;
        int idDocument;

    private:
        int id;
        QString makeView();
        QString loadTemplate();
        QString initDocumentInfo(QString string);
        QString initCompagnyInfo(QString string);
        QString initCustomerInfo(QString string);
        QString initProductInfo(QString string);
        bool createEntry();
        bool updateEntry();

};

#endif // VALIDDOCUMENT_H
