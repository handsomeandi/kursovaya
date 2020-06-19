#ifndef CATEGORYADD_H
#define CATEGORYADD_H

#include "httprequesthandler.h"

using namespace stefanfrings;

class CategoryAdd : public HttpRequestHandler {
    Q_OBJECT
public:
    CategoryAdd(QObject* parent=0);
    void service(HttpRequest& request, HttpResponse& response);
};

#endif // CATEGORYADD_H

