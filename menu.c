//
// Created by Daniel on 06-12-2021.
//

#include "menu.h"


int interface () {
    int scan;
    int amount_menu;
    int i = 0;
    int amount_files = 0;
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

    const unsigned MAX_LENGTH = 256;
    char buffer[MAX_LENGTH];

    while (fgets(buffer, MAX_LENGTH, fp)) {
        strcpy(menu[i++].file_name, buffer);
        amount_files = i;
    }


    for (int i = 0; i < amount_files; i++) {
        //printf("%s",currentDir);
        char filename[100];
        strcpy(filename, menu[i].file_name);
        const unsigned MAX_LENGTH = 256;
        char buffer[MAX_LENGTH];
        strcpy(filepath, currentDir);
        strcat(strcat(filepath, "/"), filename);
        strcpy(filepath, "/mnt/c/GIT/P1/cmake-build-debug/menufiles/main_menu.txt");
        FILE *fp = fopen(filepath, "r");

        if (!fp)
            printf("Error: could not open file %s", filepath);

        while (fgets(buffer, MAX_LENGTH, fp)) {
            strcpy(menu[i++].main_name, buffer);
            amount_menu = i;
            //printf("buff %s",buffer);
        }
    }
    for (int j = 0; j < amount_files; j++) {
        if (j == 0)
            printf("Main menu: \n");
        printf("[%d] %s", j + 1, menu[j].main_name);
    }
    while (scan < 0 || scan > amount_menu || scan == 0) {
        printf("\n What sub menu do you want to enter, choose from 1 to %d\n ", amount_files);
        scanf(" %d", &scan);
        if (scan < 0 || scan > amount_menu || scan == 0)
            printf("That number is not part of the menu, try again");
    }

    printf("%s menu",menu[scan-1].main_name);


}

