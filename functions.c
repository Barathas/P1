//
// Created by Andreas Hansen on 01-12-2021.
//

#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
typedef struct input minerals;

void data_setup(char scan) {
    FILE *data = fopen("data.csv", "r+");
    if (!data) {
        printf("Can't open data.csv\n");
        printf("Do you want to create a new data.csv file? Y/n\n");
        scanf(" %c", &scan);
        if (scan == 'y' || scan == 'Y') {
            fopen("data.csv", "w+");
            printf("data.csv has been created\n");
        }
    }
}
void config_setup(char scan) {
    FILE *config = fopen("config.csv", "r+");
    if (!config) {
        printf("Can't open config.csv\n");
        printf("Do you want to create a new config.csv file? Y/n\n");
        scanf(" %c", &scan);
        if (scan == 'y' || scan == 'Y') {
            fopen("config.csv", "w+");
            printf("config.csv has been created\n");
        }
    }
}

void modify_config(struct input minerals[20], int x, char scan) {
    FILE *config = fopen("config.csv", "r+");
    printf("Do you want to modify the limit values? Y/n\n");
    scanf(" %c", &scan);
    if (scan == 'y' || scan == 'Y') {
        fopen("config.csv", "w+");
        for (int i = 0; i < 4; i++) {
            fprintf(config, "%s;", minerals[i].name);
        }
        fprintf(config, "\n");
        for (int i = 0; i < 4; i++) {
            printf("What shall the limit of %s be?\n", minerals[i].name);
            scanf(" %d", &x);
            fprintf(config, "%d;", x);
        }
    }
}

void calculate(struct input minerals[20]){
    for (int i = 0; i < 4; i++) {
        if (minerals[i].measured_value < 0){
            printf("ERROR, MEASURED DATA CANNOT BE NEGATIVE\n");
        } else {
            float difference = minerals[i].limit_of_mineral - minerals[i].measured_value;
            if (difference < 0) {
                printf("Too many minerals. Water needs to be replaced!\n");
            } else if (difference == 0) {
                printf("Nothing needs to be added\n");
            } else {
                printf("%f needs to be added\n", difference);
            }
        } return;
    } 
}

void compareFile(struct input minerals[20]) {
    FILE *pt1 = fopen("config.csv", "r");

    int x = 0;
    int y = 0;

    if (!pt1)
        printf("Can't open file 1\n");
    else {
        // Here we have taken size of
        // array 1024 you can modify it
        char buffer[1024];
        int row = 0;
        int column = 0;
        int i = 0;
        char name[10];
        while (fgets(buffer, 1024, pt1)) {
            column = 0;
            row++;
            int i = 0;
            // To avoid printing of column
            // names in file can be changed
            // according to need

            // Splitting the data
            char *value = strtok(buffer, ";");

            if (row == 1) {
                while (value) {
                    strcpy(minerals[i++].name, value);
                    value = strtok(NULL, ";"); // HEllo
                    x = i - 1;
                }
                printf("%s %d", name, x);
            }
            if (row == 2) {
                while (value) {
                    strcpy(name, value);
                    minerals[i++].measured_value = atof(name);
                    value = strtok(NULL, ";");
                }
            }
        }

        // Close the file
        fclose(pt1);
    }
}