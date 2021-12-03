#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void modify_config(struct input minerals[20], int data_width, char scan, float y) {
    FILE *config = fopen("config.csv", "r+");
    printf("Do you want to modify the limit values? Y/n\n");
    scanf(" %c", &scan);
    if (scan == 'y' || scan == 'Y') {
        fopen("config.csv", "w+");
        for (int i = 0; i < 4; i++) {
            fprintf(config, "%s;", minerals[i].measured_name);
        }
        fprintf(config, "\n");
        for (int i = 0; i < 4; i++) {
            printf("What shall the limit of %s be?\n", minerals[i].measured_name);
            scanf(" %f", &y);
            fprintf(config, "%f;", y);
        }
    }
}

void calculate(struct input minerals[20]) {
    for (int i = 0; i < 4; i++) {
        if (minerals[i].measured_value < 0) {
            printf("ERROR, MEASURED DATA CANNOT BE NEGATIVE\n");
        } else {
            minerals[i].calculated_value = minerals[i].limit_of_mineral - minerals[i].measured_value;
            if (minerals[i].calculated_value < 0) {
                printf("%f, Too many minerals. Water needs to be replaced!\n", minerals[i].calculated_value);

            } else if (minerals[i].calculated_value == 0) {
                printf("Nothing needs to be added\n");

            } else {
                printf("%f needs to be added\n", minerals[i].calculated_value);
            }
        }
    }
}
void load_data(struct input minerals[20],int data_width) {
    FILE *pt1 = fopen("config.csv", "r");

    if (!pt1)
        printf("Can't open file 1\n");
    else {
        // Here we have taken size of
        // array 1024 you can modify it
        char buffer[1024];
        int row = 0;
        char name[10];
        while (fgets(buffer, 1024, pt1)) {
            row++;
            int i = 0;
            // To avoid printing of column
            // names in file can be changed
            // according to need
            // Splitting the data
            char *value = strtok(buffer, ";");

            if (row == 1) {
                while (value) {
                    strcpy(minerals[i++].measured_name, value);
                    value = strtok(NULL, ";");
                    data_width = i - 1;
                }
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

void data_to_file(struct input minerals[20]) {
    FILE *fpt;
    fpt = fopen("calculated_data.csv", "w+");
    fprintf(fpt, "Name; ");
    for (int i = 0; i < 4; i++) {
        fprintf(fpt, "%s;", minerals[i].name);
    } fprintf(fpt, "\n Measured values; ");
    for (int i = 0; i < 4; i++) {
        fprintf(fpt, "%f;", minerals[i].measured_value);
    } fprintf(fpt, "\n Added values; ");
    for (int i = 0; i < 4; i++) {
        fprintf(fpt, "%f;", minerals[i].calculated_value);
    } fprintf(fpt, "\n");
    fclose(fpt);
}

