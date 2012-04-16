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

#include "customer.h"

/**
 * Constructeur simple
 * Utilise pour creer un nouveau client
 */
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

/**
 * Constructeur qui initialise le client par rapport au info contenu dans la BDD
 * @param identifiant, identifiant du client au sein de la BDD
 */
Customer::Customer(int identifiant){

    QSqlDatabase base = QSqlDatabase::database();
    QSqlQuery query;
    query.prepare("SELECT * FROM customer WHERE idCustomer=:id");
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

    query.finish();
    base.commit();

}

int Customer::getId(){
    return id;
}

/**
 * Methode qui sauvegarde l'utilisateur dans la base de données
 * @return true si l'enregistrement n'a pas poser de probleme, false sinon
 */
bool Customer::save(){


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
 * Methode qui permet de mettre a jour un utilisateur dans la BDD
 * @return true si l'enregistrement n'a pas poser de probleme, false sinon
 */
bool Customer::updateEntry(){

    QSqlQuery query;
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

    bool retour= query.exec();
    query.finish();
    return retour;

}

/**
 * Methode qui permet de creer un utilisateur dans la BDD
 * @return true si l'enregistrement n'a pas poser de probleme, false sinon
 */
bool Customer::createEntry(){
    QSqlQuery query;
    bool retour=false;

    query.prepare("INSERT INTO customer (name,adress,adress2,postalCode,city,country,email,phone) VALUES (:name,:adress,:adress2,:postalCode,:city,:country,:email,:phone )");
    query.bindValue(":name",name);
    query.bindValue(":adress",adress);
    query.bindValue(":adress2",adress2);
    query.bindValue(":postalCode",postalCode);
    query.bindValue(":city",city);
    query.bindValue(":country",country);
    query.bindValue(":email",email);
    query.bindValue(":phone",phone);
    retour=query.exec();

    if(retour)
     id=query.lastInsertId().toInt();

    query.finish();
    return retour;

}


