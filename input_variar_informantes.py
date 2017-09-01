from random import randint, choice

informantes_min = 5
informantes_max = 25
respuestas = 20
repeticiones = 10

for n in range(0, repeticiones):
    for informantes in range(informantes_min, informantes_max):
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