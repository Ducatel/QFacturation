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

    QVBoxLayout *layoutClient= new QVBoxLayout;
    QGroupBox *groupClient = new QGroupBox(tr("Rechercher un client"), this);

    QFormLayout *layoutFormClient=new QFormLayout;

    typeSearchClient= new QComboBox(this);
    typeSearchClient->addItem(tr("Nom"));
    typeSearchClient->addItem(tr("Ville"));
    typeSearchClient->addItem(tr("Code postal"));
    typeSearchClient->addItem(tr("Numéro de téléphone"));
    layoutFormClient->addRow(tr("Rechercher par: "),typeSearchClient);

    lineSearchClient=new QLineEdit(this);
    layoutFormClient->addRow(tr("Mots clés: "),lineSearchClient);


    searchButtonCustomer=new QPushButton(tr("Rechercher"),this);
    layoutFormClient->addRow(tr("Rechercher le client: "),searchButtonCustomer);
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

    loadCustomer();

    layoutTabClient->addWidget(customerView);
    layoutClient->addLayout(layoutTabClient);

    groupClient->setLayout(layoutClient);
    layoutPrinc->addWidget(groupClient);


    /** ******************************* **/
    /**    Partie Recherche Produit     **/
    /** ******************************* **/

    QVBoxLayout *layoutProduct= new QVBoxLayout;
    QGroupBox *groupProduct = new QGroupBox(tr("Rechercher un Produit"), this);

    QFormLayout *layoutFormProduct=new QFormLayout;

    typeSearchProduct= new QComboBox(this);
    typeSearchProduct->addItem(tr("Nom"));
    typeSearchProduct->addItem(tr("Prix"));

    layoutFormProduct->addRow(tr("Rechercher par: "),typeSearchProduct);

    lineSearchProduct=new QLineEdit(this);
    layoutFormProduct->addRow(tr("Mots clés: "),lineSearchProduct);


    buttonSearchProduct=new QPushButton(tr("Rechercher"),this);
    layoutFormProduct->addRow(tr("Rechercher le client: "),buttonSearchProduct);

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

    loadProduct();

    layoutTabProduct->addWidget(productView);
    layoutProduct->addLayout(layoutTabProduct);

    groupProduct->setLayout(layoutProduct);
    layoutPrinc->addWidget(groupProduct);

    /** ******************************* **/
    /**             Slots               **/
    /** ******************************* **/

    connect(searchButtonCustomer, SIGNAL(clicked()), this, SLOT(showCustomerResult()));


    setLayout(layoutPrinc);

}

/**
 * Methode permettant de charger la liste complete des cliens
 * trier par nom
 */
void SearchWindow::loadCustomer(){
    QSqlDatabase base = QSqlDatabase::addDatabase("QSQLITE");
    base.setDatabaseName(QDir::fromNativeSeparators(QDir::homePath()+"/.QFacturation/data.db"));
    base.open();
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
    base.close();
    QSqlDatabase::removeDatabase(QDir::fromNativeSeparators(QDir::homePath()+"/.QFacturation/data.db"));
}

/**
 * Methode permettant de charger la liste complete des produits
 * trier par nom
 */
void SearchWindow::loadProduct(){
    QSqlDatabase base = QSqlDatabase::addDatabase("QSQLITE");
    base.setDatabaseName(QDir::fromNativeSeparators(QDir::homePath()+"/.QFacturation/data.db"));
    base.open();
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
    base.close();
    QSqlDatabase::removeDatabase(QDir::fromNativeSeparators(QDir::homePath()+"/.QFacturation/data.db"));
}


/**
 * Methode permettant de charger la liste complete des documents
 * trier par nom
 */
void SearchWindow::loadDocument(){

}

/**
 * Methode qui permet de faire la recherche d'un client
 * et de l'afficher
 */
void SearchWindow::showCustomerResult(){
    QSqlDatabase base = QSqlDatabase::addDatabase("QSQLITE");
    base.setDatabaseName(QDir::fromNativeSeparators(QDir::homePath()+"/.QFacturation/data.db"));
    base.open();

    QSqlQuery query;
    switch (typeSearchClient->currentIndex()){
    case 0:
        query.prepare("SELECT * FROM customer WHERE name LIKE % :value %");
        query.bindValue(":value",lineSearchClient->text());
        break;

    case 1:
        query.prepare("SELECT * FROM customer WHERE city LIKE % :value %");
        query.bindValue(":value",lineSearchClient->text());
        break;

    case 2:
        query.prepare("SELECT * FROM customer WHERE postalCode=:value");
        query.bindValue(":value",lineSearchClient->text());
        break;
    case 3:
        query.prepare("SELECT * FROM customer WHERE phone=:value");
        query.bindValue(":value",lineSearchClient->text());
        break;
    }

    // TODO trouver comment connaitre le nombre de resultat retourner
    // TODO verifier le fonctionnement de chaque requete

    query.exec();

    if(query.size()==0){
        QMessageBox::information(this, tr("Aucun Resultat"), tr("Votre recherche n'a retourné aucun resultat."));
    }
    else{
        while(customerModel->rowCount()>0)
            customerModel->removeRow(0);
    }
    qDebug()<<query.size();
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
    base.close();
    QSqlDatabase::removeDatabase(QDir::fromNativeSeparators(QDir::homePath()+"/.QFacturation/data.db"));
}

/**
 * Methode qui permet de faire la recherche d'un produit
 * et de l'afficher
 */
void SearchWindow::showProductResult(){

}
