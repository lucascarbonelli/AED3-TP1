#ifndef CASOS_H
#define CASOS_H

#include <vector>

class Casos {
    public:
        Casos(int informantes, int respuestas);
        void agregarOpinion(int agenteX, int agenteY);
        void calcularAgentesConfiables(unsigned int podas);

        int getCantidadInformantes();
        int getCantidadRespuestas();
        double getBenchmarkTiempo();
        unsigned int getCantidadAgentesConfiables();
        void benchmark(unsigned int repeticiones, unsigned int podas);

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

        unsigned int cantidadAgentesConfiablesBTSinPodas(std::vector<int> conjuntoDeAgentes);
        unsigned int cantidadAgentesConfiablesBTUnaPodas(std::vector<int> conjuntoDeAgentes);
        unsigned int cantidadAgentesConfiablesBTDosPodas(std::vector<int> conjuntoDeAgentes);
};

#endif