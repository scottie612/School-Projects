figure()
N=256;
I = zeros(N,N,3);
f=19;

for x=-20:20    %% Draw some filled color circles
    for y=-20:20
        if x^2 + y^2 < 20^2
           
            I(75+y, 50+x,:)=[255,0,255];       
             
            
        end
    end
end


imshow(I);
title('HW6b by Scottie Jacobs');

text(50 , 75 , 'SAJ', 'HorizontalAlignment','center')
text(100, 75 , 'SAJ', 'HorizontalAlignment','center')
text(150, 75 , 'SAJ', 'HorizontalAlignment','center')
text(50 , 125, 'SAJ', 'HorizontalAlignment','center')
text(100, 125, 'SAJ', 'HorizontalAlignment','center')
text(150, 125, 'SAJ', 'HorizontalAlignment','center')
text(50 , 175 , 'SAJ', 'HorizontalAlignment','center')
text(100, 175 , 'SAJ', 'HorizontalAlignment','center')
text(150, 175 , 'SAJ', 'HorizontalAlignment','center')
