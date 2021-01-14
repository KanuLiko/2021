function f = adaptfun(x,y)
E = [40*cos(x) 40*sin(x)];
F =[100-2*cos(y) 2*sin(y)];
D =[0 100];
C =[100 100];
f=sqrt(sum((E-D).^2))+sqrt(sum((E-C).^2))+sqrt(sum((E-F).^2));
end

