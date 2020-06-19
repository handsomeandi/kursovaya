#ifndef GLOBAL_H
#define GLOBAL_H

#include "httpsessionstore.h"
#include "staticfilecontroller.h"
#include "templatecache.h"
#include <QtSql>
#include<QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include "picosha2.h"
#include <iostream>
#include <QCryptographicHash>
#include "sqlconnection.h"
#include "template.h"
#include <QImage>

using namespace stefanfrings;


extern HttpSessionStore* sessionStore;
extern StaticFileController* staticFileController;
extern TemplateCache* templateCache;





#endif // GLOBAL_H
