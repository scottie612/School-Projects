function fourEverAlone(img)
    a=imread(img);
    b=flip(a,2);
    c=rgb2gray(a);
    d=255-a;
    e(:,:,1)=a(:,:,2);
    e(:,:,2)=a(:,:,1);
    e(:,:,3)=a(:,:,3);
    
   
   
    out=imtile({d b c e},'Frames',1:4,'GridSize',[2 2]);
    img=strtok(img,'.');
    imwrite(out,strcat(img,'_Alone.png'))
    
    
    
    
   