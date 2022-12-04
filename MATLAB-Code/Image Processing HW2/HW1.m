fig=1;

f= fopen('Suzi1-1.bin');
suzi=fread(f,[256,256],"uint8");

img=mat2gray(transpose(suzi));




figure(fig); fig=fig+1;
imshow(img);

figure(fig); fig=fig+1;
imhist(img,256);

figure(fig); fig=fig+1;
x=im2bw(img,.6)



figure(fig); fig=fig+1;
suzi1=x*suzi;
img=mat2gray(transpose(suzi));
imshow(img)


