from random import randint, choice

repeticiones = 10
informantes = 20
respuestas_min = 0
respuestas_max = 100

for n in range(0, repeticiones):
    for respuestas in range(respuestas_min, respuestas_max):
        caso = []
        for x in range(0, respuestas):
            opinion = randint(1, informantes), randint(1, informantes) * choice((-1, 1))
            while (opinion[0], opinion[1]) in caso or (opinion[0], -opinion[1]) in caso :
                opinion = randint(1, informantes), randint(1, informantes) * choice((-1, 1))
            caso.append(opinion)

        print('{} {}'.format(informantes, respuestas))
        for agenteX, agenteY in caso:
            print('{} {}'.format(agenteX, agenteY))

print('0 0')