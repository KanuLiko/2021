v=fraction_dx(25,4,32,0.15,0)/sqrt(8);
x=fraction(25,4,32,0.15,0);
plot(x,v,'LineWidth',1);
xlabel('Postion','fontname','Times New Roman italic','fontsize',12)
ylabel('Velocity/w_n','fontname','Times New Roman italic','fontsize',12)
axis equal
line([-30 30],[0 0],'Color','k','linestyle','-')
line([0 0],[-30 30],'Color','k','linestyle','-')
line([1.5 1.5],[-30 30],'Color','k','linestyle',':')
line([-1.5 -1.5],[-30 30],'Color','k','linestyle',':')
text(1.5,26,'$\frac{v}{w_n}$','interpreter','latex','fontname','Times New Roman italic','fontsize',14)
text(28,-1.5,'$x$','interpreter','latex','fontname','Times New Roman italic','fontsize',14)
text(-1.5,-1.5,'$o$','interpreter','latex','fontname','Times New Roman italic','fontsize',14)
title('Postion-Velocity/w_n Curve','fontname','Times New Roman italic','fontsize',12)
