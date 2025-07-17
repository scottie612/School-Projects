fig=1;

f= fopen('Mammogram-1.bin');
suzi=fread(f,[256,256],"uint8");

img=mat2gray(transpose(suzi));




figure(fig); fig=fig+1;
imshow(img);

figure(fig); fig=fig+1;
imhist(img,256);

figure(fig); fig=fig+1;
result1=im2bw(img,.4);
imshow(result1);

figure(fig); fig=fig+1;
result2= edge(result1);
imshow(result2);