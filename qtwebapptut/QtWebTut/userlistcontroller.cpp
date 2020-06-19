#include "userlistcontroller.h"
#include "template.h"
#include "global.h"

UserListController::UserListController(QObject* parent)
    :HttpRequestHandler(parent)
{

}

void UserListController::service(HttpRequest &request, HttpResponse &response) {
    QByteArray language=request.getHeader("Accept-Language");
    response.setHeader("Content-Type", "text/html; charset=UTF-8");
    HttpSession session = sessionStore->getSession(request,response,true);
    Template t=templateCache->getTemplate("files/user_list",language);
    QSqlDatabase database = sqlconnection("user_list");
    if(database.open()){
            qDebug("Connected");
    }
    else{
        qDebug("Not connected");
    }
    QSqlQuery *list_of_users = new QSqlQuery(database);
    list_of_users->exec("SELECT login,id from accounts");
    QSqlQuery *num_of_users = new QSqlQuery(database);
    num_of_users->exec("SELECT COUNT(*) from accounts");
    QString num_of_users_row;
    while(num_of_users->next()){
        num_of_users_row = num_of_users->value(0).toString();
    }
    int num_of_users_int = num_of_users_row.toInt();
    t.loop("users", num_of_users_int);
    int counter=0;
    while(list_of_users->next()){
        QString number = QString::number(counter);
        t.setVariable("users"+number+".name", list_of_users->value(0).toString());
        t.setVariable("users"+number+".id", list_of_users->value(1).toString());
        counter++;
    }
    response.write(t.toUtf8());
}
