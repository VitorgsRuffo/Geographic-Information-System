#include "./include/headers.h"
#include "./include/utils.h"
#include "drawing.h"
#include "./qry/qry.h"

int main(int argc, char* argv[]){
    
    //Criando o TAD parametros e obtendo os parametros de execução do programa.
    Parameters parameters = createParameters();
    setParameters(parameters, argv, argc);

    //Abrindo o arquivo de entrada (.geo)
    File geo = openInputFile(parameters, "geo");

    //Criando o TAD desenho:
    Drawing drawing = createDrawing();

    //Lendo o arquivo geo:
    readGeo(geo, drawing);
    closeInputFile(geo);
    
    //Criando SVG do geo:
    Svg geoSvg = NULL;
    geoSvg = createSvg(parameters, drawing, "geo");
    if(geoSvg != NULL){
        drawOnSvg(geoSvg, drawing);
        finishSvg(geoSvg);
    }
    
    if(!isQryNull(parameters)){
        //Abrindo o arquivo de entrada (.qry)
        File qry = openInputFile(parameters, "qry");

        //Lendo o arquivo qry e executando os comandos:
        executeQry(qry, drawing, parameters);
        closeInputFile(qry);

        //Criando SVG do qry:
        Svg qrySvg = NULL;
        qrySvg = createSvg(parameters, drawing, "qry");
        if(qrySvg != NULL){
            drawOnSvg(qrySvg, drawing);
            finishSvg(qrySvg);
        }
    }
    
    freeParameters(parameters);
    freeDrawing(drawing);
    return 0;
}