#include <stdio.h>
#include <string.h>
#include "functions.h"
#include <stdlib.h>
#include "menu.h"

int main(){
    //printf("test0");
    //config_setup();
    data_setup();
    int data_width = 0;
    int config_width = 0;
    float amount_of_water;
    mineral minerals[20];
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
                    data_width = i-1;
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
    int produce = interface(minerals, data_width);
    char buff[PATH_MAX] = "";
    FILE *producefile = fopen(strcat(getcwd(buff, PATH_MAX),"/menufiles/produce.csv"), "r");
    if (!producefile)
        printf("Error: could not open file %s\n", buff);
    else {
        char buffer[1024];
        int row = 0;
        while (fgets(buffer, 1024, producefile)) {
            row++;
            int i = 0;
            char *value = strtok(buffer, ";");
            if (row == 1) {
                while (value) {
                    strcpy(minerals[i++].produce_name, value);
                    value = strtok(NULL, ";");
                }
            }
        }
        fclose(producefile);
    }

    printf("The produce choosen is %s\n",minerals[produce].produce_name);
    //printf("int %d\n",data_width);
    //modify_config(minerals, data_width);
    FILE *pt2 = fopen(strcat(strcat(strcat(getcwd(buff, PATH_MAX),"/produce/"),minerals[produce].produce_name),".csv"), "r");
    if (!pt2)
        printf("Can't open file \n");
    else {
        char buffer[1024];
        int row = 0;
        while (fgets(buffer, 1024, pt2)) {
            row++;
            int i = 0;
            char *value = strtok(buffer, ";");
            if (row == 1) {
                while (value) {
                    strcpy(minerals[i++].limit_name, value);
                    value = strtok(NULL, ";");
                    config_width = i-1;
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
    printf("config width: %d data width %d\n",config_width, data_width);
    for (int i = 0; i < config_width; i++) {
        printf("config values are %d: %f \n",i,minerals[i].limit_value);
    }
    //Testing if there is the same amount of data in both files.
    if (data_width != config_width) {
        printf("Theres is more data in the config or the data file");
        return 0;
    }
    printf("Insert amount of water in L\n");
    scanf(" %f", &amount_of_water);
    //config_update(scan);
    //printf("int %d\n",data_width)
    for (int i = 0; i < data_width; i++) {
        //printf("test %f\n",minerals[i].measured_value);
        minerals[i].calculated_value = calculate(minerals[i].measured_value,minerals[i].limit_value, amount_of_water);
        //printf("Calculated %f\n",minerals[i].calculated_value);
    }
    data_to_file(minerals, data_width,produce);
    logfile_update(minerals, data_width);
    return 0;
}
