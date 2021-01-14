t= linspace(0,2*pi*sqrt(2)/4,10000);
x=zeros(1,10000);
for e = 1:10000
    x(e)=kulunfun(25,4,32,0.15,0,t(e));
end
plot(t,x,'LineWidth',1.5);
annotation('arrow',[0.3 0.38],[0.4 0.15]) 
annotation('arrow',[0.62 0.7],[0.5 0.7])
xlabel('Time','fontname','Times New Roman italic','fontsize',12)
ylabel('Postion','fontname','Times New Roman italic','fontsize',12)
hold on
axis tight
text(pi*sqrt(2)/4-0.1,2,'$\frac{\pi}{w_n}$','interpreter','latex','fontname','Times New Roman italic','fontsize',14)
text(2*pi*sqrt(2)/4-0.2,2,'$\frac{2\pi}{w_n}$','interpreter','latex','fontname','Times New Roman italic','fontsize',14)
text(pi*sqrt(2)/4,-24,'$B$','interpreter','latex','fontname','Times New Roman italic','fontsize',14)
text(2*pi*sqrt(2)/4,25-4*1.47+0.1,'$C$','interpreter','latex','fontname','Times New Roman italic','fontsize',14)
text(0.1,25,'$A$','interpreter','latex','fontname','Times New Roman italic','fontsize',14)
line([0 2.5],[0 0],'color','k','linestyle','-','Linewidth',1)
line([2*pi*sqrt(2)/4 2*pi*sqrt(2)/4],[0 25-4*1.47],'color','k','linestyle','-','Linewidth',1)
line([pi*sqrt(2)/4 pi*sqrt(2)/4],[0 -25+2*1.47],'color','k','linestyle','-','Linewidth',1)
line([0 pi*sqrt(2)/4],[1.47 1.47],'color','k','linestyle',':','Linewidth',1)
line([pi*sqrt(2)/4 2.5],[-1.47 -1.47],'color','k','linestyle',':','Linewidth',1)
