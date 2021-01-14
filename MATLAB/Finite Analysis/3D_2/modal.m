clc
clear all
syms w s

M=[0.5 0 0;0 1.0 0;0 0 1.5]
K=[3000 -1000 -1000;-1000 3000 -1000;-1000 -1000 3000]
C=[1500 0 0;0 0 0;0 0 1500]

F=K-M.*w^2
Fs=K+M.*s^2+C.*s

fs=det(Fs)
c2=sym2poly(fs);
c1=sym2poly(Fs);
r1=roots(c1);
r2=roots(c2);
solve(fs)
f=det(F);

X=trisolve(-3/4,8250,-24e6,16e9);
X=sqrt(X)
Y=zeros(3,3);
for i=1:3
    temf=subs(F,w,X(i));
    Y(:,i)=eval(eig(temf));
end
Y
r
