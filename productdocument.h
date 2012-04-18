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

#ifndef PRODUCTDOCUMENT_H
#define PRODUCTDOCUMENT_H

#include<QtSql>
#include<QString>
#include<QDir>

#define qDebug(msg) qDebug() << Q_FUNC_INFO << msg


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
        ProductDocument(int identifiantProduct,int identifiantDocument);

        int getId();
        bool save();
        bool remove();
        static bool removeAllByIdDocument(int identifiant);
        static QList<ProductDocument> getAllByIdDocument(int identifiant);

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
