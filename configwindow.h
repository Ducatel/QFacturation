#ifndef CONFIGWINDOW_H
#define CONFIGWINDOW_H
#include <QtGui>
#include <QtXml>
#include <QtSql>

/**
 * Class qui gere la fenetre de configuration de base
 * @author David Ducatel
 */
class ConfigWindow : public QDialog{
    Q_OBJECT
    public:
        ConfigWindow(QMainWindow *parent);
        void initByConfigFile();
    private:
        QMainWindow *parent;

        QLineEdit *companyName;
        QLineEdit *description;
        QLineEdit *adress;
        QLineEdit *adress2;
        QLineEdit *zipCode;
        QLineEdit *city;
        QLineEdit *country;
        QLineEdit *phone;
        QLineEdit *email;
        QLineEdit *internetSite;
        QLineEdit *siret;
        QLineEdit *ape;

        QPushButton *validate;
        QPushButton *close;

        void writeXMLConfigFile();
        bool createDatabase();


        QString bddFilePath;
        QString configFilePath;

    private slots:
        void validateInfo();
};

#endif // CONFIGWINDOW_H
