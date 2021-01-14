% a0 = 25;
% g=10;
% m = 4;
% k = 32;
% N = m*g;
% fs=0.15;

a0 = 5;
g=10;
m = 2;
k = 2*pi^2;
N = m*g;
fs=0.025;

r= fs*g;
Wn=sqrt(k/m);
num = 300;
t1 = linspace(0,a0/(2*r)*pi/Wn,num);
x = zeros(1,num);

%displacement
% for e =1:num
%     x(e) = (a0-2*r*Wn/pi*t1(e))*cos(Wn*t1(e));
% end
% plot(t1,x,'ko')
% hold on
% y=fraction(a0,m,k,fs,0);
% plot(linspace(0,a0/(2*r)*pi/Wn,1000),y)
% xlabel('Time','fontname','Times New Roman italic','fontsize',12);
% ylabel('Position','fontname','Times New Roman italic','fontsize',12);
% text(6,4,'$r=0.25,{w_n}=\pi,{a_0}=5$','interpreter','latex','fontname','Times New Roman italic','fontsize',10)
% line([0 10],[0 0],'linestyle','-','Color','k')

%v
% for e =1:num
%     x(e) = -2*r*Wn/pi*cos(Wn*t1(e))-Wn*(a0-2*r*Wn/pi*t1(e))*sin(Wn*t1(e));
% end
% plot(t1,x,'ko')
% hold on
% y=fraction_dx(a0,m,k,fs,0);
% plot(linspace(0,a0/(2*r)*pi/Wn,1000),y)
% xlabel('Time','fontname','Times New Roman italic','fontsize',12);
% ylabel('Velocity','fontname','Times New Roman italic','fontsize',12);
% text(6,11,'$r=0.25,{w_n}=\pi,{a_0}=5$','interpreter','latex','fontname','Times New Roman italic','fontsize',10)
% line([0 10],[0 0],'linestyle','-','Color','k')

%a
for e =1:num
    x(e) = 4*r*Wn^2/pi*sin(Wn*t1(e))-Wn^2*(a0-2*r*Wn/pi*t1(e))*cos(Wn*t1(e));
end
plot(t1,x,'ko')
hold on
y=fraction_dx2(a0,m,k,fs,0);
plot(linspace(0,a0/(2*r)*pi/Wn,1000),y)
xlabel('Time','fontname','Times New Roman italic','fontsize',12);
ylabel('Acceleration','fontname','Times New Roman italic','fontsize',12);
text(6,40,'$r=0.25,{w_n}=\pi,{a_0}=5$','interpreter','latex','fontname','Times New Roman italic','fontsize',10)
line([0 10],[0 0],'linestyle','-','Color','k')




