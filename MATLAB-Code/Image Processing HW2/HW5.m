fig=1;

f= fopen('actontBin-1.bin');
acton=fread(f,[256,256],"uint8");

img=mat2gray(transpose(acton));

figure(fig); fig=fig+1;
imshow(img);

T=imread("T.png");
figure(fig); fig=fig+1;
imshow(T);
T=rgb2gray(T);


