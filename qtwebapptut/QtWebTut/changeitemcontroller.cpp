#include "changeitemcontroller.h"
#include "template.h"
#include "global.h"
ChangeItemController::ChangeItemController(QObject* parent) :HttpRequestHandler(parent)
{

}

void ChangeItemController::service(HttpRequest& request, HttpResponse& response){
    QByteArray language=request.getHeader("Accept-Language");
    response.setHeader("Content-Type", "text/html; charset=UTF-8");
    HttpSession session = sessionStore->getSession(request,response,true);
    Template t=templateCache->getTemplate("files/change",language);
    QSqlDatabase database = sqlconnection("change_items");
    QString photo_change = request.getParameter("photo");
    QString changed_title = request.getParameter("changed_title");
    QString changed_descript = request.getParameter("changed_description");
    QString changed_price = request.getParameter("changed_price");
    QString changed_link = request.getParameter("changed_link");
    QString changed_category = request.getParameter("changed_category");
    QString changed_photo = request.getParameter("changed_photo");
    if(database.open()){
            qDebug("Connected");
    }
    else{
        qDebug("Not connected");
    }
    QSqlQuery *items = new QSqlQuery(database);
    if(!photo_change.isEmpty()){
        qDebug("success photo");
        items->exec("SELECT title, descript, photo, price, link, category FROM items WHERE photo='"+photo_change+"'");
        while(items->next()){
            QString title = items->value(0).toString();
            QString descript = items->value(1).toString();
            QString photo_on_change = items->value(2).toString();
            QDir pathhh = QDir::currentPath();
            QString path_ph = pathhh.relativeFilePath("../QtWebTut/docroot/files/user-images/");
            QString photo = path_ph + items->value(2).toString();
            QString price = items->value(3).toString();
            QString link = items->value(4).toString();
            QString category = items->value(5).toString();
            t.setCondition("desc_exist", descript != "");
            t.setCondition("price_exist", price != "");
            t.setCondition("link_exist", link != "");
            t.setVariable("items.title",title);
            t.setVariable("items.descript",descript);
            t.setVariable("items.photo","user-images/"+photo_on_change);
            t.setVariable("items.photo_change",photo_on_change);
            t.setVariable("items.price",price);
            t.setVariable("items.link",link);
            t.setVariable("items.category",category);
            t.setVariable("photo_change", photo_change);
        }
    }else{
        qDebug("null photo");
    }
        QString command = "UPDATE items SET title='" + changed_title + "',descript='" + changed_descript + "', price=" + changed_price + ",link='"+changed_link+"',category=" + changed_category;
        if(!changed_photo.isEmpty()){

            QTemporaryFile* file=request.getUploadedFile("changed_photo");
            if (file)
            {
                qDebug("Success upload");
                while (!file->atEnd() && !file->error())
                {
                    const QByteArray buffer=file->read(10000000);
                    QImage image = QImage::fromData(buffer);
                    QDir pathhh = QDir::currentPath();
                    QString path_ph = pathhh.relativeFilePath("../QtWebTut/docroot/files/user-images/");
                    QString changed_filename = QString::number(QDateTime::currentMSecsSinceEpoch(),10) + changed_photo;
                    const QString saveFileName = path_ph + "/" + changed_filename;
                    if(image.save(saveFileName)){
                        qDebug("Success upload");
                        response.write("<p class=\"prog\">Предмет успешно изменен!</p>");
                        command.append(", photo='" + changed_filename + "'");
                    }else{
                        qDebug("Erorr loaded!");
                    }
                }
            }else{
                qDebug("Failed to upload");
            }
        }
        command.append(" WHERE photo='"+photo_change+"'");
        if(!changed_title.isEmpty()){
            qDebug() << command;
            QSqlQuery *change_item = new QSqlQuery(database);
            change_item->exec(command);
        }
        else{

        }
    response.write(t.toUtf8(), true);
}
