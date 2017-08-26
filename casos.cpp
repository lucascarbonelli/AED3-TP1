#include "casos.h"
#include <time.h> /* time */

#include <stdlib.h>

Casos::Casos(int informantes, int respuestas){
    _informantes = informantes;
    _respuestas = respuestas;
    _benchmarkTiempo = 0.0;
    _cantidadAgentesConfiables = -1;
}

void Casos::agregarOpinion(int agenteX, int agenteY){
    Opinion op;
    op.agenteX = agenteX;
    op.agenteY = agenteY;
    _listaOpiniones.push_back(op);
}

int Casos::cantidadAgentesConfiables(unsigned int podas){
    std::vector<int> conjDeAgentes = std::vector<int>();
    if(podas == 0){
        return cantidadAgentesConfiablesBTSinPodas(conjDeAgentes);
    }
    else if(podas == 1){
        return cantidadAgentesConfiablesBTUnaPodas(conjDeAgentes);
    }
    else {
        return cantidadAgentesConfiablesBTDosPodas(conjDeAgentes);
    }
}

unsigned int Casos::cantidadAgentesConfiablesBTSinPodas(std::vector<int> conjuntoDeAgentes){
    for(unsigned int i = 0; i < conjuntoDeAgentes.size(); i++){
        for(unsigned int j = 0; j < _listaOpiniones.size(); j++){
            if(_listaOpiniones[j].agenteX == conjuntoDeAgentes[i]){
                // Se busca en el conjunto al agente Y
                bool agenteYEstaEnConjuntoDeAgentes = false;
                for(unsigned int k = 0; !agenteYEstaEnConjuntoDeAgentes && k < conjuntoDeAgentes.size(); k++){
                    if(abs(_listaOpiniones[j].agenteY) == conjuntoDeAgentes[k]){
                        agenteYEstaEnConjuntoDeAgentes = true;
                    }
                }

                // Validación del conjunto
                if(agenteYEstaEnConjuntoDeAgentes && _listaOpiniones[j].agenteY < 0){
                    // Los agentes X e Y estan el conjunto pero X no confia en Y
                    // El conjunto no es valido
                    return 0;
                }

                // Puede ocurrir que un agente diga que algun agente que no esta en el conjunto es confiable
                // y el conjunto no deba considerarse invalido, ya que puede que ese agente se "agregue" al 
                // conjunto al avanzar en la rama. Para que esto ultimo ocurra, necesariamente 
                // el numero del agente debe ser mayor al del ultimo agente agregado, 
                // ya que se agregan al conjunto conjuntoDeAgentes de menor a mayor.
                if(!agenteYEstaEnConjuntoDeAgentes && _listaOpiniones[j].agenteY > 0 && _listaOpiniones[j].agenteY < conjuntoDeAgentes.back()){
                    // El agente Y no esta en el conjunto, X confia en Y
                    // Agente Y es menor al ultimo agente X agregado, por lo tanto nunca va a ser agregado
                    // El conjunto no es valido
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
        agentesConfiablesTmp = cantidadAgentesConfiablesBTSinPodas(conjuntoDeAgentes);

        if(agentesConfiablesTmp > agentesConfiablesHastaAhora){
            agentesConfiablesHastaAhora = agentesConfiablesTmp;
        }

        conjuntoDeAgentes.pop_back();
        agente++;
    }

    return agentesConfiablesHastaAhora;
}

unsigned int Casos::cantidadAgentesConfiablesBTUnaPodas(std::vector<int> conjuntoDeAgentes){
    for(unsigned int i = 0; i < conjuntoDeAgentes.size(); i++){
        for(unsigned int j = 0; j < _listaOpiniones.size(); j++){
            if(_listaOpiniones[j].agenteX == conjuntoDeAgentes[i]){
                // Se busca en el conjunto al agente Y
                bool agenteYEstaEnConjuntoDeAgentes = false;
                for(unsigned int k = 0; !agenteYEstaEnConjuntoDeAgentes && k < conjuntoDeAgentes.size(); k++){
                    if(abs(_listaOpiniones[j].agenteY) == conjuntoDeAgentes[k]){
                        agenteYEstaEnConjuntoDeAgentes = true;
                    }
                }

                // Validación del conjunto
                if(agenteYEstaEnConjuntoDeAgentes && _listaOpiniones[j].agenteY < 0){
                    // Los agentes X e Y estan el conjunto pero X no confia en Y
                    // El conjunto no es valido
                    return 0;
                }

                // Puede ocurrir que un agente diga que algun agente que no esta en el conjunto es confiable
                // y el conjunto no deba considerarse invalido, ya que puede que ese agente se "agregue" al 
                // conjunto al avanzar en la rama. Para que esto ultimo ocurra, necesariamente 
                // el numero del agente debe ser mayor al del ultimo agente agregado, 
                // ya que se agregan al conjunto conjuntoDeAgentes de menor a mayor.
                if(!agenteYEstaEnConjuntoDeAgentes && _listaOpiniones[j].agenteY > 0 && _listaOpiniones[j].agenteY < conjuntoDeAgentes.back()){
                    // El agente Y no esta en el conjunto, X confia en Y
                    // Agente Y es menor al ultimo agente X agregado, por lo tanto nunca va a ser agregado
                    // El conjunto no es valido
                    return 0;
                }

                // Poda
                // Si el AgenteY no está en el conjunto, pero dentro del conjunto hay un agente que dice
                // que es confiable y otro dice que no, eventualmente el cojunto será considerado invalido.
                if(!agenteYEstaEnConjuntoDeAgentes && _listaOpiniones[j].agenteY > 0){
                    for(unsigned int k = 0; k < _listaOpiniones.size(); k++){
                        if(_listaOpiniones[k].agenteY == -(_listaOpiniones[j].agenteY)){
                            for(unsigned int l = 0; l < conjuntoDeAgentes.size(); l++){
                                if(conjuntoDeAgentes[l] == _listaOpiniones[k].agenteX){
                                    return 0;
                                }
                            }
                        }
                    }
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
        agentesConfiablesTmp = cantidadAgentesConfiablesBTUnaPodas(conjuntoDeAgentes);

        if(agentesConfiablesTmp > agentesConfiablesHastaAhora){
            agentesConfiablesHastaAhora = agentesConfiablesTmp;
        }

        conjuntoDeAgentes.pop_back();
        agente++;
    }

    return agentesConfiablesHastaAhora;
}

unsigned int Casos::cantidadAgentesConfiablesBTDosPodas(std::vector<int> conjuntoDeAgentes){
    for(unsigned int i = 0; i < conjuntoDeAgentes.size(); i++){
        for(unsigned int j = 0; j < _listaOpiniones.size(); j++){
            if(_listaOpiniones[j].agenteX == conjuntoDeAgentes[i]){
                // Se busca en el conjunto al agente Y
                bool agenteYEstaEnConjuntoDeAgentes = false;
                for(unsigned int k = 0; !agenteYEstaEnConjuntoDeAgentes && k < conjuntoDeAgentes.size(); k++){
                    if(abs(_listaOpiniones[j].agenteY) == conjuntoDeAgentes[k]){
                        agenteYEstaEnConjuntoDeAgentes = true;
                    }
                }

                // Validación del conjunto
                if(agenteYEstaEnConjuntoDeAgentes && _listaOpiniones[j].agenteY < 0){
                    // Los agentes X e Y estan el conjunto pero X no confia en Y
                    // El conjunto no es valido
                    return 0;
                }

                // Puede ocurrir que un agente diga que algun agente que no esta en el conjunto es confiable
                // y el conjunto no deba considerarse invalido, ya que puede que ese agente se "agregue" al 
                // conjunto al avanzar en la rama. Para que esto ultimo ocurra, necesariamente 
                // el numero del agente debe ser mayor al del ultimo agente agregado, 
                // ya que se agregan al conjunto conjuntoDeAgentes de menor a mayor.
                if(!agenteYEstaEnConjuntoDeAgentes && _listaOpiniones[j].agenteY > 0 && _listaOpiniones[j].agenteY < conjuntoDeAgentes.back()){
                    // El agente Y no esta en el conjunto, X confia en Y
                    // Agente Y es menor al ultimo agente X agregado, por lo tanto nunca va a ser agregado
                    // El conjunto no es valido
                    return 0;
                }

                // Poda 1
                // Si el AgenteY no está en el conjunto, pero dentro del conjunto hay un agente que dice
                // que es confiable y otro dice que no, eventualmente el cojunto será considerado invalido.
                if(!agenteYEstaEnConjuntoDeAgentes && _listaOpiniones[j].agenteY > 0){
                    for(unsigned int k = 0; k < _listaOpiniones.size(); k++){
                        if(_listaOpiniones[k].agenteY == -(_listaOpiniones[j].agenteY)){
                            for(unsigned int l = 0; l < conjuntoDeAgentes.size(); l++){
                                if(conjuntoDeAgentes[l] == _listaOpiniones[k].agenteX){
                                    return 0;
                                }
                            }
                        }
                    }
                }

                // Poda 2
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
        agentesConfiablesTmp = cantidadAgentesConfiablesBTDosPodas(conjuntoDeAgentes);

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
    return _benchmarkTiempo;
}

unsigned int Casos::getCantidadAgentesConfiables(){
    return _cantidadAgentesConfiables;
}

void Casos::benchmark(unsigned int repeticiones, unsigned int podas){
    // Coloca en _benchmarkTiempo el tiempo promedio de las n repeticiones
    double tiempo = 0.0;
    clock_t start;
    clock_t end;

    for(unsigned int i = 0; i < repeticiones; i++){
        start = clock();
        _cantidadAgentesConfiables = cantidadAgentesConfiables(podas);
        end = clock();
        tiempo += (((double)(end - start)) / CLOCKS_PER_SEC);// * 1000; //dejo todo en milisegundos, para que no salte notación cientifica
    }

    _benchmarkTiempo = tiempo/repeticiones;
}