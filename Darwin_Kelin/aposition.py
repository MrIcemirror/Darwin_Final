import numpy as np
import os
import matplotlib.pyplot as plt
import seaborn as sns 
from pandas import DataFrame as df
import gc
from numpy import pi

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

def xyz_set(lines):
    x = []; y =[]; z = []
    for line in lines:
        if(line.find("x = ")==-1):continue
        posi = line.replace("#","").split("||")
        x.append(float(posi[0].split("=")[-1]))
        y.append(float(posi[1].split("=")[-1]))
        z.append(float(posi[2].split("=")[-1]))
    return [x,y,z]

add = os.getcwd()
results = os.path.join(add,"results")

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
    x = []; y = []; z = []
    for file in files:
        if(file.find(write_file_name)==-1):continue
        with open(os.path.join(results,file),'r') as txt:
            lines = txt.readlines()
            [x0,y0,z0] = xyz_set(lines)
            x = x+x0
            y = y+y0
            z = z+z0
    #print(z)
    z_up = (np.abs(np.array(z)))/1000<1
    side_prob = np.sum(z_up)/4372
    
    
    bott_area = 1.05**2*pi
    side_area = 2*pi*1
    side_prob0 = side_area/(side_area+2*bott_area)
    
    print(side_prob, "||", side_prob0)
    
    fig,ax = plt.subplots(subplot_kw={"projection":"3d"})
    ax.scatter(x,y,z)
    plt.show()
    
