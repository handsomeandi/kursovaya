#include "categoriescontroller.h"
#include "template.h"
#include "global.h"

CategoriesController::CategoriesController(QObject* parent)
    :HttpRequestHandler(parent) {

}

void CategoriesController::service(HttpRequest &request, HttpResponse &response) {
    QByteArray language=request.getHeader("Accept-Language");
    response.setHeader("Content-Type", "text/html; charset=UTF-8");
    HttpSession session = sessionStore->getSession(request,response,true);
    Template t=templateCache->getTemplate("files/categories",language);
    QSqlDatabase database = sqlconnection("categories");
    if(database.open()){
            qDebug("Connected");
    }
    else{
        qDebug("Not connected");
    }
    QSqlQuery *user_id_q = new QSqlQuery(database);
    QString user_id;
    user_id_q->exec("SELECT * FROM accounts WHERE login='"+session.get("username").toString()+"'");
    while(user_id_q->next()){
        user_id = user_id_q->value(0).toString();
    }
    QString user_id_param = request.getParameter("user_id");
    QString category_id_param = request.getParameter("category_id");
    t.setCondition("display_cats", user_id_param.isEmpty());
    if(user_id_param.isEmpty() && category_id_param.isEmpty()){
        QSqlQuery *num_rows = new QSqlQuery(database);
        num_rows->exec("SELECT COUNT(*) FROM categories WHERE user_id="+user_id);
        int numrows;
        while(num_rows->next()){
            numrows = num_rows->value(0).toInt();
            qDebug("Number of rows");
            qDebug() << numrows;
        }
        t.loop("category", numrows);

        QSqlQuery *categories = new QSqlQuery(database);
        categories->exec("SELECT name, category_id FROM categories WHERE user_id="+user_id);
        t.setVariable("user_id",user_id);
        int counter = 0;
        while(categories->next()){
            QString number = QString::number(counter);
            t.setVariable("category"+number+".name",categories->value(0).toString());
            t.setVariable("category"+number+".id",categories->value(1).toString());
            t.setVariable("category_opened",categories->value(0).toString());
            counter++;
        }
        response.write(t.toUtf8());
    }else{
        QSqlQuery *num_rows = new QSqlQuery(database);
        num_rows->exec("SELECT COUNT(*) FROM items WHERE user_id="+user_id+" AND category="+category_id_param);
        int numrows;
        while(num_rows->next()){
            numrows = num_rows->value(0).toInt();
            qDebug("Number of rows");
            qDebug() << numrows;
        }
        t.loop("items",numrows);
        int counter = 0;
        QSqlQuery *items = new QSqlQuery(database);
        items->exec("SELECT title, descript, photo, price, link, category FROM items WHERE user_id="+user_id+" AND category="+category_id_param);
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
            t.setVariable("items"+number+".category",category);

            counter++;
        }
        QSqlQuery *catetegories = new QSqlQuery(database);
        catetegories->exec("SELECT name FROM categories WHERE category_id="+category_id_param+" AND user_id="+user_id);
        while(catetegories->next()){
            t.setVariable("category_opened",catetegories->value(0).toString());
        }
        response.write(t.toUtf8());
        if (numrows==0) response.write("<p>No items added in this category yet</p>");
    }
}
