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

#include "paymenttypewindow.h"

/**
 * Constructeur de l'interface de choix du type de paiement
 * lors d'une transformation devis --> facture
 */
PaymentTypeWindow::PaymentTypeWindow(QWidget *parent) :QDialog(parent){
    QVBoxLayout *layoutPrinc=new QVBoxLayout;

    QFormLayout *layoutForm=new QFormLayout;
    payment=new QComboBox(this);
    payment->addItem(trUtf8("Cheque"));
    payment->addItem(trUtf8("Virement"));
    payment->addItem(trUtf8("Espece"));
    layoutForm->addRow(trUtf8("Moyen de paiement: "),payment);

    layoutPrinc->addLayout(layoutForm);

    valideButton=new QPushButton(trUtf8("Valider"),this);
    layoutPrinc->addWidget(valideButton);



    connect(valideButton,SIGNAL(clicked()),this,SLOT(valide()));
    setLayout(layoutPrinc);
    setWindowIcon(QIcon(QCoreApplication::applicationDirPath()+QDir::separator()+"img"+QDir::separator()+"icon.png"));
    setModal(true);
    setWindowTitle(trUtf8("Transformation Devis --> Facture"));

}

void PaymentTypeWindow::valide(){
    Document::PaymentEnum type=Document::Cheque;
    if(payment->currentIndex()==0){
        type=Document::Cheque;
    }
    else if(payment->currentIndex()==1){
         type=Document::Virement;
    }
    else if(payment->currentIndex()==2){
         type=Document::Especes;
    }
    emit choixEffectuer(type);
    this->accept();
}

void PaymentTypeWindow::closeEvent(QCloseEvent* event){
    QMessageBox::information(this, trUtf8("Fermeture impossible"), trUtf8("Vous ne pouvez fermer cette fenetre. Veuillez valider votre saisie"));

    event->ignore();
}
