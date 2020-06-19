#ifndef CATEGORIESCONTROLLER_H
#define CATEGORIESCONTROLLER_H

#include "httprequesthandler.h"

using namespace stefanfrings;

class CategoriesController : public HttpRequestHandler {
    Q_OBJECT
public:
    CategoriesController(QObject* parent=0);
    void service(HttpRequest& request, HttpResponse& response);
};

#endif // CATEGORIESCONTROLLER_H


