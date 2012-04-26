#!/bin/sh
# install.sh programme de compilation et d'installation de QFacturation

# Installation des lib
echo "Installation des librairies"
sudo apt-get -y install libqt4-dev libqt4-sql-sqlite libsqlite3-dev

# Generation du makefile
if test -f /usr/bin/qmake-qt4 ;
then
    qmake-qt4 QFacturation.pro
else
    qmake QFacturation.pro
fi

# compilation
make

# installation
sudo cp QFacturation /usr/local/bin/QFacturation
sudo cp qfacturation.png /usr/share/pixmaps/qfacturation.png
sudo cp qfacturation.desktop /usr/share/applications/qfacturation.desktop

# Nettoyage de la compilation
make clean
