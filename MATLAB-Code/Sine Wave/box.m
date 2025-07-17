%% Create a box video
clear all; close all;
N=300;
I = zeros(N,N,3);
f=19;
vidObj = VideoWriter('boxes.avi'); % Prepare the new file
vidObj.FrameRate = 5;    % 3 pics per second => 12/3= 4 second movie

open(vidObj);
no=0;

for x=1:1:size(I,2)
    for y=round(-sin(x*2*pi/size(I, 2)*2)*140 + 150)
        I(sub2ind(size(I), round(y), round(x))) = 1;       
    end
    imshow(I);
    currFrame = getframe;
    writeVideo(vidObj,currFrame);
    no=no+1;
end
close(vidObj) % Close the file