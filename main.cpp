#include <iostream>
#include <vector>
#include "opiniones.h"

int main(){
    int informantes;
    int respuestas;
    int agenteX, agenteY;
    std::vector<Opiniones> lista_casos;

    do {
        std::cin >> informantes;
        std::cin >> respuestas;

        if(informantes != 0 && respuestas != 0){
            Opiniones op(informantes);

            for(int i = 0; i < respuestas; i++){
                std::cin >> agenteX;
                std::cin >> agenteY;

                if(agenteY > 0){ op.agregar_opinion(agenteX, agenteY, CONFIABLE); }
                else{ op.agregar_opinion(agenteX, -agenteY, NO_CONFIABLE); } // Se invierte el agenteY!
            }

            lista_casos.push_back(op);
        }

    } while(informantes != 0 && respuestas != 0);

    for(unsigned int i = 0; i < lista_casos.size(); i++){
        std::cout << lista_casos[i].cantidadAgentesConfiablesFuerzaBruta() << std::endl;
    }

    return 0;
}