#include "aboutframe.h"

AboutFrame::AboutFrame() : QDialog(0){

    QHBoxLayout *layoutPrinc=new QHBoxLayout;

    QLabel  *label_img  = new QLabel(this);
    QPixmap *pixmap_img = new QPixmap(QCoreApplication::applicationDirPath()+QDir::separator()+"img"+QDir::separator()+"copyleft.png");
    label_img->setPixmap(*pixmap_img);
    layoutPrinc->addWidget(label_img);

    QLabel *info=new QLabel(tr("<center><b>QFacturation</b></center><br/>\
                               D�velopp� par <b>David Ducatel</b><br/>\
                               Version: <b>1.0</b><br/>\
                               Sous licence: <a href='http://www.gnu.org/licenses/gpl.html'>GNU General Public License (GPL) version 3</a><br/>\
                               Site: <a href='http://ducatel.github.com'>ducatel.github.com</a>","Contenue de la fenetre a propos"));

    info->setOpenExternalLinks(true);
    layoutPrinc->addWidget(info);
    setLayout(layoutPrinc);
    setModal(true);
    setWindowTitle(tr("Information sur le d�veloppeur"));
}
