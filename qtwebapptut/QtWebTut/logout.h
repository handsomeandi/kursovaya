#ifndef LOGOUT_H
#define LOGOUT_H


#include "httprequesthandler.h"

using namespace stefanfrings;

class Logout : public HttpRequestHandler {
    Q_OBJECT
public:
    Logout(QObject* parent=0);
    void service(HttpRequest& request, HttpResponse& response);
};

#endif // LOGOUT_H
