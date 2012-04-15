#include "main.h"


//TODO supprimer include de test
#include "customer.h"
#include "product.h"
#include "document.h"
#include "productdocument.h"



/**
 * Fonction qui verifie si la configuration de base est présente
 * @return true si la conf est presente, false sinon
 */
bool configExist(){
    QDir confDir(QDir::fromNativeSeparators(QDir::homePath()+"/.QFacturation"));
    if(!confDir.exists())
        confDir.mkdir(confDir.absolutePath());

    QFile confFile(QDir::fromNativeSeparators(confDir.absolutePath()+"/stdConfig.xml"));


    if(confFile.size()==0)
       return false;
    else
        return true;
}


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);


    ConfigWindow confWin;
    if(!configExist()){
        confWin.show();
    }

    MainWindow w;
    w.show();
   // w.showMaximized();

    return a.exec();
}
