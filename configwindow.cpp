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

#include "configwindow.h"

/**
 * Constructeur de la fenetre d'edition de la configuration de base
 */
ConfigWindow::ConfigWindow(QMainWindow *parent=0) : QDialog(parent){

    this->parent=parent;
    mbddFilePath=QDir::fromNativeSeparators(QDir::homePath()+"/.QFacturation/data.db");
    mconfigFilePath=QDir::fromNativeSeparators(QDir::homePath()+"/.QFacturation/stdConfig.xml");
    mtemplateFilePath=QDir::fromNativeSeparators(QDir::homePath()+"/.QFacturation/template.html");
    setWindowIcon(QIcon(QCoreApplication::applicationDirPath()+QDir::separator()+"img"+QDir::separator()+"icon.png"));

    QVBoxLayout *layoutPrin=new QVBoxLayout();
    /** ************************************** **/
    /**         Formulaire  societe            **/
    /** ************************************** **/

    QHBoxLayout *layoutForm=new QHBoxLayout;

    QGroupBox *groupCampagny = new QGroupBox(trUtf8("Information sur la société"), this);

    QFormLayout *layoutFormCompagny = new QFormLayout;


    companyName=new QLineEdit();
    companyName->setMinimumWidth(250);
    layoutFormCompagny->addRow(trUtf8("Nom  de la société: "),companyName);

    description=new QLineEdit();
    layoutFormCompagny->addRow(trUtf8("Déscription de votre activité: "),description);

    adress=new QLineEdit();
    layoutFormCompagny->addRow(trUtf8("Adresse: "),adress);

    adress2=new QLineEdit();
    layoutFormCompagny->addRow(trUtf8("Complément d'adresse: "),adress2);

    zipCode=new QSpinBox();
    zipCode->setMaximum(99999);
    zipCode->setMinimum(0);
    layoutFormCompagny->addRow(trUtf8("Code Postal: "),zipCode);

    city=new QLineEdit();
    layoutFormCompagny->addRow(trUtf8("Ville: "),city);

    country=new QLineEdit();
    layoutFormCompagny->addRow(trUtf8("Pays: "),country);

    phone=new QLineEdit();
    layoutFormCompagny->addRow(trUtf8("Téléphone: "),phone);

    email=new QLineEdit();
    layoutFormCompagny->addRow(trUtf8("Email: "),email);

    internetSite=new QLineEdit();
    layoutFormCompagny->addRow(trUtf8("Site internet: "),internetSite);

    siret=new QLineEdit();
    layoutFormCompagny->addRow(trUtf8("SIRET: ","Numero d'enregistrement de l'entreprise"),siret);

    ape=new QLineEdit();
    layoutFormCompagny->addRow(trUtf8("Code APE: ","Code designant l'activité de l'entreprise"),ape);

    groupCampagny->setLayout(layoutFormCompagny);
    layoutForm->addWidget(groupCampagny);
    layoutPrin->addLayout(layoutForm);

    /** ************************************** **/
    /**                 Boutons                **/
    /** ************************************** **/

    QHBoxLayout *layoutBouton=new QHBoxLayout();
    validate=new QPushButton(trUtf8("Valider"),this);
    layoutBouton->addWidget(validate);

    close=new QPushButton(trUtf8("Fermer"),this);
    layoutBouton->addWidget(close);

    layoutPrin->addLayout(layoutBouton);

    setLayout(layoutPrin);
    setModal(true);
    setWindowTitle(trUtf8("Information sur l'entreprise","titre de la popup concernant les informations de l'entreprise"));

    /** ************************************** **/
    /**                  Slots                 **/
    /** ************************************** **/

    connect(close, SIGNAL(clicked()), this, SLOT(accept()));
    connect(validate, SIGNAL(clicked()), this, SLOT(validateInfo()));
}

/**
 * Methode permettant de valider les informations
 * --> Ecriture des informations dans un fichier XML
 */
void ConfigWindow::validateInfo(){
    if(!createDatabase()){
        exit(2);
    }
    writeXMLConfigFile();
    createDocumentTemplate();

    if(parent!=NULL){
        QStatusBar *statBar = parent->statusBar();
        statBar->showMessage(trUtf8("Informations sur l'entreprise sauvegardé"), 4000);
    }
    this->accept();
}

/**
 * Methode qui ecrie le template HTML du document
 * @return true si l'ecriture a ete effectuer, false sinon
 */
bool ConfigWindow::createDocumentTemplate(){

    QFile file(mtemplateFilePath);
    if(!file.exists()){
        file.open(QIODevice::WriteOnly);
        QTextStream flux(&file);
        flux.setCodec("UTF-8");
        flux<<"<html><head><meta http-equiv='content-type' content='text/html; charset=utf-8' /><style type=\"text/css\">"<<endl;
        flux<<"#compagnyInfo{margin:5px;padding:5px;text-align:left;float:left;}"<<endl;
        flux<<"#customerInfo{float:right;text-align:right;margin:5px;padding:5px;}"<<endl;
        flux<<"#documentInfo{padding-top:10px;}"<<endl;
        flux<<"#totalPrice{font-weight:bold;text-align:right;}"<<endl;
        flux<<"#endPage{text-align:center;}"<<endl;
        flux<<".title{text-weight:bold;text-transform:uppercase;}"<<endl;
        flux<<".stopFloat{clear: both;}"<<endl;
        flux<<".emptyCell{border:none;}"<<endl;
        flux<<"table{margin:10px auto;border-collapse:collapse;width:95%;}"<<endl;
        flux<<"td,th{border:1px solid black;}"<<endl;
        flux<<"th{background-color:#BCBCBC;}</style></head>"<<endl;
        flux<<"<body>"<<endl;
        flux<<"<div id='compagnyInfo'>{compagnyName}<br/>{description}<br/>{compagnyAdress}<br/>{compagnyAdress2}<br/>{compagnyZipCode} {compagnyCity}<br/>{compagnyCountry}<br/></div>"<<endl;
        flux<<"<div id='customerInfo'>{customerName}<br/>{customerAdress}<br/>{customerAdress2}<br/>{customerZipCode} {customerCity}<br/>{customerCountry}<br/></div>"<<endl;
        flux<<"<div class=\"stopFloat\"></div>"<<endl;
        flux<<"<div id='documentInfo'><span class='title'>{documentType} N&deg; {documentId}</span> "<<trUtf8("du","document numero XX du xx/xx/xxxx")<<" {date}<br/><span class='title'>"<<trUtf8("Moyen de reglement")<<": </span>{payment}<br/></div>"<<endl;
        flux<<"<table>"<<endl;
        flux<<" <tr><th>"<<trUtf8("Nom")<<"</th><th>"<<trUtf8("Quantit&eacute;","les caracteres speciaux sont encoder en HTML")<<"</th><th>"<<trUtf8("Prix unitaire")<<"</th><th>"<<trUtf8("Prix de base")<<"</th><th>"<<trUtf8("Remise")<<"</th><th>"<<trUtf8("Prix finale")<<"</th></tr>"<<endl;
        flux<<"{product}"<<endl;
        flux<<"<tr class='emptyCell'><td colspan='5' class='emptyCell' ></td><td id='totalPrice'>"<<trUtf8("TVA")<<": {tva}<br/>"<<trUtf8("Total HT")<<": {totalPriceHT}<br/>"<<trUtf8("Total TTC")<<": {totalPriceTTC}</td></tr>"<<endl;
        flux<<"</table>"<<endl;
        flux<<"<div id='endPage'>{compagnyName}, SIRET: {siret}, Code APE: {ape}, "<<trUtf8("T&eacute;l&eacute;phone: ","les caracteres speciaux sont encoder en HTML")<<" {phone}<br/>"<<trUtf8("Email: ")<<" {email}, "<<trUtf8("Site internet: ")<<" {site}</div>"<<endl;
        flux<<"</body></html>"<<endl;
        flux.flush();
        file.close();
        return true;
    }
    else
        return false;
}

/**
 * Methode permettant de creer la base de donnees
 * @return true si la creation n'a pas eu de problème, false sinon
 */
bool ConfigWindow::createDatabase(){

    QSqlDatabase base = QSqlDatabase::database();

    if (!base.isOpen()){
        QMessageBox::critical(this,trUtf8("Erreur de création de la base de données"),base.lastError().text()+"\nVeuillez contacter votre administrateur.") ;
        return false;
    }

    if( base.tables().size()==0){
        QSqlQuery result ;
        result = base.exec("CREATE  TABLE IF NOT EXISTS product(\
                           idProduct INTEGER PRIMARY KEY,\
                           name VARCHAR(45),\
                           price REAL,\
                           description VARCHAR(255))") ;

        if(result.lastError().type()!=QSqlError::NoError){
             QMessageBox::critical(this,trUtf8("Erreur de création de la table 'product'"),result.lastError().text()+"\nVeuillez contacter votre administrateur.");
             return false;
        }

        result = base.exec("CREATE  TABLE IF NOT EXISTS customer (\
                           idCustomer INTEGER PRIMARY KEY,\
                           name VARCHAR(255),\
                           adress VARCHAR(255),\
                           adress2 VARCHAR(255),\
                           postalCode INTEGER\
                           ,city VARCHAR(255),\
                           country VARCHAR(45),\
                           email VARCHAR(255),\
                           phone VARCHAR(15))") ;

        if(result.lastError().type()!=QSqlError::NoError){
             QMessageBox::critical(this,trUtf8("Erreur de création de la table 'customer'"),result.lastError().text()+"\nVeuillez contacter votre administrateur.") ;
             return false;
        }

        result = base.exec("CREATE  TABLE IF NOT EXISTS document (\
                           idDocument INTEGER PRIMARY KEY,\
                           idCustomer INTEGER,\
                           totalPrice REAL,\
                           type VARCHAR(255),\
                           payment VARCHAR(45),\
                           tva INTEGER,\
                           date VARCHAR(45))") ;

        if(result.lastError().type()!=QSqlError::NoError){
             QMessageBox::critical(this,trUtf8("Erreur de création de la table 'document'"),result.lastError().text()+"\nVeuillez contacter votre administrateur.") ;
             return false;
        }

        result = base.exec("CREATE  TABLE IF NOT EXISTS product_document (\
                          idproduct_document INTEGER PRIMARY KEY ,\
                          idDocument INTEGER,\
                          idProduct INTEGER,\
                          reduction VARCHAR(45),\
                          quantity INTEGER )") ;

        if(result.lastError().type()!=QSqlError::NoError){
             QMessageBox::critical(this,trUtf8("Erreur de création de la table 'product_document'"),result.lastError().text()+"\nVeuillez contacter votre administrateur.") ;
             return false;
        }

        result = base.exec("CREATE  TABLE IF NOT EXISTS DocumentValide(\
                           id INTEGER PRIMARY KEY,\
                           idCustomer INTEGER,\
                           date VARCHAR(45),\
                           price REAL,\
                           type INTEGER,\
                           payment INTEGER,\
                           tva REAL,\
                           view TEXT)") ;

        if(result.lastError().type()!=QSqlError::NoError){
             QMessageBox::critical(this,trUtf8("Erreur de création de la table 'DocumentValide'"),result.lastError().text()+"\nVeuillez contacter votre administrateur.");
             return false;
        }

        base.commit();
    }

    return true;

}

/**
 * Methode qui ecrie le fichier de configuration au format XML
 */
void ConfigWindow::writeXMLConfigFile(){

    QDomDocument doc;
    QDomNode xmlNode = doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");

    doc.insertBefore(xmlNode, doc.firstChild());

    QDomElement config = doc.createElement("config");
    doc.appendChild(config);

    /** *************************** **/
    /**        Info Societe         **/
    /** *************************** **/

    QDomElement userElt = doc.createElement("user");
    config.appendChild(userElt);

    QDomElement nameElt = doc.createElement("name");
    userElt.appendChild(nameElt);
    QDomText nameText = doc.createTextNode(companyName->text());
    nameElt.appendChild(nameText);

    QDomElement infoElt = doc.createElement("info");
    userElt.appendChild(infoElt);
    QDomText infoText = doc.createTextNode(description->text());
    infoElt.appendChild(infoText);

    QDomElement adressElt = doc.createElement("adress");
    userElt.appendChild(adressElt);
    QDomText adressText = doc.createTextNode(adress->text());
    adressElt.appendChild(adressText);

    QDomElement adress2Elt = doc.createElement("adress2");
    userElt.appendChild(adress2Elt);
    QDomText adress2Text = doc.createTextNode(adress2->text());
    adress2Elt.appendChild(adress2Text);

    QDomElement zipCodeElt = doc.createElement("zipCode");
    userElt.appendChild(zipCodeElt);
    QDomText zipCodeText = doc.createTextNode(QString::number(zipCode->value()));
    zipCodeElt.appendChild(zipCodeText);

    QDomElement cityElt = doc.createElement("city");
    userElt.appendChild(cityElt);
    QDomText cityText = doc.createTextNode(city->text());
    cityElt.appendChild(cityText);

    QDomElement countryElt = doc.createElement("country");
    userElt.appendChild(countryElt);
    QDomText countryText = doc.createTextNode(country->text());
    countryElt.appendChild(countryText);

    QDomElement phoneElt = doc.createElement("phone");
    userElt.appendChild(phoneElt);
    QDomText phoneText = doc.createTextNode(phone->text());
    phoneElt.appendChild(phoneText);

    QDomElement emailElt = doc.createElement("email");
    userElt.appendChild(emailElt);
    QDomText emailText = doc.createTextNode(email->text());
    emailElt.appendChild(emailText);

    QDomElement internetSiteElt = doc.createElement("internetSite");
    userElt.appendChild(internetSiteElt);
    QDomText internetSiteText = doc.createTextNode(internetSite->text());
    internetSiteElt.appendChild(internetSiteText);

    QDomElement siretElt = doc.createElement("siret");
    userElt.appendChild(siretElt);
    QDomText siretText = doc.createTextNode(siret->text());
    siretElt.appendChild(siretText);

    QDomElement apeElt = doc.createElement("ape");
    userElt.appendChild(apeElt);
    QDomText apeText = doc.createTextNode(ape->text());
    apeElt.appendChild(apeText);

    /** *************************** **/
    /**                             **/
    /** *************************** **/

    QFile file(mconfigFilePath);
    file.open(QIODevice::WriteOnly);
    QTextStream ts(&file);
    ts.setCodec("UTF-8");
    doc.save(ts, 4);
}

/**
 * Methode permettant d'initialiser les champs grâce au
 * informations contenue dans le fichier de configuration
 */
void ConfigWindow::initByConfigFile(){

    QFile file(mconfigFilePath);
    file.open(QFile::ReadOnly | QFile::Text);

    QDomDocument doc;
    doc.setContent(&file, false);

    QDomElement racine = doc.documentElement();
    racine = racine.firstChildElement();

    if(racine.tagName() == "user")
    {
        // On récupère le premier enfant de l'élément site c'est a dire <nom> ou <url>
        QDomElement elt = racine.firstChildElement();

        // On parcourt tous les enfants de l'élément <site>
        while(!elt.isNull())
        {
            if(elt.tagName() == "name")
                 companyName->setText(elt.text());
            else if(elt.tagName() == "info")
                description->setText(elt.text());
            else if(elt.tagName() == "adress")
                adress->setText(elt.text());
            else if(elt.tagName() == "adress2")
                adress2->setText(elt.text());
            else if(elt.tagName() == "zipCode")
                zipCode->setValue(elt.text().toInt());
            else if(elt.tagName() == "city")
                city->setText(elt.text());
            else if(elt.tagName() == "country")
                country->setText(elt.text());
            else if(elt.tagName() == "phone")
                phone->setText(elt.text());
            else if(elt.tagName() == "email")
                email->setText(elt.text());
            else if(elt.tagName() == "internetSite")
                internetSite->setText(elt.text());
            else if(elt.tagName() == "siret")
                siret->setText(elt.text());
            else if(elt.tagName() == "ape")
                ape->setText(elt.text());

            elt = elt.nextSiblingElement();
        }
    }
}
