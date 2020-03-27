#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "parameters.h"

void svg_append_tag_to_final_document(char* *finalTag, char* *svgFinalDocument, char* *svgFinalDocument2){

    //Vamos precisar de mais espaço na string svgFinalDocument, pois vamos anexar a circle tag nela:
    int finalDocLen = strlen(*svgFinalDocument);
    int finalTagLen = strlen(*finalTag);

    
    *svgFinalDocument2 = (char*) malloc((finalDocLen + finalTagLen + 1) * sizeof(char));

    sprintf(*svgFinalDocument2, "%s%s", *svgFinalDocument, *finalTag);

    char* aux = *svgFinalDocument;

    *svgFinalDocument = *svgFinalDocument2;

    *svgFinalDocument2 = aux;

}


void svg_finalize_final_document(char* *svgFinalDocument){

    strcat(*svgFinalDocument, "</svg>");

    printf("\n.svg content:\n");
    printf("%s\n", *svgFinalDocument);

}



void svg_build_circ_tag(char* *tag, char* i, char* rad, char* x, char* y, char* corb, char* corp){

    //example: <circle cx="50" cy="50" r="40" stroke="black" stroke-width="3" fill="red" />
        
    sprintf(*tag, " <circle cx=\"%s\" cy=\"%s\" r=\"%s\" stroke=\"%s\" stroke-width=\"2.0\" fill=\"%s\" /> <text x=\"%s\" y=\"%s\" fill=\"blue\" > %s </text> ", x, y, rad, corb, corp, x, y, i);

}

    
void svg_build_rect_tag(char* *tag, char* i, char* w, char* h, char* x, char* y, char* corb, char* corp){

    //example: <rect width="100" height="100" x="130.00" y="90.9" fill="rgb(0,0,255)" stroke-width="3" stroke="rgb(0,0,0)" />
        
    sprintf(*tag, " <rect width=\"%s\" height=\"%s\" x=\"%s\" y=\"%s\" stroke=\"%s\" stroke-width=\"1.5\" fill=\"%s\" /> <text x=\"%s\" y=\"%s\" fill=\"blue\" > %s </text> ", w, h, x, y, corb, corp, x, y, i);
   
}


void svg_build_txt_tag(char* *tag, char* x, char* y, char* corb, char* corp, char* txt){

    //example: <text x="0" y="15" stroke="blue" stroke-width="0.3" fill="red">I love SVG!</text>

    sprintf(*tag, " <text x=\"%s\" y=\"%s\" stroke=\"%s\" stroke-width=\"0.3\" fill=\"%s\" > %s </text> ", x, y, corb, corp, txt);
    
}



void svg_interpret_command(char* *command, char* *commandElements, int commandNum){
        
    //ex of circ command:   c 1 50.00 50.00 30.00 grey magenta

    //ex of rect command:   r 4 10.0 150.0 90.0 40.0 cyan yellow

    /*ex of command elements:
            c 
            50.00 
            50.0
            30.00
            grey 
            magenta
    */

    //lidando com circulos:
    if(*(command[0]) == 'c'){

        sscanf(*command, "%s %s %s %s %s %s %s", commandElements[0], commandElements[1], commandElements[2], commandElements[3], commandElements[4], commandElements[5], commandElements[6]);

    //lidando com retangulos:
    }else if(*(command[0]) == 'r'){

        sscanf(*command, "%s %s %s %s %s %s %s %s", commandElements[0], commandElements[1], commandElements[2], commandElements[3], commandElements[4], commandElements[5], commandElements[6], commandElements[7]);

    }else if(*(command[0]) == 't'){
            
        sscanf(*command, "%s %s %s %s %s %s %s", commandElements[0], commandElements[1], commandElements[2], commandElements[3], commandElements[4], commandElements[5], commandElements[6]);

    }

    for(int j = 0; j<commandNum; ++j){
        printf("%s\n", commandElements[j]);
    }

}


void svg_draw(char* *command, char* *svgFinalDocument, int commandNum){

    //Separando as partes do comando:

        //recebemos o comando. Agora devemos dividir suas partes.
            
        //matriz de strings onde cada string é uma parte do comando:
        char* commandElements[commandNum]; //commandNum == 7 para circulos e texto e 8 para retangulos

        if(*(command[0]) == 'c' || *(command[0]) == 'r'){

            for(int j = 0; j<commandNum; ++j){

                commandElements[j] = (char*) malloc(15*sizeof(char)); //Supomos que 15 == tamanho máx de um pedaço do comando

                if(commandElements[j] == NULL){
                    printf("Error allocating memory for commandElements array.\nFinishing execution..");
                    exit(1);
                }
            }
            
        }else if(*(command[0]) == 't'){

            for(int j = 0; j<commandNum; ++j){

                if(j != commandNum-1){
                    commandElements[j] = (char*) malloc(15*sizeof(char)); //Supomos que 15 == tamanho máx de um pedaço do comando
                }else{
                    commandElements[j] = (char*) malloc(80*sizeof(char)); //aloca 20 bytes para o texto a ser desenhado.
                }


                if(commandElements[j] == NULL){
                    printf("Error allocating memory for commandElements array.\nFinishing execution..");
                    exit(1);
                }
            }

        }

        //Separando, de fato, as partes do comando:
        svg_interpret_command(command, commandElements, commandNum);


    //Criando a tag da figura e a tag do ID da figura a partir do comando:

        char* tag = (char*) malloc(300 * sizeof(char)); //aqui estamos supondo que o tamanho de uma tag vai ser até 50 bytes.

        if(tag == NULL){
            printf("Error! could not allocate memory for tag..");
            exit(1);
        }

            
        //lidando com circulos:
        if(*(command[0]) == 'c'){

            svg_build_circ_tag(&tag, commandElements[1], commandElements[2], commandElements[3], commandElements[4],commandElements[5], commandElements[6]);

        //lidando com retangulos:
        }else if(*(command[0]) == 'r'){

            svg_build_rect_tag(&tag, commandElements[1], commandElements[2], commandElements[3], commandElements[4],commandElements[5], commandElements[6], commandElements[7]);
            
        //lidando com texto:
        }else if(*(command[0]) == 't'){

            svg_build_txt_tag(&tag, commandElements[2], commandElements[3], commandElements[4], commandElements[5], commandElements[6]);

        }

        int tagSize = strlen(tag);

        char* finalTag;

        finalTag = (char*) malloc((tagSize + 1) * sizeof(char));

        if(finalTag == NULL){
            printf("Error! could not allocate memory for finalTag..");
            exit(1);
        }

        strcpy(finalTag, tag);

        free(tag);

            
    //Anexando a tag da figura e a tag do ID da figura na string final:
            
        char* svgFinalDocument2 = NULL;
            
        svg_append_tag_to_final_document(&finalTag, svgFinalDocument, &svgFinalDocument2);

    //Limpando o resto de memoria:
            
        free(svgFinalDocument2);

        for(int j = 0; j<commandNum; ++j){

            free(commandElements[j]);
        }

        free(finalTag);
    
}


void buildSvgPath(Parameter *parameter){

    int outputDirLen = strlen(parameter->outputDir);
    int svgFileNameLen = strlen(parameter->geoFileName);

    char* svgFileName  = (char*) malloc((svgFileNameLen + 1) * sizeof(char));

    strcpy(svgFileName, parameter->geoFileName);

    int aux = 0;

    for(int i = 0; i<svgFileNameLen; ++i){

        if(svgFileName[i] == '.')
            aux = 1;

        if(aux){
            
            if(svgFileName[i] == 'g'){
                svgFileName[i] = 's';
            }else if(svgFileName[i] == 'e'){
                svgFileName[i] = 'v';
            }else if(svgFileName[i] == 'o'){
                svgFileName[i] = 'g';
            }
        }
    }
    
    parameter->svgFullPath = (char*) malloc((outputDirLen + svgFileNameLen + 1) * sizeof(char));

    if(parameter->outputDir[outputDirLen-1] == '/'){

        sprintf(parameter->svgFullPath, "%s%s", parameter->outputDir, svgFileName);

    }else{

        sprintf(parameter->svgFullPath, "%s/%s", parameter->outputDir, svgFileName);

    }

    free(svgFileName);

    printf("\n%s\n", parameter->svgFullPath);

}



//void buildSvgQryPath(Parameter *parameter){

//}

void svg_build_o_rect_tag(char* *tag, float w, float h, float x, float y, int isThereCollision){

    //example: <rect width="100" height="100" x="130.00" y="90.9" fill="#044B94" fill-opacity="0.0" stroke-width="1.5" stroke="rgb(0,0,0)" stroke-dasharray="5,5" />

    if(isThereCollision){
        sprintf(*tag, " <rect width=\"%g\" height=\"%g\" x=\"%g\" y=\"%g\" fill=\"#044B94\" fill-opacity=\"0.0\" stroke-width=\"1.5\" stroke=\"rgb(0,0,0)\" /> ", w, h, x, y);
    }else{
        sprintf(*tag, " <rect width=\"%g\" height=\"%g\" x=\"%g\" y=\"%g\" fill=\"#044B94\" fill-opacity=\"0.0\" stroke-width=\"1.5\" stroke=\"rgb(0,0,0)\" stroke-dasharray=\"5,5\" /> ", w, h, x, y);
    }  

}

float svg_rect_point_next_to_circ_center(float min, float max, float value){

    if(value < min){
        return min;
    }else if(value > max){
        return max;
    }else{
        return value;
    }

}

void svg_qry_o(char* *qryCommand, char* commands[][8], int geo_lines_count){

    //Conseguindo o ID das figuras a serem testadas:

        char J = qryCommand[0][3];
        char K = qryCommand[0][5];

    //extraindo as informaçoes de cada uma das duas figuras:

        char* jShape[8];
        char* kShape[8];
        
        for(int i = 0; i < geo_lines_count; ++i){
            
            if(*commands[i][1] == J){
                
                for(int y = 0; y<8; ++y){

                    jShape[y] = (char*) malloc((strlen(commands[i][y]) + 1) * sizeof(char));  

                    strcpy(jShape[y], commands[i][y]);

                    printf("\n%s\n", jShape[y]);
                }

            }else if(*commands[i][1] == K){
                
                for(int y = 0; y<8; ++y){

                    kShape[y] = (char*) malloc((strlen(commands[i][y]) + 1) * sizeof(char));

                    strcpy(kShape[y], commands[i][y]);

                    printf("\n%s\n", kShape[y]);
                }

            }

        }

    //determinando se ha uma sopreposiçao:

        int isThereCollision;

        float rectX, rectY, rectW, rectH;

        //Temos 4 possibilidades, podemos estar testando:  

        //dois circulos:
        //Eles vão se sobrepor quando a distancia entre os centros dos circulos for menor que a soma dos seus raios.
        if(*jShape[0] == 'c' && *kShape[0] == 'c'){

            float jRadius = strtof(jShape[2], NULL); 
            float kRadius = strtof(kShape[2], NULL);
            
            //printf("\njR:%f kR:%f\n", jRadius, kRadius);

            float jX = strtof(jShape[3], NULL), jY = strtof(jShape[4], NULL);
            float kX = strtof(kShape[3], NULL), kY = strtof(kShape[4], NULL);

            //printf("\njX:%f jY:%f\nkX:%f kY:%f\n", jX, jY, kX, kY);


            //distancia entre os centros dos circulos:
            float D = sqrt(pow((kX - jX), 2) + pow((kY - jY), 2));

            //Se sobrepõem:
            if(D < jRadius + kRadius){
                isThereCollision = 1;
            //Não se sobrepõem:
            }else if (D >= jRadius + kRadius){
                isThereCollision = 0;
            }

            //calculando as informaçoes do retangulo que vai envolve-los:

                //X:
                if(jX - jRadius < kX - kRadius){
                    rectX = (jX - jRadius) - 10; //os 10px são para dar uma "folginha" entre o rect e os dois circulos.
                }else{
                    rectX = (kX - kRadius) - 10;
                }

                //Y:
                if(jY - jRadius < kY - kRadius){
                    rectY = (jY - jRadius) - 10;
                }else{
                    rectY = (kY - kRadius) - 10;
                }

                //W:
                if(jX + jRadius > kX + kRadius){
                    rectW = (jX + jRadius + 10) - rectX;
                }else{
                    rectW = (kX + kRadius + 10) - rectX;
                }

                //H:
                if(jY + jRadius > kY + kRadius){
                    rectH = (jY + jRadius + 10) - rectY;
                }else{
                    rectH = (kY + kRadius + 10) - rectY;
                }


        //dois retangulos:
        }else if(*jShape[0] == 'r' && *kShape[0] == 'r'){

            float jW = strtof(jShape[2], NULL), jH = strtof(jShape[3], NULL);
            float kW = strtof(kShape[2], NULL), kH = strtof(kShape[3], NULL);

            float jX = strtof(jShape[4], NULL), jY = strtof(jShape[5], NULL);
            float kX = strtof(kShape[4], NULL), kY = strtof(kShape[5], NULL);

            //Eles vão se sobrepor quando pelo menos umas das condiçoes abaixo forem satisfeitas: 
            if( ((kY + kH > jY) && (kY < jY + jH)) ||
                ((kY < jY + jH) && (kY + kH > jY)) ||
                ((kX + kW > jX) && (kX < jX + jW)) ||
                ((kX < jX + jW) && (kX + kW > jX)) ){

                isThereCollision = 1;
            }else{
                isThereCollision = 0;
            }

            //calculando as informaçoes do retangulo que vai envolve-los:

                //X:
                if(jX < kX){
                    rectX = jX - 10; //os 10px são para dar uma "folginha" entre o rect e os dois rect.
                }else{
                    rectX = kX - 10;
                }

                //Y:
                if(jY < kY){
                    rectY = jY - 10;
                }else{
                    rectY = kY - 10;
                }

                //W:
                if(jX + jW > kX + kW){
                    rectW = (jX + jW + 10) - rectX;
                }else{
                    rectW = (kX + kW + 10) - rectX;
                }

                //H:
                if(jY + jH > kY + kH){
                    rectH = (jY + jH + 10) - rectY;
                }else{
                    rectH = (kY + kH + 10) - rectY;
                }


        //um circulo e um retangulo: para determinarmos isso precisamos, primeiramente, encontrar
        //o ponto do retangulo mais proximo do centro do circulo. Depois calculamos a distancia entre
        //esses dois pontos e se ela for menor que o raio do circulo entao ha sobreposição.
        }else if((*jShape[0] == 'c' && *kShape[0] == 'r')){

            float jRadius = strtof(jShape[2], NULL);
            float jX = strtof(jShape[3], NULL), jY = strtof(jShape[4], NULL);

            float kW = strtof(kShape[2], NULL), kH = strtof(kShape[3], NULL);
            float kX = strtof(kShape[4], NULL), kY = strtof(kShape[5], NULL);

            float rectPointX = svg_rect_point_next_to_circ_center(kX, kX + kW, jX);
            float rectPointY = svg_rect_point_next_to_circ_center(kY, kY + kH, jY);

            //distancia entre o centro dos circulo e o ponto do retangulo mais proximo dele:
            float D = sqrt(pow((rectPointX - jX), 2) + pow((rectPointY - jY), 2));

            if(D < jRadius){
                isThereCollision = 1;
            }else if(D >= jRadius){
                isThereCollision = 0;
            }

            //calculando as informaçoes do retangulo que vai envolve-los:
                
                //X:
                if(jX - jRadius < kX){
                    rectX = (jX - jRadius) - 10; //os 10px são para dar uma "folginha" entre o rect e os dois rect.
                }else{
                    rectX = kX - 10;
                }

                //Y:
                if(jY - jRadius < kY){
                    rectY = (jY - jRadius) - 10;
                }else{
                    rectY = kY - 10;
                }

                //W:
                if(jX + jRadius > kX + kW){
                    rectW = (jX + jRadius + 10) - rectX;
                }else{
                    rectW = (kX + kW + 10) - rectX;
                }

                //H:
                if(jY + jRadius > kY + kH){
                    rectH = (jY + jRadius + 10) - rectY;
                }else{
                    rectH = (kY + kH + 10) - rectY;
                }

        

        //um retangulo e um ciculo:
        }else if((*jShape[0] == 'r' && *kShape[0] == 'c')){

            float jW = strtof(jShape[2], NULL), jH = strtof(jShape[3], NULL);
            float jX = strtof(jShape[4], NULL), jY = strtof(jShape[5], NULL);

            float kRadius = strtof(kShape[2], NULL);
            float kX = strtof(kShape[3], NULL), kY = strtof(kShape[4], NULL);
            
            float rectPointX = svg_rect_point_next_to_circ_center(jX, jX + jW, kX);
            float rectPointY = svg_rect_point_next_to_circ_center(jY, jY + jH, kY);

            //distancia entre o centro dos circulo e o ponto do retangulo mais proximo dele:
            float D = sqrt(pow((rectPointX - kX), 2) + pow((rectPointY - kY), 2));

            if(D < kRadius){
                isThereCollision = 1;
            }else if(D >= kRadius){
                isThereCollision = 0;
            }

            //calculando as informaçoes do retangulo que vai envolve-los:

                //X:
                if(jX < kX - kRadius){
                    rectX = jX - 10; //os 10px são para dar uma "folginha" entre o rect e os dois rect.
                }else{
                    rectX = (kX - kRadius) - 10;
                }

                //Y:
                if(jY < kY - kRadius){
                    rectY = jY - 10;
                }else{
                    rectY = (kY - kRadius) - 10;
                }

                //W:
                if(jX + jW > kX + kRadius){
                    rectW = (jX + jW + 10) - rectX;
                }else{
                    rectW = (kX + kRadius + 10) - rectX;
                }

                //H:
                if(jY + jH > kY + kRadius){
                    rectH = (jY + jH + 10) - rectX;
                }else{
                    rectH = (kY + kRadius + 10) - rectX;
                }

        }

        printf("\n\nisThereCollision: %d\n\n", isThereCollision);

    //Criando a tag para mostrar visualmente o resultado desta consulta:

        char* tag = (char*) malloc(150 * sizeof(char));

        svg_build_o_rect_tag(&tag, rectW, rectH, rectX, rectY, isThereCollision);

        int tagSize = strlen(tag);

        char* rectTag = (char*) malloc((tagSize + 1) * sizeof(char));

        strcpy(rectTag, tag);

        free(tag);

        printf("\nrect tag:\n%s\n", rectTag);

}

void svg_build_i_dot_line_tag(char* *tag, float pX, float pY, float cmX, float cmY, int isInside){

    //example: <circle cx="50" cy="50" r="40" stroke="black" stroke-width="3" fill="red" /> 
    //                                          <line x1="0" y1="0" x2="200" y2="200" stroke="rgb(255,100,110)" stroke-width="2" />

    if(isInside){

        sprintf(*tag," <circle cx=\"%f\" cy=\"%f\" r=\"1.0\" stroke=\"blue\" stroke-width=\"3\" fill=\"blue\" /> <line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"blue\" stroke-width=\"0.8\" /> " , pX, pY, pX, pY, cmX, cmY);

    }else{

        sprintf(*tag," <circle cx=\"%f\" cy=\"%f\" r=\"1.0\" stroke=\"magenta\" stroke-width=\"3\" fill=\"magenta\" /> <line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"magenta\" stroke-width=\"0.8\" /> " , pX, pY, pX, pY, cmX, cmY); 

    }  
}


void svg_qry_i(char* *qryCommand, char* commands[][8], int geo_lines_count){

    //printf("\ni? - j: %c\n", qryCommand[0][3]);

    //Conseguindo o ID da figura e as coordenadas do ponto:
        
        char J;
        float pX, pY;

        sscanf(&qryCommand[0][3], "%s %f %f", &J, &pX, &pY);

        //printf("J, pX, pY: %c %f %f", J, pX, pY);

    //Extraindo as informaçoes da figura:

        char* jShape[8];

        for(int i = 0; i < geo_lines_count; ++i){

            if(commands[i][1][0] == J){

                printf("J: %c", J);

                for(int k = 0; k<6; ++k){

                    jShape[k] = (char*) malloc((strlen(commands[i][k]) + 1) * sizeof(char));

                    strcpy(jShape[k], commands[i][k]);

                    printf("\njShape[%d]:%s\n", k, jShape[k]);

                } 

            }

        }

    //Determinando se o ponto é interno a figura:

        int isInside;
        float cmX, cmY;

        //Se J for um circulo: 
        //(Sera interno se a distancia entre o ponto e o centro do circulo for menor que o raio.)
        if(*jShape[0] == 'c'){

            float jRadius = strtof(jShape[2], NULL);
            float jX = strtof(jShape[3], NULL);
            float jY = strtof(jShape[4], NULL);
        
            //printf("\njR:%f jX:%f jY:%f\n", jRadius, jX, jY);

            //distancia entre o centro dos circulo e o ponto:
            float D = sqrt(pow((pX - jX), 2) + pow((pY - jY), 2));

            if(D < jRadius){
                isInside = 1;
            }else if (D >= jRadius){
                isInside = 0;
            }

            //determinando o centro de massa da figura:
            cmX = jX; cmY = jY;


        //Se J for um retangulo:
        }else if(*jShape[0] == 'r'){

            float jW = strtof(jShape[2], NULL);
            float jH = strtof(jShape[3], NULL);
            float jX = strtof(jShape[4], NULL);
            float jY = strtof(jShape[5], NULL);

            //printf("\njW:%f jH:%f jX:%f jY:%f\n", jW, jH, jX, jY);

            //sera interno se as condiçoes a seguir forem atendidas:
            if(pX < jX + jW && pX > jX && pY < jY + jH && pY > jY){
                isInside = 1;
            }else{
                isInside = 0;
            }

            //determinando o centro de massa da figura:
            cmX = jX + (jW / 2.0); cmY = jY + (jH / 2.0); 

        }

    //Criando a tag para mostrar visualmente o resultado desta consulta:

        char* tag = (char*) malloc(300 * sizeof(char));

        svg_build_i_dot_line_tag(&tag, pX, pY, cmX, cmY, isInside);

        int tagSize = strlen(tag);

        char* dotLineTag = (char*) malloc((tagSize + 1) * sizeof(char));

        strcpy(dotLineTag, tag);

        free(tag);

        printf("\ndotLine tag:\n%s\n", dotLineTag);

}


void  svg_qry_pnt(){

}


void svg_qry_delf(){

}


void svg_qry_delf2(){

}