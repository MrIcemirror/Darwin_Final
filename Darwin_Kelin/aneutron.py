import numpy as np
import os
import matplotlib.pyplot as plt
import seaborn as sns 
from pandas import DataFrame as df
import gc

def useful(lines):
    start = []; end = []
    for i in range(len(lines)):
        line = lines[i]
        #if(line.find("Xe")!=-1):raise ValueError("XE!!!!")
        if(line.find("START")!=-1):start.append(i)
        elif(line.find("END")!=-1):end.append(i)
        else:pass
    start = np.sort(start)
    end = np.sort(end)
    #print(start)
    diff = end-start
    #print(diff)
    start = start[diff!=2]
  #  print(start)
    end = end[diff!=2]
    return [start,end]

def Ek_set(lines):
    Ek = []
    for line in lines:
        if(line.find("Ek")==-1):continue
        Ek.append(float(line.replace("#","").split("=")[-1]))
    return Ek

add = os.getcwd()
results = os.path.join(add,"results_other")

for root,dirs,files in os.walk(results):break
os.system("cd results && mkdir Activation")
file_set = set()
for file in files:
    if(file.find(".txt")==-1):continue
    file0 = file.split("_")
    file_set.add(file0[1]+"_"+file0[2])
print(file_set)

os.system("cd figures && mkdir neutrons")

for write_file_name in file_set:
    Ek = []
    for file in files:
        if(file.find(write_file_name)==-1):continue
        with open(os.path.join(results,file),'r') as txt:
            lines = txt.readlines()
            Ek = Ek+Ek_set(lines)
            break
    plt.figure(figsize=(12.8,10.8),dpi=300)
    sns.histplot(np.array(Ek)*1000)
    plt.xlabel("Ek/keV")
    plt.ylabel("Counts")
    plt.title(write_file_name)
    plt.xscale("log")
    plt.yscale("log")
    plt.show()
    plt.savefig(os.path.join(os.path.join(os.path.join(os.getcwd(),"figures"),"neutrons"),write_file_name+'.png'))
    plt.cla()
    del Ek
    gc.collect()
