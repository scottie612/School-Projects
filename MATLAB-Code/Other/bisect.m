function root = bisect(fun, xL, xU, tol)
y1 = feval(fun, xL);
i = 0;
while (abs(xU - xL) >= tol)
    i = i + 1;
    root = (xU + xL)/2;
    y3 = feval(fun, root);
    if y3 == 0
        fprintf('Root = %f \n', root);
        return
    end

    if y1 * y3 > 0
        xL = root;
        y1 = y3;
    else
        xU = root;
    end
end
fprintf('\n Root = %f', root);
fprintf('\n Error = %f',(abs(xU - xL)));
fprintf('\n Iterations = %f \n', i-1);