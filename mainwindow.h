#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include "configwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = 0);
        ~MainWindow();

    private:
        ConfigWindow *confWin;


    private slots:
        void createNewCustomer();
        void createNewDocument();
        void editConfFile();
        void showAboutWindow();
};

#endif // MAINWINDOW_H
