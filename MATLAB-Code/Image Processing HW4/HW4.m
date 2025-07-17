%Scottie Jacobs HW 4
%Digital Image Processing
%3/7/2022

fig=1;
I=meshgrid(0:7,0:7);
J=meshgrid(0:7,0:7);
u=1.5;
v=1.5;
image1=cos((2*pi/8)*(u*I + v*J));

r1=real(image1)
im1=imag(image1)

figure(fig); fig=fig+1;
r1=imresize(r1,8);
imshow(r1,[]);

figure(fig); fig=fig+1;
im1=imresize(im1,8);
imshow(im1,[]);


fr1=fft2(image1);
fr1=log(1+abs(fr1));
fr1 = fftshift(fr1);

real(fr1)
imag(fr1)

figure(fig); fig=fig+1;
fr1=imresize(fr1,8);
imshow(fr1,[]);










