#include "opiniones.h"

Opiniones::Opiniones(int informantes){
    matriz_opiniones = std::vector<std::vector<opinion> >(informantes, std::vector<opinion>(informantes, SIN_OPINION));
}

void Opiniones::agregar_opinion(int agenteX, int agenteY, opinion opinionDeXSobreY){
    // El numero de agente empieza en 1, se le resta uno para aprovechar la posicion cero del vector
    matriz_opiniones[agenteX-1][agenteY-1] = opinionDeXSobreY;
}

int Opiniones::cantidadAgentesConfiablesFuerzaBruta(){
    // Se construyen todos los conjuntos posibles de agentes (n!)
    unsigned int maxCantidadAgentesConfiables = 0;
    std::set<int> conjuntoDeAgentesConfiables;

    for(unsigned int i = 0; i < matriz_opiniones.size(); i++){
        
        for(unsigned int j = i; j < matriz_opiniones.size(); j++){
            conjuntoDeAgentesConfiables.clear();
            conjuntoDeAgentesConfiables.insert(i);

            for(unsigned int k = j; k < matriz_opiniones.size(); k++){
                conjuntoDeAgentesConfiables.insert(k);
                if(esConjuntoConfiable(conjuntoDeAgentesConfiables) && conjuntoDeAgentesConfiables.size() > maxCantidadAgentesConfiables){
                    maxCantidadAgentesConfiables = conjuntoDeAgentesConfiables.size();
                }
            }
        }
    }

    return maxCantidadAgentesConfiables;
}

bool Opiniones::esConjuntoConfiable(std::set<int> &conjuntoDeAgentes){
    bool esConfiable = true;

    for(unsigned int i = 0; i < matriz_opiniones.size(); i++){
        for(unsigned int j = 0; j < matriz_opiniones.size(); j++){
            if(conjuntoDeAgentes.find(i) != conjuntoDeAgentes.end()){
                // El agente i esta en el subconjunto analizado
                if(conjuntoDeAgentes.find(j) != conjuntoDeAgentes.end()){
                    // El agente j esta en el subconjunto analizado
                    if(matriz_opiniones[i][j] == NO_CONFIABLE){
                        esConfiable = false;
                    }
                } else {
                    // El agente j no esta en el subconjunto analizado
                    if(matriz_opiniones[i][j] == CONFIABLE){
                        esConfiable = false;
                    }
                }
            }
        }
    }

    return esConfiable;
}
