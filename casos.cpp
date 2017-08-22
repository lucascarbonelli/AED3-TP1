#include "casos.h"

#include <stdlib.h>

Casos::Casos(int informantes, int respuestas){
    _informantes = informantes;
    _respuestas = respuestas;
}

void Casos::agregar_opinion(int agenteX, int agenteY){
    Opinion op;
    op.agenteX = agenteX;
    op.agenteY = agenteY;
    lista_opiniones.push_back(op);
}

int Casos::cantidadAgentesConfiables(){
    std::vector<int> conjDeAgentes = std::vector<int>();

    cantidadAgentesConfiablesBT(conjDeAgentes);

    return conjDeAgentes.size();
}

bool Casos::cantidadAgentesConfiablesBT(std::vector<int> &conjuntoDeAgentes){
    bool conjuntoAceptado = true;

    // Se rechaza el conjunto?
    for(unsigned int i = 0; i < conjuntoDeAgentes.size(); i++){
        for(unsigned int j = 0; j < lista_opiniones.size(); j++){
            if(lista_opiniones[j].agenteX == conjuntoDeAgentes[i]){
                // Se busca en el conjunto al agente Y
                bool agenteYEstaEnConjuntoDeAgentes = false;
                for(unsigned int k = 0; !agenteYEstaEnConjuntoDeAgentes && k < conjuntoDeAgentes.size(); k++){
                    if(abs(lista_opiniones[j].agenteY) == conjuntoDeAgentes[k]){
                        agenteYEstaEnConjuntoDeAgentes = true;
                        if(lista_opiniones[j].agenteY < 0){
                            return false; // se poda la rama!
                        } 
                    }
                }
                // Si no está en el conjunto, se verifica que no sea confiable
                if(!agenteYEstaEnConjuntoDeAgentes && lista_opiniones[j].agenteY > 0){
                    conjuntoAceptado = false; // el agente deberia sumarse al conjunto mas adelante
                }
            }
        }
    }

    // Se acepta el conjunto?
    if(conjuntoDeAgentes.size() > 0 && conjuntoAceptado){
        return true;
    }

    // Se expande el conjunto
    int i;
    if(conjuntoDeAgentes.size() == 0) {i = 1;}
    else {i = conjuntoDeAgentes.back() + 1; }

    for( ; i <= _informantes; i++){
        conjuntoDeAgentes.push_back(i);
        if(!cantidadAgentesConfiablesBT(conjuntoDeAgentes)){
            conjuntoDeAgentes.pop_back();
        } else {
            return true;
        }
    }

    return false; // no se alcanza nunca
}