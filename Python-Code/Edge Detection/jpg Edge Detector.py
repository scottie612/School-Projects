# -*- coding: utf-8 -*-
"""
Spyder Editor
 
This is a temporary script file.
"""
 
 
import cv2
 
path="C:\\Users\\Scottie\\.spyder-py3\\Not Mif.jpg"
img = cv2.imread(path,0)
 
cv2.imshow("temp2",img)

res=(320,480)
res2=(640,480)
 
image1 = cv2.resize(img,res)
image2 = cv2.Canny(image1,100,150)
image2 = cv2.resize(image2,res)


final = cv2.hconcat([image1 ,image2]);
final = cv2.resize(final,res2)
 
cv2.imwrite("C:\\Users\\Scottie\\.spyder-py3\\Mif.jpg",final)

rows,cols=final.shape
file= open("MeOnEdge.mif", 'w')
file.write("depth= 307200;\n")
file.write("width= 8;\n")
file.write("address_radix = dec;\n")
file.write("data_radix = dec;\n")
file.write("content\n")
file.write("begin\n")
index=0
 
for i in range(rows):
    for j in range(cols):
        pixel= final[i,j]
        file.write(str(index)+":"+ str(pixel) +";\n") 
        index += 1
 
 
file.write("end\n")
file.close()
