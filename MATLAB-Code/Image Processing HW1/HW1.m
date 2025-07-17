%HW 1 Scottie Jacobs

%Question 1
X=1;

johnny= fopen("johnny.bin");
a=fread(johnny,[256,256],"uint8");
bwjohnny =mat2gray(transpose(a));
figure(X)
imshow(bwjohnny);
X=X+1;

mandril= fopen("mandril.bin");
c=fread(mandril,[256,256],"uint8");
bwmandril =mat2gray(transpose(c));
figure(X)
imshow(bwmandril);
X=X+1;


j=[a(:,129:256),c(:,1:128)];
half=mat2gray(transpose(j));
figure(X)
imshow(half);
X=X+1;



figure(X)
imhist(bwjohnny,256)
X=X+1;

figure(X)
im2bw(bwjohnny,190/255);
X=X+1;



