#ifndef CASOS_H
#define CASOS_H

#include <vector>

class Casos {
    public:
        Casos(int informantes, int respuestas);
        void agregarOpinion(int agenteX, int agenteY);
        int cantidadAgentesConfiables();

        int getCantidadInformantes();
        int getCantidadRespuestas();
        double getBenchmarkTiempo();
        unsigned int getCantidadAgentesConfiables();
        void benchmark(unsigned int repeticiones);

    private:
        int _informantes;
        int _respuestas;

        struct Opinion {
            int agenteX;
            int agenteY;
        };
        
        std::vector<Opinion > _listaOpiniones;

        double _benchmarkTiempo;
        unsigned int _cantidadAgentesConfiables;

        unsigned int cantidadAgentesConfiablesBT(std::vector<int> conjuntoDeAgentes);
};

#endif