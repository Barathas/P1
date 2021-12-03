//
// Created by Andreas Hansen on 01-12-2021.
//
struct input {
    char name[50]; //name of mineral
    float limit_of_mineral; //limit of the mineral in mg/l
    float measured_value; //measured value of the mineral in mg/l
};

void config_setup(char scan);
void data_setup (char scan);
void config_update(char scan);
void modify_config(struct input minerals[20], int x, char scan);
void calculate(struct input minerals[20]);
void compareFile(struct input minerals[20]);

