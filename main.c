#include <stdio.h>
#include <string.h>
#include "functions.h"
#include <stdlib.h>
#include "menu.h"

int main(){
    config_setup();
    data_setup();
    int data_width = 0;
    int config_width = 0;
    mineral minerals[20];
    int produce = interface();
    FILE *pt1 = fopen("data.csv", "r");
    if (!pt1)
        printf("Can't open file \n");
    else {
        char buffer[1024];
        int row = 0;
        while (fgets(buffer, 1024, pt1)) {
            row++;
            int i = 0;
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
                    minerals[i++].measured_value = atof(value);
                    value = strtok(NULL, ";");
                }
            }
        }
        fclose(pt1);
    }
    //printf("int %d\n",data_width);
    modify_config(minerals, data_width);
    FILE *pt2 = fopen("config.csv", "r");
    if (!pt2)
        printf("Can't open file \n");
    else {
        char buffer[1024];
        int row = 0;
        while (fgets(buffer, 1024, pt1)) {
            row++;
            int i = 0;
            char *value = strtok(buffer, ";");
            if (row == 1) {
                while (value) {
                    strcpy(minerals[i++].limit_name, value);
                    value = strtok(NULL, ";");
                    config_width = i - 1;
                }
            }
            if (row == 2) {
                while (value) {
                    minerals[i++].limit_value = atof(value);
                    value = strtok(NULL, ";");
                }
            }
        }
        fclose(pt2);
    }
    //Testing if there is the same amount of data in both files.
    if (data_width != config_width) {
        printf("Theres is more data in the config or the data file");
        return 0;
    }
    //config_update(scan);
    //printf("int %d\n",data_width);
    for (int i = 0; i < data_width; i++) {
        //printf("test %f\n",minerals[i].measured_value);
        minerals[i].calculated_value = calculate(minerals[i].measured_value, minerals[i].limit_value);
        //printf("Calculated %f\n",minerals[i].calculated_value);
    }
    data_to_file(minerals, data_width);
    logfile_update(minerals, data_width);
    return 0;
}
