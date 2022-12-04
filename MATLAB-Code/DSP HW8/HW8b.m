f=imread("coins.png");
subplot(3,2,1);
imshow(f);
[width, height]=size(f);

noise=imnoise(f,'salt & pepper');

wrand=randi([width-1],2,1);
hrand=randi([height-1],2,1);

noise(wrand(1),:)=randi(2)-1;
noise(wrand(2),:)=randi(2)-1;
noise(:,hrand(1))=randi(2)-1;
noise(:,hrand(2))=randi(2)-1;
subplot(3,2,2);
imshow(noise);
       
medf=medfilt2(noise,[1, 5]); 
medf=medfilt2(medf,[5, 1]); 
subplot(3,2,3);
imshow(medf);

avg5filt=fspecial('average',[5 5]);
avg5=imfilter(noise,avg5filt,'replicate');
subplot(3,2,4);
imshow(avg5);


fiveby=medfilt2(noise,[5 5]);
subplot(3,2,5);
imshow(fiveby);

elevenby=medfilt2(noise,[11 11]);
subplot(3,2,6);
imshow(elevenby);
