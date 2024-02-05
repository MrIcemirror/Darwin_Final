import os
import time
from numpy import pi

year = 86400*365.25
flux = 1e-6*year/(0.01**2)

string = "world_length,p_type,shielding_material,shielding_thickness,gen_radius,gen_z,test_number,sphere,file_output"
datanames = string.split(",")

for i in range(len(datanames)):
    datanames[i] = datanames[i]+"_python"
    
params = open("params.dat","r").readlines()
txt_file = open("Darwin_shielding_main.txt","r").readlines()
os.system("mkdir results")

for i in range(len(params)):
    param = params[i]
    if(param.find(r"//")!=-1):continue
    elif(param=="" or param=="/n"):continue
    elif(param.find("###")!=-1):break
    param = param.split(",")
    #print(param)
    for j in range(len(param)):
        locals()[datanames[j]] = param[j]
    #print(world_length_python)
    try:float(test_number_python)
    except:test_number_python = float(test_number_python.replace("y",""))
    else:pass
    
    gen_radius = float(gen_radius_python.split("*")[0])
    test_number_python = str(int(4*gen_radius**2*pi*flux))
    print(test_number_python)
    
    for j in range(1):
        cc_file = open("Darwin_shielding_main.cc","w")
        t = time.strftime("%Y-%m-%d %H:%M:%S", time.localtime()) 
        
        #print(world_length_python)
        file_name = "Activation_%s_%s_%s_%s.txt" % (shielding_material_python.replace("\"",""),
                                                    shielding_thickness_python.replace(".*","").replace("*",""),
                                                    test_number_python,
                                                    t)
        file_output_python = "\"../results/%s\""%file_name  
        for line in txt_file:
            for dataname in datanames:
                if(line.find(dataname)!=-1):line = line.replace(dataname,locals()[dataname])
            cc_file.write(line)
        cc_file.close()
        os.system("rm -rf build && mkdir build && cd build && cmake .. && make && ./Darwin_shielding_main ")
        
