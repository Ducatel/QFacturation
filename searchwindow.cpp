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

#include "searchwindow.h"

/**
 * Constructeur de l'interface de recherche
 * @param parent, pointeur vers la fenetre principale
 */
SearchWindow::SearchWindow(QMainWindow *parent) :QWidget(parent){
    this->parent=parent;

    QHBoxLayout *layoutPrinc=new QHBoxLayout;
    QVBoxLayout *subLayout1=new QVBoxLayout;
    QVBoxLayout *subLayout2=new QVBoxLayout;

    /** ******************************* **/
    /**     Partie Recherche Client     **/
    /** ******************************* **/

    subLayout1->addWidget(createCustomerSearchInterface());

    /** ******************************* **/
    /**    Partie Recherche Produit     **/
    /** ******************************* **/

    subLayout1->addWidget(createProductSearchInterface());

    /** ***************************************** **/
    /**   Partie Recherche document non valider   **/
    /** ***************************************** **/

    subLayout2->addWidget(createNotValidateDocumentSearchInterface());

    /** ***************************************** **/
    /**     Partie Recherche document valider     **/
    /** ***************************************** **/

    subLayout2->addWidget(createValidateDocumentSearchInterface());


    layoutPrinc->addLayout(subLayout1);
    layoutPrinc->addLayout(subLayout2);

    setLayout(layoutPrinc);

}

/**
 * Methode permettant de construire la partie interface
 * de recherche client
 * @return le QGroupBox contenant l'interface
 */
QGroupBox* SearchWindow::createCustomerSearchInterface(){

    QGroupBox *groupClient = new QGroupBox(trUtf8("Rechercher un client"), this);
    QVBoxLayout *layoutClient= new QVBoxLayout;


    QFormLayout *layoutFormClient=new QFormLayout;

    typeSearchClient= new QComboBox(this);
    typeSearchClient->addItem(trUtf8("Nom"));
    typeSearchClient->addItem(trUtf8("Ville"));
    typeSearchClient->addItem(trUtf8("Code postal"));
    typeSearchClient->addItem(trUtf8("Numéro de téléphone"));
    layoutFormClient->addRow(trUtf8("Rechercher par: "),typeSearchClient);

    lineSearchClient=new QLineEdit(this);
    layoutFormClient->addRow(trUtf8("Mots clés: "),lineSearchClient);


    QHBoxLayout *layoutButtonCustomer=new QHBoxLayout;

    searchButtonCustomer=new QPushButton(trUtf8("Rechercher"),this);
    layoutButtonCustomer->addWidget(searchButtonCustomer);

    editButtonCustomer=new QPushButton(trUtf8("Editer le client sélectionné"),this);
    layoutButtonCustomer->addWidget(editButtonCustomer);

    layoutFormClient->addRow(trUtf8("Action: "),layoutButtonCustomer);


    layoutClient->addLayout(layoutFormClient);

    /***********************************************/

    QHBoxLayout *layoutTabClient= new QHBoxLayout;
    customerModel = new QStandardItemModel(0, 9);
    customerModel->setHeaderData(0,Qt::Horizontal,"id");
    customerModel->setHeaderData(1,Qt::Horizontal,trUtf8("Nom"));
    customerModel->setHeaderData(2,Qt::Horizontal,trUtf8("Adresse"));
    customerModel->setHeaderData(3,Qt::Horizontal,trUtf8("Complément"));
    customerModel->setHeaderData(4,Qt::Horizontal,trUtf8("Code postal"));
    customerModel->setHeaderData(5,Qt::Horizontal,trUtf8("Ville"));
    customerModel->setHeaderData(6,Qt::Horizontal,trUtf8("Pays"));
    customerModel->setHeaderData(7,Qt::Horizontal,trUtf8("Email"));
    customerModel->setHeaderData(8,Qt::Horizontal,trUtf8("Téléphone"));


    customerView = new QTableView(this);
    customerView->verticalHeader()->hide();
    customerView->setModel(customerModel);
    customerView->setSelectionMode(QAbstractItemView::SingleSelection);
    customerView->setSelectionBehavior(QAbstractItemView::SelectRows);
    customerView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    loadCustomer();

    layoutTabClient->addWidget(customerView);
    layoutClient->addLayout(layoutTabClient);

    groupClient->setLayout(layoutClient);

    /** ******************************* **/
    /**             Slots               **/
    /** ******************************* **/
    connect(editButtonCustomer, SIGNAL(clicked()), this, SLOT(editCustomer()));
    connect(searchButtonCustomer, SIGNAL(clicked()), this, SLOT(showCustomerResult()));

    return groupClient;
}

/**
 * Methode permettant de construire la partie interface
 * de recherche produit
 * @return le QGroupBox contenant l'interface
 */
QGroupBox* SearchWindow::createProductSearchInterface(){
    QVBoxLayout *layoutProduct= new QVBoxLayout;
    QGroupBox *groupProduct = new QGroupBox(trUtf8("Rechercher un Produit"), this);

    QFormLayout *layoutFormProduct=new QFormLayout;

    typeSearchProduct= new QComboBox(this);
    typeSearchProduct->addItem(trUtf8("Nom"));
    typeSearchProduct->addItem(trUtf8("Prix HT"));

    layoutFormProduct->addRow(trUtf8("Rechercher par: "),typeSearchProduct);

    lineSearchProduct=new QLineEdit(this);
    layoutFormProduct->addRow(trUtf8("Mots clés: "),lineSearchProduct);


    QHBoxLayout *layoutButtonProduct=new QHBoxLayout;

    searchButtonProduct=new QPushButton(trUtf8("Rechercher"),this);
    layoutButtonProduct->addWidget(searchButtonProduct);

    editButtonProduct=new QPushButton(trUtf8("Editer le produit sélectionné"),this);
    layoutButtonProduct->addWidget(editButtonProduct);

    layoutFormProduct->addRow(trUtf8("Action: "),layoutButtonProduct);


    layoutProduct->addLayout(layoutFormProduct);

    /***********************************************/

    QHBoxLayout *layoutTabProduct= new QHBoxLayout;
    productModel = new QStandardItemModel(0, 4);
    productModel->setHeaderData(0,Qt::Horizontal,"id");
    productModel->setHeaderData(1,Qt::Horizontal,trUtf8("Nom"));
    productModel->setHeaderData(2,Qt::Horizontal,trUtf8("Prix HT"));
    productModel->setHeaderData(3,Qt::Horizontal,trUtf8("Description"));

    productView = new QTableView(this);
    productView->verticalHeader()->hide();
    productView->setModel(productModel);
    productView->setSelectionMode(QAbstractItemView::SingleSelection);
    productView->setSelectionBehavior(QAbstractItemView::SelectRows);
    productView->setEditTriggers(QAbstractItemView::NoEditTriggers);


    loadProduct();

    layoutTabProduct->addWidget(productView);
    layoutProduct->addLayout(layoutTabProduct);

    groupProduct->setLayout(layoutProduct);

    /** ******************************* **/
    /**             Slots               **/
    /** ******************************* **/

    connect(editButtonProduct, SIGNAL(clicked()), this, SLOT(editProduct()));
    connect(searchButtonProduct, SIGNAL(clicked()), this, SLOT(showProductResult()));

    return groupProduct;
}

/**
 * Methode permettant de construire la partie interface
 * de recherche d'un document non validé
 * @return le QGroupBox contenant l'interface
 */
QGroupBox* SearchWindow::createNotValidateDocumentSearchInterface(){

    QVBoxLayout *layoutDoc= new QVBoxLayout;
    QGroupBox *groupDoc = new QGroupBox(trUtf8("Rechercher un document non validé"), this);
    QFormLayout *layoutFormDoc=new QFormLayout;

    typeSearchDocumentNotValidate=new QComboBox(this);
    typeSearchDocumentNotValidate->addItem(trUtf8("Nom de client"));
    typeSearchDocumentNotValidate->addItem(trUtf8("Date"));
    typeSearchDocumentNotValidate->addItem(trUtf8("Prix HT"));

    layoutFormDoc->addRow(trUtf8("Rechercher par: "),typeSearchDocumentNotValidate);

    typeDocumentNotValidate=new QComboBox(this);
    typeDocumentNotValidate->addItem(trUtf8("Tout"));
    typeDocumentNotValidate->addItem(trUtf8("Facture"));
    typeDocumentNotValidate->addItem(trUtf8("Devis"));

    layoutFormDoc->addRow(trUtf8("Type de document: "),typeDocumentNotValidate);

    paymentDocumentNotValidate=new QComboBox(this);
    paymentDocumentNotValidate->addItem(trUtf8("Tout"));
    paymentDocumentNotValidate->addItem(trUtf8("Cheque"));
    paymentDocumentNotValidate->addItem(trUtf8("Virement"));
    paymentDocumentNotValidate->addItem(trUtf8("Espece"));

    layoutFormDoc->addRow(trUtf8("Moyen de paiement: "),paymentDocumentNotValidate);


    lineSearchDocumentNotValidate=new QLineEdit(this);
    layoutFormDoc->addRow(trUtf8("Mots clés: "),lineSearchDocumentNotValidate);

    QGridLayout *layoutButtonDoc=new QGridLayout;

    searchButtonDocumentNotValidate=new QPushButton(trUtf8("Rechercher"),this);
    layoutButtonDoc->addWidget(searchButtonDocumentNotValidate,0,0);

    editButtonDocumentNotValidate=new QPushButton(trUtf8("Editer le document sélectionné"),this);
    layoutButtonDoc->addWidget(editButtonDocumentNotValidate,0,1);

    validateDocumentButton=new QPushButton(trUtf8("Valider le document sélectionné"),this);
    layoutButtonDoc->addWidget(validateDocumentButton,1,0);

    deleteButtonDocumentNotValidate=new QPushButton(trUtf8("Supprimer le document sélectionné"),this);
    layoutButtonDoc->addWidget(deleteButtonDocumentNotValidate,1,1);

    layoutFormDoc->addRow(trUtf8("Action: "),layoutButtonDoc);

    layoutDoc->addLayout(layoutFormDoc);

    /***********************************************************/

    QHBoxLayout *layoutTabDoc= new QHBoxLayout;
    documentNotValidateModel = new QStandardItemModel(0, 7);
    documentNotValidateModel->setHeaderData(0,Qt::Horizontal,"id");
    documentNotValidateModel->setHeaderData(1,Qt::Horizontal,trUtf8("Nom du client"));
    documentNotValidateModel->setHeaderData(2,Qt::Horizontal,trUtf8("Prix HT"));
    documentNotValidateModel->setHeaderData(3,Qt::Horizontal,trUtf8("Date"));
    documentNotValidateModel->setHeaderData(4,Qt::Horizontal,trUtf8("Type de document"));
    documentNotValidateModel->setHeaderData(5,Qt::Horizontal,trUtf8("Moyen de paiement"));
    documentNotValidateModel->setHeaderData(6,Qt::Horizontal,trUtf8("TVA"));

    documentNotValidateView = new QTableView(this);
    documentNotValidateView->verticalHeader()->hide();
    documentNotValidateView->setModel(documentNotValidateModel);
    documentNotValidateView->setSelectionMode(QAbstractItemView::SingleSelection);
    documentNotValidateView->setSelectionBehavior(QAbstractItemView::SelectRows);
    documentNotValidateView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    loadDocumentNotValidate();

    layoutTabDoc->addWidget(documentNotValidateView);
    layoutDoc->addLayout(layoutTabDoc);

    groupDoc->setLayout(layoutDoc);

    /** ******************************* **/
    /**             Slots               **/
    /** ******************************* **/

    connect(searchButtonDocumentNotValidate, SIGNAL(clicked()), this, SLOT(showDocumentNotValideResult()));
    connect(editButtonDocumentNotValidate, SIGNAL(clicked()), this, SLOT(editDocument()));
    connect(validateDocumentButton, SIGNAL(clicked()), this, SLOT(valideDocument()));
    connect(deleteButtonDocumentNotValidate, SIGNAL(clicked()), this, SLOT(deleteDocument()));



    return groupDoc;
}


/**
 * Methode permettant de construire la partie interface
 * de recherche d'un document validé
 * @return le QGroupBox contenant l'interface
 */
QGroupBox* SearchWindow::createValidateDocumentSearchInterface(){

    QVBoxLayout *layoutDoc= new QVBoxLayout;
    QGroupBox *groupDoc = new QGroupBox(trUtf8("Rechercher un document validé"), this);
    QFormLayout *layoutFormDoc=new QFormLayout;

    typeSearchDocumentValidate=new QComboBox(this);
    typeSearchDocumentValidate->addItem(trUtf8("Nom de client"));
    typeSearchDocumentValidate->addItem(trUtf8("Date"));
    typeSearchDocumentValidate->addItem(trUtf8("Prix HT"));

    layoutFormDoc->addRow(trUtf8("Rechercher par: "),typeSearchDocumentValidate);

    typeDocumentValidate=new QComboBox(this);
    typeDocumentValidate->addItem(trUtf8("Tout"));
    typeDocumentValidate->addItem(trUtf8("Facture"));
    typeDocumentValidate->addItem(trUtf8("Devis"));

    layoutFormDoc->addRow(trUtf8("Type de document: "),typeDocumentValidate);

    paymentDocumentValidate=new QComboBox(this);
    paymentDocumentValidate->addItem(trUtf8("Tout"));
    paymentDocumentValidate->addItem(trUtf8("Cheque"));
    paymentDocumentValidate->addItem(trUtf8("Virement"));
    paymentDocumentValidate->addItem(trUtf8("Espece"));

    layoutFormDoc->addRow(trUtf8("Moyen de paiement: "),paymentDocumentValidate);


    lineSearchDocumentValidate=new QLineEdit(this);
    layoutFormDoc->addRow(trUtf8("Mots clés: "),lineSearchDocumentValidate);

    QGridLayout *layoutButtonDoc = new QGridLayout;

    searchButtonDocumentValidate=new QPushButton(trUtf8("Rechercher"),this);
    layoutButtonDoc->addWidget(searchButtonDocumentValidate,0,0,1,2);

    printButtonDocumentValidate=new QPushButton(trUtf8("Imprimer le document sélectionné"),this);
    layoutButtonDoc->addWidget(printButtonDocumentValidate,1,0);

    transformDocumentButton=new QPushButton(trUtf8("Transformer un devis en facture"),this);
    layoutButtonDoc->addWidget(transformDocumentButton,1,1);


    layoutFormDoc->addRow(trUtf8("Action: "),layoutButtonDoc);

    layoutDoc->addLayout(layoutFormDoc);

    /***********************************************************/

    QHBoxLayout *layoutTabDoc= new QHBoxLayout;
    documentValidateModel = new QStandardItemModel(0, 7);
    documentValidateModel->setHeaderData(0,Qt::Horizontal,"id");
    documentValidateModel->setHeaderData(1,Qt::Horizontal,trUtf8("Nom du client"));
    documentValidateModel->setHeaderData(2,Qt::Horizontal,trUtf8("Prix HT"));
    documentValidateModel->setHeaderData(3,Qt::Horizontal,trUtf8("Date"));
    documentValidateModel->setHeaderData(4,Qt::Horizontal,trUtf8("Type de document"));
    documentValidateModel->setHeaderData(5,Qt::Horizontal,trUtf8("Moyen de paiement"));
    documentValidateModel->setHeaderData(6,Qt::Horizontal,trUtf8("TVA"));


    documentValidateView = new QTableView(this);
    documentValidateView->verticalHeader()->hide();
    documentValidateView->setModel(documentValidateModel);
    documentValidateView->setSelectionMode(QAbstractItemView::SingleSelection);
    documentValidateView->setSelectionBehavior(QAbstractItemView::SelectRows);
    documentValidateView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    loadDocumentValidate();

    layoutTabDoc->addWidget(documentValidateView);
    layoutDoc->addLayout(layoutTabDoc);

    groupDoc->setLayout(layoutDoc);

    /** ******************************* **/
    /**             Slots               **/
    /** ******************************* **/

    connect(searchButtonDocumentValidate, SIGNAL(clicked()), this, SLOT(showDocumentValideResult()));
    connect(printButtonDocumentValidate, SIGNAL(clicked()), this, SLOT(printDocument()));
    connect(transformDocumentButton, SIGNAL(clicked()), this, SLOT(transformDocument()));

    return groupDoc;

}

/**
 * Methode permettant de charger la liste complete des cliens
 * trier par nom
 */
void SearchWindow::loadCustomer(){
    QSqlDatabase base = QSqlDatabase::database();
    QSqlQuery query;
    query.exec("SELECT * FROM customer ORDER BY name");

    while(customerModel->rowCount()>0)
        customerModel->removeRow(0);

    int i=0;
    while(query.next()){
        QSqlRecord rec = query.record();
        customerModel->setItem(i, 0, new QStandardItem(rec.value("idCustomer").toString()));
        customerModel->setItem(i, 1, new QStandardItem(rec.value("name").toString()));
        customerModel->setItem(i, 2, new QStandardItem(rec.value("adress").toString()));
        customerModel->setItem(i, 3, new QStandardItem(rec.value("adress2").toString()));
        customerModel->setItem(i, 4, new QStandardItem(rec.value("postalCode").toString()));
        customerModel->setItem(i, 5, new QStandardItem(rec.value("city").toString()));
        customerModel->setItem(i, 6, new QStandardItem(rec.value("country").toString()));
        customerModel->setItem(i, 7, new QStandardItem(rec.value("email").toString()));
        customerModel->setItem(i, 8, new QStandardItem(rec.value("phone").toString()));
        i++;
    }
    customerView->resizeColumnsToContents();

    query.finish();
    base.commit();
}

/**
 * Methode permettant de charger la liste complete des produits
 * trier par nom
 */
void SearchWindow::loadProduct(){
    QSqlDatabase base = QSqlDatabase::database();
    QSqlQuery query;
    query.exec("SELECT * FROM product ORDER BY name");

    while(productModel->rowCount()>0)
        productModel->removeRow(0);

    int i=0;
    while(query.next()){
        QSqlRecord rec = query.record();
        productModel->setItem(i, 0, new QStandardItem(rec.value("idProduct").toString()));
        productModel->setItem(i, 1, new QStandardItem(rec.value("name").toString()));
        productModel->setItem(i, 2, new QStandardItem(rec.value("price").toString()));
        productModel->setItem(i, 3, new QStandardItem(rec.value("description").toString()));

        i++;
    }
    productView->resizeColumnsToContents();

    query.finish();
    base.commit();
}

/**
 * Methode permettant de charger la liste complete des documents
 * trier par nom
 */
void SearchWindow::loadDocumentNotValidate(){
    QSqlDatabase base = QSqlDatabase::database();
    QSqlQuery query;
    query.exec("SELECT D.*, C.name FROM document D, customer C WHERE D.idCustomer=C.idCustomer ORDER BY date");

    while(documentNotValidateModel->rowCount()>0)
        documentNotValidateModel->removeRow(0);


    int i=0;
    while(query.next()){
        QSqlRecord rec = query.record();

        documentNotValidateModel->setItem(i, 0, new QStandardItem(rec.value("idDocument").toString()));
        documentNotValidateModel->setItem(i, 1, new QStandardItem(rec.value("name").toString()));
        documentNotValidateModel->setItem(i, 2, new QStandardItem(rec.value("totalPrice").toString()));

        QDate date=QDate::fromString(rec.value("date").toString(),"yyyy-MM-dd");
        documentNotValidateModel->setItem(i, 3, new QStandardItem(date.toString("dd-MM-yyyy")));

        int docType=rec.value("type").toInt();
        QString type=(docType==Document::Facture)?trUtf8("Facture"):trUtf8("Devis");
        documentNotValidateModel->setItem(i, 4, new QStandardItem(type));

        int paymentType=rec.value("payment").toInt();
        QString payment="";
        if(paymentType==Document::Cheque)
            payment=trUtf8("Cheque");
        else if(paymentType==Document::Virement)
            payment=trUtf8("Virement");
        else
            payment=trUtf8("Espece");

        documentNotValidateModel->setItem(i, 5, new QStandardItem(payment));
        documentNotValidateModel->setItem(i, 6, new QStandardItem(rec.value("tva").toString()));
        i++;
    }
    documentNotValidateView->resizeColumnsToContents();

    query.finish();
    base.commit();
}

/**
 * Methode permettant de charger la liste complete des documents valider
 * trier par nom
 */
void SearchWindow::loadDocumentValidate(){
    QSqlDatabase base = QSqlDatabase::database();
    QSqlQuery query;
    query.exec("SELECT D.*, C.name FROM DocumentValide D, customer C WHERE D.idCustomer=C.idCustomer ORDER BY date");

    while(documentValidateModel->rowCount()>0)
        documentValidateModel->removeRow(0);


    int i=0;
    while(query.next()){
        QSqlRecord rec = query.record();

        documentValidateModel->setItem(i, 0, new QStandardItem(rec.value("id").toString()));
        documentValidateModel->setItem(i, 1, new QStandardItem(rec.value("name").toString()));
        documentValidateModel->setItem(i, 2, new QStandardItem(rec.value("price").toString()));

        QDate date=QDate::fromString(rec.value("date").toString(),"yyyy-MM-dd");
        documentValidateModel->setItem(i, 3, new QStandardItem(date.toString("dd-MM-yyyy")));

        int docType=rec.value("type").toInt();
        QString type=(docType==Document::Facture)?trUtf8("Facture"):trUtf8("Devis");
        documentValidateModel->setItem(i, 4, new QStandardItem(type));

        int paymentType=rec.value("payment").toInt();
        QString payment="";
        if(paymentType==Document::Cheque)
            payment=trUtf8("Cheque");
        else if(paymentType==Document::Virement)
            payment=trUtf8("Virement");
        else
            payment=trUtf8("Espece");

        documentValidateModel->setItem(i, 5, new QStandardItem(payment));
        documentValidateModel->setItem(i, 6, new QStandardItem(rec.value("tva").toString()));
        i++;
    }
    documentValidateView->resizeColumnsToContents();

    query.finish();
    base.commit();
}

/**
 * Methode qui permet de faire la recherche d'un client
 * et de l'afficher
 */
void SearchWindow::showCustomerResult(){
    QSqlDatabase base = QSqlDatabase::database();
    QSqlQueryModel queryModel;
    QSqlQuery query;
    QString paramValue = lineSearchClient->text();

    switch (typeSearchClient->currentIndex()){
    case 0:
        query.prepare("SELECT * FROM customer WHERE name LIKE :value");
        paramValue.prepend("%");
        paramValue.append("%");
        query.bindValue(":value",paramValue);
        break;

    case 1:
        query.prepare("SELECT * FROM customer WHERE city LIKE :value ");
        paramValue.prepend("%");
        paramValue.append("%");
        query.bindValue(":value",paramValue);
        break;

    case 2:
        query.prepare("SELECT * FROM customer WHERE postalCode=:value");
        query.bindValue(":value",paramValue);
        break;
    case 3:
        query.prepare("SELECT * FROM customer WHERE phone=:value");
        query.bindValue(":value",paramValue);
        break;
    }

    query.exec();
    queryModel.setQuery(query);
    int nbResult=queryModel.rowCount();

    if(nbResult==0){
        QMessageBox::information(this, trUtf8("Aucun Resultat"), trUtf8("Votre recherche n'a retourné aucun resultat."));
    }
    else{
        while(customerModel->rowCount()>0)
            customerModel->removeRow(0);

        for (int i=0;i<nbResult;i++){

            QSqlRecord rec = queryModel.record(i);
            customerModel->setItem(i, 0, new QStandardItem(rec.value("idCustomer").toString()));
            customerModel->setItem(i, 1, new QStandardItem(rec.value("name").toString()));
            customerModel->setItem(i, 2, new QStandardItem(rec.value("adress").toString()));
            customerModel->setItem(i, 3, new QStandardItem(rec.value("adress2").toString()));
            customerModel->setItem(i, 4, new QStandardItem(rec.value("postalCode").toString()));
            customerModel->setItem(i, 5, new QStandardItem(rec.value("city").toString()));
            customerModel->setItem(i, 6, new QStandardItem(rec.value("country").toString()));
            customerModel->setItem(i, 7, new QStandardItem(rec.value("email").toString()));
            customerModel->setItem(i, 8, new QStandardItem(rec.value("phone").toString()));

        }
        customerView->resizeColumnsToContents();
    }

    query.finish();
    queryModel.clear();
    base.commit();
}

/**
 * Methode qui permet de faire la recherche d'un produit
 * et de l'afficher
 */
void SearchWindow::showProductResult(){
    QSqlDatabase base = QSqlDatabase::database();
    QSqlQueryModel queryModel;
    QSqlQuery query;
    QString paramValue = lineSearchProduct->text();

    switch (typeSearchProduct->currentIndex()){
    case 0:
        query.prepare("SELECT * FROM product WHERE name LIKE :value");
        paramValue.prepend("%");
        paramValue.append("%");
        query.bindValue(":value",paramValue);
        break;

    case 1:
        query.prepare("SELECT * FROM product WHERE price=:value ");
        query.bindValue(":value",paramValue.toDouble());
        break;
    }

    query.exec();
    queryModel.setQuery(query);
    int nbResult=queryModel.rowCount();

    if(nbResult==0){
        QMessageBox::information(this, trUtf8("Aucun Resultat"), trUtf8("Votre recherche n'a retourné aucun resultat."));
    }
    else{
        while(productModel->rowCount()>0)
            productModel->removeRow(0);

        for (int i=0;i<nbResult;i++){

            QSqlRecord rec = queryModel.record(i);
            productModel->setItem(i, 0, new QStandardItem(rec.value("idProduct").toString()));
            productModel->setItem(i, 1, new QStandardItem(rec.value("name").toString()));
            productModel->setItem(i, 2, new QStandardItem(rec.value("price").toString()));
            productModel->setItem(i, 3, new QStandardItem(rec.value("description").toString()));

        }
        productView->resizeColumnsToContents();
    }

    query.finish();
    queryModel.clear();
    base.commit();
}

/**
 * Methode qui lance l'edition d'un client
 */
void SearchWindow::editCustomer(){

    QItemSelectionModel *select = customerView->selectionModel();
    if(select->hasSelection()){
        QModelIndexList rows=select->selectedRows(0);
        QModelIndex row=rows.at(0);
        parent->setCentralWidget(new NewCustomerWindow(parent,row.data(0).toInt()));
    }
    else
        QMessageBox::information(this, trUtf8("Edition impossible"), trUtf8("Edition impossible, aucun client sélectionné"));
}

/**
 * Methode qui lance l'edition d'un produit
 */
void SearchWindow::editProduct(){
    QItemSelectionModel *select = productView->selectionModel();
    if(select->hasSelection()){
        QModelIndexList rows=select->selectedRows(0);
        QModelIndex row=rows.at(0);
        parent->setCentralWidget(new NewProductWindow(parent,row.data(0).toInt()));
    }
    else
        QMessageBox::information(this, trUtf8("Edition impossible"), trUtf8("Edition impossible, aucun produit sélectionné"));
}

/**
 * Methode qui effectue la recherche en fonction des infos de l'interface
 * et qui affiche les resultats dans la table
 */
void SearchWindow::showDocumentNotValideResult(){
    QSqlDatabase base = QSqlDatabase::database();
    QSqlQueryModel queryModel;
    QSqlQuery query;
    QString paramValue = lineSearchDocumentNotValidate->text();

    QString typeSearch="";
    if(typeSearchDocumentNotValidate->currentIndex()==0){
        //ici on recherche par nom de client
        paramValue.prepend("%");
        paramValue.append("%");
        typeSearch=" C.name LIKE :paramValue ";
    }
    else if(typeSearchDocumentNotValidate->currentIndex()==1){
        // ici on recherche par date
        paramValue=QDate::fromString(paramValue,"dd-MM-yyyy").toString("yyyy-MM-dd");
        typeSearch=" D.date=:paramValue ";
    }
    else{
        // ici on recherche par prix
        typeSearch=" D.totalPrice=:paramValue ";
    }

    QString typeDoc="";
    bool usePaymentInfo=true;// si il s'agit d'un devis on utilisera pas le mode de paiement
    if(typeDocumentNotValidate->currentIndex()==1){
        //ici une facture
        typeDoc=" AND D.type="+QVariant(Document::Facture).toString();
    }
    else if(typeDocumentNotValidate->currentIndex()==2){
        //ici un devis
        typeDoc=" AND D.type="+QVariant(Document::Devis).toString();
        usePaymentInfo=false;
    }

    QString typePayment="";
    if(usePaymentInfo){
        if(paymentDocumentNotValidate->currentIndex()==1){
            //ici un cheque
            typePayment=" AND D.payment="+QVariant(Document::Cheque).toString();
        }
        else if(paymentDocumentNotValidate->currentIndex()==2){
            //ici un virement
            typePayment=" AND D.payment="+QVariant(Document::Virement).toString();
        }
        else if(paymentDocumentNotValidate->currentIndex()==3){
            //ici en espece
            typePayment=" AND D.payment="+QVariant(Document::Especes).toString();
        }
    }

    QString requete="SELECT D.*, C.name FROM document D, customer C WHERE C.idCustomer=D.idCustomer AND "+typeSearch+typeDoc+typePayment;
    query.prepare(requete);
    query.bindValue(":paramValue",paramValue);
    query.exec();
    queryModel.setQuery(query);

    int nbResult=queryModel.rowCount();
    if(nbResult==0){
        QMessageBox::information(this, trUtf8("Aucun Resultat"), trUtf8("Votre recherche n'a retourné aucun resultat."));
    }
    else{
        // ici on affiche les resultat;

        while(documentNotValidateModel->rowCount()>0)
            documentNotValidateModel->removeRow(0);

        for (int i=0;i<nbResult;i++){

            QSqlRecord rec = queryModel.record(i);
            documentNotValidateModel->setItem(i, 0, new QStandardItem(rec.value("idDocument").toString()));
            documentNotValidateModel->setItem(i, 1, new QStandardItem(rec.value("name").toString()));
            documentNotValidateModel->setItem(i, 2, new QStandardItem(rec.value("totalPrice").toString()));

            QDate date=QDate::fromString(rec.value("date").toString(),"yyyy-MM-dd");
            documentNotValidateModel->setItem(i, 3, new QStandardItem(date.toString("dd-MM-yyyy")));

            int docType=rec.value("type").toInt();
            QString type=(docType==Document::Facture)?trUtf8("Facture"):trUtf8("Devis");
            documentNotValidateModel->setItem(i, 4, new QStandardItem(type));

            int paymentType=rec.value("payment").toInt();
            QString payment="";
            if(paymentType==Document::Cheque)
                payment=trUtf8("Cheque");
            else if(paymentType==Document::Virement)
                payment=trUtf8("Virement");
            else
                payment=trUtf8("Espece");

            documentNotValidateModel->setItem(i, 5, new QStandardItem(payment));
            documentNotValidateModel->setItem(i, 6, new QStandardItem(rec.value("tva").toString()));

        }
        documentNotValidateView->resizeColumnsToContents();
    }

    query.finish();
    base.commit();
}

/**
 * Methode permettant de lancer l'edition d'un document
 */
void SearchWindow::editDocument(){
    QItemSelectionModel *select = documentNotValidateView->selectionModel();
    if(select->hasSelection()){
        QModelIndexList rows=select->selectedRows(0);
        QModelIndex row=rows.at(0);
        parent->setCentralWidget(new NewDocumentWindow(parent,row.data(0).toInt()));
    }
    else
        QMessageBox::information(this, trUtf8("Edition impossible"), trUtf8("Edition impossible, aucun document sélectionné"));

}

/**
 * Methode permettant de valider un document
 */
void SearchWindow::valideDocument(){
    QItemSelectionModel *select = documentNotValidateView->selectionModel();
    if(select->hasSelection()){
        int ret = QMessageBox::question(this,trUtf8("Valider le document ?"),trUtf8("La validation d'un document empeche toutes modification ultérieure.<br/>Voulez-vous vraiment valider le document?"),QMessageBox::Yes | QMessageBox::No);

        if (ret == QMessageBox::Yes){
            QModelIndexList rows=select->selectedRows(0);
            QModelIndex row=rows.at(0);

            int idDoc=row.data(0).toInt();
            Document d(idDoc);
            ValidDocument vd(d);
            vd.save();
            documentNotValidateModel->removeRow(row.row());
            loadDocumentValidate();

            QStatusBar *statBar = parent->statusBar();
            statBar->showMessage(trUtf8("Document validé"), 4000);
        }
    }
    else
        QMessageBox::information(this, trUtf8("Validation impossible"), trUtf8("Validation impossible, aucun document sélectionné"));


}

/**
 * Methode permettant de supprimer un document selectionner
 */
void SearchWindow::deleteDocument(){
    QItemSelectionModel *select = documentNotValidateView->selectionModel();
    if(select->hasSelection()){
        QModelIndexList rows=select->selectedRows(0);
        QModelIndex row=rows.at(0);

        int idDoc=row.data(0).toInt();
        Document d(idDoc);
        d.remove();

        documentNotValidateModel->removeRow(row.row());
        QStatusBar *statBar = parent->statusBar();
        statBar->showMessage(trUtf8("Document supprimé"), 4000);
    }
    else
        QMessageBox::information(this, trUtf8("Suppression impossible"), trUtf8("Suppression impossible, aucun document sélectionné"));
}

/**
 * Methode qui effectue la recherche en fonction des infos de l'interface
 * et qui affiche les resultats dans la table
 */
void SearchWindow::showDocumentValideResult(){
    QSqlDatabase base = QSqlDatabase::database();
    QSqlQueryModel queryModel;
    QSqlQuery query;
    QString paramValue = lineSearchDocumentValidate->text();

    QString typeSearch="";
    if(typeSearchDocumentValidate->currentIndex()==0){
        //ici on recherche par nom de client
        paramValue.prepend("%");
        paramValue.append("%");
        typeSearch=" C.name LIKE :paramValue ";
    }
    else if(typeSearchDocumentValidate->currentIndex()==1){
        // ici on recherche par date
        paramValue=QDate::fromString(paramValue,"dd-MM-yyyy").toString("yyyy-MM-dd");
        typeSearch=" D.date=:paramValue ";
    }
    else{
        // ici on recherche par prix
        typeSearch=" D.price=:paramValue ";
    }

    QString typeDoc="";
    bool usePaymentInfo=true;// si il s'agit d'un devis on utilisera pas le mode de paiement
    if(typeDocumentValidate->currentIndex()==1){
        //ici une facture
        typeDoc=" AND D.type="+QVariant(Document::Facture).toString();
    }
    else if(typeDocumentValidate->currentIndex()==2){
        //ici un devis
        typeDoc=" AND D.type="+QVariant(Document::Devis).toString();
        usePaymentInfo=false;
    }

    QString typePayment="";
    if(usePaymentInfo){
        if(paymentDocumentValidate->currentIndex()==1){
            //ici un cheque
            typePayment=" AND D.payment="+QVariant(Document::Cheque).toString();
        }
        else if(paymentDocumentValidate->currentIndex()==2){
            //ici un virement
            typePayment=" AND D.payment="+QVariant(Document::Virement).toString();
        }
        else if(paymentDocumentValidate->currentIndex()==3){
            //ici en espece
            typePayment=" AND D.payment="+QVariant(Document::Especes).toString();
        }
    }

    QString requete="SELECT D.*, C.name FROM DocumentValide D, customer C WHERE C.idCustomer=D.idCustomer AND "+typeSearch+typeDoc+typePayment;
    query.prepare(requete);
    query.bindValue(":paramValue",paramValue);
    query.exec();
    queryModel.setQuery(query);

    int nbResult=queryModel.rowCount();
    if(nbResult==0){
        QMessageBox::information(this, trUtf8("Aucun Resultat"), trUtf8("Votre recherche n'a retourné aucun resultat."));
    }
    else{
        // ici on affiche les resultat;

        while(documentValidateModel->rowCount()>0)
            documentValidateModel->removeRow(0);

        for (int i=0;i<nbResult;i++){

            QSqlRecord rec = queryModel.record(i);
            documentValidateModel->setItem(i, 0, new QStandardItem(rec.value("id").toString()));
            documentValidateModel->setItem(i, 1, new QStandardItem(rec.value("name").toString()));
            documentValidateModel->setItem(i, 2, new QStandardItem(rec.value("price").toString()));

            QDate date=QDate::fromString(rec.value("date").toString(),"yyyy-MM-dd");
            documentValidateModel->setItem(i, 3, new QStandardItem(date.toString("dd-MM-yyyy")));

            int docType=rec.value("type").toInt();
            QString type=(docType==Document::Facture)?trUtf8("Facture"):trUtf8("Devis");
            documentValidateModel->setItem(i, 4, new QStandardItem(type));

            int paymentType=rec.value("payment").toInt();
            QString payment="";
            if(paymentType==Document::Cheque)
                payment=trUtf8("Cheque");
            else if(paymentType==Document::Virement)
                payment=trUtf8("Virement");
            else
                payment=trUtf8("Espece");

            documentValidateModel->setItem(i, 5, new QStandardItem(payment));
            documentValidateModel->setItem(i, 6, new QStandardItem(rec.value("tva").toString()));

        }
        documentValidateView->resizeColumnsToContents();
    }

    query.finish();
    base.commit();
}

/**
 * Methode permettant d'imprimer un document valider
 */
void SearchWindow::printDocument(){
    QItemSelectionModel *select = documentValidateView->selectionModel();
    if(select->hasSelection()){
        QModelIndexList rows=select->selectedRows(0);
        QModelIndex row=rows.at(0);
        int idDoc=row.data(0).toInt();

        ValidDocument vd(idDoc);
        vd.print();
        QStatusBar *statBar = parent->statusBar();
        statBar->showMessage(trUtf8("Document en cour d'impression"), 4000);
    }
    else
        QMessageBox::information(this, trUtf8("Impression impossible"), trUtf8("Impression impossible, aucun document sélectionné"));

}

/**
 * Methode permettant de transformer un devis en facture (valider)
 */
void SearchWindow::transformDocument(){
    QItemSelectionModel *select = documentValidateView->selectionModel();
    if(select->hasSelection()){
        QModelIndexList rows=select->selectedRows(0);
        QModelIndex row=rows.at(0);

        int idDoc=row.data(0).toInt();
        ValidDocument vd(idDoc);
        if(vd.docType==Document::Facture){
            QMessageBox::information(this, trUtf8("Transformation impossible"), trUtf8("Transformation impossible, vous avez sélectionné une facture"));
            return;
        }
        else{
            // afficher une boite de dialogue demandant le type de reglement
            PaymentTypeWindow *ptw=new PaymentTypeWindow(this);
            ptw->show();
            connect(ptw,SIGNAL(choixEffectuer(Document::PaymentEnum)),this,SLOT(endTransformDocument(Document::PaymentEnum)));
        }
    }
    else
        QMessageBox::information(this, trUtf8("Transformation impossible"), trUtf8("Transformation impossible, aucun devis sélectionné"));

}

/**
 * Slot qui est appeler lorsque l'utilisateur a choisie le moyen de paiement pour
 * la transformation du devis en facture
 */
void SearchWindow::endTransformDocument(Document::PaymentEnum choice){
    QItemSelectionModel *select = documentValidateView->selectionModel();
    QModelIndexList rows=select->selectedRows(0);
    QModelIndex row=rows.at(0);
    int idDoc=row.data(0).toInt();
    ValidDocument vd(idDoc);
    vd.transform(choice);
    loadDocumentValidate();
    QStatusBar *statBar = parent->statusBar();
    statBar->showMessage(trUtf8("Devis tranformé en facture"), 4000);
}
