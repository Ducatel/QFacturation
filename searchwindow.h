#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include <QtGui>
#include <QtSql>

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
        QLineEdit *lineSearchClient;
        QComboBox *typeSearchClient;
        QStandardItemModel *customerModel;
        QTableView *customerView;

        QPushButton *buttonSearchProduct;
        QLineEdit *lineSearchProduct;
        QComboBox *typeSearchProduct;
        QStandardItemModel *productModel;
        QTableView *productView;

        void loadCustomer();
        void loadProduct();
        void loadDocument();

    private slots:
        void showCustomerResult();
        void showProductResult();

};

#endif // SEARCHWINDOW_H
