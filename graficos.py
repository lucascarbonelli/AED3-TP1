
# coding: utf-8

# In[2]:

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from math import sqrt

#df = pd.read_csv('resultados.csv', delimiter=',')
#df.sort_values(by='Tiempo_s')


# In[3]:

#plt.clf()
#df.sort_values(by='Informantes').plot(x='Informantes', y='Tiempo_s', logy='true')
#plt.show()


# In[4]:

#df.groupby('Informantes').mean()

#plt.clf()
#df.groupby('Informantes').mean().plot(y='Tiempo_s', logy='true')
#plt.show()


# In[5]:

#df[df.Informantes==20].sort_values(by='Tiempo_s')
#df[df.Informantes==20].groupby('Respuestas').mean().sort_values(by='Tiempo_s')


# In[6]:

#df[df.Informantes==20].groupby('Respuestas').mean().sort_values(by='Tiempo_s').apply(lambda Tiempo_s : Tiempo_s ** 1/2)


# In[7]:

#plt.clf()
#df[df.Informantes==20].groupby('Respuestas').mean().plot(y='Tiempo_s', logy='true')
#plt.show()


# In[8]:

#plt.clf()
#df[df.Informantes==20].groupby('Respuestas').mean().apply(lambda Tiempo_s : Tiempo_s ** 1/3).plot(y='Tiempo_s')
#plt.show()


# In[9]:

#plt.clf()
#df.groupby('Respuestas').mean().plot(y='Tiempo_s')
#plt.show()


# In[10]:

df_i_p0 = pd.read_csv('resultados_p0_informantes_5_a_25_opiniones_20.csv', delimiter=',')
#plt.clf()
#df_i_p0.groupby('Informantes').mean().plot(y='Tiempo_s')
#plt.show()


# In[11]:

df_i_p1a = pd.read_csv('resultados_p1a_informantes_5_a_25_opiniones_20.csv', delimiter=',')
#plt.clf()
#df_i_p1a.groupby('Informantes').mean().plot(y='Tiempo_s')
#plt.show()


# In[12]:

df_i_p1b = pd.read_csv('resultados_p1b_informantes_5_a_25_opiniones_20.csv', delimiter=',')
#plt.clf()
#df_i_p1b.groupby('Informantes').mean().plot(y='Tiempo_s')
#plt.show()


# In[13]:

df_i_p2 = pd.read_csv('resultados_p2_informantes_5_a_25_opiniones_20.csv', delimiter=',')
#plt.clf()
#df_i_p2.groupby('Informantes').mean().plot(y='Tiempo_s')
#plt.show()


# In[14]:

data = {'Informantes' : df_i_p2.Informantes, 'Sin cotas' : df_i_p0.Tiempo_s, 'Cota A' : df_i_p1a.Tiempo_s, 'Cota B' : df_i_p1b.Tiempo_s, 'Cotas A + B' : df_i_p2.Tiempo_s}
df_i = pd.DataFrame(data)
#df_i
plt.clf()
grafico_i = df_i.groupby('Informantes').mean().plot(logy='true')
grafico_i.set_ylabel('Tiempo (log(s))')
#grafico_i.set_title('Tiempo en funcion de la cantidad de agentes')
plt.show()


# In[15]:

df_r_p0 = pd.read_csv('resultados_p0_informantes_20_opiniones_0_a_100.csv', delimiter=',')
#plt.clf()
#df_r_p0.groupby('Respuestas').mean().plot(y='Tiempo_s')
#plt.show()


# In[16]:

df_r_p1a = pd.read_csv('resultados_p1a_informantes_20_opiniones_0_a_100.csv', delimiter=',')
#plt.clf()
#df_r_p1a.groupby('Respuestas').mean().plot(y='Tiempo_s')
#plt.show()


# In[17]:

df_r_p1b = pd.read_csv('resultados_p1b_informantes_20_opiniones_0_a_100.csv', delimiter=',')
#plt.clf()
#df_r_p1b.groupby('Respuestas').mean().plot(y='Tiempo_s')
#plt.show()


# In[18]:

df_r_p2 = pd.read_csv('resultados_p2_informantes_20_opiniones_0_a_100.csv', delimiter=',')
plt.clf()
grafico_r_p2 = df_r_p2.groupby('Respuestas').mean().plot(y='Tiempo_s', legend=False)
grafico_r_p2.set_ylabel('Tiempo (s)')
#grafico_r_p2.set_title('Tiempo en funcion de la cantidad de respuestas (Cotas A + B)')
plt.show()


# In[38]:

#plt.clf()
#df_r_p2[df_r_p2.Respuestas<10].groupby('Respuestas').mean().apply(lambda Tiempo_s : Tiempo_s ** 1/2).plot(y='Tiempo_s', legend=False)
#plt.show()


# In[20]:

df_r_p2_10_20 = df_r_p2[df_r_p2.Respuestas<=25]
data_r_p2_box = {'Respuestas' : df_r_p2_10_20.Respuestas, 'Tiempo' : df_r_p2_10_20.Tiempo_s}
df_r_p2_box = pd.DataFrame(data_r_p2_box)
plt.clf()
grafico_r = df_r_p2_box.boxplot(by='Respuestas')
grafico_r.set_ylabel('Tiempo (s)')
grafico_r.set_xlabel('Respuestas')
#grafico_r.set_title('Tiempo en funcion de la cantidad de respuestas (boxplot)')
grafico_r.set_title('')
plt.suptitle('')
plt.show()
#df_r_p2_box.sort_values('Respuestas')
#df_r_p2_10_20.sort_values('Respuestas')

# In[21]:

data_r = {'Respuestas' : df_r_p2.Respuestas, 'Sin cotas' : df_r_p0.Tiempo_s, 'Cota A' : df_r_p1a.Tiempo_s, 'Cota B' : df_r_p1b.Tiempo_s, 'Cotas A + B' : df_r_p2.Tiempo_s}
df_r = pd.DataFrame(data_r)
#df_r
plt.clf()
grafico_r = df_r.groupby('Respuestas').mean().plot()
grafico_r.set_ylabel('Tiempo (s)')
#grafico_r.set_title('Tiempo en funcion de la cantidad de respuestas')
plt.show()

