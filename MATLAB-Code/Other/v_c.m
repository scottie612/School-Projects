function voltage=v_c(t)

if (t<=0)
    voltage=.5;
else
    voltage=-4.1667*(exp(-t))+.6667*(exp(-5.*t))+4;
end