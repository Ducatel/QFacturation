#include "aboutframe.h"

AboutFrame::AboutFrame() : QDialog(0){

    QHBoxLayout *layoutPrinc=new QHBoxLayout;
    QLabel *info=new QLabel(tr("<center><b>QFacturation</b></center><br/>\
                               Devellopé par <b>D.Ducatel</b><br/>\
                               Version: <b>1.0</b><br/>\
                               Sous licence: <a href='http://www.gnu.org/licenses/gpl.html'>GNU General Public License (GPL) version 3</a><br/>\
                               Site: <a href='http://ducatel.github.com'>ducatel.github.com</a>","Contenue de la fenetre a propos"));
    info->setOpenExternalLinks(true);
    layoutPrinc->addWidget(info);
    setLayout(layoutPrinc);
    setModal(true);
    setWindowTitle(tr("Information sur le develloper"));
}
