from random import randint, choice

informantes_min = 10
informantes_max = 20
respuestas = 30

for informantes in range(informantes_min, informantes_max):
    caso = []
    for x in range(0, respuestas):
        opinion = randint(1, informantes), randint(1, informantes) * choice((-1, 1))
        while (opinion[0], abs(opinion[1])) in caso :
            opinion = randint(1, informantes), randint(1, informantes) * choice((-1, 1))
        caso.append(opinion)

    print('{} {}'.format(informantes, respuestas))
    for agenteX, agenteY in caso:
        print('{} {}'.format(agenteX, agenteY))

print('0 0')