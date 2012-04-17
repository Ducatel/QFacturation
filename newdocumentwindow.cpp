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
    createInterface();
}

NewDocumentWindow::NewDocumentWindow(QMainWindow *parent,int identifiant){

}

void NewDocumentWindow::createInterface(){
    QVBoxLayout *layoutPrinc=new QVBoxLayout;

    /** ******************************** **/
    /**        Formulaire de Base        **/
    /** ******************************** **/

    QGroupBox *groupBase = new QGroupBox(tr("Informations de base"), this);
    QFormLayout *layoutFormBase=new QFormLayout;

    customerName=new QComboBox(this);
    QList<Customer> list= Customer::getAllCustomer();

    for(int i=0;i<list.size();i++)
        customerName->addItem(list.at(i).name+", "+list.at(i).city);

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


    connect(documentType, SIGNAL(currentIndexChanged(int)), this, SLOT(turnOnOffDocumentType(int)));



    setLayout(layoutPrinc);

}

/**
 * Methode qui permet d'activ� ou de desactiv� le choix du type
 * de reglement (SLOT).
 * @param currentIndex index qui viens d'etre selectionner
 */
void NewDocumentWindow::turnOnOffDocumentType(int currentIndex){

    // currentIndex ==0, facture
    // currentIndex ==1, devis

    if(currentIndex==0)
        reglementMode->setDisabled(false);
    else
        reglementMode->setDisabled(true);

}
