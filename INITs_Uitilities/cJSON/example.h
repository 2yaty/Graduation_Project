/*
#include "Log_Module/cJSON.h"


int main() {

    cJSON *root;
    cJSON *fmt = NULL;
    root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "name", "Jack  Nimble");
    cJSON_AddItemToObject(root, "format", fmt = cJSON_CreateObject());
    cJSON_AddStringToObject(fmt, "type", "rect");
    cJSON_AddNumberToObject(fmt, "width", 1920);
    cJSON_AddNumberToObject(fmt, "height", 1080);
    cJSON_AddFalseToObject (fmt, "interlace");
    cJSON_AddNumberToObject(fmt, "frame rate", 24);

    printf("%s",cJSON_Print(root));

    return 0;
}



------ Output ------
{
        "name": "Jack  Nimble",
        "format":       {
                "type": "rect",
                "width":        1920,
                "height":       1080,
                "interlace":    false,
                "frame rate":   24
        }
}

    cJSON *root;
    cJSON *fmt = NULL;
    root = cJSON_CreateObject();

    cJSON_AddStringToObject(root, "src", "MPU");
    cJSON_AddItemToObject(root, "ACCEL", fmt = cJSON_CreateObject());
    cJSON_AddNumberToObject(fmt, "X", 1920);
    cJSON_AddNumberToObject(fmt, "Y", 1080);

{
		"src":"MPU" ,

		"Accel": {
					"X": 10,
					"Y": 10,
					"Z": 10,
					},

		"GYRO": {
					"X": 10,
					"Y": 10,
					"Z": 10,
					}
}
*/


