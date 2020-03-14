#ifndef PARAMETERS_H
#define PARAMETERS_H

struct parameter{
    char* inputDir;
    char* geoFileName;
    char* qryFileName;
    char* outputDir;
};

typedef struct parameter Parameter;



void deal_with_parameters(int paraNum, char* parameters[], Parameter *parameter);



#endif