//
//  main.c
//  Cuoiky
//
//  Created by Linh Dang on 10/29/15.
//  Copyright (c) 2015 Linh Dang. All rights reserved.
//


#include "my_global.h"
#include <mysql.h>
#include "dictionary.h"
#include "db.h"

void debug();
int main(int argc, const char * argv[]) {
    
    
    connectIt();
    //debug();
    //add_word();
    menu();
    //search();
    
    cleanIt();
    
    
    return 0;
}
void debug(){
    char current_word[30] ;
    //search();
    //strcpy(query,"SELECT * FROM `EE` WHERE `word` LIKE 'well' ");
    /*strcpy(query,"SELECT * FROM `EV` WHERE `COL 1` LIKE 'exta' ");
    queryIt(query);
    printWordEV();*/
    //add_word();
    strcpy(current_word,"%00linh1%");
    selectIt("EV",current_word);
    printWordEV();
    sign_up();
    //deleteIt("EV",current_word);
    //printWordEE();
    
    
}
