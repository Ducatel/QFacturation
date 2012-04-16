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

#include "aboutframe.h"

AboutFrame::AboutFrame() : QDialog(0){

    QHBoxLayout *layoutPrinc=new QHBoxLayout;

    QLabel  *label_img  = new QLabel(this);
    QPixmap *pixmap_img = new QPixmap(QCoreApplication::applicationDirPath()+QDir::separator()+"img"+QDir::separator()+"copyleft.png");
    label_img->setPixmap(*pixmap_img);
    layoutPrinc->addWidget(label_img);

    QLabel *info=new QLabel(tr("<center><b>QFacturation</b></center><br/>\
                               Développé par <b>David Ducatel</b><br/>\
                               Version: <b>1.0</b><br/>\
                               Sous licence: <a href='http://www.gnu.org/licenses/gpl.html'>GNU General Public License (GPL) version 3</a><br/>\
                               Site: <a href='http://ducatel.github.com'>ducatel.github.com</a>","Contenue de la fenetre a propos"));

    info->setOpenExternalLinks(true);
    layoutPrinc->addWidget(info);
    setLayout(layoutPrinc);
    setModal(true);
    setWindowTitle(tr("Information sur le développeur"));
}
