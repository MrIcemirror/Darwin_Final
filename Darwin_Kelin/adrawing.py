import seaborn as sns
import pandas as pd
from pandas import DataFrame as df
import matplotlib.pyplot as plt
import os

data = pd.read_csv("data0.csv")

materials = "Materials"
thickness = "Thickness"
isotopes = "Isotopes"
counts = "Counts"

material_order = set(data[materials])
material_order = sorted(list(material_order),key=str.lower)
thickness_order = set(data[thickness])
thickness_order = ["5mm","10mm","15mm","25mm","50mm","100mm","200mm","300mm"]
isotopes_order = set(data[isotopes])
isotopes_order = sorted(list(isotopes_order),key=str.lower)

os.system("mkdir figures && cd figures && mkdir material && mkdir thickness")
material_add = os.path.join(os.path.join(os.getcwd(),"figures"),"material")
thickness_add = os.path.join(os.path.join(os.getcwd(),"figures"),"thickness")
for material in material_order:
    plt.figure(figsize=(12.8,10.8),dpi=300)
    pdf = data[data[materials]==material]
    sns.barplot(pdf,x=isotopes,y=counts,hue=thickness,hue_order=thickness_order,errorbar=None)
    plt.yscale("log")
    plt.title(material)
    plt.savefig(os.path.join(material_add,material+".png"))
    plt.cla()
    
for thick in thickness_order:
    plt.figure(figsize=(12.8,10.8),dpi=300)
    pdf = data[data[thickness] == thick]
    sns.barplot(pdf,x=isotopes,y=counts,hue=materials,hue_order=material_order,errorbar=None)
    plt.yscale("log")
    plt.title(thick)
    plt.savefig(os.path.join(thickness_add,thick+".png"))
    plt.cla()
