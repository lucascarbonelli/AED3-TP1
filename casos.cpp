#include "casos.h"
#include <time.h> /* time */

#include <stdlib.h>

Casos::Casos(int informantes, int respuestas){
    _informantes = informantes;
    _respuestas = respuestas;
    _benchmark_tiempo = 0.0;
    _cantidadAgentesConfiables = -1;
}

void Casos::agregarOpinion(int agenteX, int agenteY){
    Opinion op;
    op.agenteX = agenteX;
    op.agenteY = agenteY;
    lista_opiniones.push_back(op);
}

int Casos::cantidadAgentesConfiables(){
    std::vector<int> conjDeAgentes = std::vector<int>();
    return cantidadAgentesConfiablesBT(conjDeAgentes);
}

unsigned int Casos::cantidadAgentesConfiablesBT(std::vector<int> conjuntoDeAgentes){
    for(unsigned int i = 0; i < conjuntoDeAgentes.size(); i++){
        for(unsigned int j = 0; j < lista_opiniones.size(); j++){
            if(lista_opiniones[j].agenteX == conjuntoDeAgentes[i]){
                // Se busca en el conjunto al agente Y
                bool agenteYEstaEnConjuntoDeAgentes = false;
                for(unsigned int k = 0; !agenteYEstaEnConjuntoDeAgentes && k < conjuntoDeAgentes.size(); k++){
                    if(abs(lista_opiniones[j].agenteY) == conjuntoDeAgentes[k]){
                        agenteYEstaEnConjuntoDeAgentes = true;
                    }
                }

                if(agenteYEstaEnConjuntoDeAgentes && lista_opiniones[j].agenteY < 0){
                    // Los agentes X e Y estan el conjunto pero X no confia en Y
                    // se poda la rama!
                    return 0;
                }

                // Se acepta el conjunto?
                // Ningún agente en el conjunto diga que es confiable un agente que no esta en el conjunto.
                // Puede ocurrir que un agente diga que algun agente que no esta en el conjunto es confiable
                // y la rama no deba podarse, ya que puede que ese agente se "agregue" al conjunto al avanzar
                // en la rama. Para que esto ultimo ocurra, necesariamente el numero del agente debe ser mayor
                // al del ultimo agente agregado, ya que se agregan al conjunto conjuntoDeAgentes de menor
                // a mayor.
                // !! La rama se poda si algun agente del conjunto dice que es confiable un agente fuera del
                // conjunto de numero menor al ultimo agregado !!

                // Si no está en el conjunto, se verifica que no sea confiable
                if(!agenteYEstaEnConjuntoDeAgentes && lista_opiniones[j].agenteY > 0 && lista_opiniones[j].agenteY < conjuntoDeAgentes.back()){
                    // El agente Y no esta en el conjunto, X confia en Y
                    // Agente Y es menor al ultimo agente X agregado, por lo tanto nunca va a ser agregado
                    // se poda la rama!
                    return 0;
                }
            }
        }
    }
 
    // Se expande el conjunto, si el conjunto esta vacio, se agrega el agente 1
    // Si no esta vacio se agrega el agente que sigue al ultimo agregado
    int agente = conjuntoDeAgentes.size() == 0 ? 1 : conjuntoDeAgentes.back() + 1;
    unsigned int agentesConfiablesHastaAhora = conjuntoDeAgentes.size();
    unsigned int agentesConfiablesTmp;

    while(agente <= _informantes){
        conjuntoDeAgentes.push_back(agente);
        agentesConfiablesTmp = cantidadAgentesConfiablesBT(conjuntoDeAgentes);

        if(agentesConfiablesTmp > agentesConfiablesHastaAhora){
            agentesConfiablesHastaAhora = agentesConfiablesTmp;
        }

        conjuntoDeAgentes.pop_back();
        agente++;
    }

    return agentesConfiablesHastaAhora;
}

int Casos::getCantidadInformantes(){
    return _informantes;
}

int Casos::getCantidadRespuestas(){
    return _respuestas;
}

double Casos::getBenchmarkTiempo(){
    return _benchmark_tiempo;
}

unsigned int Casos::getCantidadAgentesConfiables(){
    return _cantidadAgentesConfiables;
}

void Casos::benchmark(unsigned int repeticiones){
    // Coloca en _benchmark_tiempo el tiempo promedio de las n repeticiones
    double tiempo = 0.0;
    clock_t start;
    clock_t end;

    for(unsigned int i = 0; i < repeticiones; i++){
        start = clock();
        _cantidadAgentesConfiables = cantidadAgentesConfiables();
        end = clock();
        tiempo += (((double)(end - start)) / CLOCKS_PER_SEC);// * 1000; //dejo todo en milisegundos, para que no salte notación cientifica
    }

    _benchmark_tiempo = tiempo/repeticiones;
}