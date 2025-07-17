

moon= imread('Moon at night.png');
figure, imshow(moon)

moong=rgb2gray(moon);
figure, imshow(moong)

moong=wiener2(moong,[15 15]);
figure, imshow(moong)


red = moon(:,:,1);
green = moon(:,:,2);
blue = moon(:,:,3);

redW=wiener2(red,[15 15]);
greenW=wiener2(green,[15 15]);
blueW=wiener2(blue,[15 15]);

moon2=cat(3,redW,greenW,blueW);
figure, imshow(moon2)