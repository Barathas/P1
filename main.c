#include <stdio.h>
#include <string.h>
#include "functions.h"
#include <stdlib.h>
#include "menu.h"

int main(){
    int data;
    data  = data_setup();
    if(data){
        return 40;
    }
    int data_width = 0;
    int config_width = 0;
    float amount_of_water;
    int negative_calculation = 0;
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
    int produce = interface(minerals, data_width);//menu
    char buff[PATH_MAX] = "";
    FILE *producefile = fopen(strcat(getcwd(buff, PATH_MAX),"/menufiles/produce.csv"), "r");
    if (!producefile)
        printf("Error: could not open file %s\n", buff);
    else {
        char buffer[1024];
        while (fgets(buffer, 1024, producefile)) {
            int i = 0;
            char *value = strtok(buffer, ";");
                while (value) {
                    strcpy(minerals[i++].produce_name, value);
                    value = strtok(NULL, ";");
                }
        }
        fclose(producefile);
    }
    printf("The produce choosen is %s\n\n",minerals[produce].produce_name);
    FILE *select_produce = fopen(strcat(strcat(strcat(getcwd(buff, PATH_MAX),"/produce/"),minerals[produce].produce_name),".csv"), "r");
    if (!select_produce)
        printf("Error: could not open file %s\n", buff);
    else {
        char buffer[1024];
        int row = 0;
        while (fgets(buffer, 1024, select_produce)) {
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
        fclose(select_produce);
    }

    for (int i = 0; i < config_width; i++) {
        printf("The limit for %s is: %.2f mg/L \n",minerals[i].measured_name,minerals[i].limit_value);
    }
    //Testing if there is the same amount of data in both files.
    if (data_width != config_width) {
        printf("Theres is more data in the config or the data file");
        return 1;
    }
    printf("Insert amount of water in liter\n");
    scanf(" %f", &amount_of_water);
    while (0 > amount_of_water) {
        printf("Please insert a new valid number above 0: ");
        scanf(" %f", &amount_of_water);
    }
    //printf("int %d\n",data_width)
    for (int i = 0; i < data_width; i++) {
        minerals[i].calculated_value = calculate(minerals[i].measured_value,minerals[i].limit_value, amount_of_water);
        amount_of_water += (minerals[i].calculated_value/1000000);
        if (minerals[i].calculated_value < 0) {
            printf("ERROR with %s value\n", minerals[i].measured_name);
            negative_calculation = 1;
        }
    } if (negative_calculation == 1){
        printf("End of program! WARNING! This water cant be used for %s",minerals[produce].produce_name);
        return -1;
    }
    data_to_file(minerals, data_width, produce);
    logfile_update(minerals, data_width, produce);
    printf("calculated_data.csv was printed with the minerals to be added in mg, for the produce %s. The file is located in %s. The logfile is updated with timestamp.",minerals[produce].produce_name,strcat(getcwd(buff, PATH_MAX),"/calculated_data.csv"));
    return 0;
}
