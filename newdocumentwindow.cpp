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

#include "newdocumentwindow.h"


NewDocumentWindow::NewDocumentWindow(QMainWindow *parent) :QWidget(parent){
    this->parent=parent;
    idDocument=-1;
    createInterface();
    isSave=false;
}

NewDocumentWindow::NewDocumentWindow(QMainWindow *parent,int identifiant){
    this->parent=parent;
    idDocument=identifiant;
    createInterface();
    isSave=false;
    initByBDD();
}

/**
 * Methode qui initialise les champs grace au info de la BDD
 */
void NewDocumentWindow::initByBDD(){

    Document d(idDocument);
    customerName->setCurrentIndex(d.m_idCustomer-1);

    if(d.m_docType==Document::Facture)
        documentType->setCurrentIndex(0);
    else
        documentType->setCurrentIndex(1);

    if(d.m_payment==Document::Cheque)
        reglementMode->setCurrentIndex(0);
    else if(d.m_payment==Document::Especes)
        reglementMode->setCurrentIndex(1);
    else
        reglementMode->setCurrentIndex(2);

    documentTva->setValue(d.m_tva);

    QList<ProductDocument> list=ProductDocument::getAllByIdDocument(idDocument);
    for(int i=0;i<list.size();i++){
        ProductDocument prodDoc=list.at(i);
        Product p(prodDoc.idProduct);

        double priceWithoutReduction=prodDoc.quantity*p.price;
        bool percentValue=prodDoc.reduction.endsWith('%');

        double reduction=0.0;
        if(percentValue){
            double pourcentage=prodDoc.reduction.mid(0,prodDoc.reduction.size()-1).toDouble();
            reduction=((prodDoc.quantity*p.price)*pourcentage)/100.0;
        }
        else{
            reduction=prodDoc.reduction.toDouble();
        }

        double finalPrice=prodDoc.quantity*p.price-reduction;

        productModel->setItem(i, 0, new QStandardItem(QVariant(prodDoc.idProduct).toString()));
        productModel->setItem(i, 1, new QStandardItem(p.name));
        productModel->setItem(i, 2, new QStandardItem(QVariant(prodDoc.quantity).toString()));
        productModel->setItem(i, 3, new QStandardItem(QVariant(p.price).toString()));
        productModel->setItem(i, 4, new QStandardItem(QVariant(priceWithoutReduction).toString()));
        productModel->setItem(i, 5, new QStandardItem(prodDoc.reduction));
        productModel->setItem(i, 6, new QStandardItem(QVariant(finalPrice).toString()));

    }
    productView->resizeColumnsToContents();

}

void NewDocumentWindow::createInterface(){
    QVBoxLayout *layoutPrinc=new QVBoxLayout;

    /** ******************************** **/
    /**        Formulaire de Base        **/
    /** ******************************** **/

    layoutPrinc->addWidget(createBasicInfoInterface());

    /** ******************************** **/
    /**     Formulaire Ajout Produit     **/
    /** ******************************** **/

    layoutPrinc->addWidget(createAddProductInterface());

    /** ******************************** **/
    /**     Produit dans le document     **/
    /** ******************************** **/

    layoutPrinc->addWidget(createProductViewInterface());

    /** ******************************** **/
    /**       Bouton bas interface       **/
    /** ******************************** **/

    QHBoxLayout *layoutBouton=new QHBoxLayout;

    layoutBouton->addStretch();
    saveButton=new QPushButton(trUtf8("Enregistrer le document"),this);
    layoutBouton->addWidget(saveButton);

    validateButton=new QPushButton(trUtf8("Valider le document"),this);
    layoutBouton->addWidget(validateButton);
    layoutBouton->addStretch();

    layoutPrinc->addLayout(layoutBouton);

    connect(saveButton, SIGNAL(clicked()), this, SLOT(save()));
    connect(validateButton, SIGNAL(clicked()), this, SLOT(validate()));

    setLayout(layoutPrinc);
}

/**
 * Methode permettant de creer l'interface de saisie des
 * information de base du document
 * @return l'interface
 */
QGroupBox* NewDocumentWindow::createBasicInfoInterface(){

    QGroupBox *groupBase = new QGroupBox(trUtf8("Informations de base"), this);
    QFormLayout *layoutFormBase=new QFormLayout;

    customerName=new QComboBox(this);
    customerName->setToolTip(trUtf8("Nom du client, ville"));
    QList<Customer> listCustomer= Customer::getAllCustomer();

    if(listCustomer.size()==0){
        this->setDisabled(true);
    }

    for(int i=0;i<listCustomer.size();i++)
        customerName->addItem(listCustomer.at(i).m_name+", "+listCustomer.at(i).m_city);

    layoutFormBase->addRow(trUtf8("Client: "),customerName);


    documentType=new QComboBox(this);
    documentType->addItem(trUtf8("Facture"));
    documentType->addItem(trUtf8("Devis"));
    layoutFormBase->addRow(trUtf8("Type de document: "),documentType);


    reglementMode=new QComboBox(this);
    reglementMode->addItem(trUtf8("Cheque"));
    reglementMode->addItem(trUtf8("Espece"));
    reglementMode->addItem(trUtf8("Virement"));
    layoutFormBase->addRow(trUtf8("Mode de paiement: "),reglementMode);

    documentTva=new QDoubleSpinBox(this);
    documentTva->setMinimum(0.0);
    documentTva->setMaximum(100.0);
    layoutFormBase->addRow(trUtf8("TVA du document: "),documentTva);


    groupBase->setLayout(layoutFormBase);

    /** ******************************** **/
    /**               Slots              **/
    /** ******************************** **/

    connect(documentType, SIGNAL(currentIndexChanged(int)), this, SLOT(turnOnOffDocumentType(int)));

    return groupBase;

}

/**
 * Methode permettant de creer l'interface d'ajout
 * de produit au documents
 * @return l'interface
 */
QGroupBox* NewDocumentWindow::createAddProductInterface(){

    QGroupBox *groupAddProduct = new QGroupBox(trUtf8("Ajout de produit"), this);
    QFormLayout *layoutFormAddProduct=new QFormLayout;

    productName=new QComboBox(this);
    productName->setToolTip(trUtf8("Nom du produit, description, prix"));
    QList<Product> listProduct= Product::getAllProduct();

    if(listProduct.size()==0){
        this->setDisabled(true);
    }

    for(int i=0;i<listProduct.size();i++)
        productName->addItem(listProduct.at(i).name+", "+listProduct.at(i).description+", "+QVariant(listProduct.at(i).price).toString()+QString(8364));

    layoutFormAddProduct->addRow(trUtf8("Produit: "),productName);


    productQuantity=new QSpinBox(this);
    productQuantity->setMinimum(1);
    productQuantity->setMaximum(99999);
    layoutFormAddProduct->addRow(trUtf8("Quantité: "),productQuantity);

    productReduction=new QDoubleSpinBox(this);
    productQuantity->setMinimum(0);
    productQuantity->setMaximum(99999);
    layoutFormAddProduct->addRow(trUtf8("Remise: "),productReduction);

    QGroupBox *groupTypeReduction = new QGroupBox(this);

    fixedValue=new QRadioButton(trUtf8("Valeur fixe"),this);
    fixedValue->setChecked(true);
    percentage=new QRadioButton(trUtf8("Pourcentage"),this);

    QHBoxLayout *layoutRadioButton = new QHBoxLayout;
    layoutRadioButton->addWidget(fixedValue);
    layoutRadioButton->addWidget(percentage);
    layoutRadioButton->addStretch();

    groupTypeReduction->setLayout(layoutRadioButton);

    layoutFormAddProduct->addRow(trUtf8("Type de reduction"),groupTypeReduction);


    QHBoxLayout *layoutButtonProduct=new QHBoxLayout;

    buttonAddProduct=new QPushButton(trUtf8("Ajouter le produit"),this);
    layoutButtonProduct->addWidget(buttonAddProduct);

    buttonRemoveProduct=new QPushButton(trUtf8("Supprimer le produit sélectionné"),this);
    layoutButtonProduct->addWidget(buttonRemoveProduct);

    layoutButtonProduct->addStretch();
    layoutFormAddProduct->addRow(trUtf8("Actions: "),layoutButtonProduct);

    groupAddProduct->setLayout(layoutFormAddProduct);

    /** ******************************** **/
    /**               Slots              **/
    /** ******************************** **/
    connect(buttonAddProduct, SIGNAL(clicked()), this, SLOT(addProduct()));
    connect(buttonRemoveProduct, SIGNAL(clicked()), this, SLOT(removeProduct()));


    return groupAddProduct;

}

/**
 * Methode permettant de creer l'interface de visualisation
 * des produits present dans le document
 * @return l'interface
 */
QGroupBox* NewDocumentWindow::createProductViewInterface(){
    QHBoxLayout *layoutProductView=new QHBoxLayout;
    QGroupBox *groupProduct = new QGroupBox(trUtf8("Produit dans le document"), this);


    productModel = new QStandardItemModel(0, 7);
    productModel->setHeaderData(0,Qt::Horizontal,"id");
    productModel->setHeaderData(1,Qt::Horizontal,trUtf8("Nom"));
    productModel->setHeaderData(2,Qt::Horizontal,trUtf8("Quantité"));
    productModel->setHeaderData(3,Qt::Horizontal,trUtf8("Prix unitaire"));
    productModel->setHeaderData(4,Qt::Horizontal,trUtf8("Prix de base"));
    productModel->setHeaderData(5,Qt::Horizontal,trUtf8("Remise"));
    productModel->setHeaderData(6,Qt::Horizontal,trUtf8("Prix final"));


    productView = new QTableView(this);
    productView->verticalHeader()->hide();
    productView->setModel(productModel);
    productView->setSelectionMode(QAbstractItemView::SingleSelection);
    productView->setSelectionBehavior(QAbstractItemView::SelectRows);
    productView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    layoutProductView->addWidget(productView);
    groupProduct->setLayout(layoutProductView);
    return groupProduct;
}

/**
 * Methode qui permet d'activé ou de desactivé le choix du type
 * de reglement (SLOT).
 * @param currentIndex index qui viens d'etre selectionner
 */
void NewDocumentWindow::turnOnOffDocumentType(int currentIndex){
    // currentIndex ==0, facture
    // currentIndex ==1, devis
    reglementMode->setDisabled((currentIndex!=0));
}


/**
 * Methode permettant d'ajouter un produit au document
 */
void NewDocumentWindow::addProduct(){
    int positionInView=productModel->rowCount();
    int idProduct=productName->currentIndex()+1;
    Product p(idProduct);

    double priceWithoutReduction=productQuantity->value()*p.price;
    double remise=0.0;
    if(productReduction->value()>0){
        if(fixedValue->isChecked()){
            remise=productReduction->value();
            productModel->setItem(positionInView, 5, new QStandardItem(QVariant(remise).toString()));

        }
        else{
            remise=(priceWithoutReduction*productReduction->value())/100.0;
            productModel->setItem(positionInView, 5, new QStandardItem(QVariant(productReduction->value()).toString()+"%"));

        }
    }
    else
        productModel->setItem(positionInView, 5, new QStandardItem("0"));

    double priceWithReduction=priceWithoutReduction-remise;

    productModel->setItem(positionInView, 0, new QStandardItem(QVariant(idProduct).toString()));
    productModel->setItem(positionInView, 1, new QStandardItem(p.name));
    productModel->setItem(positionInView, 2, new QStandardItem(QVariant(productQuantity->value()).toString()));
    productModel->setItem(positionInView, 3, new QStandardItem(QVariant(p.price).toString()));
    productModel->setItem(positionInView, 4, new QStandardItem(QVariant(priceWithoutReduction).toString()));
    productModel->setItem(positionInView, 6, new QStandardItem(QVariant(priceWithReduction).toString()));

    productView->resizeColumnsToContents();

}

/**
 * Methode permettant de supprimer un produit du document
 */
void NewDocumentWindow::removeProduct(){
    QItemSelectionModel *select = productView->selectionModel();

    if(select->hasSelection()){

        QModelIndexList rows=select->selectedRows();
        QModelIndex row=rows.at(0);
        productModel->removeRow(row.row());
    }
    else
        QMessageBox::information(this, trUtf8("Suppression impossible"), trUtf8("Suppression impossible, aucun produit sélectionné"));

}

/**
 * Methode permettant de sauvegarder le document
 */
void NewDocumentWindow::save(){
    Document d;
    if(idDocument==-1)
        d=Document();
    else
        d=Document(idDocument);

    d.m_idCustomer=customerName->currentIndex()+1;

    if(reglementMode->currentText()==trUtf8("Cheque"))
        d.m_payment=Document::Cheque;
    else if(reglementMode->currentText()==trUtf8("Espece"))
        d.m_payment=Document::Especes;
    else
        d.m_payment=Document::Virement;

    if(documentType->currentText()==trUtf8("Facture"))
        d.m_docType=Document::Facture;
    else
         d.m_docType=Document::Devis;

    d.m_tva=documentTva->value();

    d.save();
    idDocument=d.getId();

    ProductDocument::removeAllByIdDocument(idDocument);

    for(int i=0;i<productModel->rowCount();i++){
        int prodId=productModel->item(i,0)->text().toInt();
        int quantity=productModel->item(i,2)->text().toInt();
        QString reduction=productModel->item(i,5)->text();

        d.addProduct(prodId,quantity,reduction);
    }

    d.save();
    QStatusBar *statBar = parent->statusBar();
    statBar->showMessage(trUtf8("Informations du document sauvegardé"), 4000);
    parent->setCentralWidget(new SearchWindow(parent));

}

/**
 * Methode permettant de valider un document
 * (redirige vers la page de recherche)
 */
void NewDocumentWindow::validate(){
    int ret = QMessageBox::question(this,trUtf8("Valider le document ?"),trUtf8("La validation d'un document empeche toutes modification ultérieure.<br/>Voulez-vous vraiment valider le document?"),QMessageBox::Yes | QMessageBox::No);

    if (ret == QMessageBox::Yes){
        save();
        Document d(idDocument);
        ValidDocument vd(d);
        vd.save();
        QStatusBar *statBar = parent->statusBar();
        statBar->showMessage(trUtf8("Informations du document sauvegardé et valider"), 4000);
        parent->setCentralWidget(new SearchWindow(parent));
    }
}
