fig=1;

f= fopen('camera9.bin');
cam9=fread(f,[256,256],"uint8");
cam9=mat2gray(transpose(cam9));

f= fopen('camera99.bin');
cam99=fread(f,[256,256],"uint8");
cam99=mat2gray(transpose(cam99));

SE = strel('square',3);

figure(fig); fig=fig+1;
imshow(cam9)

figure(fig); fig=fig+1;
imshow(cam99)


cam9open=imopen(cam9,SE);
cam99open=imopen(cam99,SE);

figure(fig); fig=fig+1;
imshow(cam9open)

figure(fig); fig=fig+1;
imshow(cam99open)

cam9close=imclose(cam9,SE);
cam99close=imclose(cam99,SE);

figure(fig); fig=fig+1;
imshow(cam9close)

figure(fig); fig=fig+1;
imshow(cam99close)

cam9med=medfilt2(cam9);
cam99med=medfilt2(cam99);

figure(fig); fig=fig+1;
imshow(cam9med)

figure(fig); fig=fig+1;
imshow(cam99med)
