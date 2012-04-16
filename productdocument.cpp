#include "productdocument.h"

/**
 * Constructeur simple
 * Utilise pour creer une liaison entre produit et document
 */
ProductDocument::ProductDocument()
{
    id=-1;
    idDocument=-1;
    idProduct=-1;
    reduction="";
    quantity=0;
}

/**
 * Constructeur qui initialise la liaison produit<-->document grace au info contenu dans la BDD
 * @param identifiant, identifiant de la liaison au sein de la BDD
 */
ProductDocument::ProductDocument(int identifiant){

    QSqlDatabase base = QSqlDatabase::database();
    QSqlQuery query;
    query.prepare("SELECT * FROM product_document WHERE idProduct_document=:id");
    query.bindValue(":id",identifiant);
    query.exec();

    query.next();
    QSqlRecord rec = query.record();

    idDocument=rec.value("idDocument").toInt();
    idProduct=rec.value("idProduct").toInt();
    reduction=rec.value("reduction").toString();
    quantity=rec.value("quantity").toInt();
    this->id=identifiant;

    query.finish();
    base.commit();
}

int ProductDocument::getId(){
    return id;
}

/**
 * Methode qui sauvegarde une laison dans la base de données
 * @return true si l'enregistrement n'a pas poser de probleme, false sinon
 */
bool ProductDocument::save(){
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

/**
 * Methode qui permet de supprimer une liaison produit<-->document
 * @return true si la suppression n'a pas poser de probleme, false sinon
 */
bool ProductDocument::remove(){
    QSqlDatabase base = QSqlDatabase::database();

    QSqlQuery query;
    query.prepare("DELETE FROM product_document WHERE idProduct_document=:id ");
    query.bindValue(":id",id);
    bool retour=query.exec();

    query.finish();

    base.commit();
    return retour;

}

/**
 * Methode qui permet de mettre a jour une liaison dans la BDD
 * @return true si l'enregistrement n'a pas poser de probleme, false sinon
 */
bool ProductDocument::updateEntry(){
    QSqlQuery query;

    query.prepare("UPDATE product_document SET idDocument=:idDocument, idProduct=:idProduct,reduction=:reduction, quantity=:quantity WHERE idProduct_document=:id ");
    query.bindValue(":idDocument",idDocument);
    query.bindValue(":idProduct",idProduct);
    query.bindValue(":reduction",reduction);
    query.bindValue(":quantity",quantity);
    query.bindValue(":id",id);

    bool retour=query.exec();
    query.finish();
    return retour;
}

/**
 * Methode qui permet de creer une liaison document<-->produit dans la BDD
 * @return true si l'enregistrement n'a pas poser de probleme, false sinon
 */
bool ProductDocument::createEntry(){
    QSqlQuery query;
    bool retour=false;

    query.prepare("INSERT INTO product_document (idDocument,idProduct,reduction,quantity) VALUES (:idDocument,:idProduct,:reduction,:quantity )");
    query.bindValue(":idDocument",idDocument);
    query.bindValue(":idProduct",idProduct);
    query.bindValue(":reduction",reduction);
    query.bindValue(":quantity",quantity);

    retour=query.exec();

    if(retour)
        id=query.lastInsertId().toInt();

    query.finish();

    return retour;
}


