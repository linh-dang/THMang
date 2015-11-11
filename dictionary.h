//
//  dictionary.h
//  Cuoiky
//
//  Created by Linh Dang on 10/29/15.
//  Copyright (c) 2015 Linh Dang. All rights reserved.
//

#ifndef __Cuoiky__dictionary__
#define __Cuoiky__dictionary__
#include <mysql.h>
#include "my_global.h"
#define BUFSIZE 15000

char query[BUFSIZE];
struct User_ {
    char name[256];
    int role;
    char pass[256];
};

typedef struct User_ User;
User *current_user;
int menu();
void search();
void add_word();
void remove_word();
void timkiem();
void display();
void log_in();
void sign_up();
void log_out();
void change_pass();
#endif /* defined(__Cuoiky__dictionary__) */
