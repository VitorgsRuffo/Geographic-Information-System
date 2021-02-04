#include "../include/headers.h"
#include "../include/elements.h"
#include "./input/parameters.h"

char** createCommandParts(int numberOfParts){
    char** commandParts = (char**) malloc(sizeof(char*) * numberOfParts);
    
    for(int i = 0; i<numberOfParts; i++)
        commandParts[i] = (char*) malloc(60 * sizeof(char));
    
    return commandParts;
}

char* getFileNameWithoutPathAndExtension(char* fullFileName){ //Retorna somente o nome do arquivo, retirando possiveis caminho e a sua extensão.
    
    int j = 0;
    int fullFileNameLength = strlen(fullFileName); 

    char* fileNameWithoutExtension;

    for(int i = 0; i<fullFileNameLength; ++i){  

        if(fullFileName[i] == '/'){
            j = i + 1;
        }

        if(fullFileName[i] == '.' && fullFileName[i+1] != '/'){ //corrige o erro ./dir/arq.extension
            
            fullFileName[i] = ' ';
            fileNameWithoutExtension = (char*) malloc((strlen(&fullFileName[j]) - 3) * sizeof(char));
            sscanf(&fullFileName[j],"%s", fileNameWithoutExtension);
            fullFileName[i] = '.';
            break;
        }
    }
    return fileNameWithoutExtension;
}

char* buildQryOutputPath(Parameters Param, char* extension){
    char* outputDirectory = getOutputDirectory(Param);
    int outputDirectoryLength = strlen(outputDirectory);

    char* fullGeoName = getGeoName(Param);
    char* geoNameWithoutPathAndExtension = getFileNameWithoutPathAndExtension(fullGeoName);
    
    char* fullQryName = getQryName(Param);
    char* qryNameWithoutPathAndExtension = getFileNameWithoutPathAndExtension(fullQryName);

    int qryOutputPathLength = strlen(outputDirectory) + strlen(geoNameWithoutPathAndExtension) + strlen(qryNameWithoutPathAndExtension) + strlen(".ext") + 5;
    char* qryOutputPath = (char*) malloc(qryOutputPathLength * sizeof(char));

    if(outputDirectory[outputDirectoryLength - 1] == '/'){
        sprintf(qryOutputPath, "%s%s-%s.%s", outputDirectory, geoNameWithoutPathAndExtension, qryNameWithoutPathAndExtension, extension);    
    }else{
        sprintf(qryOutputPath, "%s/%s-%s.%s", outputDirectory, geoNameWithoutPathAndExtension, qryNameWithoutPathAndExtension, extension);    
    }

    free(geoNameWithoutPathAndExtension);
    free(qryNameWithoutPathAndExtension);
    return qryOutputPath;
}

int isBlockInCircleRange(Info blockInfo, double x, double y, double radius){ 
    double blockX = atof(getBlockX(blockInfo));
    double blockY = atof(getBlockY(blockInfo));
    
    double blockWidth = atof(getBlockWidth(blockInfo));
    double blockHeight = atof(getBlockHeight(blockInfo));
    
    double point1X, point2X, point3X, point4X;
    double point1Y, point2Y, point3Y, point4Y;

    point1X = blockX;               point1Y = blockY;
    point2X = blockX + blockWidth;  point2Y = blockY;
    point3X = blockX;               point3Y = blockY + blockHeight;
    point4X = blockX + blockWidth;  point4Y = blockY + blockHeight;


    if((pow(x - point1X, 2) + pow(y - point1Y, 2) <= pow(radius, 2)) &&
       (pow(x - point2X, 2) + pow(y - point2Y, 2) <= pow(radius, 2)) &&
       (pow(x - point3X, 2) + pow(y - point3Y, 2) <= pow(radius, 2)) &&
       (pow(x - point4X, 2) + pow(y - point4Y, 2) <= pow(radius, 2)) ){
        
        return 1;
    }else{
        return 0;
    }
}

char* getUrbanElementToString(Info urbanElementInfo, char* urbanElementType){
    char* urbanElementToString = NULL;

    if(urbanElementType[0] == 'q')
        urbanElementToString = blockToString(urbanElementInfo);

    else if(urbanElementType[0] == 'h')
        urbanElementToString = hydrantToString(urbanElementInfo);
        
    else if(urbanElementType[0] == 's')
        urbanElementToString = semaphoreToString(urbanElementInfo);
        
    else if(urbanElementType[0] == 'r') 
        urbanElementToString = baseRadioToString(urbanElementInfo);
       
    return urbanElementToString;
}

double getNextestRectPointToCircCenter(double min, double max, double value){

    if(value < min){
        return min;
    }else if(value > max){
        return max;
    }else{
        return value;
    }
}

int checkRectCircOverlap(Info rect, Info circ){
    double jX = atof(getRectangleX(rect));
    double jY = atof(getRectangleY(rect));
    double jWidth = atof(getRectangleWidth(rect));
    double jHeight = atof(getRectangleHeight(rect));

    double kRadius = atof(getCircleRadius(circ));
    double kX = atof(getCircleX(circ));
    double kY = atof(getCircleY(circ));

    double rectPointX = getNextestRectPointToCircCenter(jX, jX + jWidth, kX);
    double rectPointY = getNextestRectPointToCircCenter(jY, jY + jHeight, kY);                                                        

    //distancia entre o centro dos circulo e o ponto do retangulo mais proximo dele:
    double D = sqrt(pow((rectPointX - kX), 2) + pow((rectPointY - kY), 2));

    if(D < kRadius){
        return 1;
    }else{
        return 0;
    }
}