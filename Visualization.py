#Delaunay triangulation and convert to VRML file
import numpy as np
from scipy.spatial import Delaunay

#裏表判定(外積のz成分で)
def outer_product_z(pt1,pt2,pt3):
    v1=[pt2[0]-pt1[0],pt2[1]-pt1[1]]
    v2=[pt3[0]-pt1[0],pt3[1]-pt1[1]]
    
    return v1[0]*v2[1]-v2[0]*v1[1]
    

#ファイルの読み込み(データはリストで管理)
file_data=input("Enter the File name\n")
points=[]
with open(file_data) as f:
    lines=f.readlines()
    for line in lines:
        pnt=line.split()
        points.append([float(pnt[0]),float(pnt[1]),float(pnt[2]),int(pnt[3])])
    
#print(point)

point_delaunay=[]
for i in range(len(points)):
    point_delaunay.append([points[i][0],points[i][1]])

points_delaunay_2=np.array(point_delaunay)
tri=Delaunay(points_delaunay_2)
#print(points_delaunay_2)
#print(tri.simplices)

points_ground=[]
points_building=[]
for line in tri.simplices:
    if points[line[0]][3]==0 and points[line[1]][3]==0 and points[line[2]][3]==0:
        points_ground.append([line[0],line[1],line[2]])
    else:
        points_building.append([line[0],line[1],line[2]])
        
#print(points_ground)
#print(points_building)

#VRML
output_data=input("Enter the output file name ")
with open(output_data,'w',encoding="utf_8") as f2:
    f2.write("#VRML V2.0 utf8\n")
    
    #最初に建物から(赤)
    f2.write("Shape{\n")
    f2.write("\tappearance Appearance{\n")
    f2.write("\t\tmaterial Material{\n")
    f2.write("\t\t\tdiffuseColor 1 0 0\n")
    f2.write("\t\t}\n")
    f2.write("\t}\n")
    f2.write("\tgeometry IndexedFaceSet{\n")
    #f2.write("\t\tsolid FALSE\n")
    f2.write("\t\tcoord Coordinate{\n")
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
    f2.write("\t\tcoord Coordinate{\n")
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
    
