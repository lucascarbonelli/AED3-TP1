#include <iostream>
#include <vector>
#include "casos.h"

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

                caso.agregar_opinion(agenteX, agenteY);
            }

            lista_casos.push_back(caso);
        }

    } while(!(informantes == 0 && respuestas == 0));

    for(unsigned int i = 0; i < lista_casos.size(); i++){
        std::cout << lista_casos[i].cantidadAgentesConfiables() << std::endl;
    }

    return 0;
}