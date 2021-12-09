//
// Created by Daniel on 06-12-2021.
//
#include "menu.h"
#include "functions.h"

int interface (struct input minerals[20], int data_width) {
    int produce_number = 0;
    int scan = 0;
    int subscan = 0;
    int amount_menu = 0;
    int i = 0;
    int amount_files = 0;
    int amount_produce = 0;
    int amount_config = 0;
    int amount_submenu = 0;
    int size_submenu = 0;
    char buff[PATH_MAX] = "";
    char foldername[PATH_MAX] = "/menufiles";
    char *currentDir = getcwd(buff, PATH_MAX);
    char rootfilename[PATH_MAX] = "/menu_files.txt";
    char filepath[PATH_MAX];
    char latestfilepath[PATH_MAX];
    char latestfile[PATH_MAX] = "/produce/latest.txt";
    strcpy(filepath, currentDir);
    strcpy(latestfilepath, strcat(filepath, latestfile));
    strcpy(filepath, currentDir);
    strcat(filepath, strcat(foldername, rootfilename));
    printf("%s", filepath);

    FILE *latest = fopen(latestfilepath, "r");
    if (!latest)
        printf("Error: could not open file %s", latestfilepath);
    else {
        //const unsigned MAX_LENGTH = 256;
        //char buffer[MAX_LENGTH];
        fscanf(latest, "%d", &produce_number);
        /*while (fgets(buffer, MAX_LENGTH, latest)) {
            int i = 0;
            char *value = strtok(buffer, ";");
            while (value) {
                produce_number = atof(value);
                value = strtok(NULL, ";");*/
            }
        fclose(latest);
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
        //converting filename to complete filepath in struct
        for (int i = 0; i < amount_files; i++) {
            char foldername[PATH_MAX] = "/menufiles/";
            //printf("%s",currentDir);
            char filename[100];
            strcpy(filename, menu[i].file_name);
            strcpy(filepath, currentDir);
            strcat(filepath, strcat(foldername,filename));
            strcpy(menu[i].file_name, filepath);
        }
        //printing file paths
        for (int j = 0; j < amount_files; j++) {
            printf("path file %d:  %s\n", j + 1, menu[j].file_name);
        }
        //for (int j = 0; j < 2; j++) {
        //int i = 0;
        FILE *fp2 = fopen(menu[0].file_name, "r");
        if (!fp2)
            printf("Error: could not open file %s", menu[0].file_name);
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
            }
        } fclose(fp2);
       /* FILE *produce = fopen(menu[2].file_name, "r");
            if (!produce)
                printf("Error: could not open file %s", filepath);
            else {
                const unsigned MAX_LENGTH = 256;
                char buffer[MAX_LENGTH];
                while (fgets(buffer, MAX_LENGTH, produce)) {
                    int i = 0;
                    char *value = strtok(buffer, ";");
                    //if (j == 0){
                    while (value) {
                        strcpy(menu[i++].produce_name, value);
                        value = strtok(NULL, ";");
                        amount_produce = i;
                    }
                }
                /*if (j == 1){
                        while (value) {
                            strcpy(menu[i++].produce_name, value);
                            value = strtok(NULL, ";");
                        }
                    } /*else if (j == 2){
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
                    }
            }*/

           // fclose(produce);
        while (subscan > 0 || subscan < amount_submenu + 1 || subscan == 0) {
            FILE *produce = fopen(menu[2].file_name, "r");
            if (!produce)
                printf("Error: could not open file %s", menu[2].file_name);
            else {
                const unsigned MAX_LENGTH = 256;
                char buffer[MAX_LENGTH];
                while (fgets(buffer, MAX_LENGTH, produce)) {
                    int i = 0;
                    char *value = strtok(buffer, ";");
                    //if (j == 0){
                    while (value) {
                        strcpy(menu[i++].produce_name, value);
                        value = strtok(NULL, ";");
                        amount_produce = i;
                    }
                }
                fclose(produce);
            subscan = 0;
            for (int j = 0; j < amount_menu; j++) {
                if (j == 0) {
                    printf("Main menu: \n");
                    printf("[%d] %s %s\n", j + 1, menu[j].main_name, menu[produce_number].produce_name);
                    continue;
                }
                printf("[%d] %s\n", j + 1, menu[j].main_name);
            }
            while (scan < 0 || scan > amount_menu || scan == 0) {
                printf("\n What sub menu do you want to enter, choose from 1 to %d\n ", amount_menu);
                scanf(" %d", &scan);
                if (scan == 1) {
                    FILE *latest = fopen(latestfilepath, "w");
                    fprintf(latest, "%d", produce_number);
                    return produce_number;
                } else if (scan < 0 || scan > amount_menu || scan == 0)
                    printf("That number is not part of the menu, try again");
            }
            printf("%s menu\n", menu[scan - 1].main_name);
            FILE *fp3 = fopen(menu[scan].file_name, "r");
            if (!fp3)
                printf("Error: could not open file %s", menu[scan].file_name);
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
            printf("[%d] Back\n", amount_submenu + 1);
            while (subscan < 0 || subscan > amount_submenu + 1 || subscan == 0) {
                printf("What do you want to do, choose from 1 to %d\n ", amount_submenu + 1);
                scanf(" %d", &subscan);
                if (subscan < 0 || subscan > amount_submenu + 1 || subscan == 0)
                    printf("That number is not part of the menu, try again");
                else if (subscan == amount_submenu + 1) {
                    scan = 0;
                    continue;
                } else if (scan == 2) {
                    produce_number = subscan-1;
                    scan = 0;
                    continue;
                } else if (scan == 3 && subscan == 1){
                    for (int j = 0; j < amount_produce; j++) {
                        printf("[%d] %s\n", j + 1, menu[j].produce_name);
                    }
                    scan = 0;
                    printf("[%d] Back\n",amount_produce+1);
                    while (scan < 0 || scan > amount_produce || scan == 0) {
                        printf("\n What produce do you want to edit, choose from 1 to %d\n ", amount_produce);
                        scanf(" %d", &scan);
                        if (scan < 0 || scan > amount_produce || scan == 0)
                            printf("That number is not part of the menu, try again");
                    }
                    printf("You have choosen %s\n",menu[scan-1].produce_name);
                    char producefolder[PATH_MAX] = "/produce/";
                    strcpy(filepath,currentDir);
                    int newfile = 0;
                    modify_config(minerals,data_width,strcat(filepath,strcat(strcat(producefolder,menu[scan-1].produce_name),".csv")),newfile,menu[scan-1].produce_name);
                    //strcat(filepath,strcat(strcat(producefolder,menu[scan-1].produce_name),".csv"));
                    //FILE *config = fopen(filepath, "r+");
                    //fopen(config, "r");
                    scan = 0;
                    continue;
                } else if(scan == 3 && subscan == 2){
                    char newproduce[PATH_MAX];
                    char producefolder[PATH_MAX] = "/produce/";
                    strcpy(filepath,currentDir);
                    printf("What is the name of the new produce?\n");
                    scanf(" %s",newproduce);
                    FILE *produce = fopen(menu[2].file_name, "a");
                    fprintf(produce,";%s",newproduce);
                    strcat(strcat(filepath,producefolder),strcat(newproduce,".csv"));
                    FILE *newproducefile = fopen(filepath, "w");
                    if(!newproducefile)
                        printf("Error: could not open file %s", filepath);
                    else {
                        int newfile = 1;
                        modify_config(minerals, data_width,filepath,newfile,newproduce);
                    }
                    scan = 0;
                    fclose(produce);
                    continue;
                }
            }
        }
    }
}




//
// }
