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

#ifndef CONFIGWINDOW_H
#define CONFIGWINDOW_H

#include <QString>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QCoreApplication>

#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QMainWindow>
#include <QDialog>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QMessageBox>
#include <QStatusBar>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include <QDomDocument>
#include <QDomNode>
#include <QDomElement>

#define qDebug(msg) qDebug() << Q_FUNC_INFO << msg


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
        QSpinBox *zipCode;
        QLineEdit *country;
        QLineEdit *phone;
        QLineEdit *email;
        QLineEdit *internetSite;
        QLineEdit *siret;
        QLineEdit *ape;

        QLineEdit *city;


        QPushButton *validate;
        QPushButton *close;

        void writeXMLConfigFile();
        bool createDatabase();
        bool createDocumentTemplate();

        QString mbddFilePath;
        QString mconfigFilePath;
        QString mtemplateFilePath;

    private slots:
        void validateInfo();
};

#endif // CONFIGWINDOW_H
