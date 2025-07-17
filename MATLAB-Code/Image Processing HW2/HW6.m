fig=1;

f= fopen('lady256.bin');
lady=fread(f,[256,256],"uint8");

img=mat2gray(transpose(lady));

figure(fig); fig=fig+1;
imshow(img);

figure(fig); fig=fig+1;
imhist(img,256);

figure(fig); fig=fig+1;
J = imadjust(img,stretchlim(img),[]);
imshow(J)
figure(fig); fig=fig+1;
imhist(J,256);