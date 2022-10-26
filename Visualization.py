#Delaunay triangulation and convert to VRML file
import numpy as np
from scipy.spatial import Delaunay

#ファイルの読み込み(データはリストで管理)
file_data=input("Enter the File name\n")
point=[]
with open(file_data) as f:
    lines=f.readlines()
    for line in lines:
        pnt=line.split()
        point.append([float(pnt[0]),float(pnt[1]),float(pnt[2]),int(pnt[3])])
    
#print(point)

point_delaunay=[]
for i in range(len(point)):
    point_delaunay.append([point[i][0],point[i][1]])

point_delaunay_2=np.array(point_delaunay)
tri=Delaunay(point_delaunay_2)
#print(point_delaunay_2)
print(tri.simplices)
