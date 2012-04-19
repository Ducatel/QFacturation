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

#include "document.h"

Document::Document(){
    idCustomer=-1;
    id=-1;
    date=QDate::currentDate();
    docType=Document::Facture;
    payment=Document::Cheque;
}

Document::Document(int identifiant){

    QSqlDatabase base = QSqlDatabase::database();

    QSqlQuery query;
    query.prepare("SELECT * FROM document where idDocument=:id");
    query.bindValue(":id",identifiant);
    query.exec();
    query.next();

    QSqlRecord rec = query.record();

    idCustomer=rec.value("idCustomer").toInt();
    docType=(rec.value("type").toInt()==Document::Devis)?Document::Devis:Document::Facture;

    int tmpPayment=rec.value("payment").toInt();
    if(tmpPayment==Document::Cheque)
        payment=Document::Cheque;
    else if(tmpPayment==Document::Virement)
        payment=Document::Virement;
    else
        payment=Document::Especes;

    date=QDate::fromString(rec.value("date").toString(),"yyyy-MM-dd");
    this->id=identifiant;

    query.finish();
    base.commit();
}

int Document::getId(){
    return this->id;
}

/**
 * Methode qui sauvegarde un document dans la base de données
 * @return true si l'enregistrement n'a pas poser de probleme, false sinon
 */
bool Document::save(){
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
 * Methode qui permet de mettre a jour un document dans la BDD
 * @return true si l'enregistrement n'a pas poser de probleme, false sinon
 */
bool Document::updateEntry(){
    QSqlQuery query;

    query.prepare("UPDATE document SET idCustomer=:idCustomer, totalPrice=:totalPrice, type=:type, payment=:payment, date=:date WHERE idDocument=:id ");    
    query.bindValue(":idCustomer",idCustomer);
    query.bindValue(":totalPrice",getTotalPrice());
    query.bindValue(":type",docType);
    query.bindValue(":payment",payment);
    query.bindValue(":date",date.toString("yyyy-MM-dd"));
    query.bindValue(":id",this->id);

    bool retour=query.exec();
    query.finish();
    return retour;

}

/**
 * Methode qui permet de creer un document dans la BDD
 * @return true si l'enregistrement n'a pas poser de probleme, false sinon
 */
bool Document::createEntry(){

    QSqlQuery query;
    bool retour=false;

    query.prepare("INSERT INTO document (idCustomer,totalPrice,type,payment,date) VALUES (:idCustomer,:totalPrice,:type,:payment,:date )");
    query.bindValue(":idCustomer",idCustomer);
    query.bindValue(":totalPrice",getTotalPrice());
    query.bindValue(":type",docType);
    query.bindValue(":payment",payment);
    query.bindValue(":date",date.toString("yyyy-MM-dd"));

    retour=query.exec();

    if(retour)
        id=query.lastInsertId().toInt();

    query.finish();

    return retour;
}

bool Document::remove(){
    bool removeLink=ProductDocument::removeAllByIdDocument(id);

    QSqlDatabase base = QSqlDatabase::database();

    QSqlQuery query;
    query.prepare("DELETE FROM document WHERE idDocument=:id ");
    query.bindValue(":id",id);
    bool remove=query.exec();

    query.finish();

    base.commit();
    return (remove && removeLink );
}

double Document::getTotalPrice(){
    QList<ProductDocument> list=ProductDocument::getAllByIdDocument(id);

    double result=0.0;
    for(int i=0;i<list.size();i++){
        ProductDocument prodDoc=list.at(i);
        Product prod(prodDoc.idProduct);

        double reduction=0.0;
        if(prodDoc.reduction.endsWith('%')){
           double pourcentage=prodDoc.reduction.mid(0,prodDoc.reduction.size()-1).toDouble();
           reduction=((prodDoc.quantity*prod.price)*pourcentage)/100.0;
        }
        else
            reduction=prodDoc.reduction.toDouble();

        result+=prodDoc.quantity*prod.price-reduction;
    }

    return result;
}

bool Document::addProduct(int idProduct,int quantity,QString reduction){
    ProductDocument prodDoc;

    prodDoc.idDocument=this->id;
    prodDoc.idProduct=idProduct;
    prodDoc.quantity=quantity;
    prodDoc.reduction=reduction;
    bool addProd=prodDoc.save();

    return (save() && addProd);
}

QDate Document::getDate(){
    return date;
}

QString Document::getDateInString(){
    return date.toString("dd/MM/yyyy");
}



