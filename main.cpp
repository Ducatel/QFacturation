#include "main.h"
#include "customer.h"
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
    Customer c(1);
    qDebug()<<c.name;
    qDebug()<<c.adress;
    qDebug()<<c.city;
    qDebug()<<c.country;
    qDebug()<<c.phone;
    qDebug()<<c.email;
    qDebug()<<c.postalCode;

    c.name="michel";
    c.save();
    Customer c2(1);
    qDebug()<<c2.name;
    /*c.name="david ducatel";
    c.adress="1328 le four a chaux";
    c.city="Saint Aubin Routôt";
    c.country="France";
    c.email="david.ducatel@yahoo.fr";
    c.phone="0300000000";
    c.postalCode=76430;
    qDebug()<<c.save();
    qDebug()<<c.getId();*/

    /*
    ConfigWindow confWin;
    if(!configExist()){
        confWin.show();
    }

    MainWindow w;
    w.showMaximized();*/

    return a.exec();
}
