% Scottie Jacobs
% Project 3
%4/20/2021
clc;
close all;
clear;

figure();
N=420;
I = zeros(N,N,3);
vidObj = VideoWriter('lilac1.avi'); % Prepare the new file
vidObj.FrameRate = 40;

open(vidObj);
for z=1:420
    for w=1:420
        I(z,w,:)=[190,190,190]/255;
    end
end
for i=-10:10
    I(210+i,210,:)=[0,0,0];
    I(210,210+i,:)=[0,0,0];
    
end
i=0;
z=0;
for i=1:40
    for k=0:11
        for z=1:5
            for x=-25:25
                for y=-25:25
                    if x^2 +y^2 <25^2
                        for u=0:11
                            rvar=randi([0 20],1,1);
                            r=2*sqrt(x^2+y^2);
                            I(round(165*sin(u*2*pi/12)+210+x),round(165*cos(u*2*pi /12)+210+y),:)=  [225-r+rvar,150+r-rvar,225-r+rvar]/255;
                        end
                        I(round(165*sin(k*2*pi/12)+210+x),round(165*cos(k*2*pi /12)+210+y),:)= [190,190,190]/255;
                        
                    end
                    
                end
            end
        imshow(I);
        currFrame=getframe;
        writeVideo(vidObj,currFrame);
        end

    end
end

close(vidObj);
