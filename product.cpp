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

#include "product.h"

/**
 * Constructeur simple
 * Utilise pour creer un nouveau produit
 */
Product::Product(){
    name="";
    description="";
    price=0.0;
    id=-1;
}

/**
 * Constructeur qui initialise le produit par rapport au info contenu dans la BDD
 * @param identifiant, identifiant du produit au sein de la BDD
 */
Product::Product(int identifiant){
    QSqlDatabase base = QSqlDatabase::database();
    QSqlQuery query;
    query.prepare("SELECT * FROM product WHERE idProduct=:id");
    query.bindValue(":id",identifiant);
    query.exec();

    query.next();
    QSqlRecord rec = query.record();

    name=rec.value("name").toString();
    price=rec.value("price").toDouble();
    description=rec.value("description").toString();
    this->id=identifiant;

    query.finish();
    base.commit();
}

/**
 * Methode qui sauvegarde un produit dans la base de données
 * @return true si l'enregistrement n'a pas poser de probleme, false sinon
 */
bool Product::save(){

    QSqlDatabase base = QSqlDatabase::database();
    bool retour=false;

    if(id==-1){
        retour=createEntry();
    }
    else{
        retour=updateEntry();
    }

    base.commit();
    return retour;
}

int Product::getId(){
    return id;
}

/**
 * Methode qui permet de mettre a jour un produit dans la BDD
 * @return true si l'enregistrement n'a pas poser de probleme, false sinon
 */
bool Product::updateEntry(){
    QSqlQuery query;

    query.prepare("UPDATE product SET name=:name, price=:price,description=:description WHERE idProduct=:id ");
    query.bindValue(":name",name);
    query.bindValue(":price",price);
    query.bindValue(":description",description);
    query.bindValue(":id",id);

    bool retour=query.exec();
    query.finish();
    return retour;

}

/**
 * Methode qui permet de creer un produit dans la BDD
 * @return true si l'enregistrement n'a pas poser de probleme, false sinon
 */
bool Product::createEntry(){

    QSqlQuery query;
    bool retour=false;

    query.prepare("INSERT INTO product (name,price,description) VALUES (:name,:price,:description )");
    query.bindValue(":name",name);
    query.bindValue(":price",price);
    query.bindValue(":description",description);

    retour=query.exec();

    if(retour)
        id=query.lastInsertId().toInt();

    query.finish();

    return retour;
}

QList<Product> Product::getAllProduct(){
    QList<Product> list;

    QSqlDatabase base = QSqlDatabase::database();
    QSqlQuery query;
    query.exec("SELECT idProduct FROM product ORDER BY idProduct");

    while(query.next()){
        Product p(query.record().value("idProduct").toInt());
        list.append(p);
    }

    query.finish();
    base.commit();
    return list;
}

/**
 * Methode qui met a jour le prix total des documents qui utilise
 * le produit courant
 */
void Product::updateDocumentPrice(){
    QSqlDatabase base = QSqlDatabase::database();
    QSqlQuery query;

    query.prepare("SELECT idDocument FROM product_document WHERE idProduct=:idProd GROUP BY idDocument");
    query.bindValue(":idProd",this->id);
    query.exec();

    while(query.next()){
        QSqlRecord rec = query.record();
        int idDoc=rec.value("idDocument").toInt();

        Document d(idDoc);
        d.save();
    }

    query.finish();
    base.commit();
}
