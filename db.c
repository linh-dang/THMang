//
//  db.c
//  Cuoiky
//
//  Created by Linh Dang on 10/29/15.
//  Copyright (c) 2015 Linh Dang. All rights reserved.
//

#include "db.h"


void finish_with_error(MYSQL *conn)
{
    fprintf(stderr, "%s\n", mysql_error(conn));
    mysql_close(conn);
    exit(1);
}

void connectIt(){
    current_user =malloc(sizeof(User));
    current_user->role = -1;
    conn = mysql_init(NULL);
    mysql_options(conn , MYSQL_SET_CHARSET_NAME, "utf8");
    mysql_options(conn , MYSQL_INIT_COMMAND, "SET NAMES utf8");
    if (!mysql_real_connect(conn, "127.0.0.1", "root","","02-tudien" ,0,0,0)){
        finish_with_error(conn);
    } else {
        
        printf("Ket noi thanh cong! Bat dau chuong trinh...\n");
    }
        
}
void cleanIt(){
    free(current_user);
    mysql_free_result(result);
    mysql_close(conn);
}
void testIt(){
    
}
int queryIt(char* str){
    if (mysql_query(conn, str))
    {
        finish_with_error(conn);
    }
    result = mysql_store_result(conn);
    
    if (result){
        num_rows = mysql_num_rows(result);//select
        return 1;
    }
    else
    {
        if(mysql_field_count(conn) == 0)
        {
            num_rows = mysql_affected_rows(conn);
            return 0;
        }
        else
        {
            finish_with_error(conn);
        }
    }
    return -1;
    
}
void remove_N(char* str){
    char c = 'a';
    char lookAhead;
    for(int i = 0; i< strlen (str); i++)
    {
        c = str[i];
        lookAhead = str[i+1];
        if((c =='\\')&&(lookAhead =='n')){
            str[i] = '\n';
            str[i+1] = '\t';
        }
    }
    
}

void showItAll(){
    MYSQL_ROW row;
    int num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
    {
        for(int i = 0; i < num_fields; i++)
        {
            printf("%s ", row[i] ? row[i] : "NULL");
        }
        printf("\n");
    }
    
}
void printWordEE(){
    MYSQL_ROW row;
    int i = 1;
    while ((row = mysql_fetch_row(result)))
    {
        printf("%d. ",i++);
        printf("%s\n",row[1]);
        puts(row[2]);
    }
}
void printWordEV(){
    MYSQL_ROW row;
    int i = 1;
    if (num_rows == 0)  printf("\nKhong co tu nay trong tu dien\n");
    while ((row = mysql_fetch_row(result)))
    {
            printf("\n%d. ",i++);
            remove_N(row[1]);
            printf("%s",row[1]);
    }
}

int deleteIt(char* dbname, char * word){
    
    strcpy(query,"DELETE FROM `");
    strcat(query, dbname);
    strcat(query, "` WHERE `COL 1` LIKE \'");
    strcat(query, word);
    strcat(query, "\'");
    printf("\n%s",query);
    queryIt(query);
    return (int)num_rows;
}
int selectIt(char* dbname, char * word){
    
    strcpy(query,"SELECT * FROM `");
    strcat(query, dbname);
    strcat(query, "` WHERE `COL 1` LIKE \'");
    strcat(query, word);
    strcat(query, "\'");
    printf("\n%s",query);
    queryIt(query);
    return (int)num_rows;// 0 neu k ton tai
    
}
int logIn(char* pass){
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result)))
    {
        if (strcmp(row[1],pass)) {
            strcpy(current_user->name,row[0]);
            strcpy(current_user->pass,row[1]);
            current_user->role = atoi(row[2]);
            return 1;
        }
        
    }
    return 0;
}
