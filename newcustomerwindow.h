#ifndef NEWCUSTOMERWINDOW_H
#define NEWCUSTOMERWINDOW_H

#include <QtGui>
#include "customer.h"

/**
 * Class qui gere le widget permettant de créer un nouveau client
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
