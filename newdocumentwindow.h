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

#ifndef NEWDOCUMENTWINDOW_H
#define NEWDOCUMENTWINDOW_H

#include <QtGui>

#define qDebug(msg) qDebug() << Q_FUNC_INFO << msg

#include "customer.h"
#include "product.h"
#include "document.h"
#include "searchwindow.h"
#include "validdocument.h"
/**
 * Class qui va géré l'interface de création/edition d'un document
 * @author David Ducatel
 */
class NewDocumentWindow : public QWidget
{
    Q_OBJECT
    public:
        explicit NewDocumentWindow(QMainWindow *parent);
        explicit NewDocumentWindow(QMainWindow *parent,int identifiant);

    private:
        bool isSave;
        int idDocument;
        QMainWindow *parent;

        QComboBox *customerName;
        QComboBox *documentType;
        QComboBox *reglementMode;

        QComboBox *productName;
        QSpinBox *productQuantity;
        QDoubleSpinBox *productReduction;
        QRadioButton *percentage;
        QRadioButton *fixedValue;
        QPushButton *buttonAddProduct;
        QPushButton *buttonRemoveProduct;

        QStandardItemModel *productModel;
        QTableView *productView;

        QPushButton *validateButton;
        QPushButton *saveButton;


        void createInterface();
        QGroupBox* createBasicInfoInterface();
        QGroupBox* createAddProductInterface();
        QGroupBox* createProductViewInterface();
        void initByBDD();


    private slots:
        void turnOnOffDocumentType(int currentIndex);
        void addProduct();
        void removeProduct();
        void save();
        void validate();

};

#endif // NEWDOCUMENTWINDOW_H
