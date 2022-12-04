%HW2
%Scottie Jacobs
fig=1
SW=imread("Seaweed.png");
EC=imread("Easy Company at Berchtesgaden.png");

figure(fig)
imshow(SW);
fig=fig+1;


figure(fig)
imshow(EC);
fig=fig+1;

figure(fig)
SW=rgb2gray(SW);
imshow(SW);
fig=fig+1;

figure(fig)
EC=rgb2gray(EC);
imshow(EC);
fig=fig+1;

figure(fig)
[m,n] = size(EC);
b=double(EC);
c=de2bi(b);
c8=c(:,8);
ECB = reshape(c8,1053,1600);
imshow(ECB)
fig=fig+1;


figure(fig)
[m,n] = size(SW);
b=double(SW);
c=de2bi(b);
c8=c(:,8);
SWB = reshape(c8,4032,3024);
imshow(SWB)
fig=fig+1;