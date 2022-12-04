
moss= imread('Moss on sand.png');
moss=rgb2gray(mat2gray(moss));



mosslabel =moss <130/255; % extracting moss

%mosslabel=bwareaopen(mosslabel,5000);


moss2=moss.*double(mosslabel); % using mask



[row,column]=size(moss2);
for i=1:row
    for j=1:column
        if (moss2(i,j)==0)
            moss2(i,j)=1;
       
        end
    end
end

figure,imshow(moss2)
