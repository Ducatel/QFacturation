#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include "configwindow.h"
#include "aboutframe.h"

/**
 * Class qui gere l'interface principale
 * @author David Ducatel
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = 0);
        ~MainWindow();

    private:
        ConfigWindow *confWin;
        AboutFrame *aboutWin;


    private slots:
        void createNewCustomer();
        void createNewDocument();
        void createNewProduct();
        void editConfFile();
        void showAboutWindow();
        void search();
};

#endif // MAINWINDOW_H
