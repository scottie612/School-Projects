fig=1;

clean= imread('Shells messy.png');
figure(fig); fig=fig+1;
imshow(clean)
clean=rgb2gray(clean);

figure(fig);
imshow(clean)

SE=strel('diamond',3);

clean=imbinarize(clean,170/255);
figure(fig); fig=fig+1;
imshow(clean)

clean=imclose(clean,SE);
figure(fig); fig=fig+1;
imshow(clean)

SE=strel('diamond',26);

clean=imopen(clean,SE);
figure(fig); fig=fig+1;
imshow(clean)

clean=~imclearborder(~clean);
clean = ~bwareafilt(~clean, 3,'largest');
figure(fig); fig=fig+1;
imshow(clean)
 
