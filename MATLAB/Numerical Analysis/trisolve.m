function [x] = trisolve( a,b,c,d )
%TRISOLVE Summary of this function goes here
%   a*x^3+b*x^2+c*x+d=0's solution 
u=(9*a*b*c-27*a^2*d-2*b^3)/(54*a^3);
v=sqrt(3*(4*a*c^3-b^2*c^2-18*a*b*c*d+27*a^2*d^2+4*b^3*d))/(18*a^2);
if abs(u+v)<abs(u-v)
    m=(u-v)^(1/3);
else
    m=(u+v)^(1/3);
end
if abs(m)==0
    n=0;
else
    n=(b^2-3*a*c)/(9*a*m);
end
w=-1/2+1i*sqrt(3)/2;
x1=m+n-b/(3*a);
x2=w*m+w^2*n-b/(3*a);
x3=w^2*m+w^3*n-b/(3*a);
x=[x1 x2 x3];
end

