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
#define qDebug(msg) qDebug() << Q_FUNC_INFO << msg

#include "newcustomerwindow.h"
#include "newdocumentwindow.h"
#include "newproductwindow.h"
#include "validdocument.h"
#include "paymenttypewindow.h"

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

        QPushButton *searchButtonDocumentNotValidate;
        QPushButton *editButtonDocumentNotValidate;
        QPushButton *validateDocumentButton;
        QPushButton *deleteButtonDocumentNotValidate;
        QLineEdit *lineSearchDocumentNotValidate;
        QComboBox *typeSearchDocumentNotValidate;
        QComboBox *typeDocumentNotValidate;
        QComboBox *paymentDocumentNotValidate;
        QStandardItemModel *documentNotValidateModel;
        QTableView *documentNotValidateView;

        QLineEdit *lineSearchDocumentValidate;
        QComboBox *typeSearchDocumentValidate;
        QComboBox *typeDocumentValidate;
        QComboBox *paymentDocumentValidate;
        QStandardItemModel *documentValidateModel;
        QTableView *documentValidateView;
        QPushButton *searchButtonDocumentValidate;
        QPushButton *printButtonDocumentValidate;
        QPushButton *transformDocumentButton;




        void loadCustomer();
        void loadProduct();
        void loadDocumentNotValidate();
        void loadDocumentValidate();

        QGroupBox* createCustomerSearchInterface();
        QGroupBox* createProductSearchInterface();
        QGroupBox* createNotValidateDocumentSearchInterface();
        QGroupBox* createValidateDocumentSearchInterface();




    private slots:
        void showCustomerResult();
        void showProductResult();
        void editCustomer();
        void editProduct();
        void showDocumentNotValideResult();
        void editDocument();
        void valideDocument();
        void deleteDocument();
        void showDocumentValideResult();
        void printDocument();
        void transformDocument();
        void endTransformDocument(Document::PaymentEnum choice);

};

#endif // SEARCHWINDOW_H
