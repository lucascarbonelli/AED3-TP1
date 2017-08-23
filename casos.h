#ifndef CASOS_H
#define CASOS_H

#include <vector>

class Casos {
    public:
        Casos(int informantes, int respuestas);
        void agregar_opinion(int agenteX, int agenteY);
        int cantidadAgentesConfiables();

    private:
        int _informantes;
        int _respuestas;

        struct Opinion {
            int agenteX;
            int agenteY;
        };
        
        std::vector<Opinion > lista_opiniones;

        unsigned int cantidadAgentesConfiablesBT(std::vector<int> conjuntoDeAgentes, unsigned int maxCantAgentesConfiables);
};

#endif