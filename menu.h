#ifndef P1_MENU_H
#define P1_MENU_H
#include "stdio.h"
#include "string.h"
#include "unistd.h"
#include "limits.h"
#include "stdlib.h"
#include "functions.h"

struct menu{
    char file_name[PATH_MAX];
    char main_name[1024]; //Contains the menu points of the main menu.
    char produce_name[50];//Mineral name for the limit value
    //char config_name[50]; //limit of the mineral in mg/l
    char sub_menu[1024];
};
typedef struct menu menu;


int interface (struct input minerals[20], int data_width);



#endif //P1_MENU_H
