#Delaunay triangulation and convert to VRML file
import numpy as np
from scipy.spatial import Delaunay
from time import perf_counter_ns

start_time = perf_counter_ns()

#裏表判定(外積のz成分で)
def outer_product_z(pt1,pt2,pt3):
    v1=[pt2[0]-pt1[0],pt2[1]-pt1[1]]
    v2=[pt3[0]-pt1[0],pt3[1]-pt1[1]]
    
    return v1[0]*v2[1]-v2[0]*v1[1]
    

#ファイルの読み込み(データはリストで管理)
file_data="53394640_dsm_1m_removed.dat"
points=[]
with open(file_data) as f:
    lines=f.readlines()
    for line in lines:
        pnt=line.split()
        points.append([float(pnt[0]),float(pnt[1]),float(pnt[2]),int(pnt[3])])
    
#外側に点を追加(判定は地面判定)
for i in range(929):
    points.append([float(-7541),float(-33280+i),float(-0.5),int(0)])
    points.append([float(-6406),float(-33280+i),float(-0.5),int(0)])

for i in range(1,1135):
    points.append([float(-7541+i),float(-32352),float(-0.5),int(0)])
    points.append([float(-7541+i),float(-33280),float(-0.5),int(0)])

#三角形分割
point_delaunay=[]
l = len(points)
for i in range(l):
    point_delaunay.append([points[i][0],points[i][1]])

points_delaunay_2=np.array(point_delaunay)
tri=Delaunay(points_delaunay_2)


points_ground=[]
points_building=[]
for line in tri.simplices:
    if points[line[0]][3]==0 and points[line[1]][3]==0 and points[line[2]][3]==0:
        points_ground.append([line[0],line[1],line[2]])
    else:
        points_building.append([line[0],line[1],line[2]])
    
for point in points:
    point[1]=-point[1]
    
#VRML
output_data=input('Enter the output file name : ')
with open(output_data,'w',encoding="utf_8") as f2:
    f2.write("#VRML V2.0 utf8\n")
    f2.write("DEF FUJIKURA Transform{ #Sei\n")
    f2.write("\ttranslation -7085 11 32800\n")
    f2.write("\tscale 25 25 25\n")
    f2.write("\trotation 0 1 0 3.14\n")
    f2.write("\tchildren [Inline{url \"ImageToStl.com_1201.wrl\"}]\n")
    f2.write("}\n")
    f2.write("Transform{ #Ryuki\n")
    f2.write("\ttranslation -7330 23 32695\n")
    f2.write("\tscale 25 25 25\n")
    f2.write("\trotation 0 1 0 1.55\n")
    f2.write("\tchildren [Inline{url \"ImageToStl.com_1202.wrl\"}]\n")
    f2.write("}\n")
    f2.write("Transform{ #Ryouta\n")
    f2.write("\ttranslation -7070 65 33000 # 東京ドーム\n")
    f2.write("\tscale 25 25 25\n")
    f2.write("\trotation 0 1 1 3.14\n")
    f2.write("\tchildren [Inline{url \"ImageToStl.com_1203.wrl\"}]\n")
    f2.write("}\n")
    f2.write("Transform{ #Takumi\n")
    f2.write("\ttranslation -7120 8 32865\n")
    f2.write("\tscale 25 25 25\n")
    f2.write("\trotation 0 1 0 3.14\n")
    f2.write("\tchildren [Inline{url \"ImageToStl.com_1204.wrl\"}]\n")
    f2.write("}\n")
    f2.write("DEF TAGUCHI Transform{ #Ryouichiro\n")
    f2.write("\ttranslation -6778.00 8 33280.31\n")
    f2.write("\tscale 25 25 25\n")
    f2.write("\trotation 0 1 -0.4 3.45\n")
    f2.write("\tchildren [Inline{url \"ImageToStl.com_1205.wrl\"}]\n")
    f2.write("}\n")
    f2.write("DEF TIMER1 TimeSensor {\n")
    f2.write("\tcycleInterval 5\n")
    f2.write("\tloop TRUE\n")
    f2.write("}\n")
    f2.write("DEF TIMER2 TimeSensor {\n")
    f2.write("\tcycleInterval 10\n")
    f2.write("\tloop TRUE\n")
    f2.write("}\n")
    f2.write("DEF PI1 PositionInterpolator {\n")
    f2.write("\tkey [0.0 1.0]\n")
    f2.write("\tkeyValue [\n")
    f2.write("\t\t-6778.00 8 33280.31,\n")
    f2.write("\t\t-6986 8 32390,\n")
    f2.write("\t]\n")
    f2.write("}\n")
    f2.write("DEF PI2 PositionInterpolator {\n")
    f2.write("\tkey [0.0 0.4 1.0]\n")
    f2.write("\tkeyValue [\n")
    f2.write("\t\t-7085 11 32800,\n")
    f2.write("\t\t-7085 11 32700,\n")
    f2.write("\t\t-7285 22 32695\n")
    f2.write("\t]\n")
    f2.write("}\n")
    f2.write("DEF OI OrientationInterpolator {\n")
    f2.write("\tkey [0.0 0.385 0.415 1.0]\n")
    f2.write("\tkeyValue [\n")
    f2.write("\t\t0 1 0 3.14,\n")
    f2.write("\t\t0 1 0 3.14,\n")
    f2.write("\t\t0 1 0 4.71,\n")
    f2.write("\t\t0 1 0 4.71,\n")
    f2.write("\t]\n")
    f2.write("}\n")
    f2.write("ROUTE TIMER1.fraction_changed TO PI1.set_fraction\n")
    f2.write("ROUTE PI1.value_changed TO TAGUCHI.set_translation\n")
    f2.write("ROUTE TIMER2.fraction_changed TO PI2.set_fraction\n")
    f2.write("ROUTE PI2.value_changed TO FUJIKURA.set_translation\n")
    f2.write("ROUTE TIMER2.fraction_changed TO OI.set_fraction\n")
    f2.write("ROUTE OI.value_changed TO FUJIKURA.set_rotation\n")
    f2.write("Viewpoint{\n")
    f2.write("\tposition -6984.23 1220.36 35000.31\n")
    f2.write("}\n")
    
    #最初に建物から(赤)
    f2.write("Shape{\n")
    f2.write("\tappearance Appearance{\n")
    f2.write("\t\tmaterial Material{\n")
    f2.write("\t\t\tdiffuseColor 1 0 0\n")
    f2.write("\t\t}\n")
    f2.write("\t}\n")
    f2.write("\tgeometry IndexedFaceSet{\n")
    #f2.write("\t\tsolid FALSE\n")
    f2.write("\t\tcoord DEF Coord Coordinate{\n")
    f2.write("\t\t\tpoint[\n")
    for point1 in points:
        point1=list(map(str,point1))
        f2.write("\t\t\t\t")
        f2.write(point1[0])
        f2.write(" ")
        f2.write(point1[2])
        f2.write(" ")
        f2.write(point1[1])
        f2.write(",\n")
        
    f2.write("\t\t\t]\n")
    f2.write("\t\t}\n")
    f2.write("\t\t\tcoordIndex[\n")
    for point2 in points_building:
        point2=list(map(str,point2))
        f2.write("\t\t\t\t")
        f2.write(point2[0])
        f2.write(",")
        if outer_product_z(points[int(point2[0])],points[int(point2[1])],points[int(point2[2])])>0:
            f2.write(point2[2])
            f2.write(",")
            f2.write(point2[1])
            f2.write(",-1\n")
        else:
            f2.write(point2[1])
            f2.write(",")
            f2.write(point2[2])
            f2.write(",-1\n")
    f2.write("\t\t\t\t]\n")
    
    f2.write("\t}\n")
    f2.write("}\n")
    
    #次に地面を(緑)
    f2.write("Shape{\n")
    f2.write("\tappearance Appearance{\n")
    f2.write("\t\tmaterial Material{\n")
    f2.write("\t\t\tdiffuseColor 0 1 0\n")
    f2.write("\t\t}\n")
    f2.write("\t}\n")
    f2.write("\tgeometry IndexedFaceSet{\n")
    #f2.write("\t\tsolid FALSE\n")
    f2.write("\t\tcoord USE Coord\n")
    f2.write("\t\t\tcoordIndex[\n")
    for point2 in points_ground:
        point2=list(map(str,point2))
        f2.write("\t\t\t\t")
        f2.write(point2[0])
        f2.write(",")
        if outer_product_z(points[int(point2[0])],points[int(point2[1])],points[int(point2[2])])>0:
            f2.write(point2[2])
            f2.write(",")
            f2.write(point2[1])
            f2.write(",-1\n")
        else:
            f2.write(point2[1])
            f2.write(",")
            f2.write(point2[2])
            f2.write(",-1\n")
    f2.write("\t\t\t\t]\n")
    f2.write("\t}\n")
    f2.write("}\n")
    
    #最後に3D出力用の土台を
    f2.write("Shape{\n")
    f2.write("\tappearance Appearance{\n")
    f2.write("\t\tmaterial Material{\n")
    f2.write("\t\t\tdiffuseColor 0 1 0\n")
    f2.write("\t\t}\n")
    f2.write("\t}\n")
    f2.write("\tgeometry IndexedFaceSet{\n")
    f2.write("\t\tcoord Coordinate{\n")
    f2.write("\t\t\tpoint[\n")
    f2.write("\t\t\t\t-7541 -0.5 33280,\n")
    f2.write("\t\t\t\t-7541 -0.5 32352,\n")
    f2.write("\t\t\t\t-6406 -0.5 32352,\n")
    f2.write("\t\t\t\t-6406 -0.5 33280,\n")
    f2.write("\t\t\t\t-7541 -5.5 33280,\n")
    f2.write("\t\t\t\t-7541 -5.5 32352,\n")
    f2.write("\t\t\t\t-6406 -5.5 32352,\n")
    f2.write("\t\t\t\t-6406 -5.5 33280,\n")
    f2.write("\t\t\t]\n")
    f2.write("\t\t}\n")
    f2.write("\t\t\tcoordIndex[\n")
    f2.write("\t\t\t\t0,1,5,4,-1\n")
    f2.write("\t\t\t\t1,2,6,5,-1\n")
    f2.write("\t\t\t\t2,3,7,6,-1\n")
    f2.write("\t\t\t\t3,0,4,7,-1\n")
    f2.write("\t\t\t\t4,5,6,7,-1\n")
    f2.write("\t\t\t]\n")
    f2.write("\t}\n")
    f2.write("}\n")

end_time = perf_counter_ns()

print('visualization.py:', end_time - start_time, 'nanoseconds')
