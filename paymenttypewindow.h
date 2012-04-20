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

#ifndef PAYMENTTYPEWINDOW_H
#define PAYMENTTYPEWINDOW_H

#include <QtGui>
#include "document.h"


/**
 * Class qui permet de gerer la fenetre de choix du type de moyen
 * de paiement pour la transformation de devis en facture
 */
class PaymentTypeWindow : public QDialog
{
    Q_OBJECT
    public:
        explicit PaymentTypeWindow(QWidget *parent);

    private:
        QPushButton *valideButton;
        QComboBox *payment;

    protected :
        void closeEvent(QCloseEvent* event);

    private slots:
        void valide();

    signals:
        void choixEffectuer(Document::PaymentEnum);

};

#endif // PAYMENTTYPEWINDOW_H
