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

#include "balisetemplateframe.h"

BaliseTemplateFrame::BaliseTemplateFrame(QWidget *parent): QDialog(parent){

    QGridLayout *layoutPrinc=new QGridLayout(this);

    QGroupBox *groupCompagny = new QGroupBox(trUtf8("Société"), this);
    QFormLayout *layoutCompagny=new QFormLayout;

    layoutCompagny->addRow(trUtf8("Balise"),new QLabel(trUtf8("Description"),this));
    layoutCompagny->addRow("{compagnyName}",new QLabel(trUtf8("Nom de la société"),this));
    layoutCompagny->addRow("{description}",new QLabel(trUtf8("Déscription de l'activité de la société"),this));
    layoutCompagny->addRow("{compagnyAdress}",new QLabel(trUtf8("Adresse de la société"),this));
    layoutCompagny->addRow("{compagnyAdress2}",new QLabel(trUtf8("Complement d'adresse de la société"),this));
    layoutCompagny->addRow("{compagnyZipCode}",new QLabel(trUtf8("Code postal de la société"),this));
    layoutCompagny->addRow("{compagnyCity}",new QLabel(trUtf8("Ville de la société"),this));
    layoutCompagny->addRow("{compagnyCountry}",new QLabel(trUtf8("Pays de la société"),this));
    layoutCompagny->addRow("{siret}",new QLabel(trUtf8("Numéro de SIRET de la société"),this));
    layoutCompagny->addRow("{ape}",new QLabel(trUtf8("Numéro APE de la société"),this));
    layoutCompagny->addRow("{phone}",new QLabel(trUtf8("Numéro de téléphone de la société"),this));
    layoutCompagny->addRow("{email}",new QLabel(trUtf8("Adresse email de la société"),this));
    layoutCompagny->addRow("{site}",new QLabel(trUtf8("Site internet de la société"),this));

    groupCompagny->setLayout(layoutCompagny);

    QGroupBox *groupCustomer = new QGroupBox(trUtf8("Client"), this);
    QFormLayout *layoutCustomer=new QFormLayout;

    layoutCustomer->addRow(trUtf8("Balise"),new QLabel(trUtf8("Description"),this));
    layoutCustomer->addRow("{customerName}",new QLabel(trUtf8("Nom du client"),this));
    layoutCustomer->addRow("{customerAdress}",new QLabel(trUtf8("Adresse du client"),this));
    layoutCustomer->addRow("{customerAdress2}",new QLabel(trUtf8("Complement d'adresse du client"),this));
    layoutCustomer->addRow("{customerZipCode}",new QLabel(trUtf8("Code postal du client"),this));
    layoutCustomer->addRow("{customerCity}",new QLabel(trUtf8("Ville du client"),this));
    layoutCustomer->addRow("{customerCountry}",new QLabel(trUtf8("Pays du client"),this));

    groupCustomer->setLayout(layoutCustomer);

    QGroupBox *groupDocument = new QGroupBox(trUtf8("Document"), this);
    QFormLayout *layoutDocument=new QFormLayout;

    layoutDocument->addRow(trUtf8("Balise"),new QLabel(trUtf8("Description"),this));
    layoutDocument->addRow("{documentType}",new QLabel(trUtf8("Type du document (facture ou devis)"),this));
    layoutDocument->addRow("{documentId}",new QLabel(trUtf8("Identifiant du document"),this));
    layoutDocument->addRow("{date}",new QLabel(trUtf8("Date de création du document"),this));
    layoutDocument->addRow("{payment}",new QLabel(trUtf8("Moyen de paiement utilisé par le client"),this));
    layoutDocument->addRow("{product}",new QLabel(trUtf8("Liste des produits du document"),this));
    layoutDocument->addRow("{tva}",new QLabel(trUtf8("Taxe sur le document"),this));
    layoutDocument->addRow("{totalPriceHT}",new QLabel(trUtf8("Prix hors taxe du document"),this));
    layoutDocument->addRow("{totalPriceTTC}",new QLabel(trUtf8("Prix toutes taxes comprise du document"),this));

    groupDocument->setLayout(layoutDocument);

    layoutPrinc->addWidget(groupCustomer,0,0);
    layoutPrinc->addWidget(groupDocument,0,1);
    layoutPrinc->addWidget(groupCompagny,1,0,1,2);

    setLayout(layoutPrinc);

    setModal(true);
    setWindowTitle(trUtf8("Balise disponible pour le template"));
    show();
}
