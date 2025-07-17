close all;
clear;
clc;
fig=1;
%Load in folder with License Plate images

path=".\My Pics\Jeep";
files=dir(strcat(path,"\*.jpg"));
L=length(files);

%loop through images
for i=1:L
    figure(fig);fig=fig+1;
    car=imrotate(imread(strcat(path,'\',files(i).name)),-90);

    %Import and Display original Image
    subplot(331)
    imshow(car)

    %Convert to grayscale and display image
    cargray=rgb2gray(car);
    subplot(332)
    imshow(cargray)

    %Find edges in grayscale image
    edges=edge(cargray);
    subplot(333)
    imshow(edges)

    %Takes the edge picture and finds the largest enclosed region and crops the imgage
    edges=bwareafilt(edges,1);
    box=regionprops(edges,"BoundingBox","Area","Orientation");
    BB = box.BoundingBox;
    cropped=imcrop(car,[BB(1),BB(2),BB(3),BB(4)]);
    subplot(334)
    imshow(cropped)

    %Extract the Green from the image.
    cropped=cropped(:,:,1);
    subplot(335)
    imshow(cropped)

    %Displays Historgram of the Image
    subplot(336)
    imhist(cropped)

    %Binarize the Image with threshhold 30%
    cropped=imbinarize(cropped,.30);
    cropped=imclearborder(~cropped);
    subplot(337)
    imshow(cropped)

    %Find the 6 Largest blobs
    cropped=bwareafilt(cropped,6);
    subplot(338)
    imshow(cropped)
    
    %fix for rotational skew and dilate
    allOrientations = [box.Orientation];
    angleToRotate = -allOrientations(1);
    cropped = imrotate(cropped, angleToRotate);
    [r,c]=size(cropped);
    cropped=imresize(cropped,[r,1.25*c]);
    cropped=imclose(cropped,ones(2));
    subplot(339)
    imshow(cropped)
    
    %Perform OCR
    results=ocr(cropped);
    disp(results.Text);
end









