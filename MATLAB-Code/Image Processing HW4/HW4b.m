fig=1;

f= fopen('lena.bin');
I=fread(f,[256,256],"uint8");
I=mat2gray(transpose(I));


%J=imfilter(I,fspecial("average",7),'circular');
%figure(fig); fig=fig+1;
%imshow(J)

I1=fft2(I);

I1 = fftshift(I1);


B=(1/49)*ones(7);
K=zeros(256);
K(1:3,1:3)=1;
K=fft2(K);
K=log(1+abs(K));
K = fftshift(K);
figure(fig); fig=fig+1;
imshow(K)
J=I1.*K;
figure(fig); fig=fig+1;
imshow(J)

J2=ifft2(J);
J2=log(1+abs(J2));
figure(fig); fig=fig+1;
imshow(J2,[])


