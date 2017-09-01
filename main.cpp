#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "casos.h"

#define REPETICIONES 10
#define DELIMITADOR ','
#define ARCHIVO_RESULTADOS "resultados.csv"

int main(int argc, char* argv[]){
    int informantes;
    int respuestas;
    int agenteX, agenteY;
    int podas = 2;
    bool esBench = false;
    std::string podasParam;
    std::string archivo_res;
    std::vector<Casos> lista_casos;

    if(argc == 3){
        archivo_res = std::string(argv[2]);
        esBench = true;
        podasParam = std::string(argv[1]);
        if(podasParam == "-p0"){
            podas = 0;
        }
        else if(podasParam == "-p1a"){
            podas = 11;
        }
        else if(podasParam == "-p1b"){
            podas = 12;
        }
        else if(podasParam == "-p2"){
            podas = 2;
        }
    }

    do {
        std::cin >> informantes;
        std::cin >> respuestas;

        if(!(informantes == 0 && respuestas == 0)){
            Casos caso(informantes, respuestas);    

            for(int i = 0; i < respuestas; i++){
                std::cin >> agenteX;
                std::cin >> agenteY;

                caso.agregarOpinion(agenteX, agenteY);
            }

            lista_casos.push_back(caso);
        }

    } while(!(informantes == 0 && respuestas == 0));

    if(esBench){
        for(unsigned int i = 0; i < lista_casos.size(); i++){
            lista_casos[i].benchmark(REPETICIONES, podas);
        }
        
        std::ofstream resultados;
        resultados.open(archivo_res);
        resultados << "Informantes" << DELIMITADOR << "Respuestas" << DELIMITADOR << "Agentes_Confiables" << DELIMITADOR << "Tiempo_s" << std::endl;
        for(unsigned int i = 0; i < lista_casos.size(); i++){
            resultados << lista_casos[i].getCantidadInformantes() << DELIMITADOR;
            resultados << lista_casos[i].getCantidadRespuestas() << DELIMITADOR;
            resultados << lista_casos[i].getCantidadAgentesConfiables() << DELIMITADOR;
            resultados << lista_casos[i].getBenchmarkTiempo() << std::endl;
        }
        resultados.close();
    } else {
        for(unsigned int i = 0; i < lista_casos.size(); i++){
            lista_casos[i].calcularAgentesConfiables(podas);
        }
    }

    for(unsigned int i = 0; i < lista_casos.size(); i++){
        std::cout << lista_casos[i].getCantidadAgentesConfiables() << std::endl;
    }

    return 0;
}