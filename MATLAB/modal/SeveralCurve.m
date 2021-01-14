t= linspace(0,30,10000);
x=zeros(1,10000);
a0=5;
m=8;
k=m*1^2;
fs=0.5/9.8;
stoppos = 0;
Wn =sqrt(k/m);
flag =1;
r = fs*9.8;
for ii =1:10
    x(ii)=kulunfun(a0,m,k,fs,0,t(ii));
end
stoPos = 0;
for e = 11:10000
    x(e)=kulunfun(a0,m,k,fs,0,t(e));
    if abs(x(e)-x(e-1)/x(e))<10e-5
        stoPos = e;
        break;
    end
end
disp(stoPos)
for p =e+1:10000
    x(p)=x(stoPos);
end
y=zeros(1,10000)+r;
plot(t,x,'LineWidth',1.5)
hold on
axis tight
axisx = linspace(0,3*pi,10000);
plot(axisx,zeros(1,10000),'k')
plot(t,y,'k--','LineWidth',1)
plot(t,-y,'k--','LineWidth',1)