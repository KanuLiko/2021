t= linspace(0,3*pi,10000);
x=zeros(1,10000);
a0=25;
m=4;
k=32;
fs=0.15;
for e = 1:10000
    x(e)=kulunfun(a0,4,k,fs,0,t(e));
end
y=zeros(1,10000)+1.47;
plot(t,x,'LineWidth',1.5)
hold on
axis tight
axisx = linspace(0,3*pi,10000);
plot(axisx,zeros(1,10000),'k')
plot(t,y,'k--','LineWidth',1)
plot(t,-y,'k--','LineWidth',1)
plot([0,9.5],[25,0],'k--',[0,9.5],[-25,0],'k--','LineWidth',1);
text(-1,25,'\alpha_0');
text(-1,1.47,'+r','fontname','Times New Roman italic','fontsize',14);
text(-0.9,-1.47,'-r','fontname','Times New Roman italic','fontsize',14);
text(pi*sqrt(2)/4+0.1,-23,'\alpha_0-2r','fontname','Times New Roman italic','fontsize',14)
text(2*pi*sqrt(2)/4+0.1,20,'\alpha_0-4r','fontname','Times New Roman italic','fontsize',14)
text(3*pi*sqrt(2)/4+0.1,-17,'\alpha_0-6r','fontname','Times New Roman italic','fontsize',14)
text(4*pi*sqrt(2)/4+0.1,14,'\alpha_0-8r','fontname','Times New Roman italic','fontsize',14)
text(5*pi*sqrt(2)/4+0.1,-11,'\alpha_0-10r','fontname','Times New Roman italic','fontsize',14)
text(6*pi*sqrt(2)/4+0.1,8,'\alpha_0-12r','fontname','Times New Roman italic','fontsize',14)
text(pi*sqrt(2)/4-0.2,2,'$\frac{\pi}{w_n}$','interpreter','latex','fontname','Times New Roman italic','fontsize',14)
text(2*pi*sqrt(2)/4-0.2,2,'$\frac{2\pi}{w_n}$','interpreter','latex','fontname','Times New Roman italic','fontsize',14)
text(3*pi*sqrt(2)/4-0.2,2,'$\frac{3\pi}{w_n}$','interpreter','latex','fontname','Times New Roman italic','fontsize',14)
text(4*pi*sqrt(2)/4-0.2,2,'$\frac{4\pi}{w_n}$','interpreter','latex','fontname','Times New Roman italic','fontsize',14)
text(5*pi*sqrt(2)/4-0.2,2,'$\frac{5\pi}{w_n}$','interpreter','latex','fontname','Times New Roman italic','fontsize',14)
text(6*pi*sqrt(2)/4-0.2,2,'$\frac{6\pi}{w_n}$','interpreter','latex','fontname','Times New Roman italic','fontsize',14)
text(7*pi*sqrt(2)/4-0.2,2,'$\frac{7\pi}{w_n}$','interpreter','latex','fontname','Times New Roman italic','fontsize',14)
text(8*pi*sqrt(2)/4-0.2,2,'$\frac{8\pi}{w_n}$','interpreter','latex','fontname','Times New Roman italic','fontsize',14)
hold on
line([pi*sqrt(2)/4 pi*sqrt(2)/4],[0 -25+2*1.47],'linestyle',':','Linewidth',1)
line([2*pi*sqrt(2)/4 2*pi*sqrt(2)/4],[0 25-4*1.47],'linestyle',':','Linewidth',1)
line([3*pi*sqrt(2)/4 3*pi*sqrt(2)/4],[0  -25+6*1.47],'linestyle',':','Linewidth',1)
line([4*pi*sqrt(2)/4 4*pi*sqrt(2)/4],[0 25-8*1.47],'linestyle',':','Linewidth',1)
line([5*pi*sqrt(2)/4 5*pi*sqrt(2)/4],[0  -25+10*1.47],'linestyle',':','Linewidth',1)
line([6*pi*sqrt(2)/4 6*pi*sqrt(2)/4],[0 25-12*1.47],'linestyle',':','Linewidth',1)
line([7*pi*sqrt(2)/4 7*pi*sqrt(2)/4],[0 -25+14*1.47],'linestyle',':','Linewidth',1)
line([8*pi*sqrt(2)/4 8*pi*sqrt(2)/4],[0 25-16*1.47],'linestyle',':','Linewidth',1)
handle=legend('displacement','r=1.47');
set(handle,'fontname','Times New Roman italic');
title('Coulomb friction displacement response','fontsize',16,'fontname','Times New Roman italic')
