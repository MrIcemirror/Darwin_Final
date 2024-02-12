import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns 

params = ['x','y','z','px','py','pz','Ek']

for param in params: locals()[param] = []

lines = open("GenTest.dat","r").readlines()

for line in lines:
    data = line.split()
    for i in range(len(params)):
        locals()[params[i]].append(float(data[i]))


sns.histplot(Ek,log_scale=True)
plt.show()