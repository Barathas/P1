#ifndef P1_FUNCTIONS_H
#define P1_FUNCTIONS_H
#include <stdio.h>
#include <time.h>
#include <unistd.h>

struct input{
    char measured_name[50]; //Mineral name for the measured value
    float measured_value; //Measured value of the mineral in mg/l
    char limit_name[50];//Mineral name for the limit value
    float limit_value; //limit of the mineral in mg/l
    float calculated_value;
    char produce_name[50];
};
typedef struct input mineral;


int data_setup ();
void modify_config(struct input minerals[20], int data_width, char file[4096], int newfile, char producename[50]);
float calculate(float measured_value, float limit_value, float amount_of_water);
void data_to_file(struct input minerals[20], int data_width, int produce);
void logfile_update(struct input minerals[20], int data_width, int produce);

#endif //P1_MENU_H
