#ifndef ADDINGITEMCONTROLLER_H
#define ADDINGITEMCONTROLLER_H
#include "httprequesthandler.h"
using namespace stefanfrings;

class AddingItemController : public HttpRequestHandler
{
    Q_OBJECT
public:
    AddingItemController(QObject* parent=0);
    void service(HttpRequest& request, HttpResponse& response);
};


#endif // ADDINGITEMCONTROLLER_H
