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
    QSqlDatabase base = QSqlDatabase::addDatabase("QSQLITE");
    base.setDatabaseName(QDir::fromNativeSeparators(QDir::homePath()+"/.QFacturation/data.db"));
    base.open();

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

    base.commit();
    base.close();
    QSqlDatabase::removeDatabase(QDir::fromNativeSeparators(QDir::homePath()+"/.QFacturation/data.db"));
}

/**
 * Methode qui sauvegarde un produit dans la base de données
 * @return true si l'enregistrement n'a pas poser de probleme, false sinon
 */
bool Product::save(){

    QSqlDatabase base = QSqlDatabase::addDatabase("QSQLITE");
    base.setDatabaseName(QDir::fromNativeSeparators(QDir::homePath()+"/.QFacturation/data.db"));
    if(!base.open())
        return false;

    bool retour=false;

    if(id==-1){
        retour=createEntry();
    }
    else{
        retour=updateEntry();
    }

    base.commit();
    base.close();
    QSqlDatabase::removeDatabase(QDir::fromNativeSeparators(QDir::homePath()+"/.QFacturation/data.db"));

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

    return query.exec();
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

    return retour;


}
