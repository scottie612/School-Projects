function plot2x2
    x=[0:.1:3];
    y=exp(-x).*sin(2.*pi.*x);
        
    subplot(2,2,1);
    plot(x,y);
    title('Linear Plot by Saj')
    xlabel('x')
    ylabel('y(x)')
    subplot(2,2,2);
    stairs(x,y); 
    title('Stairs Plot by Saj')
    xlabel('x')
    ylabel('y(x)')
    subplot(2,2,3);  
    stem(x,y);
    title("Stem Plot by Saj")
    xlabel('x')
    ylabel('y(x)')
    subplot(2,2,4);
    semilogx(x,y);
    title("Log/linear Plot by Saj")
    xlabel('x')
    ylabel('y(x)')