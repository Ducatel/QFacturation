#include "customer.h"

Customer::Customer()
{
    name="";
    adress="";
    adress2="";
    city="";
    country="";
    email="";
    phone="";
    postalCode=-1;
    id=-1;
}

Customer::Customer(int identifiant){
    QSqlDatabase base = QSqlDatabase::addDatabase("QSQLITE");
    base.setDatabaseName(QDir::fromNativeSeparators(QDir::homePath()+"/.QFacturation/data.db"));
    base.open();

    QSqlQuery query;
    query.prepare("select * from customer where idCustomer=:id");
    query.bindValue(":id",identifiant);
    query.exec();

    query.next();
    QSqlRecord rec = query.record();

    name=rec.value("name").toString();
    adress=rec.value("adress").toString();
    adress2=rec.value("adress2").toString();
    city=rec.value("city").toString();
    country=rec.value("country").toString();
    email=rec.value("email").toString();
    phone=rec.value("phone").toString();
    postalCode=rec.value("postalCode").toInt();
    this->id=identifiant;

    base.commit();
    base.close();
    QSqlDatabase::removeDatabase(QDir::fromNativeSeparators(QDir::homePath()+"/.QFacturation/data.db"));
}

int Customer::getId(){
    return id;
}

bool Customer::save(){
    QSqlDatabase base = QSqlDatabase::addDatabase("QSQLITE");
    base.setDatabaseName(QDir::fromNativeSeparators(QDir::homePath()+"/.QFacturation/data.db"));
    if(!base.open())
        return false;

    QSqlQuery query;
    bool retour=false;

    if(id==-1){
        //ici on fait l'insertion

        query.prepare("insert into customer (name,adress,adress2,postalCode,city,country,email,phone) values (:name,:adress,:adress2,:postalCode,:city,:country,:email,:phone )");
        query.bindValue(":name",name);
        query.bindValue(":adress",adress);
        query.bindValue(":adress2",adress2);
        query.bindValue(":postalCode",postalCode);
        query.bindValue(":city",city);
        query.bindValue(":country",country);
        query.bindValue(":email",email);
        query.bindValue(":phone",phone);

        retour=query.exec();
        base.commit();

        if(retour)
         id=query.lastInsertId().toInt();
    }
    else{
        //ici on fait un update;
        query.prepare("UPDATE customer SET name=:name, adress=:adress, adress2=:adress2, postalCode=:postalCode, city=:city, country=:country,email=:email,phone=:phone WHERE idCustomer=:id ");
        query.bindValue(":name",name);
        query.bindValue(":adress",adress);
        query.bindValue(":adress2",adress2);
        query.bindValue(":postalCode",postalCode);
        query.bindValue(":city",city);
        query.bindValue(":country",country);
        query.bindValue(":email",email);
        query.bindValue(":phone",phone);
        query.bindValue(":id",id);

        retour=query.exec();
        base.commit();
    }

    base.close();
    QSqlDatabase::removeDatabase(QDir::fromNativeSeparators(QDir::homePath()+"/.QFacturation/data.db"));

    return retour;
}



