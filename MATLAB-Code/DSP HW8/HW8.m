
fig=1;

width=16;
height=16;
I=zeros(width,height);

%%% MAKES I
for w = 1:(width)
    for h=1:(height)
        if( w<=7+1 && h <=7+1) % +1 cause no index 0
            I(w,h)=100;
        else
            I(w,h)=200;
        end
    end
end
figure(fig);fig=fig+1;
imshow(I,[0,255]);


%%% MAKING MASK
Mx=[-1 0 1; -1 0 1; -1 0 1;];
My=[-1, -1, -1; 0, 0, 0; 1, 1, 1;];


%%% APPLY MASK AND SHOW
Gx=imfilter(I,Mx,'replicate');
figure(fig);fig=fig+1;
imshow(Gx,[0,255]);


Gy=imfilter(I,My,'replicate');
figure(fig);fig=fig+1;
imshow(Gy,[0,255]);

G=sqrt((Gx.^2)+(Gy.^2));
figure(fig);fig=fig+1;
imshow(G,[0,255]);