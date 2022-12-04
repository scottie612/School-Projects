function asciiGarden
    prompt="Please enter the Excell file name =";
    inp = input(prompt,'s');
    [x,y,data]= xlsread(inp);
 
    rows=size(data,1);
    totalrows=sum(cell2mat(data(:,3)));
    cols=2*totalrows;
    
    inp=strtok(inp,'.');
    outfile=fopen(strcat('ascii_',inp,'.txt'),'w');
    
    for i=1:rows
        symb=string(cell2mat(data(i,2)));
        num=cell2mat(data(i,3));
        symbsize=strlength(symb);
        for j=1:num
            for k=1:(cols/symbsize)
                 fprintf(outfile,'%s',symb);
                 
            end
           fprintf(outfile,'\n');
        end
   
    end
    fclose(outfile);

    