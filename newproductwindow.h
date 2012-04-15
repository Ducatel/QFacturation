#ifndef NEWPRODUCTWINDOW_H
#define NEWPRODUCTWINDOW_H

#include <QtGui>
#include "product.h"

/**
 * Class qui gere le widget permettant de créer/editer un nouveau produit
 * @author David Ducatel
 */
class NewProductWindow : public QWidget
{
    Q_OBJECT

    public:
        explicit NewProductWindow(QMainWindow *parent);
        explicit NewProductWindow(QMainWindow *parent,int id);

        QLineEdit *name;
        QLineEdit *description;
        QDoubleSpinBox *price;

    private:
        void createInterface();
        void initByBDD();
        void clean();

        QMainWindow *parent;
        int idProduct;
        QPushButton *validate;

    private slots:
        void validateProduct();


};

#endif // NEWPRODUCTWINDOW_H
