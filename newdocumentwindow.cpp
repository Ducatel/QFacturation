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
}

NewDocumentWindow::NewDocumentWindow(QMainWindow *parent,int identifiant){
    this->parent=parent;
    idDocument=identifiant;
    createInterface();
    //TODO faire le init by DB
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


    setLayout(layoutPrinc);

}

/**
 * Methode permettant de creer l'interface de saisie des
 * information de base du document
 * @return l'interface
 */
QGroupBox* NewDocumentWindow::createBasicInfoInterface(){

    QGroupBox *groupBase = new QGroupBox(tr("Informations de base"), this);
    QFormLayout *layoutFormBase=new QFormLayout;

    customerName=new QComboBox(this);
    customerName->setToolTip(tr("Nom du client, ville"));
    QList<Customer> listCustomer= Customer::getAllCustomer();

    for(int i=0;i<listCustomer.size();i++)
        customerName->addItem(listCustomer.at(i).name+", "+listCustomer.at(i).city);

    layoutFormBase->addRow(tr("Client: "),customerName);


    documentType=new QComboBox(this);
    documentType->addItem(tr("Facture"));
    documentType->addItem(tr("Devis"));
    layoutFormBase->addRow(tr("Type de document: "),documentType);


    reglementMode=new QComboBox(this);
    reglementMode->addItem(tr("Cheque"));
    reglementMode->addItem(tr("Espece"));
    reglementMode->addItem(tr("Virement"));
    layoutFormBase->addRow(tr("Mode de paiement: "),reglementMode);


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

    QGroupBox *groupAddProduct = new QGroupBox(tr("Ajout de produit"), this);
    QFormLayout *layoutFormAddProduct=new QFormLayout;

    productName=new QComboBox(this);
    productName->setToolTip(tr("Nom du produit, description, prix"));
    QList<Product> listProduct= Product::getAllProduct();

    for(int i=0;i<listProduct.size();i++)
        productName->addItem(listProduct.at(i).name+", "+listProduct.at(i).description+", "+QVariant(listProduct.at(i).price).toString()+QString(8364));

    layoutFormAddProduct->addRow(tr("Produit: "),productName);


    productQuantity=new QSpinBox(this);
    productQuantity->setMinimum(1);
    productQuantity->setMaximum(99999);
    layoutFormAddProduct->addRow(tr("Quantité: "),productQuantity);

    productReduction=new QDoubleSpinBox(this);
    productQuantity->setMinimum(0);
    productQuantity->setMaximum(99999);
    layoutFormAddProduct->addRow(tr("Remise: "),productReduction);

    QGroupBox *groupTypeReduction = new QGroupBox(this);

    fixedValue=new QRadioButton(tr("Valeur fixe"),this);
    fixedValue->setChecked(true);
    percentage=new QRadioButton(tr("Pourcentage"),this);

    QHBoxLayout *layoutRadioButton = new QHBoxLayout;
    layoutRadioButton->addWidget(fixedValue);
    layoutRadioButton->addWidget(percentage);

    groupTypeReduction->setLayout(layoutRadioButton);

    layoutFormAddProduct->addRow(tr("Type de reduction"),groupTypeReduction);


    QHBoxLayout *layoutButtonProduct=new QHBoxLayout;

    buttonAddProduct=new QPushButton(tr("Ajouter le produit"),this);
    layoutButtonProduct->addWidget(buttonAddProduct);

    buttonRemoveProduct=new QPushButton(tr("Supprimer le produit sélectionné"),this);
    layoutButtonProduct->addWidget(buttonRemoveProduct);

    layoutFormAddProduct->addRow(tr("Actions: "),layoutButtonProduct);

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
    QGroupBox *groupProduct = new QGroupBox(tr("Produit dans le document"), this);


    productModel = new QStandardItemModel(0, 7);
    productModel->setHeaderData(0,Qt::Horizontal,"id");
    productModel->setHeaderData(1,Qt::Horizontal,tr("Nom"));
    productModel->setHeaderData(2,Qt::Horizontal,tr("Quantité"));
    productModel->setHeaderData(3,Qt::Horizontal,tr("Prix unitaire"));
    productModel->setHeaderData(4,Qt::Horizontal,tr("Prix de base"));
    productModel->setHeaderData(5,Qt::Horizontal,tr("Remise"));
    productModel->setHeaderData(6,Qt::Horizontal,tr("Prix final"));


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
        }
        else{
            remise=(priceWithoutReduction*productReduction->value())/100.0;
        }
    }
    double priceWithReduction=priceWithoutReduction-remise;


    productModel->setItem(positionInView, 0, new QStandardItem(QVariant(idProduct).toString()));
    productModel->setItem(positionInView, 1, new QStandardItem(p.name));
    productModel->setItem(positionInView, 2, new QStandardItem(QVariant(productQuantity->value()).toString()));
    productModel->setItem(positionInView, 3, new QStandardItem(QVariant(p.price).toString()));
    productModel->setItem(positionInView, 4, new QStandardItem(QVariant(priceWithoutReduction).toString()));
    productModel->setItem(positionInView, 5, new QStandardItem(QVariant(remise).toString()));
    productModel->setItem(positionInView, 6, new QStandardItem(QVariant(priceWithReduction).toString()));

    productView->resizeColumnsToContents();

}

/**
 * Methode permettant de supprimer un produit du document
 */
void NewDocumentWindow::removeProduct(){

}
