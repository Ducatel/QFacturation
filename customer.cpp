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
    m_name="";
    m_adress="";
    m_adress2="";
    m_city="";
    m_country="";
    m_email="";
    m_phone="";
    m_postalCode=-1;
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

    m_name=rec.value("name").toString();
    m_adress=rec.value("adress").toString();
    m_adress2=rec.value("adress2").toString();
    m_city=rec.value("city").toString();
    m_country=rec.value("country").toString();
    m_email=rec.value("email").toString();
    m_phone=rec.value("phone").toString();
    m_postalCode=rec.value("postalCode").toInt();
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
    query.bindValue(":name",m_name);
    query.bindValue(":adress",m_adress);
    query.bindValue(":adress2",m_adress2);
    query.bindValue(":postalCode",m_postalCode);
    query.bindValue(":city",m_city);
    query.bindValue(":country",m_country);
    query.bindValue(":email",m_email);
    query.bindValue(":phone",m_phone);
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
    query.bindValue(":name",m_name);
    query.bindValue(":adress",m_adress);
    query.bindValue(":adress2",m_adress2);
    query.bindValue(":postalCode",m_postalCode);
    query.bindValue(":city",m_city);
    query.bindValue(":country",m_country);
    query.bindValue(":email",m_email);
    query.bindValue(":phone",m_phone);
    retour=query.exec();

    if(retour)
     id=query.lastInsertId().toInt();

    query.finish();
    return retour;

}

QList<Customer> Customer::getAllCustomer(){
    QList<Customer> list;

    QSqlDatabase base = QSqlDatabase::database();
    QSqlQuery query;
    query.exec("SELECT idCustomer FROM customer ORDER BY idCustomer");

    while(query.next()){
        Customer c(query.record().value("idCustomer").toInt());
        list.append(c);
    }

    query.finish();
    base.commit();
    return list;
}

