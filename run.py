import os
import numpy as np
from datetime import datetime
import time
ddn = time.perf_counter
os.system("mkdir results")

years = 5


#------------------------------change Years-------------------------

os.system("python params.py")
param_names = ["shielding_material","shielding_thickness","gen_radius","gen_z","test_number","file_output","info_string"]
change_names = []
for param_name in param_names:
    change_names.append(param_name+"_python")

rest = 0
finish_time = 0
time0 = 360
cc = 0

with open("Darwin_PS.txt",'r') as run_text:
    origin_lines = run_text.readlines()
    with open("params.dat",'r') as param_txt:
        param_lines = param_txt.readlines()
        rest = (len(param_lines)-1)*years
        for param_line in param_lines:
            if(param_line.find("+++")!=-1):continue
            elif(param_names=="" or param_names=="\n"):continue
            else:pass
            
            [shielding_material, shielding_thickness, gen_radius, gen_z,test_number] = param_line.split(",")
            
            file_output = "\"../results/%s_%s.dat\"" %(shielding_material.replace("\"",""),shielding_thickness.split(".")[0])
            
            for i in range(years):
                start = ddn()
                rest_time = rest*time0
                rest_hour = int(rest_time/3600)
                rest_mins = int((rest_time-rest_hour*3600)/60)
                rest_secs = rest_time-rest_hour*3600-rest_mins*60
                
                finish_hour = int(finish_time/3600)
                finish_mins = int((finish_time-finish_hour*3600)/60)
                finish_secs = finish_time-finish_hour*3600-finish_mins*60
                
                info_string = ("\""+
                               "Processing Running....." + r"\n"+
                               "Total Simulated Time is %d Years" % years + r"\n"+
                               "Currently Running %s %s in the %d Years"%(shielding_material.replace("\"",""),shielding_thickness,i+1)+ r"\n"+
                               "Present Time Cost is %02d:%02d:%02d" % (finish_hour,finish_mins,finish_secs) + r"\n"+
                               "Estimated Remaining Time is %02d:%02d:%02d" % (rest_hour,rest_mins,rest_secs) + r"\n"+
                               "\"")
                with open("Darwin_PS.cc",'w') as cc_file:
                    for origin_line in origin_lines:
                        for j in range(len(change_names)):
                            origin_line = origin_line.replace(change_names[j],locals()[param_names[j]])
                        cc_file.write(origin_line)
                os.system("cd build && make && ./Darwin_PS")
                #else:os.system("cd build && ./Darwin_PS")
                end = ddn()
                time0 = end-start
                finish_time = finish_time+time0
                cc = cc+1
                time0 = finish_time/cc
                rest = rest-1
print("\n\n--------------================== Finished ==================--------------\n\n")

        
    
