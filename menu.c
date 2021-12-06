//
// Created by Daniel on 06-12-2021.
//

#include "menu.h"


int interface (){
    int i = 0;
    int amount_files = 0;
    char buff[PATH_MAX] = "";
    char foldername[PATH_MAX] = "/menufiles";
    char *currentDir =strcat(getcwd(buff,PATH_MAX), foldername);
    char rootfilename[PATH_MAX] = "/menu_files.txt";
    char filepath[PATH_MAX];
    strcpy(filepath, currentDir);
    strcat(filepath,rootfilename);

    menu menu[20];

    FILE *fp = fopen(filepath, "r");
    if (!fp)
        printf("Error: could not open file %s", filepath);

    const unsigned MAX_LENGTH = 256;
    char buffer[MAX_LENGTH];

    while(fgets(buffer, MAX_LENGTH, fp)){
        strcpy(menu[i++].file_name, buffer);
    printf("\n%s",buffer);
    amount_files = i;

    }

   for (int i = 0; i < amount_files; i++){
       printf("%s",currentDir);
       char filename[100];
       strcpy(filename, menu[i].file_name);
       const unsigned MAX_LENGTH = 256;
       char buffer[MAX_LENGTH];
       strcpy(filepath, currentDir);
       strcat(strcat(filepath,"/"), filename);
       strcpy(filepath, "/mnt/c/GIT/P1/cmake-build-debug/menufiles/main_menu.txt");
       FILE *fp = fopen(filepath, "r");

       if (!fp)
           printf("Error: could not open file %s", filepath);

       while(fgets(buffer, MAX_LENGTH, fp)){
           strcpy(menu[i++].file_name, buffer);
           printf("\n%s",buffer);
           amount_files = i;
           printf("files nr %d\n",amount_files);
       }
   }







}
