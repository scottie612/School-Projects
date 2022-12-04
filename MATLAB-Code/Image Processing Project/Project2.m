close all;
clear;
clc;

fig=1;

%Load in folder with License Plate images
path=".\My Pics\P2";
files=dir(strcat(path,"\*.jpg"));
L=length(files);

%loop through images
for i=1:L
    figure(fig);fig=fig+1;
    car=imread(strcat(path,'\',files(i).name));

    %display the original
    subplot(321)
    imshow(car)
    title('Original')

    %show the grayscale green channel of the image
    cropped=car(:,:,1);
    subplot(322)
    imshow(cropped)
    title('Grayscale of green channel')

    %histogram of Gray image
    subplot(323)
    imhist(cropped)
    title("Histogram of Grayscale")

    %binarize the image
    cropped=imbinarize(cropped,.30);
    cropped=imclearborder(~cropped);
    subplot(324)
    imshow(cropped)
    title("Binarized Image")

    %find 6 largest blobs
    cropped=bwareafilt(cropped,6);
    subplot(325)
    imshow(cropped)
    title("Largest 6 blobs extracted")

    %use OCR to determine text in image
    results=ocr(cropped);
    disp(results.Text)

end