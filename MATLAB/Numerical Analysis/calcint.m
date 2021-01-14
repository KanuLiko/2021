syms x l
x0=linspace(0,2.5,100);
f=2/3*asin(sqrt(2.5^2-(2.5-x)^2)/6);
y0 = eval(subs(f,x,x0));
plot(x0,y0)