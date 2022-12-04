# -*- coding: utf-8 -*-
"""
@author: Scottie
"""

import matplotlib.pyplot as plt
import matplotlib.image as img 
import time
import urllib.request





urllib.request.urlretrieve("https://talgovsvcp.talgov.net/TallahasseeAtmsWeb/cctvimages/video046.jpg",'image1.jpg')
urllib.request.urlretrieve("https://talgovsvcp.talgov.net/TallahasseeAtmsWeb/cctvimages/video098.jpg","image2.jpg")
urllib.request.urlretrieve("https://talgovsvcp.talgov.net/TallahasseeAtmsWeb/cctvimages/video037.jpg","image3.jpg")
urllib.request.urlretrieve("https://talgovsvcp.talgov.net/TallahasseeAtmsWeb/cctvimages/video038.jpg","image4.jpg")

img1=img.imread('image1.jpg')
img2=img.imread('image2.jpg')
img3=img.imread('image3.jpg')
img4=img.imread('image4.jpg')




plt.figure()

plt.title(time.asctime( time.localtime(time.time()) ))
plt.subplot(2, 2,1)
plt.imshow(img1)
plt.axis('off')
plt.title(time.asctime( time.localtime(time.time()) ))
plt.subplot(2, 2,2)
plt.imshow(img2)
plt.axis('off')
plt.title(time.asctime( time.localtime(time.time()) ))
plt.subplot(2, 2,3)
plt.imshow(img3)
plt.axis('off')
plt.title(time.asctime( time.localtime(time.time()) ))
plt.subplot(2, 2,4)
plt.imshow(img4)
plt.axis('off')

plt.title(time.asctime( time.localtime(time.time()) ))

plt.show()


