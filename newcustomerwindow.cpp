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
    layoutForm->addRow(tr("Nom du client: "),name);

    adress=new QLineEdit();
    layoutForm->addRow(tr("Adresse du client: "),adress);

    adress2=new QLineEdit();
    layoutForm->addRow(tr("Complement d'adresse: "),adress2);

    postalCode=new QSpinBox();
    postalCode->setMaximum(9999999);
    layoutForm->addRow(tr("Code Postal: "),postalCode);

    city=new QLineEdit();
    layoutForm->addRow(tr("Ville: "),city);

    country=new QLineEdit();
    layoutForm->addRow(tr("Pays: "),country);

    email=new QLineEdit();
    layoutForm->addRow(tr("Email: "),email);

    phone=new QLineEdit();
    layoutForm->addRow(tr("Numero de téléphone: "),phone);

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

    connect(validate, SIGNAL(clicked()), this, SLOT(validateCustomer()));
}

/**
 * Methode qui initialise les champs grace au info de la BDD
 */
void NewCustomerWindow::initByBDD(){
    Customer c(idCustomer);
    name->setText(c.name);
    adress->setText(c.adress);
    adress2->setText(c.adress2);
    city->setText(c.city);
    country->setText(c.country);
    email->setText(c.email);
    phone->setText(c.phone);
    postalCode->setValue(c.postalCode);
}

/**
 * Methode (Slot) qui va mettre a jour les infos du client
 * (creation d'un nouveau client ou mise a jour du client)
 */
void NewCustomerWindow::validateCustomer(){

    if(idCustomer==-1){
        //creation d'un nouveau client
        Customer c;
        c.name=name->text();
        c.adress=adress->text();
        c.adress2=adress2->text();
        c.city=city->text();
        c.country=country->text();
        c.email=email->text();
        c.phone=phone->text();
        c.postalCode=postalCode->value();
        c.save();
    }
    else{
        //Mise a jour d'un client
        Customer c(idCustomer);
        c.name=name->text();
        c.adress=adress->text();
        c.adress2=adress2->text();
        c.city=city->text();
        c.country=country->text();
        c.email=email->text();
        c.phone=phone->text();
        c.postalCode=postalCode->value();
        c.save();
    }

    QStatusBar *statBar = parent->statusBar();
    statBar->showMessage(tr("Informations client sauvegardé"), 4000);
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

