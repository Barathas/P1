//
// Created by Daniel on 06-12-2021.
//

#include "menu.h"


int interface () {
    int scan = 0;
    int amount_menu = 0;
    int i = 0;
    int amount_files = 0;
    int amount_produce = 0;
    int amount_config = 0;
    int amount_submenu = 0;
    char buff[PATH_MAX] = "";
    char foldername[PATH_MAX] = "/menufiles";
    char *currentDir = strcat(getcwd(buff, PATH_MAX), foldername);
    char rootfilename[PATH_MAX] = "/menu_files.txt";
    char filepath[PATH_MAX];
    strcpy(filepath, currentDir);
    strcat(filepath, rootfilename);

    menu menu[20];

    FILE *fp = fopen(filepath, "r");
    if (!fp)
        printf("Error: could not open file %s", filepath);
    else {
        const unsigned MAX_LENGTH = 256;
        char buffer[MAX_LENGTH];
        while (fgets(buffer, MAX_LENGTH, fp)) {
            char *value = strtok(buffer, ";");
            while (value) {
                strcpy(menu[i++].file_name, value);
                value = strtok(NULL, ";");
                amount_files = i;
            }
        }
    }
    fclose(fp);


    for (int i = 0; i < amount_files; i++) {
        //printf("%s",currentDir);
        char filename[100];
        strcpy(filename, menu[i].file_name);
        const unsigned MAX_LENGTH = 256;
        char buffer[MAX_LENGTH];
        strcpy(filepath, currentDir);
        strcat(strcat(filepath, "/"), filename);
        strcpy(menu[i].file_name, filepath);
    }
    for (int j = 0; j < amount_files; j++) {
        printf("path file %d:  %s\n", j + 1, menu[j].file_name);
    }


    //for (int j = 0; j < amount_files; j++) {
    //int i = 0;
    FILE *fp2 = fopen(menu[0].file_name, "r");
    if (!fp)
        printf("Error: could not open file %s", filepath);
    else {
        const unsigned MAX_LENGTH = 256;
        char buffer[MAX_LENGTH];
        while (fgets(buffer, MAX_LENGTH, fp2)) {
            int i = 0;
            char *value = strtok(buffer, ";");
            //if (j == 0){
            while (value) {
                strcpy(menu[i++].main_name, value);
                value = strtok(NULL, ";");
                amount_menu = i;
            }
        } /*if (j == 1){
                    while (value) {
                        strcpy(menu[i++].produce_name, value);
                        value = strtok(NULL, ";");
                        amount_produce = i;
                    }
                } else if (j == 2){
                    while (value) {
                        strcpy(menu[i++].config_name, value);
                        value = strtok(NULL, ";");
                        amount_config = i;
                    }
                }else if (j == 3){
                    while (value) {
                        strcpy(menu[i++].main_name, value);
                        value = strtok(NULL, ";");
                        amount_menu = i;
                    }
                }*/
    }

    fclose(fp2);

    for (int j = 0; j < amount_menu; j++) {
        if (j == 0)
            printf("Main menu: \n");
        printf("[%d] %s\n", j + 1, menu[j].main_name);
    }
    while (scan < 0 || scan > amount_menu || scan == 0) {
        printf("\n What sub menu do you want to enter, choose from 1 to %d\n ", amount_menu);
        scanf(" %d", &scan);
        if (scan < 0 || scan > amount_menu || scan == 0)
            printf("That number is not part of the menu, try again");
    }
    printf("%s menu\n", menu[scan - 1].main_name);

    FILE *fp3 = fopen(menu[scan - 1].file_name, "r");
    if (!fp)
        printf("Error: could not open file %s", filepath);
    else {
        const unsigned MAX_LENGTH = 256;
        char buffer[MAX_LENGTH];
        while (fgets(buffer, MAX_LENGTH, fp3)) {
            int i = 0;
            char *value = strtok(buffer, ";");
            while (value) {
                strcpy(menu[i++].sub_menu, value);
                value = strtok(NULL, ";");
                amount_submenu = i;
            }
        }
    }
    for (int j = 0; j < amount_submenu; j++) {
        printf("[%d] %s\n", j + 1, menu[j].sub_menu);
    }
}




//
// }
