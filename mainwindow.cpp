#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    confWin=new ConfigWindow(this);
    confWin->initByConfigFile();

    aboutWin=new AboutFrame();

    QString imgDirPath=QCoreApplication::applicationDirPath()+QDir::separator()+"img"+QDir::separator();

    setWindowIcon(QIcon(imgDirPath+"icon.png"));
    setWindowTitle(QString("QFacturation"));

    QStatusBar *statBar = statusBar();
    statBar->showMessage(tr("Pr�t"));

    /** *************************** **/
    /**             Menu            **/
    /** *************************** **/

    QMenu *fileMenu = menuBar()->addMenu(tr("&Fichier"));

    QAction *newCustomerAction = fileMenu->addAction(tr("Nouveau client"));
    newCustomerAction->setIcon(QIcon(imgDirPath+"add-user.png"));
    newCustomerAction->setShortcut(QKeySequence(Qt::CTRL +Qt::SHIFT + Qt::Key_N));
    newCustomerAction->setStatusTip(tr("Cr�er un nouveau client"));

    QAction *newProductAction = fileMenu->addAction(tr("Nouveau produit"));
    newProductAction->setIcon(QIcon(imgDirPath+"product.png"));
    newProductAction->setShortcut(QKeySequence(Qt::CTRL +Qt::ALT + Qt::Key_N));
    newProductAction->setStatusTip(tr("Cr�er un nouveau produit"));

    QAction *newDocAction = fileMenu->addAction(tr("Nouveau document"));
    newDocAction->setIcon(QIcon(imgDirPath+"add-doc.png"));
    newDocAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    newDocAction->setStatusTip(tr("Cr�er un nouveau document (devis ou facture)"));

    QAction *editConfAction = fileMenu->addAction(tr("Modifier les informations de la soci�t�"));
    editConfAction->setIcon(QIcon(imgDirPath+"edit.png"));
    editConfAction->setStatusTip(tr("Modifier les informations de la soci�t�"));

    QAction *searchAction = fileMenu->addAction(tr("Rechercher"));
    searchAction->setIcon(QIcon(imgDirPath+"search.png"));
    searchAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F));
    searchAction->setStatusTip(tr("Rechercher un client, un produit ou un document"));

    QAction *quitAction = fileMenu->addAction(tr("Quitter"));
    quitAction->setIcon(QIcon(imgDirPath+"exit.png"));
    quitAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    quitAction->setStatusTip(tr("Quitte le programme"));

    QMenu *helpMenu = menuBar()->addMenu(tr("&Aide"));
    QAction *aboutAction = helpMenu->addAction(tr("A propos"));

    /** *************************** **/
    /**        Barre Outils         **/
    /** *************************** **/

    QToolBar *toolBar = addToolBar("toolBar");
    toolBar->setMovable(false);
    toolBar->addAction(newCustomerAction);
    toolBar->addAction(newProductAction);
    toolBar->addAction(newDocAction);
    toolBar->addAction(editConfAction);
    toolBar->addAction(searchAction);

    /** *************************** **/
    /**            Slots            **/
    /** *************************** **/

    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(newCustomerAction, SIGNAL(triggered()), this, SLOT(createNewCustomer()));
    connect(newProductAction, SIGNAL(triggered()), this, SLOT(createNewProduct()));
    connect(newDocAction, SIGNAL(triggered()), this, SLOT(createNewDocument()));
    connect(editConfAction, SIGNAL(triggered()), this, SLOT(editConfFile()));    
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(showAboutWindow()));
    connect(searchAction, SIGNAL(triggered()), this, SLOT(search()));



}

void MainWindow::createNewCustomer(){
    setCentralWidget(new NewCustomerWindow(this));

}

void MainWindow::createNewProduct(){
    setCentralWidget(new NewProductWindow(this));
}

void MainWindow::createNewDocument(){
    qDebug()<<"new document";
}

void MainWindow::editConfFile(){
    confWin->show();
}

void MainWindow::showAboutWindow(){
    aboutWin->show();
}

void MainWindow::search(){
    setCentralWidget(new SearchWindow());
}

MainWindow::~MainWindow()
{
    delete confWin;
}
