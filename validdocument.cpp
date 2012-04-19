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

#include "validdocument.h"

ValidDocument::ValidDocument(Document d){
    date=d.getDate();
    price=d.getTotalPrice();
    docType=d.docType;
    payment=d.payment;
    view=makeView();
    idCustomer=d.idCustomer;
    idDocument=d.getId();
    id=-1;
}

bool ValidDocument::save(){
    QSqlDatabase base = QSqlDatabase::database();
    bool retour=false;

    QSqlQuery query;
    query.prepare("INSERT INTO DocumentValide (idCustomer,price,type,payment,date,view) VALUES (:idCustomer,:price,:type,:payment,:date,:view )");
    query.bindValue(":idCustomer",idCustomer);
    query.bindValue(":price",price);
    query.bindValue(":type",docType);
    query.bindValue(":payment",payment);
    query.bindValue(":date",date.toString("yyyy-MM-dd"));
    query.bindValue(":view",view);

    retour=query.exec();

    if(retour)
        id=query.lastInsertId().toInt();

    query.finish();
    base.commit();

    Document d(idDocument);
    d.remove();

    return retour;

}

int ValidDocument::getId(){
    return this->id;
}

void ValidDocument::print(){

}


QString ValidDocument::makeView(){
    QString s="";



    return s;
}
