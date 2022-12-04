function m = bisect(f, low, high, tol)
y1 = feval(f, low);
y2 = feval(f, high);
i = 0;

while (abs(high - low) >= tol)
    i = i + 1;
    m = (high + low)/2;
    y3 = feval(f, m);
    if y3 == 0
        fprintf('Root at x = %f \n\n', m);
        return
    end

    if y1 * y3 > 0
        low = m;
        y1 = y3;
    else
        high = m;
    end
end
w = feval(f, m);
fprintf('\n x = %f produces f(x) = %f \n %i iterations\n', m, y3, i-1);
fprintf(' Approximation with tolerance = %f \n', tol);