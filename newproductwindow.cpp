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

#include "newproductwindow.h"

/**
 * Constructeur de l'interface d'ajout/edition d'un produit
 * @param parent pointeur vers la fenetre principale
 */
NewProductWindow::NewProductWindow(QMainWindow *parent) :QWidget(parent)
{
    idProduct=-1;
    this->parent=parent;
    createInterface();
}

/**
 * Constructeur de l'interface d'ajout/edition d'un produit
 * Interface initialiser grace au info de la BDD
 * @param parent pointeur vers la fenetre principale
 * @param id identifiant du produit au sein de la BDD
 */
NewProductWindow::NewProductWindow(QMainWindow *parent,int id) :QWidget(parent)
{
    idProduct=id;
    this->parent=parent;
    createInterface();
    initByBDD();
}

/**
 * Methode qui construit l'interface
 */
void NewProductWindow::createInterface(){

    QVBoxLayout *layoutPrinc=new QVBoxLayout;

    /** ********************* **/
    /**       Formulaire      **/
    /** ********************* **/

    QFormLayout *layoutForm = new QFormLayout;

    name=new QLineEdit();
    name->setMinimumWidth(250);
    layoutForm->addRow(tr("Nom du produit: "),name);

    description=new QLineEdit();
    layoutForm->addRow(tr("Description du produit: "),description);

    price=new QDoubleSpinBox ();
    price->setMaximum(9999999.9);
    layoutForm->addRow(tr("Prix unitaire: "),price);


    layoutPrinc->addLayout(layoutForm);

    /** ********************* **/
    /**         Boutons       **/
    /** ********************* **/

    QFormLayout *layoutBouton = new QFormLayout;

    validate=new QPushButton(tr("Valider"));
    layoutBouton->addWidget(validate);

    layoutPrinc->addLayout(layoutBouton);
    setLayout(layoutPrinc);

    /** ********************* **/
    /**          Slots        **/
    /** ********************* **/

    connect(validate, SIGNAL(clicked()), this, SLOT(validateProduct()));

}

/**
 * Methode (Slot) qui va mettre a jour les infos du produit
 * (creation d'un nouveau produit ou mise a jour du produit)
 */
void NewProductWindow::validateProduct(){
    if(idProduct==-1){
        // creation d'un nouveau produit
        Product p;
        p.name=name->text();
        p.description=description->text();
        p.price=price->value();
        p.save();
    }
    else{
        // mise a jour d'un produit
        Product p(idProduct);
        p.name=name->text();
        p.description=description->text();
        p.price=price->value();
        p.save();
        p.updateDocumentPrice();
    }

    QStatusBar *statBar = parent->statusBar();
    statBar->showMessage(tr("Informations produit sauvegardé"), 4000);
    clean();
}

/**
 * Methode qui initialise les champs grace au info de la BDD
 */
void NewProductWindow::initByBDD(){
    Product p(idProduct);
    name->setText(p.name);
    description->setText(p.description);
    price->setValue(p.price);
}

/**
 * Methode permettant de remettre l'interface pret pour l'ajout
 * d'un autre produit
 */
void NewProductWindow::clean(){
    idProduct=-1;
    name->setText("");
    description->setText("");
    price->setValue(0.0);
}
