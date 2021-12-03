#include <stdio.h>
#include <string.h>
#include "functions.h"


int main(){

    char scan = 0;
    config_setup(scan);
    data_setup(scan);
    int data_width = 0;
    int config_width = 0;
    float y = 0;
    mineral minerals[20];
    load_data(minerals, data_width);
    load_config(minerals, config_width);

    modify_config(minerals, scan, data_width, y);
        //config_update(scan);
    calculate(minerals);


    return 0;

}
