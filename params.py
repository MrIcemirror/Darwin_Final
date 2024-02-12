from numpy import pi

materials = ["Air","Water","BoratedPolyethylene","Polyethylene"]
thickness = [10,25,50,100,200,300]


year = 86400*365.25
flux = 1e-6*year/(0.01**2)

height = 1.01
radius = 0.35
circle = pi*radius**2
side = 2*pi*radius*2*height
area = 2*circle+side

test_number = int(area*flux*1)

air = False

with open("params.dat","w") as txt:
    txt.write("+++ shielding_material, thickness, gen_radius, gen_z test_number +++\n")
    for material in materials:
        for thick in thickness:
            if(air and material=="Air"):continue
            if(material=="Air"):air=True
            line = ""
            line = line+"\"%s\""%material+","
            line = line+"%d.*mm"%thick+","
            line = line+"%.2f*m"%radius+","
            line = line+"%.2f*m"%height+","
            line = line+"%d\n"%test_number
            txt.write(line)


