#include "otherusersitemscontroller.h"
#include "template.h"
#include "global.h"

OtherUsersItemsController::OtherUsersItemsController(QObject* parent)
    :HttpRequestHandler(parent) {
    // empty

}
void OtherUsersItemsController::service(HttpRequest &request, HttpResponse &response) {
    QByteArray language=request.getHeader("Accept-Language");
    response.setHeader("Content-Type", "text/html; charset=UTF-8");
    HttpSession session = sessionStore->getSession(request,response,true);
    Template t=templateCache->getTemplate("files/other_users",language);
    QSqlDatabase database = sqlconnection("other_users");
    if(database.open()){
            qDebug("Connected");
    }
    else{
        qDebug("Not connected");
    }
    QString requested_user = request.getParameter("req_user");
    QSqlQuery *num_rows = new QSqlQuery(database);
    num_rows->exec("SELECT COUNT(*) FROM items WHERE user_id="+requested_user);
    int numrows;
    while(num_rows->next()){
        numrows = num_rows->value(0).toInt();
        qDebug("Number of rows");
        qDebug() << numrows;
    }
    t.loop("items",numrows);
    int counter = 0;
        QSqlQuery *items = new QSqlQuery(database);
        items->exec("SELECT title, descript, photo, price, link, category FROM items WHERE user_id="+requested_user);
        while(items->next()){
            QString number = QString::number(counter);
            QString title = items->value(0).toString();
            QString descript = items->value(1).toString();
            QString photo_on_delete = items->value(2).toString();
            QDir pathhh = QDir::currentPath();
            QString path_ph = pathhh.relativeFilePath("../QtWebTut/docroot/files/user-images/");
            QString photo = path_ph + items->value(2).toString();
            QString price = items->value(3).toString();
            QString link = items->value(4).toString();
            QString category = items->value(5).toString();
            t.setCondition("desc_exist", descript != "");
            t.setCondition("price_exist", price != "");
            t.setCondition("link_exist", link != "");
            t.setVariable("items"+number+".title",title);
            t.setVariable("items"+number+".descript",descript);
            t.setVariable("items"+number+".photo","user-images/"+photo_on_delete);
            t.setVariable("items"+number+".photo_change",photo_on_delete);
            t.setVariable("items"+number+".price",price);
            t.setVariable("items"+number+".link",link);
            QSqlQuery *categ_name = new QSqlQuery(database);
            QString category_name;
            QString privacyy;
            QString acc_privacy;
            categ_name->exec("SELECT name,privacy FROM categories WHERE category_id="+category+" AND user_id="+requested_user);
            while(categ_name->next()){
                QSqlQuery *get_user_privacy = new QSqlQuery(database);
                get_user_privacy->exec("SELECT prof_type FROM accounts WHERE id="+requested_user);
                while(get_user_privacy->next()){
                    acc_privacy = get_user_privacy->value(0).toString();
                }
                category_name = categ_name->value(0).toString();
                if(acc_privacy == "2"){
                    privacyy = "2";
                }else{
                    privacyy = categ_name->value(1).toString();
                }
                t.setVariable("items"+number+".category_privacy", privacyy);
            }
            t.setVariable("items"+number+".category",category_name);
            counter++;
        }
        QString username_other;
        QSqlQuery *get_user_other = new QSqlQuery(database);
        get_user_other->exec("SELECT login FROM accounts WHERE id="+requested_user);
        while(get_user_other->next()){
            username_other = get_user_other->value(0).toString();
        }
        t.setVariable("items.username_other", username_other);
    response.write(t.toUtf8());
}
