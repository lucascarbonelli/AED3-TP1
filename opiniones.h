#ifndef OPINIONES_H
#define OPINIONES_H

#include <vector>
#include <set>

enum opinion {CONFIABLE, NO_CONFIABLE, SIN_OPINION};

class Opiniones {
    public:
        Opiniones(int informantes);
        void agregar_opinion(int agenteX, int agenteY, opinion opinionDeXSobreY);
        int cantidadAgentesConfiablesFuerzaBruta();

    private:
        bool esConjuntoConfiable(std::set<int> &conjuntoDeAgentes);
        std::vector<std::vector<opinion > > matriz_opiniones;
};

#endif