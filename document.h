#ifndef DOCUMENT_H
#define DOCUMENT_H

#include<QtSql>
#include<QString>
#include<QDir>
#include<QDate>

/**
 * Class qui gere un document (devis ou facture)
 * @author David Ducatel
 */
class Document
{
    public:
        Document();
        int getId();
        QString getDateInString();
        QDate getDate();
        double getTotalPrice;

        enum DocTypeEnum{
            Facture,
            Devis
        };

        enum PaymentEnum{
            Cheque,
            Especes,
            Virement,
            None
        };

        int idCustomer;
        DocTypeEnum docType;
        PaymentEnum payment;
        bool addProduct();
        bool removeProduct();


    private:
        int id;
        QDate date;








};

#endif // DOCUMENT_H
