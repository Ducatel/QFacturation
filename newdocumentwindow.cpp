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
    layoutPrinc->addWidget(groupBase);

    /** ******************************** **/
    /**     Formulaire Ajout Produit     **/
    /** ******************************** **/

    QGroupBox *groupAddProduct = new QGroupBox(tr("Ajout de produit"), this);
    QFormLayout *layoutFormAddProduct=new QFormLayout;

    productName=new QComboBox(this);
    productName->setToolTip(tr("Nom du produit, description, prix"));
    QList<Product> listProduct= Product::getAllProduct();

    for(int i=0;i<listProduct.size();i++)
        productName->addItem(listProduct.at(i).name+", "+listProduct.at(i).description+", "+QVariant(listProduct.at(i).price).toString()+QString(8364));


    layoutFormAddProduct->addRow(tr("Produit: "),productName);


    productQuantity=new QSpinBox(this);
    productQuantity->setMaximum(99999);
    layoutFormAddProduct->addRow(tr("Quantité: "),productQuantity);


    productReduction=new QLineEdit(this);
    productReduction->setToolTip(tr("Pour une reduction en pourcentage, finir par le symbole %"));
    layoutFormAddProduct->addRow(tr("Reduction: "),productReduction);


    QHBoxLayout *layoutButtonProduct=new QHBoxLayout;

    addProduct=new QPushButton(tr("Ajouter le produit"),this);
    layoutButtonProduct->addWidget(addProduct);

    removeProduct=new QPushButton(tr("Supprimer le produit sélectionné"),this);
    layoutButtonProduct->addWidget(removeProduct);

    layoutFormAddProduct->addRow(tr("Actions: "),layoutButtonProduct);

    groupAddProduct->setLayout(layoutFormAddProduct);
    layoutPrinc->addWidget(groupAddProduct);

    /** ******************************** **/
    /**     Produit dans le document     **/
    /** ******************************** **/





    /** ******************************** **/
    /**               Slots              **/
    /** ******************************** **/

    connect(documentType, SIGNAL(currentIndexChanged(int)), this, SLOT(turnOnOffDocumentType(int)));



    setLayout(layoutPrinc);

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
