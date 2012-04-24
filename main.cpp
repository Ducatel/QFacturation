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

#include "main.h"


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
    QSqlDatabase base=QSqlDatabase::addDatabase("QSQLITE");
    base.setDatabaseName(QDir::fromNativeSeparators(QDir::homePath()+"/.QFacturation/data.db"));
    base.open();

    qDebug("Gerer l'impression du document");

    ConfigWindow confWin(0);
    if(!configExist()){
        confWin.show();
    }

    MainWindow w;
    w.show();

    return a.exec();
}
