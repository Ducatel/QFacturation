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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include "configwindow.h"
#include "aboutframe.h"
#include "newcustomerwindow.h"
#include "newproductwindow.h"
#include "searchwindow.h"

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

    protected :
        void closeEvent(QCloseEvent* event);


    private slots:
        void createNewCustomer();
        void createNewDocument();
        void createNewProduct();
        void editConfFile();
        void showAboutWindow();
        void search();
        void quitSlot();
        void quit(QCloseEvent* event=0);
};

#endif // MAINWINDOW_H
