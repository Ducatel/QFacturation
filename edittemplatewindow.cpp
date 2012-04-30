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

#include "edittemplatewindow.h"

/**
 * Constructeur de la fenetre d'edition du template
 */
EditTemplateWindow::EditTemplateWindow(QMainWindow *parent) :QWidget(parent){
    this->parent=parent;
    QVBoxLayout *layoutPrinc=new QVBoxLayout(this);

    /** ********************* **/
    /**         Edition       **/
    /** ********************* **/

    templateEdit=new QTextEdit;
    templateEdit->setAcceptRichText(false);
    templateEdit->setPlainText(loadTemplate());
    layoutPrinc->addWidget(templateEdit);

    /** ********************* **/
    /**         Boutons       **/
    /** ********************* **/

    QHBoxLayout *layoutBouton = new QHBoxLayout;

    validate=new QPushButton(trUtf8("Valider"));
    layoutBouton->addWidget(validate);

    help=new QPushButton(trUtf8("Voir les balises disponibles"));
    layoutBouton->addWidget(help);

    layoutPrinc->addLayout(layoutBouton);
    setLayout(layoutPrinc);

    /** ********************* **/
    /**          Slots        **/
    /** ********************* **/

    connect(validate, SIGNAL(clicked()), this, SLOT(save()));
    connect(help, SIGNAL(clicked()), this, SLOT(showBalise()));


}

/**
 * Methode qui charge le template de document
 * @return le template
 */
QString EditTemplateWindow::loadTemplate(){
    QString templateContent;
    QFile file(QDir::fromNativeSeparators(QDir::homePath()+"/.QFacturation/template.html"));

    if (file.open(QFile::ReadOnly))
        templateContent= QString(file.readAll());
    else
        templateContent="";

    file.close();
    return templateContent;
}


/**
 * Methode qui enregistre le template
 */
void EditTemplateWindow::save(){
    QFile file(QDir::fromNativeSeparators(QDir::homePath()+"/.QFacturation/template.html"));
    if (file.open(QFile::WriteOnly)){
        file.write(templateEdit->toPlainText().toUtf8());
        file.flush();
        file.close();
        QStatusBar *statBar = parent->statusBar();
        statBar->showMessage(trUtf8("Template sauvegardé"), 4000);
    }
    else
        QMessageBox::critical(this,trUtf8("Erreur d'écriture"),trUtf8("Ecriture du template impossible"));
}

void EditTemplateWindow::showBalise(){
    new BaliseTemplateFrame(this);
}
