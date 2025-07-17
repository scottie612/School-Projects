function output=pulse_response(R,L,C,conType)
if conType=="series"
    output=(R/2)*sqrt(C/L);
    
elseif conType=="parallel"
    output=(1/(2*R))*sqrt(L/C);
    
else
    "Input Invalid";
end