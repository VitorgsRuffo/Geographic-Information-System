#include "../../include/headers.h"
#include "../../include/dataStructure.h"
#include "../urban-elements/block.h"
#include "../urban-elements/address.h"
#include "./city.h"
#include "house.h"

#define houseWidth 15
#define houseHeight 15

typedef struct {
    char* cpf;
    Address address;
    Point coordinates;
    double w, h;
}house;

void setHouseCoordinates(house* h);

House createHouse(char* cpf, char* cep, char face, int number, char* compl, City Ct){
    
    house *h = (house*) malloc(sizeof(house));
    if(h == NULL) return NULL;

    h->cpf = (char*) malloc((strlen(cpf) + 1) * sizeof(char));
    strcpy(h->cpf, cpf);
    h->address = createAdress(cep, face, number, compl, Ct);
    h->coordinates = createPoint(0,0);
    setHouseCoordinates(h);
    h->w = houseWidth;
    h->h = houseHeight;

    return h;
}

void setHouseCoordinates(house* h){
    
    double addressX = getAddressX(h->address);
    double addressY = getAddressY(h->address);

    setPointX(h->coordinates, addressX - (h->w / 2.0));
    setPointY(h->coordinates, addressY - (h->h / 2.0));
}

char* getHouseCpf(House H){
    if(H == NULL)
        return NULL;
    house *h = (house*) H;
    return h->cpf;
}

Point getHouseCoordinates(House H){
    if(H == NULL)
        return NULL;
    house *h = (house*) H;
    return h->coordinates;
}

double getHouseW(House H){
    if(H == NULL)
        return 0;
    house *h = (house*) H;
    return h->w;
}
double getHouseH(House H){
    if(H == NULL)
        return 0;
    house *h = (house*) H;
    return h->h;
}

Point getHouseCenterOfMass(House H){
    if(H == NULL)
        return NULL;
    house *h = (house*) H;
    return getAddressCoordinates(h->address);
}


void printHouse(House H){
    if(H == NULL)
        return;
    house *h = (house*) H;
    printf("Casa:\nw: %lf\nh: %lf\nx: %lf\ny: %lf\n\n",
            h->w, h->h, getPointX(h->coordinates), getPointY(h->coordinates));
}

void freeHouse(House H){
    if(H == NULL)
        return;

    house *h = (house*) H;
    free(h->cpf);
    freeAdress(h->address);
    free(h->coordinates);
    free(h);
}