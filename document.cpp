#include "document.h"

Document::Document(){
    idCustomer=-1;
    id=-1;
    date=QDate::currentDate();
    docType=Document::Facture;
    payment=Document::None;
}


QString Document::getDateInString(){

}

