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

#ifndef NEWCUSTOMERWINDOW_H
#define NEWCUSTOMERWINDOW_H

#include <QtGui>
#include "customer.h"

/**
 * Class qui gere le widget permettant de créer/editer un nouveau client
 * @author David Ducatel
 */
class NewCustomerWindow : public QWidget
{
    Q_OBJECT
    public:
        explicit NewCustomerWindow(QMainWindow *parent);
        explicit NewCustomerWindow(QMainWindow *parent,int id);


        QLineEdit *name;
        QLineEdit *adress;
        QLineEdit *adress2;
        QLineEdit *city;
        QLineEdit *country;
        QLineEdit *email;
        QLineEdit *phone;
        QSpinBox  *postalCode;

    private:
        void createInterface();
        void initByBDD();
        void clean();

        QPushButton *validate;
        QMainWindow *parent;
        int idCustomer;


    private slots:
        void validateCustomer();

};

#endif // NEWCUSTOMERWINDOW_H
