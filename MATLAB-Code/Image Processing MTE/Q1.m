fig=1;


clean= imread('Shells clean.png');
figure(fig);fig=fig+1;
imshow(clean)
clean=rgb2gray(clean);


figure(fig);
imshow(clean)

SE=strel('diamond',2);

clean=imbinarize(clean,160/255);
figure(fig); fig=fig+1;
imshow(clean)

clean=imclose(clean,SE);
figure(fig); fig=fig+1;
imshow(clean)

SE=strel('diamond',33);

clean=imopen(clean,SE);
figure(fig); fig=fig+1;
imshow(clean)

clean=~imclearborder(~clean);
clean = ~bwareafilt(~clean, 4,'largest');
figure(fig); fig=fig+1;
imshow(clean)


