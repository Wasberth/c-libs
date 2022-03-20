/*
 * García Piña Wilberth David
 * Gómez Tagle Espinosa José Ricardo
 * 2BM1
 * Inteligencia artificial
 * 23/02/2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STR_LENGTH 100000

int askForInt(const char* askText, int min, int max) { //Min and max are inclusive
    int temp = -1;
    char tempStr[MAX_STR_LENGTH];
    char* printStr = (char *)malloc(MAX_STR_LENGTH * sizeof(char));
    char buf[MAX_STR_LENGTH];

    strcpy(tempStr, askText);
    strcat(tempStr, " (min %d, max %d)");
    sprintf(printStr, tempStr, min, max);

    puts(printStr);

    fgets(buf, MAX_STR_LENGTH, stdin);

    if ((!sscanf(buf, "%d", &temp)) || temp < min || temp > max) {
        temp = -1;
    }

    fflush(stdin);

    free(printStr);
    return temp;
}

int askForIntNoMinMax(const char* askText, int min, int max) { //Min and max are inclusive
    int temp = -1;
    char buf[MAX_STR_LENGTH];

    puts(askText);
    fgets(buf, MAX_STR_LENGTH, stdin);

    if ((!sscanf(buf, "%d", &temp)) || temp < min || temp > max) {
        fflush(stdin);
        temp = -1;
    }

    fflush(stdin);
    return temp;
}

double askForDouble(const char* askText, double min, double max) {
    double temp = -1;
    char buf[MAX_STR_LENGTH];

    puts(askText);
    fgets(buf, MAX_STR_LENGTH, stdin);

    if (!sscanf(buf, "%lf", &temp) || temp <= min || temp >= max) {
        fflush(stdin);
        temp = -1;
    }

    fflush(stdin);
    return temp;
}

void askForStr(char* result, const char* askText, int limit) {
    puts(askText);
    fgets(result, limit, stdin);
    *(result + strcspn(result, "\n")) = 0;
    fflush(stdin);
}

bool askForBool(const char* askText) { //If the response is y, returns true. Otherwise, returns false.
    puts(askText);
    char response = getchar();
    fflush(stdin);
    return response == 'y';
}