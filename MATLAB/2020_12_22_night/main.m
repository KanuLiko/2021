a0 = 5;
m =2 ;
k = 2*pi^2;
fs = 0.025;
x00 = 0;
r=fs*10;
Wn=sqrt(k/m);
subplot(2,2,1)
plot(linspace(0,a0/(2*r)*pi/Wn,1000),fraction(a0,m,k,fs,x00))
hold on
xlabel('Time','fontname','Times New Roman italic','fontsize',12)
ylabel('Postion','fontname','Times New Roman italic')
line([0 10],[0 0],'Color','k','linestyle','-')
title('Time-Postion Curve','fontname','Times New Roman italic','fontsize',12)
subplot(2,2,2)
plot(linspace(0,a0/(2*r)*pi/Wn,1000),fraction_dx(a0,m,k,fs,x00))
xlabel('Time','fontname','Times New Roman italic','fontsize',12)
ylabel('Velocity','fontname','Times New Roman italic','fontsize',12)
title('Time-Velocity Curve','fontname','Times New Roman italic','fontsize',12)
line([0 10],[0 0],'Color','k','linestyle','-')
subplot(2,2,3)
plot(linspace(0,a0/(2*r)*pi/Wn,1000),fraction_dx2(a0,m,k,fs,x00))
xlabel('Time','fontname','Times New Roman italic','fontsize',12)
ylabel('Acceleration','fontname','Times New Roman italic','fontsize',12)
title('Time-Acceleration Curve','fontname','Times New Roman italic','fontsize',12)
line([0 10],[0 0],'Color','k','linestyle','-')
subplot(2,2,4)
v=fraction_dx(a0,m,k,fs,x00)/sqrt(k/m);
x=fraction(a0,m,k,fs,x00);
plot(x,v);
xlabel('Postion','fontname','Times New Roman italic','fontsize',12)
ylabel('Velocity/w_n','fontname','Times New Roman italic','fontsize',12)
axis equal
line([-a0 a0],[0 0],'Color','k','linestyle',':')
line([0 0],[-a0 a0],'Color','k','linestyle',':')
axis tight
title('Postion-Velocity/w_n Curve','fontname','Times New Roman italic','fontsize',12)
