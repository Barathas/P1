struct input{
    char measured_name[50]; //Mineral name for the measured value
    float measured_value; //Measured value of the mineral in mg/l
    char limit_name[50];//Mineral name for the limit value
    float limit_value; //limit of the mineral in mg/l
    float calculated_value;
    float calculated_value;
};
typedef struct input mineral;

void config_setup(char scan);
void data_setup (char scan);
void config_update(char scan);
void modify_config(struct input minerals[20], int data_width, char scan, float y);
void calculate(struct input minerals[20]);
void load_data(struct input minerals[20],int data_width);
void load_config(struct input minerals[20],int config_width);
void data_to_file(struct input minerals[20]);

