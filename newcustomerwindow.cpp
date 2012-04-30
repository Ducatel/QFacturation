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

#include "newcustomerwindow.h"

/**
 * Constructeur de l'interface d'ajout/edition d'un client
 * @param parent pointeur vers la fenetre principale
 */
NewCustomerWindow::NewCustomerWindow(QMainWindow *parent) :QWidget(parent){
    idCustomer=-1;
    this->parent=parent;
    createInterface();
}

/**
 * Constructeur de l'interface d'ajout/edition d'un client
 * Interface initialiser grace au info de la BDD
 * @param parent pointeur vers la fenetre principale
 * @param id identifiant du client au sein de la BDD
 */
NewCustomerWindow::NewCustomerWindow(QMainWindow *parent,int id) :QWidget(parent){
    idCustomer=id;
    this->parent=parent;
    createInterface();
    initByBDD();
}

/**
 * Methode qui construit l'interface
 */
void NewCustomerWindow::createInterface(){
    QVBoxLayout *layoutPrinc=new QVBoxLayout;

    /** ********************* **/
    /**       Formulaire      **/
    /** ********************* **/

    QFormLayout *layoutForm = new QFormLayout;

    name=new QLineEdit();
    name->setMinimumWidth(250);
    layoutForm->addRow(trUtf8("Nom du client: "),name);

    adress=new QLineEdit();
    layoutForm->addRow(trUtf8("Adresse du client: "),adress);

    adress2=new QLineEdit();
    layoutForm->addRow(trUtf8("Complement d'adresse: "),adress2);

    postalCode=new QSpinBox();
    postalCode->setMaximum(9999999);
    layoutForm->addRow(trUtf8("Code Postal: "),postalCode);

    city=new QLineEdit();
    layoutForm->addRow(trUtf8("Ville: "),city);

    country=new QLineEdit();
    layoutForm->addRow(trUtf8("Pays: "),country);

    email=new QLineEdit();
    layoutForm->addRow(trUtf8("Email: "),email);

    phone=new QLineEdit();
    layoutForm->addRow(trUtf8("Numero de téléphone: "),phone);

    layoutPrinc->addLayout(layoutForm);

    /** ********************* **/
    /**         Boutons       **/
    /** ********************* **/

    QFormLayout *layoutBouton = new QFormLayout;

    validate=new QPushButton(trUtf8("Valider"));
    layoutBouton->addWidget(validate);

    layoutPrinc->addLayout(layoutBouton);
    setLayout(layoutPrinc);

    /** ********************* **/
    /**          Slots        **/
    /** ********************* **/

    connect(validate, SIGNAL(clicked()), this, SLOT(validateCustomer()));
}

/**
 * Methode qui initialise les champs grace au info de la BDD
 */
void NewCustomerWindow::initByBDD(){
    Customer c(idCustomer);
    name->setText(c.m_name);
    adress->setText(c.m_adress);
    adress2->setText(c.m_adress2);
    city->setText(c.m_city);
    country->setText(c.m_country);
    email->setText(c.m_email);
    phone->setText(c.m_phone);
    postalCode->setValue(c.m_postalCode);
}

/**
 * Methode (Slot) qui va mettre a jour les infos du client
 * (creation d'un nouveau client ou mise a jour du client)
 */
void NewCustomerWindow::validateCustomer(){

    if(idCustomer==-1){
        //creation d'un nouveau client
        Customer c;
        c.m_name=name->text();
        c.m_adress=adress->text();
        c.m_adress2=adress2->text();
        c.m_city=city->text();
        c.m_country=country->text();
        c.m_email=email->text();
        c.m_phone=phone->text();
        c.m_postalCode=postalCode->value();
        c.save();
    }
    else{
        //Mise a jour d'un client
        Customer c(idCustomer);
        c.m_name=name->text();
        c.m_adress=adress->text();
        c.m_adress2=adress2->text();
        c.m_city=city->text();
        c.m_country=country->text();
        c.m_email=email->text();
        c.m_phone=phone->text();
        c.m_postalCode=postalCode->value();
        c.save();
    }

    QStatusBar *statBar = parent->statusBar();
    statBar->showMessage(trUtf8("Informations client sauvegardé"), 4000);
    clean();

}

/**
 * Methode permettant de remettre l'interface pret pour l'ajout
 * d'un autre client
 */
void NewCustomerWindow::clean(){
    idCustomer=-1;
    name->setText("");
    adress->setText("");
    adress2->setText("");
    city->setText("");
    country->setText("");
    email->setText("");
    phone->setText("");
    postalCode->setValue(0);
}

