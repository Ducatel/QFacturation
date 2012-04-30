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

#include "mainwindow.h"

MainWindow::~MainWindow()
{
    delete aboutWin;
    delete confWin;
}

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    confWin=new ConfigWindow(this);
    confWin->initByConfigFile();

    aboutWin=new AboutFrame();

    QString imgDirPath=QCoreApplication::applicationDirPath()+QDir::separator()+"img"+QDir::separator();

    setWindowIcon(QIcon(imgDirPath+"icon.png"));
    setWindowTitle(QString("QFacturation"));

    QStatusBar *statBar = statusBar();
    statBar->showMessage(trUtf8("Prêt"));

    /** *************************** **/
    /**             Menu            **/
    /** *************************** **/

    QMenu *fileMenu = menuBar()->addMenu(trUtf8("&Fichier"));

    QAction *newCustomerAction = fileMenu->addAction(trUtf8("Nouveau client"));
    newCustomerAction->setIcon(QIcon(imgDirPath+"add-user.png"));
    newCustomerAction->setShortcut(QKeySequence(Qt::CTRL +Qt::SHIFT + Qt::Key_N));
    newCustomerAction->setStatusTip(trUtf8("Créer un nouveau client"));

    QAction *newProductAction = fileMenu->addAction(trUtf8("Nouveau produit"));
    newProductAction->setIcon(QIcon(imgDirPath+"product.png"));
    newProductAction->setShortcut(QKeySequence(Qt::CTRL +Qt::ALT + Qt::Key_N));
    newProductAction->setStatusTip(trUtf8("Créer un nouveau produit"));

    QAction *newDocAction = fileMenu->addAction(trUtf8("Nouveau document"));
    newDocAction->setIcon(QIcon(imgDirPath+"add-doc.png"));
    newDocAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    newDocAction->setStatusTip(trUtf8("Créer un nouveau document (devis ou facture)"));

    QAction *searchAction = fileMenu->addAction(trUtf8("Rechercher"));
    searchAction->setIcon(QIcon(imgDirPath+"search.png"));
    searchAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F));
    searchAction->setStatusTip(trUtf8("Rechercher un client, un produit ou un document"));

    QAction *editConfAction = fileMenu->addAction(trUtf8("Modifier les informations de la société"));
    editConfAction->setIcon(QIcon(imgDirPath+"edit.png"));
    editConfAction->setStatusTip(trUtf8("Modifier les informations de la société"));

    QAction *editTemplateAction = fileMenu->addAction(trUtf8("Modifier le template"));
    editTemplateAction->setIcon(QIcon(imgDirPath+"icon.png"));
    editTemplateAction->setStatusTip(trUtf8("Modifier le template des documents"));

    QAction *quitAction = fileMenu->addAction(trUtf8("Quitter"));
    quitAction->setIcon(QIcon(imgDirPath+"exit.png"));
    quitAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    quitAction->setStatusTip(trUtf8("Quitte le programme"));

    QMenu *helpMenu = menuBar()->addMenu(trUtf8("&Aide"));
    QAction *aboutAction = helpMenu->addAction(trUtf8("A propos"));

    /** *************************** **/
    /**        Barre Outils         **/
    /** *************************** **/

    QToolBar *toolBar = addToolBar("toolBar");
    toolBar->setMovable(false);
    toolBar->addAction(newCustomerAction);
    toolBar->addAction(newProductAction);
    toolBar->addAction(newDocAction);
    toolBar->addAction(searchAction);
    toolBar->addAction(editConfAction);
    toolBar->addAction(editTemplateAction);

    /** *************************** **/
    /**            Slots            **/
    /** *************************** **/

    connect(quitAction, SIGNAL(triggered()), this, SLOT(quitSlot())); //TODO faire comme la méthode closeEvent
    connect(newCustomerAction, SIGNAL(triggered()), this, SLOT(createNewCustomer()));
    connect(newProductAction, SIGNAL(triggered()), this, SLOT(createNewProduct()));
    connect(newDocAction, SIGNAL(triggered()), this, SLOT(createNewDocument()));
    connect(editConfAction, SIGNAL(triggered()), this, SLOT(editConfFile()));    
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(showAboutWindow()));
    connect(searchAction, SIGNAL(triggered()), this, SLOT(search()));
    connect(editTemplateAction,SIGNAL(triggered()),this,SLOT(editTemplate()));

    setCentralWidget(new NewDocumentWindow(this));
}


bool MainWindow::quit(){
    int ret = QMessageBox::question(this,trUtf8("Quitter?"),trUtf8("Voulez-vous vraiment quitter?"),QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::Yes){
        QSqlDatabase base = QSqlDatabase::database();
        base.commit();
        base.close();
        QSqlDatabase::removeDatabase(QDir::fromNativeSeparators(QDir::homePath()+"/.QFacturation/data.db"));
        qApp->quit();
    }

    return false;
}

/**
 * Methode qui ferme l'application
 * (slot du bouton quitter)
 */
void MainWindow::quitSlot(){
    quit();
}

/**
 * Methode appeler lors de la fermeture de l'application
 */
void MainWindow::closeEvent(QCloseEvent* event) {
    if(!quit()){
        event->ignore();
    }
}

/**
 * Methode qui créer l'interface d'edition du template
 * de document
 */
void MainWindow::editTemplate(){
     setCentralWidget(new EditTemplateWindow(this));
}

/**
 * Methode qui créer l'interface d'ajout/edition de client
 * et la place au centre de cette fenetre
 */
void MainWindow::createNewCustomer(){
    setCentralWidget(new NewCustomerWindow(this));
}

/**
 * Methode qui créer l'interface d'ajout/edition de produit
 * et la place au centre de cette fenetre
 */
void MainWindow::createNewProduct(){
    setCentralWidget(new NewProductWindow(this));
}

/**
 * Methode qui créer l'interface d'ajout/edition de document
 * et la place au centre de cette fenetre
 */
void MainWindow::createNewDocument(){
    setCentralWidget(new NewDocumentWindow(this));
}

/**
 * Methode qui créer l'interface de recherche
 * et la place au centre de cette fenetre
 */
void MainWindow::search(){
    setCentralWidget(new SearchWindow(this));
}

/**
 * Methode qui affiche la fenetre d'edition des info de la société
 */
void MainWindow::editConfFile(){
    confWin->show();
}

/**
 * Methode qui affiche la fenetre a propos
 */
void MainWindow::showAboutWindow(){
    aboutWin->show();
}


