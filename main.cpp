#include <iostream>
#include <fstream>
#include <vector>
#include "casos.h"

#define REPETICIONES 1
#define DELIMITADOR ','
#define ARCHIVO_RESULTADOS "resultados.csv"

int main(){
    int informantes;
    int respuestas;
    int agenteX, agenteY;
    std::vector<Casos> lista_casos;

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

    for(unsigned int i = 0; i < lista_casos.size(); i++){
        lista_casos[i].benchmark(REPETICIONES);
    }

    std::ofstream resultados;
    resultados.open(ARCHIVO_RESULTADOS);
    resultados << "informantes" << DELIMITADOR << "respuestas" << DELIMITADOR << "agentes_confiables" << DELIMITADOR << "tiempo" << std::endl;
    for(unsigned int i = 0; i < lista_casos.size(); i++){
        resultados << lista_casos[i].getCantidadInformantes() << DELIMITADOR;
        resultados << lista_casos[i].getCantidadRespuestas() << DELIMITADOR;
        resultados << lista_casos[i].getCantidadAgentesConfiables() << DELIMITADOR;
        resultados << lista_casos[i].getBenchmarkTiempo() << std::endl;
    }
    resultados.close();

    for(unsigned int i = 0; i < lista_casos.size(); i++){
        std::cout << lista_casos[i].getCantidadAgentesConfiables() << std::endl;
    }

    return 0;
}