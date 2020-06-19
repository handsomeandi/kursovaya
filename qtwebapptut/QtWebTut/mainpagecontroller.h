#ifndef MAINPAGECONTROLLER_H
#define MAINPAGECONTROLLER_H
#include <QMap>
#include <QList>
#include "httprequesthandler.h"
using namespace stefanfrings;

class MainPageController : public HttpRequestHandler {
    Q_OBJECT
public:
    MainPageController(QObject* parent=0);
    void service(HttpRequest& request, HttpResponse& response);
};

#endif // MAINPAGECONTROLLER_H



