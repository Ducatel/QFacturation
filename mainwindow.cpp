#include "mainwindow.h"
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    confWin=new ConfigWindow();
    confWin->initByConfigFile();

    QString imgDirPath=QCoreApplication::applicationDirPath()+QDir::separator()+"img"+QDir::separator();

    /** *************************** **/
    /**             Menu            **/
    /** *************************** **/

    QMenu *fileMenu = menuBar()->addMenu(tr("&Fichier"));

    QAction *newCustomerAction = fileMenu->addAction(tr("Nouveau client"));
    newCustomerAction->setIcon(QIcon(imgDirPath+"add-user.png"));
    newCustomerAction->setShortcut(QKeySequence(Qt::CTRL +Qt::SHIFT + Qt::Key_N));

    QAction *newDocAction = fileMenu->addAction(tr("Nouveau document"));
    newDocAction->setIcon(QIcon(imgDirPath+"add-doc.png"));
    newDocAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));

    QAction *editConfAction = fileMenu->addAction(tr("Modifier les informations de la société"));
    editConfAction->setIcon(QIcon(imgDirPath+"edit.png"));

    QAction *searchAction = fileMenu->addAction(tr("Rechercher"));
    searchAction->setIcon(QIcon(imgDirPath+"exit.png"));
    searchAction->setShortcut(QKeySequence(Qt::CTRL +Qt::SHIFT  + Qt::Key_S));

    QAction *quitAction = fileMenu->addAction(tr("Quitter"));
    quitAction->setIcon(QIcon(imgDirPath+"exit.png"));
    quitAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));

    QMenu *helpMenu = menuBar()->addMenu(tr("&Aide"));
    QAction *aboutAction = helpMenu->addAction(tr("A propos"));

    /** *************************** **/
    /**        Barre Outils         **/
    /** *************************** **/

    QToolBar *toolBar = addToolBar("toolBar");
    toolBar->setMovable(false);
    toolBar->addAction(newCustomerAction);
    toolBar->addAction(newDocAction);
    toolBar->addAction(editConfAction);

    /** *************************** **/
    /**            Slots            **/
    /** *************************** **/
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(newCustomerAction, SIGNAL(triggered()), this, SLOT(createNewCustomer()));
    connect(newDocAction, SIGNAL(triggered()), this, SLOT(createNewDocument()));
    connect(editConfAction, SIGNAL(triggered()), this, SLOT(editConfFile()));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(showAboutWindow()));

}

void MainWindow::createNewCustomer(){
    qDebug()<<"new customer";
}

void MainWindow::createNewDocument(){
    qDebug()<<"new document";
}

void MainWindow::editConfFile(){
    confWin->show();
}

void MainWindow::showAboutWindow(){
    qDebug()<<"about frame";
}

MainWindow::~MainWindow()
{
    delete confWin;
}
