subplot(2,2,1)
plot(linspace(0,25/(2*1.5)*pi/(2*sqrt(2)),1000),fraction(25,4,32,0.15,0))
hold on
xlabel('Time','fontname','Times New Roman italic','fontsize',12)
ylabel('Postion','fontname','Times New Roman italic')
line([0 10],[0 0],'Color','k','linestyle','-')
title('Time-Postion Curve','fontname','Times New Roman italic','fontsize',12)
subplot(2,2,2)
plot(linspace(0,25/(2*1.5)*pi/(2*sqrt(2)),1000),fraction_dx(25,4,32,0.15,0))
xlabel('Time','fontname','Times New Roman italic','fontsize',12)
ylabel('Velocity','fontname','Times New Roman italic','fontsize',12)
title('Time-Velocity Curve','fontname','Times New Roman italic','fontsize',12)
line([0 10],[0 0],'Color','k','linestyle','-')
subplot(2,2,3)
plot(linspace(0,25/(2*1.5)*pi/(2*sqrt(2)),1000),fraction_dx2(25,4,32,0.15,0))
xlabel('Time','fontname','Times New Roman italic','fontsize',12)
ylabel('Acceleration','fontname','Times New Roman italic','fontsize',12)
title('Time-Acceleration Curve','fontname','Times New Roman italic','fontsize',12)
line([0 10],[0 0],'Color','k','linestyle','-')
subplot(2,2,4)
v=fraction_dx(25,4,32,0.15,0)/sqrt(8);
x=fraction(25,4,32,0.15,0);
plot(x,v);
xlabel('Postion','fontname','Times New Roman italic','fontsize',12)
ylabel('Velocity/w_n','fontname','Times New Roman italic','fontsize',12)
axis equal
line([-25 25],[0 0],'Color','k','linestyle',':')
line([0 0],[-25 25],'Color','k','linestyle',':')
axis tight
title('Postion-Velocity/w_n Curve','fontname','Times New Roman italic','fontsize',12)
