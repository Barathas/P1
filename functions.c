//
// Created by Andreas Hansen on 01-12-2021.
//

#include "functions.h"
#include "stdio.h"
typedef struct input mineral;

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

void modify_config(struct input minerals, int x, char scan) {
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

void calculate(struct minerals[20]){
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