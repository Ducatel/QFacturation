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

#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include <QtGui>
#include <QtSql>
#include "newcustomerwindow.h"
#include "newdocumentwindow.h"
#include "newproductwindow.h"

/**
 * Class qui gere l'interface de recherche
 * @author David Ducatel
 */
class SearchWindow : public QWidget
{
    Q_OBJECT
    public:
        explicit SearchWindow(QMainWindow *parent = 0);

    private:
        QMainWindow *parent;

        QPushButton *searchButtonCustomer;
        QPushButton *editButtonCustomer;
        QLineEdit *lineSearchClient;
        QComboBox *typeSearchClient;
        QStandardItemModel *customerModel;
        QTableView *customerView;

        QPushButton *searchButtonProduct;
        QPushButton *editButtonProduct;
        QLineEdit *lineSearchProduct;
        QComboBox *typeSearchProduct;
        QStandardItemModel *productModel;
        QTableView *productView;

        void loadCustomer();
        void loadProduct();
        void loadDocument();

        QGroupBox* createCustomerSearchInterface();
        QGroupBox* createProductSearchInterface();


    private slots:
        void showCustomerResult();
        void showProductResult();
        void editCustomer();
        void editProduct();

};

#endif // SEARCHWINDOW_H
