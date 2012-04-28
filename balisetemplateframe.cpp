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

    QGroupBox *groupCompagny = new QGroupBox(tr("Société"), this);
    QFormLayout *layoutCompagny=new QFormLayout;

    layoutCompagny->addRow(tr("Balise"),new QLabel(tr("Description"),this));
    layoutCompagny->addRow("{compagnyName}",new QLabel(tr("Nom de la société"),this));
    layoutCompagny->addRow("{description}",new QLabel(tr("Déscription de l'activité de la société"),this));
    layoutCompagny->addRow("{compagnyAdress}",new QLabel(tr("Adresse de la société"),this));
    layoutCompagny->addRow("{compagnyAdress2}",new QLabel(tr("Complement d'adresse de la société"),this));
    layoutCompagny->addRow("{compagnyZipCode}",new QLabel(tr("Code postal de la société"),this));
    layoutCompagny->addRow("{compagnyCity}",new QLabel(tr("Ville de la société"),this));
    layoutCompagny->addRow("{compagnyCountry}",new QLabel(tr("Pays de la société"),this));
    layoutCompagny->addRow("{siret}",new QLabel(tr("Numéro de SIRET de la société"),this));
    layoutCompagny->addRow("{ape}",new QLabel(tr("Numéro APE de la société"),this));
    layoutCompagny->addRow("{phone}",new QLabel(tr("Numéro de téléphone de la société"),this));
    layoutCompagny->addRow("{email}",new QLabel(tr("Adresse email de la société"),this));
    layoutCompagny->addRow("{site}",new QLabel(tr("Site internet de la société"),this));

    groupCompagny->setLayout(layoutCompagny);

    QGroupBox *groupCustomer = new QGroupBox(tr("Client"), this);
    QFormLayout *layoutCustomer=new QFormLayout;

    layoutCustomer->addRow(tr("Balise"),new QLabel(tr("Description"),this));
    layoutCustomer->addRow("{customerName}",new QLabel(tr("Nom du client"),this));
    layoutCustomer->addRow("{customerAdress}",new QLabel(tr("Adresse du client"),this));
    layoutCustomer->addRow("{customerAdress2}",new QLabel(tr("Complement d'adresse du client"),this));
    layoutCustomer->addRow("{customerZipCode}",new QLabel(tr("Code postal du client"),this));
    layoutCustomer->addRow("{customerCity}",new QLabel(tr("Ville du client"),this));
    layoutCustomer->addRow("{customerCountry}",new QLabel(tr("Pays du client"),this));

    groupCustomer->setLayout(layoutCustomer);

    QGroupBox *groupDocument = new QGroupBox(tr("Document"), this);
    QFormLayout *layoutDocument=new QFormLayout;

    layoutDocument->addRow(tr("Balise"),new QLabel(tr("Description"),this));
    layoutDocument->addRow("{documentType}",new QLabel(tr("Type du document (facture ou devis)"),this));
    layoutDocument->addRow("{documentId}",new QLabel(tr("Identifiant du document"),this));
    layoutDocument->addRow("{date}",new QLabel(tr("Date de création du document"),this));
    layoutDocument->addRow("{payment}",new QLabel(tr("Moyen de paiement utilisé par le client"),this));
    layoutDocument->addRow("{product}",new QLabel(tr("Liste des produits du document"),this));
    layoutDocument->addRow("{tva}",new QLabel(tr("Taxe sur le document"),this));
    layoutDocument->addRow("{totalPriceHT}",new QLabel(tr("Prix hors taxe du document"),this));
    layoutDocument->addRow("{totalPriceTTC}",new QLabel(tr("Prix toutes taxes comprise du document"),this));

    groupDocument->setLayout(layoutDocument);

    layoutPrinc->addWidget(groupCustomer,0,0);
    layoutPrinc->addWidget(groupDocument,0,1);
    layoutPrinc->addWidget(groupCompagny,1,0,1,2);

    setLayout(layoutPrinc);

    setModal(true);
    setWindowTitle(tr("Balise disponible pour le template"));
    show();
}
