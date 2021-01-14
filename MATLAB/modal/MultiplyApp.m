t= linspace(0,3*pi,10000);
x=zeros(1,10000);
m=5;
k=m*8;
for v=-4:1:4
    t= linspace(0,3*pi,10000);
    x=zeros(1,10000);
    m=4;
    k=32;
    fs=0.15;
    for e = 1:10000
        x(e)=kulunfun(m,k,v,t(e));
    end
    plot(t,x,'LineWidth',1.5)
    hold on
end