#include "global.h"
#include "template.h"
#include <QTime>
#include "addingitemcontroller.h"


AddingItemController::AddingItemController(QObject* parent) : HttpRequestHandler(parent){

}

void AddingItemController::service(HttpRequest &request, HttpResponse &response){
    response.write("test");
}

//AddingItemController::AddingItemController(QObject* parent)
//    :HttpRequestHandler(parent) {

//}

//void AddingItemController::service(HttpRequest &request, HttpResponse &response){
//    response.write("hello");
//}



