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
    mdate=d.getDate();
    price=d.getTotalPrice();
    docType=d.m_docType;
    payment=d.m_payment;
    idCustomer=d.m_idCustomer;
    idDocument=d.getId();
    id=-1;
    view=makeView();
    tva=d.m_tva;
}

ValidDocument::ValidDocument(int identifiant){
    QSqlDatabase base = QSqlDatabase::database();

    QSqlQuery query;
    query.prepare("SELECT * FROM DocumentValide where id=:id");
    query.bindValue(":id",identifiant);
    query.exec();
    query.next();

    QSqlRecord rec = query.record();

    idCustomer=rec.value("idCustomer").toInt();
    price=rec.value("price").toDouble();
    view=rec.value("view").toString();

    docType=(rec.value("type").toInt()==Document::Devis)?Document::Devis:Document::Facture;

    int tmpPayment=rec.value("payment").toInt();
    if(tmpPayment==Document::Cheque)
        payment=Document::Cheque;
    else if(tmpPayment==Document::Virement)
        payment=Document::Virement;
    else
        payment=Document::Especes;

    tva=rec.value("tva").toDouble();
    mdate=QDate::fromString(rec.value("date").toString(),"yyyy-MM-dd");
    this->id=identifiant;

    idDocument=-1;


    query.finish();
    base.commit();

}

/**
 * Methode qui sauvegarde un document valider dans la base de données
 * @return true si l'enregistrement n'a pas poser de probleme, false sinon
 */
bool ValidDocument::save(){
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


bool ValidDocument::createEntry(){
    QSqlDatabase base = QSqlDatabase::database();
    bool retour=false;

    QSqlQuery query;
    query.prepare("INSERT INTO DocumentValide (idCustomer,price,type,payment,date,view,tva) VALUES (:idCustomer,:price,:type,:payment,:date,:view,:tva )");
    query.bindValue(":idCustomer",idCustomer);
    query.bindValue(":price",price);
    query.bindValue(":type",docType);
    query.bindValue(":payment",payment);
    query.bindValue(":date",mdate.toString("yyyy-MM-dd"));
    query.bindValue(":view",view);
    query.bindValue(":tva",tva);

    retour=query.exec();

    if(retour)
        id=query.lastInsertId().toInt();

    query.finish();
    base.commit();


    Document d(idDocument);
    d.remove();


    return retour;

}

/**
 * Methode qui permet de mettre a jour un document dans la BDD
 * appeler pour la transformation devis-> facture
 * @return true si l'enregistrement n'a pas poser de probleme, false sinon
 */
bool ValidDocument::updateEntry(){
    QSqlQuery query;

    query.prepare("UPDATE DocumentValide SET type=:type, payment=:payment, date=:date , view=:view WHERE id=:id ");
    query.bindValue(":type",docType);
    query.bindValue(":payment",payment);
    query.bindValue(":view",view);
    query.bindValue(":id",this->id);
    query.bindValue(":date",QDate::currentDate().toString("yyyy-MM-dd"));

    bool retour=query.exec();
    query.finish();
    return retour;

}

int ValidDocument::getId(){
    return this->id;
}

/**
 * Methode permettant d'imprimer un document
 */
void ValidDocument::print(){

    QWebView webView;
    QPrinter printer ;

    printer.setPageSize(QPrinter::A4);
    printer.setFullPage(true);
    QString type=(docType==Document::Facture)?QObject::trUtf8("Facture"):QObject::trUtf8("Devis");
    printer.setDocName(type+"_"+QString::number(id) );
    printer.setCreator(QObject::trUtf8("QFacturation"));
    printer.setOutputFormat(QPrinter::NativeFormat);

    webView.setHtml(view);
    webView.show();
    QPrintDialog printDialog(&printer);
    if(printDialog.exec() == QDialog::Accepted) {
        qDebug("Ne fonctionne pas sous windows")<<" Hack ....";

        #if defined(Q_WS_WIN)
            QTextDocument text;
            text.setHtml(view);
            text.print(&printer);
        #endif
        #if defined(Q_WS_QWS)
            webView.print(&printer);
        #endif
        #if defined(Q_WS_X11)
            webView.print(&printer);
        #endif
    }

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
    Customer c(d.m_idCustomer);

    string.replace("{customerName}",c.m_name);
    string.replace("{customerAdress}",c.m_adress);
    string.replace("{customerAdress2}",c.m_adress2);
    string.replace("{customerZipCode}",QVariant(c.m_postalCode).toString());
    string.replace("{customerCity}",c.m_city);
    string.replace("{customerCountry}",c.m_country);

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


    QString type=(d.m_docType==Document::Facture)?QObject::trUtf8("Facture"):QObject::trUtf8("Devis");
    string.replace("{documentType}",type);

    if(d.m_docType==Document::Facture){
        if(d.m_payment==Document::Cheque)
            string.replace("{payment}",QObject::trUtf8("Cheque"));
        else if(d.m_payment==Document::Virement)
            string.replace("{payment}",QObject::trUtf8("Virement"));
        else
            string.replace("{payment}",QObject::trUtf8("Espece"));
    }
    else{
        string.replace("{payment}",QObject::trUtf8("Non précisé"));
    }

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

        if(prod.description.isEmpty())
            productView+="<tr><td>"+prod.name+"</td>";
        else
            productView+="<tr><td rowspan='2'>"+prod.name+"</td>";


        productView+="<td>"+QVariant(prodDoc.quantity).toString()+"</td>";
        productView+="<td>"+QVariant(prod.price).toString()+"&euro;</td>";
        productView+="<td>"+QVariant(priceWithoutReduction).toString()+"&euro;</td>";
        productView+="<td>"+prodDoc.reduction+"</td>";
        productView+="<td>"+QVariant(priceWithReduction).toString()+"&euro;</td></tr>";

        if(!prod.description.isEmpty())
            productView+="<tr><td colspan='6'>&rarr; "+prod.description+"</td>";
    }
    string.replace("{product}",productView);

    Document d(idDocument);

    QString tvaHTML=QVariant(d.m_tva).toString()+"%";
    string.replace("{tva}",tvaHTML);

    double priceHT=d.getTotalPrice();
    QString totalPriceHT=QString::number(priceHT)+"&euro;";
    string.replace("{totalPriceHT}",totalPriceHT);

    double prixTTC=((priceHT*d.m_tva)/100.0)+priceHT;
    QString totalPriceTTC=QString::number(prixTTC)+"&euro;";
    string.replace("{totalPriceTTC}",totalPriceTTC);

    return string;
}

/**
 * Methode permettant de transformer un devis en facture
 * @param typePayment moyen de paiement a mettre sur la facture
 * @return true si la transformation a ete effectué, false sinon
 */
bool ValidDocument::transform(Document::PaymentEnum typePayment){
    if(docType==Document::Facture)
        return false;

    payment=typePayment;
    if(payment==Document::Cheque)
        view.replace(QObject::trUtf8("Non précisé"),QObject::trUtf8("Cheque"));
    else if(payment==Document::Virement)
        view.replace(QObject::trUtf8("Non précisé"),QObject::trUtf8("Virement"));
    else
        view.replace(QObject::trUtf8("Non précisé"),QObject::trUtf8("Espece"));

    docType=Document::Facture;
    view.replace(QObject::trUtf8("Devis"),QObject::trUtf8("Facture"));

    return save();

}
