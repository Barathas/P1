#include "functions.h"
 int data_setup() {
    char scan[1024];
    FILE *data = fopen("data.csv", "r+");
    if (!data) {
        printf("data.csv does not exist, please upload the file to this location %s\n",getcwd(scan,1024));
        return 1;
    }else
        return 0;
}
void modify_config(struct input minerals[20], int data_width, char file[4096], int newfile, char producename[50]) {
    char char_scan = 0;
    float float_scan = 0;
    if(newfile == 1){
        FILE *config = fopen(file, "w+");
        for (int i = 0; i < data_width; i++) {
            fprintf(config, "%s;", minerals[i].measured_name);
        }
        fprintf(config, "\n");
        for (int i = 0; i < data_width; i++) {
            printf("What shall the limit of %s be in mg/L?\n", minerals[i].measured_name);
            scanf(" %f", &float_scan);
            fprintf(config, "%f;", float_scan);
        }fclose(config);
    }
    else {
        printf("Do you want to modify the mineral limit values for the produce %s? Y/n\n",producename);
        scanf(" %c", &char_scan);
        if (char_scan == 'y' || char_scan == 'Y') {
            FILE *config = fopen(file, "w+");
            for (int i = 0; i < data_width; i++) {
                fprintf(config, "%s;", minerals[i].measured_name);
            }
            fprintf(config, "\n");
            for (int i = 0; i < data_width; i++) {
                printf("What shall the limit of %s be in mg/L?\n", minerals[i].measured_name);
                scanf(" %f", &float_scan);
                fprintf(config, "%f;", float_scan);
            }
            printf("Modification of mineral limits for the produce %s is complete!\n", producename);
            fclose(config);
        }
    }
}
float calculate(float measured_value, float limit_value, float amount_of_water) {
    float calculated_value = 0;
    calculated_value = (limit_value - measured_value) * amount_of_water;
      /*else
         if (calculated_value < 0) {
             printf("%f, Too many minerals. Water needs to be replaced!\n", calculated_value);
         } else if (calculated_value == 0) {
             printf("Nothing needs to be added\n");
         } else {
             printf("%f needs to be added\n", calculated_value);
         }
     }*/
    return calculated_value;
}
void data_to_file(struct input minerals[20], int data_width, int produce) {
    FILE *fpt = fopen("calculated_data.csv", "w+");
    fprintf(fpt, "Name - %s; ", minerals[produce].produce_name);
    for (int i = 0; i < data_width; i++) {
        fprintf(fpt, "%s;", minerals[i].measured_name);
    } fprintf(fpt, "\nMeasured values; ");
    for (int i = 0; i < data_width; i++) {
        fprintf(fpt, "%f;", minerals[i].measured_value);
    } fprintf(fpt, "\nAdded values; ");
    for (int i = 0; i < data_width; i++) {
        fprintf(fpt, "%f;", minerals[i].calculated_value);
    } fprintf(fpt, "\n");
    fclose(fpt);
}
void logfile_update(struct input minerals[20], int data_width, int produce){
    FILE *logfile = fopen("logfile.txt", "a");
    time_t raw_time;
    struct tm * time_info;
    time ( &raw_time );
    time_info = localtime ( &raw_time );
    fprintf(logfile, "%s(", asctime (time_info));
    fprintf(logfile, "|produce name, %s", minerals[produce].produce_name);
    fprintf(logfile, "|Measured values, ");
    for (int i = 0; i < data_width; i++) {
        fprintf(logfile, "%s,",minerals[i].measured_name);
    } fprintf(logfile, "|Measured values,");
    for (int i = 0; i < data_width; i++) {
        fprintf(logfile, "%f,", minerals[i].measured_value);
    } fprintf(logfile, "|Added values,");
    for (int i = 0; i < data_width; i++) {
        fprintf(logfile, "%f,", minerals[i].calculated_value);
    }fprintf(logfile, ")\n");
    fclose(logfile);
}