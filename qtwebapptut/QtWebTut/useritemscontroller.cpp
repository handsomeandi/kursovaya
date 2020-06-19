#include "useritemscontroller.h"
#include "global.h"
#include <QTime>

UserItemsController::UserItemsController(QObject* parent)
    :HttpRequestHandler(parent)
{


}



void UserItemsController::service(HttpRequest &request, HttpResponse &response) {
    QByteArray language=request.getHeader("Accept-Language");
    response.setHeader("Content-Type", "text/html; charset=UTF-8");
    HttpSession session = sessionStore->getSession(request,response,true);
    Template t=templateCache->getTemplate("files/things",language);
    QSqlDatabase database = sqlconnection("user_items");
    if(database.open()){
            qDebug("Connected");
    }
    else{
        qDebug("Not connected");
    }
    QString deleting = request.getParameter("delete");
    if(!deleting.isEmpty()){
        qDebug("Deleting item");
        qDebug() << deleting;
    }
    QByteArray change_req = request.getParameter("change");
    if(!change_req.isEmpty()){
        QByteArray cookie_change = request.getCookie("cookie_change");
        if(cookie_change.isEmpty()){
            HttpCookie cookie_change_item("cookie_change", change_req, 3600);
            response.setCookie(cookie_change_item);
            qDebug() << "Cookie";
            qDebug() << change_req;
        }
    }

    QSqlQuery *user_id_que = new QSqlQuery(database);
    user_id_que->exec("SELECT id FROM accounts WHERE login='"+session.get("username").toString()+"'");
    QString user_id;
    while(user_id_que->next()){
        user_id = user_id_que->value(0).toString();
    }
    QSqlQuery *num_rows = new QSqlQuery(database);
    num_rows->exec("SELECT COUNT(*) FROM items WHERE user_id="+user_id);
    int numrows;
    while(num_rows->next()){
        numrows = num_rows->value(0).toInt();
        qDebug("Number of rows");
        qDebug() << numrows;
    }
    t.loop("items",numrows);
    int counter = 0;
    std::string photo_on_delete;

        QSqlQuery *items = new QSqlQuery(database);
        items->exec("SELECT title, descript, photo, price, link, category FROM items WHERE user_id="+user_id);
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
            counter++;
            if(!deleting.isEmpty()){
                if(("user-images/"+photo_on_delete) == deleting){
                    QSqlQuery *delete_item = new QSqlQuery(database);
                    delete_item->exec("DELETE FROM items WHERE photo='"+photo_on_delete+"'");
                }
            }
            QSqlQuery *categ_name = new QSqlQuery(database);
            QString category_name;
            QString privacyy;
            QString acc_privacy;
            QString username_other;
            categ_name->exec("SELECT name FROM categories WHERE category_id="+category+" AND user_id="+user_id);
            while(categ_name->next()){
                category_name = categ_name->value(0).toString();
            }
            t.setVariable("items"+number+".category",category_name);
            qDebug() << "title";
            qDebug() << title;
            qDebug() << "descript";
            qDebug() << descript;
            qDebug() << "photo";
            qDebug() << photo;
            qDebug() << "price";
            qDebug() << price;
            qDebug() << "link";
            qDebug() << link;
            qDebug() << "category";
            qDebug() << category;
        }
    response.write(t.toUtf8(), true);
}
