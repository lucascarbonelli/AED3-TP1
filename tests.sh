#./bin/bash

# Gafico 1 (Variar podas e informantes)
# Variando el numero de podas (cuatro lineas en el grafico), 
# variando la cantiadad de informantes, manteniendo fijo la cantidad de opiniones
# Por ej.: 5 <= informantes <= 100, opiniones = 15

python3 input_variar_informantes.py > input_informantes_5_a_20_opiniones_20
./main -p0 resultados_p0_informantes_5_a_20_opiniones_20.csv < input_informantes_5_a_20_opiniones_20
./main -p1a resultados_p1a_informantes_5_a_20_opiniones_20.csv < input_informantes_5_a_20_opiniones_20 
./main -p1b resultados_p1b_informantes_5_a_20_opiniones_20.csv < input_informantes_5_a_20_opiniones_20 
./main -p2 resultados_p2_informantes_5_a_20_opiniones_20.csv < input_informantes_5_a_20_opiniones_20

# Gafico 2 (Variar podas y opiniones)
# Variando el numero de podas (cuatro lineas en el grafico), 
# manteniendo fijo la cantiadad de informantes, variando la cantidad de opiniones
# Por ej.: informantes = 20, 5 <= opiniones <= 100

python3 input_variar_opiniones.py > input_informantes_20_opiniones_0_a_100
./main -p0 resultados_p0_informantes_20_opiniones_0_a_100.csv < input_informantes_20_opiniones_0_a_100 
./main -p1a resultados_p1a_informantes_20_opiniones_0_a_100.csv < input_informantes_20_opiniones_0_a_100 
./main -p1b resultados_p1b_informantes_20_opiniones_0_a_100.csv < input_informantes_20_opiniones_0_a_100 
./main -p2 resultados_p2_informantes_20_opiniones_0_a_100.csv < input_informantes_20_opiniones_0_a_100 