#ifndef P1_FUNCTIONS_H
#define P1_FUNCTIONS_H
#include <stdio.h>
#include <time.h>

struct input{
    char measured_name[50]; //Mineral name for the measured value
    float measured_value; //Measured value of the mineral in mg/l
    char limit_name[50];//Mineral name for the limit value
    float limit_value; //limit of the mineral in mg/l
    float calculated_value;
    char produce_name[50];
};
typedef struct input mineral;

void config_setup();
void data_setup ();
void config_update(char scan);
void modify_config(struct input minerals[20], int data_width, char file[4096], int newfile, char producename[50]);
float calculate(float measured_value, float limit_value, float amount_of_water);
void load_config(struct input minerals[20],int config_width);
void data_to_file(struct input minerals[20], int data_width, int produce);
void logfile_update(struct input minerals[20], int data_width, int produce);

#endif //P1_MENU_H
