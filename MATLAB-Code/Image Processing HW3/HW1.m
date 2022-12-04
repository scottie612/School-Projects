fig=1;

f= fopen('johnny-1.bin');
johnny=fread(f,[256,256],"uint8");

img=mat2gray(transpose(johnny));

figure(fig); fig=fig+1;
imshow(img);

figure(fig); fig=fig+1;
imhist(img)

figure(fig); fig=fig+1;
histeq(img)

figure(fig); fig=fig+1;
imhist(histeq(img))