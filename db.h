//
//  db.h
//  Cuoiky
//
//  Created by Linh Dang on 10/29/15.
//  Copyright (c) 2015 Linh Dang. All rights reserved.
//

#ifndef __Cuoiky__db__
#define __Cuoiky__db__

#include <mysql.h>
#include "my_global.h"
#include "dictionary.h"
MYSQL* conn;
MYSQL_RES *result;
long num_rows;
void testIt();
void connectIt();
void cleanIt();
void finish_with_error(MYSQL *conn);
int queryIt(char* str);
void showItAll();
void printWordEE();
void printWordEV();
int searchIt();
int deleteIt(char* dbname, char * word);
int selectIt(char* dbname, char * word);
int logIn(char* pass);
#endif /* defined(__Cuoiky__db__) */
