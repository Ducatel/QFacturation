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
    idCustomer=d.idCustomer;
    idDocument=d.getId();
    id=-1;
    view=makeView();
    qDebug(view);
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

/**
 * Methode qui va generer le rendu HTML
 * du document
 * @return le rendu HTML du document
 */
QString ValidDocument::makeView(){
    QString page=loadTemplate();
    page=initCompagnyInfo(page);
    page=initDocumentInfo(page);
    page=initCustomerInfo(page);
    page=initProductInfo(page);
    return page;
}

/**
 * Methode qui retourne le template HTML des documents
 * @return le template HTML
 */
QString ValidDocument::loadTemplate(){
    QFile file(QDir::fromNativeSeparators(QDir::homePath()+"/.QFacturation/template.html"));
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream flux(&file);
    QString content=flux.readAll();
    flux.flush();
    file.close();
    return content;
}

/**
 * Methode qui initialise les informations de la societe dans le template
 * @param string le template
 * @return le template initialise
 */
QString ValidDocument::initCompagnyInfo(QString string){
    QFile file(QDir::fromNativeSeparators(QDir::homePath()+"/.QFacturation/stdConfig.xml"));
    file.open(QFile::ReadOnly | QFile::Text);

    QDomDocument doc;
    doc.setContent(&file, false);

    QDomElement racine = doc.documentElement();
    racine = racine.firstChildElement();

    if(racine.tagName() == "user") {
        QDomElement elt = racine.firstChildElement();
        while(!elt.isNull()){
            if(elt.tagName() == "name")
                string.replace("{compagnyName}",elt.text());
            else if(elt.tagName() == "info")
                string.replace("{description}",elt.text());
            else if(elt.tagName() == "adress")
                string.replace("{compagnyAdress}",elt.text());
            else if(elt.tagName() == "adress2")
                string.replace("{compagnyAdress2}",elt.text());
            else if(elt.tagName() == "zipCode")
                string.replace("{compagnyZipCode}",elt.text());
            else if(elt.tagName() == "city")
                string.replace("{compagnyCity}",elt.text());
            else if(elt.tagName() == "country")
                string.replace("{compagnyCountry}",elt.text());
            else if(elt.tagName() == "phone")
                string.replace("{phone}",elt.text());
            else if(elt.tagName() == "email")
                string.replace("{email}",elt.text());
            else if(elt.tagName() == "internetSite")
                string.replace("{site}",elt.text());
            else if(elt.tagName() == "siret")
                string.replace("{siret}",elt.text());
            else if(elt.tagName() == "ape")
                string.replace("{ape}",elt.text());

            elt = elt.nextSiblingElement();
        }
    }
    file.close();

    return string;
}

/**
 * Methode qui initialise les informations du client dans le template
 * @param string le template
 * @return le template initialise
 */
QString ValidDocument::initCustomerInfo(QString string){
    Document d(idDocument);
    Customer c(d.idCustomer);

    string.replace("{customerName}",c.name);
    string.replace("{customerAdress}",c.adress);
    string.replace("{customerAdress2}",c.adress2);
    string.replace("{customerZipCode}",QVariant(c.postalCode).toString());
    string.replace("{customerCity}",c.city);
    string.replace("{customerCountry}",c.country);

    return string;
}

/**
 * Methode qui initialise les informations du document dans le template
 * @param string le template
 * @return le template initialise
 */
QString ValidDocument::initDocumentInfo(QString string){
    Document d(idDocument);
    string.replace("{date}",d.getDateInString());
    string.replace("{documentId}",QVariant(d.getId()).toString());


    QString type=(d.docType==Document::Facture)?QObject::tr("Facture"):QObject::tr("Devis");
    string.replace("{documentType}",type);

    if(d.payment==Document::Cheque)
        string.replace("{payment}",QObject::tr("Cheque"));
    else if(d.payment==Document::Virement)
        string.replace("{payment}",QObject::tr("Virement"));
    else
        string.replace("{payment}",QObject::tr("Espece"));

    return string;
}


/**
 * Methode qui initialise les produits dans le template
 * @param string le template
 * @return le template initialise
 */
QString ValidDocument::initProductInfo(QString string){

    QList<ProductDocument> listProdDoc=ProductDocument::getAllByIdDocument(idDocument);

    QString productView="";
    for(int i=0;i<listProdDoc.size();i++){
        ProductDocument prodDoc=listProdDoc.at(i);
        Product prod(prodDoc.idProduct);

        double priceWithoutReduction=prod.price*prodDoc.quantity;

        double reduction=0.0;
        if(prodDoc.reduction.endsWith('%')){
           double pourcentage=prodDoc.reduction.mid(0,prodDoc.reduction.size()-1).toDouble();
           reduction=((prodDoc.quantity*prod.price)*pourcentage)/100.0;
        }
        else
            reduction=prodDoc.reduction.toDouble();

        double priceWithReduction=prodDoc.quantity*prod.price-reduction;

        productView+="<tr><td>"+prod.name+"</td>";
        productView+="<td>"+QVariant(prodDoc.quantity).toString()+"</td>";
        productView+="<td>"+QVariant(prod.price).toString()+"&euro;</td>";
        productView+="<td>"+QVariant(priceWithoutReduction).toString()+"&euro;</td>";
        productView+="<td>"+prodDoc.reduction+"</td>";
        productView+="<td>"+QVariant(priceWithReduction).toString()+"&euro;</td></tr>";
    }
    string.replace("{product}",productView);

    Document d(idDocument);
    QString totalPrice=QVariant(d.getTotalPrice()).toString()+"&euro;";
    string.replace("{totalPrice}",totalPrice);

    return string;
}
