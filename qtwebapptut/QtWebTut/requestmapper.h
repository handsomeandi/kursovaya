#ifndef REQUESTMAPPER_H
#define REQUESTMAPPER_H

#include "httprequesthandler.h"
#include "logincontroller.h"
#include "cookietestcontroller.h"
#include "mainpagecontroller.h"
#include "registercontroller.h"
#include "logout.h"
#include "itemaddingcontroller.h"
#include "useritemscontroller.h"
#include "changeitemcontroller.h"
#include "categoryadd.h"
#include "categoriescontroller.h"
#include "userlistcontroller.h"
#include "otherusersitemscontroller.h"

using namespace stefanfrings;

class RequestMapper : public HttpRequestHandler {
    Q_OBJECT
public:
    RequestMapper(QObject* parent=0);
    void service(HttpRequest& request, HttpResponse& response);
private:
    MainPageController mainPageController;
    LoginController loginController;
    CookieTestController cookieController;
    RegisterController registerController;
    Logout logout;
    ItemAddingController itemAddingController;
    UserItemsController userItemsController;
    ChangeItemController changeItemController;
    CategoryAdd categoryAdd;
    CategoriesController categoriesController;
    UserListController userListController;
    OtherUsersItemsController otherUserItemsController;
};

#endif // REQUESTMAPPER_H
