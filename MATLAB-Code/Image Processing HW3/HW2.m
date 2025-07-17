fig=1;

r=5;

f= fopen('cameraB.bin');
camera1=fread(f,[256,256],"uint8");
camera=mat2gray(transpose(camera1));

f= fopen('carB.bin');
car1=fread(f,[256,256],"uint8");
car=mat2gray(transpose(car1));

f= fopen('loisB.bin');
lois1=fread(f,[256,256],"uint8");
lois=mat2gray(transpose(lois1));

f= fopen('actontownB.bin');
acton1=fread(f,[256,256],"uint8");
acton=mat2gray(transpose(acton1));

SE = strel('diamond',r);


figure(fig); fig=fig+1;
imshow(camera);

figure(fig); fig=fig+1;
imshow(imopen(camera,SE))

figure(fig); fig=fig+1;
imshow(imclose(camera,SE))

figure(fig); fig=fig+1;
imshow(car);

figure(fig); fig=fig+1;
imshow(imopen(car,SE))

figure(fig); fig=fig+1;
imshow(imclose(car,SE))

figure(fig); fig=fig+1;
imshow(lois);

figure(fig); fig=fig+1;
imshow(imopen(lois,SE))

figure(fig); fig=fig+1;
imshow(imclose(lois,SE))

figure(fig); fig=fig+1;
imshow(acton);

figure(fig); fig=fig+1;
imshow(imopen(acton,SE))

figure(fig); fig=fig+1;
imshow(imclose(acton,SE))