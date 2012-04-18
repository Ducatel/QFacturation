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

    QVBoxLayout *layoutPrinc=new QVBoxLayout;

    /** ******************************* **/
    /**     Partie Recherche Client     **/
    /** ******************************* **/

    layoutPrinc->addWidget(createCustomerSearchInterface());

    /** ******************************* **/
    /**    Partie Recherche Produit     **/
    /** ******************************* **/

    layoutPrinc->addWidget(createProductSearchInterface());

    /** ***************************************** **/
    /**   Partie Recherche document non valider   **/
    /** ***************************************** **/

    layoutPrinc->addWidget(createNotValidateDocumentSearchInterface());

    /** ***************************************** **/
    /**     Partie Recherche document valider     **/
    /** ***************************************** **/


    setLayout(layoutPrinc);

}

/**
 * Methode permettant de construire la partie interface
 * de recherche client
 * @return le QGroupBox contenant l'interface
 */
QGroupBox* SearchWindow::createCustomerSearchInterface(){

    QGroupBox *groupClient = new QGroupBox(tr("Rechercher un client"), this);
    QVBoxLayout *layoutClient= new QVBoxLayout;


    QFormLayout *layoutFormClient=new QFormLayout;

    typeSearchClient= new QComboBox(this);
    typeSearchClient->addItem(tr("Nom"));
    typeSearchClient->addItem(tr("Ville"));
    typeSearchClient->addItem(tr("Code postal"));
    typeSearchClient->addItem(tr("Numéro de téléphone"));
    layoutFormClient->addRow(tr("Rechercher par: "),typeSearchClient);

    lineSearchClient=new QLineEdit(this);
    layoutFormClient->addRow(tr("Mots clés: "),lineSearchClient);


    QHBoxLayout *layoutButtonCustomer=new QHBoxLayout;

    searchButtonCustomer=new QPushButton(tr("Rechercher"),this);
    layoutButtonCustomer->addWidget(searchButtonCustomer);

    editButtonCustomer=new QPushButton(tr("Editer le client sélectionné"),this);
    layoutButtonCustomer->addWidget(editButtonCustomer);

    layoutFormClient->addRow(tr("Action: "),layoutButtonCustomer);


    layoutClient->addLayout(layoutFormClient);

    /***********************************************/

    QHBoxLayout *layoutTabClient= new QHBoxLayout;
    customerModel = new QStandardItemModel(0, 9);
    customerModel->setHeaderData(0,Qt::Horizontal,"id");
    customerModel->setHeaderData(1,Qt::Horizontal,tr("Nom"));
    customerModel->setHeaderData(2,Qt::Horizontal,tr("Adresse"));
    customerModel->setHeaderData(3,Qt::Horizontal,tr("Complément"));
    customerModel->setHeaderData(4,Qt::Horizontal,tr("Code postal"));
    customerModel->setHeaderData(5,Qt::Horizontal,tr("Ville"));
    customerModel->setHeaderData(6,Qt::Horizontal,tr("Pays"));
    customerModel->setHeaderData(7,Qt::Horizontal,tr("Email"));
    customerModel->setHeaderData(8,Qt::Horizontal,tr("Téléphone"));


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
    QGroupBox *groupProduct = new QGroupBox(tr("Rechercher un Produit"), this);

    QFormLayout *layoutFormProduct=new QFormLayout;

    typeSearchProduct= new QComboBox(this);
    typeSearchProduct->addItem(tr("Nom"));
    typeSearchProduct->addItem(tr("Prix"));

    layoutFormProduct->addRow(tr("Rechercher par: "),typeSearchProduct);

    lineSearchProduct=new QLineEdit(this);
    layoutFormProduct->addRow(tr("Mots clés: "),lineSearchProduct);


    QHBoxLayout *layoutButtonProduct=new QHBoxLayout;

    searchButtonProduct=new QPushButton(tr("Rechercher"),this);
    layoutButtonProduct->addWidget(searchButtonProduct);

    editButtonProduct=new QPushButton(tr("Editer le produit sélectionné"),this);
    layoutButtonProduct->addWidget(editButtonProduct);

    layoutFormProduct->addRow(tr("Action: "),layoutButtonProduct);


    layoutProduct->addLayout(layoutFormProduct);

    /***********************************************/

    QHBoxLayout *layoutTabProduct= new QHBoxLayout;
    productModel = new QStandardItemModel(0, 4);
    productModel->setHeaderData(0,Qt::Horizontal,"id");
    productModel->setHeaderData(1,Qt::Horizontal,tr("Nom"));
    productModel->setHeaderData(2,Qt::Horizontal,tr("Prix"));
    productModel->setHeaderData(3,Qt::Horizontal,tr("Description"));

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
    QGroupBox *groupDoc = new QGroupBox(tr("Rechercher un document non validé"), this);
    QFormLayout *layoutFormDoc=new QFormLayout;

    typeSearchDocumentNotValidate=new QComboBox(this);
    typeSearchDocumentNotValidate->addItem(tr("Nom de client"));
    typeSearchDocumentNotValidate->addItem(tr("Date"));
    typeSearchDocumentNotValidate->addItem(tr("Prix"));

    layoutFormDoc->addRow(tr("Rechercher par: "),typeSearchDocumentNotValidate);

    typeDocumentNotValidate=new QComboBox(this);
    typeDocumentNotValidate->addItem(tr("Tout"));
    typeDocumentNotValidate->addItem(tr("Facture"));
    typeDocumentNotValidate->addItem(tr("Devis"));

    layoutFormDoc->addRow(tr("Type de document: "),typeDocumentNotValidate);

    paymentDocumentNotValidate=new QComboBox(this);
    paymentDocumentNotValidate->addItem(tr("Tout"));
    paymentDocumentNotValidate->addItem(tr("Cheque"));
    paymentDocumentNotValidate->addItem(tr("Virement"));
    paymentDocumentNotValidate->addItem(tr("Espece"));

    layoutFormDoc->addRow(tr("Moyen de paiement: "),paymentDocumentNotValidate);


    lineSearchDocumentNotValidate=new QLineEdit(this);
    layoutFormDoc->addRow(tr("Mots clés: "),lineSearchDocumentNotValidate);

    QHBoxLayout *layoutButtonDoc=new QHBoxLayout;

    searchButtonDocumentNotValidate=new QPushButton(tr("Rechercher"),this);
    layoutButtonDoc->addWidget(searchButtonDocumentNotValidate);

    editButtonDocumentNotValidate=new QPushButton(tr("Editer le document sélectionné"),this);
    layoutButtonDoc->addWidget(editButtonDocumentNotValidate);

    validateDocumentButton=new QPushButton(tr("Valider le document sélectionné"),this);
    layoutButtonDoc->addWidget(validateDocumentButton);

    deleteButtonDocumentNotValidate=new QPushButton(tr("Supprimer le document sélectionné"),this);
    layoutButtonDoc->addWidget(deleteButtonDocumentNotValidate);

    layoutFormDoc->addRow(tr("Action: "),layoutButtonDoc);

    layoutDoc->addLayout(layoutFormDoc);

    /***********************************************************/

    QHBoxLayout *layoutTabDoc= new QHBoxLayout;
    documentNotValidateModel = new QStandardItemModel(0, 6);
    documentNotValidateModel->setHeaderData(0,Qt::Horizontal,"id");
    documentNotValidateModel->setHeaderData(1,Qt::Horizontal,tr("Nom du client"));
    documentNotValidateModel->setHeaderData(2,Qt::Horizontal,tr("Prix"));
    documentNotValidateModel->setHeaderData(3,Qt::Horizontal,tr("Date"));
    documentNotValidateModel->setHeaderData(4,Qt::Horizontal,tr("Type de document"));
    documentNotValidateModel->setHeaderData(5,Qt::Horizontal,tr("Moyen de paiement"));

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
        QString type=(docType==Document::Facture)?tr("Facture"):tr("Devis");
        documentNotValidateModel->setItem(i, 4, new QStandardItem(type));

        int paymentType=rec.value("payment").toInt();
        QString payment="";
        if(paymentType==Document::Cheque)
            payment=tr("Cheque");
        else if(paymentType==Document::Virement)
            payment=tr("Virement");
        else
            payment=tr("Espece");

        documentNotValidateModel->setItem(i, 5, new QStandardItem(payment));
        i++;
    }
    documentNotValidateView->resizeColumnsToContents();

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
        QMessageBox::information(this, tr("Aucun Resultat"), tr("Votre recherche n'a retourné aucun resultat."));
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
        QMessageBox::information(this, tr("Aucun Resultat"), tr("Votre recherche n'a retourné aucun resultat."));
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
        QMessageBox::information(this, tr("Edition impossible"), tr("Edition impossible, aucun client sélectionné"));
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
        QMessageBox::information(this, tr("Edition impossible"), tr("Edition impossible, aucun produit sélectionné"));

}

void SearchWindow::showDocumentNotValideResult(){

}

void SearchWindow::editDocument(){
    QItemSelectionModel *select = documentNotValidateView->selectionModel();
    if(select->hasSelection()){
        QModelIndexList rows=select->selectedRows(0);
        QModelIndex row=rows.at(0);
        parent->setCentralWidget(new NewDocumentWindow(parent,row.data(0).toInt()));
    }
    else
        QMessageBox::information(this, tr("Edition impossible"), tr("Edition impossible, aucun document sélectionné"));

}

void SearchWindow::valideDocument(){

}

void SearchWindow::deleteDocument(){

}
