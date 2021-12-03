#include <stdio.h>
#include <string.h>
#include "functions.h"


int main(){

    char scan = 0;
    config_setup(scan);
    data_setup(scan);
    int x = 0;

    struct input minerals[20];

    strcpy(minerals[0].name, "phosphorus");
    minerals[0].limit_of_mineral = 2;
    minerals[0].measured_value = 1;

    strcpy(minerals[1].name, "potassium");
    minerals[1].limit_of_mineral = 2;
    minerals[1].measured_value = 1;

    strcpy(minerals[2].name, "nitrate");
    minerals[2].limit_of_mineral = 2;
    minerals[2].measured_value = 1;

    strcpy(minerals[3].name, "pH");
    minerals[3].limit_of_mineral = 7;
    minerals[3].measured_value = 1;

    modify_config(minerals, scan, x);
        //config_update(scan);
    calculate(minerals);

    compareFile(minerals);
    return 0;

}
