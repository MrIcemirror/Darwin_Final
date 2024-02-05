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

save_path = os.path.join(results,"Activation")

for write_file_name in file_set:
    with open(os.path.join(save_path,write_file_name+".dat"),"w") as write_file:
        for file in files:
            if(file.find(write_file_name)==-1):continue
            with open(os.path.join(results,file),'r') as txt:
                lines = txt.readlines()
                [start,end] = useful(lines)
              #  print(start)
                #os.system("pause")
                for i in range(len(start)):
                    for j in range(start[i],end[i]+1):
                        write_file.write(lines[j])
                
            del start,end,lines
            gc.collect()


xenon0 = "Xe"
acti = os.path.join(results,"Activation")
column_names = ["Materials","Thickness","Isotopes","Counts"]
#for i in range(124,138): column_names.append("%s%d"%(xenon0,i))
for root,dirs,files in os.walk(acti):break


dataf = df(columns= column_names)

for file in files:
    Eks = []
    xenon_count = {}
    
    for i in range(124,138):
        xenon_count["Xe%d"%i] = 0
   #print(xenon_count)
    [material,thickness] = file.split(".")[0].split("_")
    
    with open(os.path.join(acti,file)) as txt:
        lines = txt.readlines()
        [start,end] = useful(lines)
        
        for i in range(len(start)):
            for j in range(start[i],end[i]+1):
                line = lines[j]
                if(j==start[i] or j==end[i]):continue
                elif(j==start[i]+1):

                    line = line.replace("#","")
                    Eks.append(float(line.split("=")[1]))
                else:
                    pri = line.split()[2]
                    if(pri.find("Xe")!=-1):continue
                    xenon = line.split()[7][0:5]
                    #if(pri[0:5]==xenon[0:5]):continue
                    try:xenon_count[xenon] = xenon_count[xenon]+1
                    except:
                        print(file)
                        raise ValueError("Other Isotope Exists: ", xenon)
        for xenon,count in xenon_count.items():
            if(material=="Air"):continue
            line = [material,thickness,xenon,count]  
            
            dataf.loc[len(dataf)] = line
dataf.to_csv("data0.csv")               
    
