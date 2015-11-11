//
//  dictionary.c
//  Cuoiky
//
//  Created by Linh Dang on 10/29/15.
//  Copyright (c) 2015 Linh Dang. All rights reserved.
//

#include "dictionary.h"
#include "db.h"
char c;

int enter_multi_line(char * buf){
    bzero(buf, BUFSIZE);
    scanf("%[^>|^<]", buf);
    getchar();
    return 1;
}
int enterLine(char * buf){
    scanf("%[^\n]", buf);
    getchar();
    return 1;
}
int enterWord(char * buf){
    scanf("%s", buf);
    getchar();
    return 1;
}
void return_menu(){
    printf("\nNhan phim bat ky de tro ve menu:  \n");
    scanf(" %c",&c);
    menu();
}

int menu(){
    if(c!='Y'){
        printf("+------- Menu ------+");
        printf("\n+-----------------+");
        printf("\n+ 1. Tim tu       +");
        printf("\n+ 2. Them tu      +");
        printf("\n+ 3. Xoa          +");
        printf("\n+ 4. Doi mat khau +");
        printf("\n+ 5. Dang nhap    +");
        printf("\n+ 6. Dang ky      +");
        printf("\n+ 7. Dang xuat    +");
        printf("\n+ 8. Quit         +");
        printf("\n Ban chon : ");
        scanf(" %c",&c);
        switch(c)
        {
            case '1' : search();
                break;
            case '2' : add_word();
                break;
            case '3' : remove_word();
                break;
            case '4' :change_pass();
                break;
            case '5' : log_in();
                break;
            case '6' :  sign_up();
                break;
            case '7' : log_out();
                break;
            case '8': printf("Quitting program!\n");
                break;
            default: printf("Wrong choice!\n\n");
                menu();
                
        }
    }
    return 0;
}
void search(){
    char current_word[30] ;
    printf("\nNhap tu can tim kiem: \n");
    enterWord(current_word);
    
    selectIt("EV",current_word);
    printWordEV();
    printf("\nBan co muon ket thuc chuong trinh? (Y/N) \n");
    scanf(" %c",&c);
    if(c=='Y'|| c=='y')menu();
    if(c=='N'|| c=='n') search();
}
void add_word(){
    char current_word[30] ;
    char meaning[BUFSIZE];
    printf("\nNhap tu can tim kiem: ");
    enterLine(current_word);
    while(selectIt("EV",current_word)!= 0){
        printf("\nTu nay da ton tai. Ban co muon xoa tu nay? (Y/N) \n");
        scanf(" %c",&c);
        getchar();
        if(c=='N'|| c=='n') {menu();break;}
        if(c=='Y'|| c=='y'){
            deleteIt("EV",current_word);
            printf("Thanh cong! %ld dong da xoa.",num_rows);
            break;
        }
    }
    
    printf("\nNhap nghia moi cho tu %s (nhan < de ket thuc): \n ",current_word);
    enter_multi_line(meaning);
    bzero(query, BUFSIZE);
    strcpy(query,"INSERT INTO `EV`(`COL 1`, `COL 2`) VALUES ( \'");
    strcat(query,current_word);
    strcat(query, "\',\'");
    strcat(query, meaning);
    strcat(query, " \')");
    queryIt(query);
    
    printf("\nBan co muon ket thuc chuong trinh? (Y/N) \n");
    scanf(" %c",&c);
    printf("%c\n",c);
    if(c=='Y'|| c=='y')menu();
    if(c=='N'|| c=='n')add_word();
}
void remove_word(){
    //MYSQL_RES *result1;
    char current_word[30] ;
    printf("\nNhap tu can tim kiem: ");
    scanf("%s", current_word);
    getchar();
    if (selectIt("EV",current_word)==0) {
        printf("\nTu nay khong ton tai");
    }
    while(selectIt("EV",current_word)!= 0){
        printf("\nBan co muon xoa tu %s? (Y/N) \n",current_word);
        scanf(" %c",&c);
        if(c=='N'|| c=='n') {menu();break;}
        if(c=='Y'|| c=='y'){
            deleteIt("EV",current_word);
            printf("Thanh cong! %d dong da xoa.",(int)num_rows);
            break;
        }
    }
    
    printf("\nBan co muon ket thuc chuong trinh? (Y/N) \n");
    scanf(" %c",&c);
    if(c=='Y'|| c=='y')menu();
    if(c=='N'|| c=='n')remove_word();
}
void display(){
    
    
    printf("\nBan co muon ket thuc chuong trinh? (Y/N) \n");
    scanf(" %c",&c);
    if(c=='Y'|| c=='y')menu();
    if(c=='N'|| c=='n') search();
}
void log_in(){
    char user_name[30] ;
    char pass[256];
    if(current_user->role != -1) {
        printf("\nBan da dang nhap");
    }else{
        printf("\nNhap ten dang nhap: ");
        enterWord(user_name);
        printf("\nMat khau cho tai khoan %s: \n",user_name);
        enterLine(pass);
        if (selectIt("User",user_name)==0) {
            printf("\nTai khoan nay khong ton tai");
        }
        else{
            if(logIn(pass))printf("\nDang nhap thanh cong.");
            else printf("\nSai mat khau.");
        }
    }
    return_menu();
}
void log_out(){
    if(current_user->role == -1) printf("\nBan chua dang nhap");
    else {
        strcpy(current_user->name,"");
        strcpy(current_user->pass,"");
        current_user->role = -1;
        printf("\nDang xuat thanh cong");
    }
    return_menu();
}
void sign_up(){
    char user_name[30] ;
    char pass[256];//INSERT INTO `02-tudien`.`User` (`COL 1`, `Pass`, `Role`, `date-added`) VALUES (
    char pass1[256];
    if(current_user->role != -1) printf("\nBan da dang nhap! log out de dang ky tk moi");
    else {
        int i= 0;
        do{
            if(i== 1)printf("\nTai khoan da ton tai!");
            printf("\nNhap ten dang nhap moi: ");
            enterWord(user_name);
        }while((i = selectIt("User",user_name)));
        printf("\nMat khau moi cho tai khoan %s: \n",user_name);
        enterLine(pass);
        printf("\nMat khau moi cho tai khoan %s: \n",user_name);
        enterLine(pass1);
        if((!strcmp(pass,pass1))&&(!selectIt("User",user_name))){
            bzero(query, BUFSIZE);
            strcpy(query,"INSERT INTO `02-tudien`.`User` (`COL 1`, `Pass`) VALUES ( \'");
            strcat(query,user_name);
            strcat(query, "\',\'");
            strcat(query, pass);
            strcat(query, " \')");
            queryIt(query);
            printf("\nDang ky thanh cong");
        }else printf("\nDang ky that bai");
        
    }
    return_menu();
}
void change_pass(){
    char pass0[256];
    char pass[256];
    char pass1[256];
    if(current_user->role == -1) {printf("\nBan chua dang nhap");}
    else {
        printf("\nMat khau cu cua tai khoan %s: \n",current_user->name);
        enterLine(pass0);
        printf("\nMat khau moi cho tai khoan %s: \n",current_user->name);
        enterLine(pass);
        printf("\nMat khau moi cho tai khoan %s: \n",current_user->name);
        enterLine(pass1);
        if(!strcmp(pass,pass1)&&(!strcmp(pass0, current_user->pass))){
            strcpy(current_user->pass,pass);
            // UPDATE `02-tudien`.`User` SET `Pass` = '123456' WHERE `user`.`COL 1` = 'name';
            bzero(query, BUFSIZE);
            strcpy(query,"UPDATE `02-tudien`.`User` SET `Pass` = \'");
            strcat(query,pass);
            strcat(query, "\'");
            strcat(query, "\' WHERE `user`.`COL 1` = \'");
            strcat(query,current_user->name);
            strcat(query, "\'");
            queryIt(query);
            printf("\nThay doi mat khau thanh cong");
        }else printf("\nThay doi mat khau that bai");
        
    }
    printf("\nBan co muon ket thuc chuong trinh? (Y/N) \n");
    scanf(" %c",&c);
    if(c=='Y'|| c=='y')menu();
    if(c=='N'|| c=='n')log_out();
}


