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

#ifndef EDITTEMPLATEWINDOW_H
#define EDITTEMPLATEWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QString>
#include <QFile>
#include <QDir>
#include <QStatusBar>
#include <QMessageBox>

#include "balisetemplateframe.h"

/**
 * Class qui gere la fenetre de modification du template
 * @author David Ducatel
 */
class EditTemplateWindow : public QWidget
{
    Q_OBJECT
    public:
        explicit EditTemplateWindow(QMainWindow *parent = 0);

    private:
        QPushButton *validate;
        QPushButton *help;
        QTextEdit *templateEdit;
        QMainWindow *parent;


        QString loadTemplate();

    private slots:
        void save();
        void showBalise();

};

#endif // EDITTEMPLATEWINDOW_H
