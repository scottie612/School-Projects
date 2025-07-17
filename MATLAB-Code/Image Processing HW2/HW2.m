fig=1;

img1=imread("First Flight at Kitty Hawk.png");
img1=rgb2gray(mat2gray(img1));
figure(fig); fig=fig+1;
imshow(img1);


im2=im2bw(img1,175/256);

figure(fig); fig=fig+1;
imshow(im2);


figure(fig); fig=fig+1;
im3=~im2;
CC = bwconncomp(im3);
numPixels = cellfun(@numel,CC.PixelIdxList);
[biggest,idx] = max(numPixels);
im3(CC.PixelIdxList{idx}) = 0;

figure(fig); fig=fig+1;
imshow(im3);

img4=im3.*img1;


for i=1:182
    for j=1:277
        if (img4(i,j)==0)
            img4(i,j)=1;
        end
    end    
end
figure(fig); fig=fig+1;
imshow(img4);
