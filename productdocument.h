#ifndef PRODUCTDOCUMENT_H
#define PRODUCTDOCUMENT_H

#include<QtSql>
#include<QString>
#include<QDir>

/**
 * class qui gere la table de jointure entre
 * les produits et les documents
 * @author David Ducatel
 */
class ProductDocument
{
    public:
        ProductDocument();
        ProductDocument(int identifiant);
        int getId();
        bool save();
        bool remove();

        int idDocument;
        int idProduct;
        int quantity;

        QString reduction;

    private:
        int id;
        bool updateEntry();
        bool createEntry();

};

#endif // PRODUCTDOCUMENT_H
