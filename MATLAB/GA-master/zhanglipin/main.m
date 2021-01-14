clc,clear;
N= 1000;
M =20;
[xvalue,yvalue,fitnessValue,best_fitness, elite, generation, last_generation]=ga(2,'adaptfun',M,15,0.1,N,10e-6);
x=linspace(0,1.5,M);
y=linspace(0,1.5,M);
[X,Y]=meshgrid(x,y);
Z=zeros(M,M);
for e=1:M
    for r=1:M
        Z(e,r)=adaptfun(X(e,r),Y(e,r));
    end
end

surf(X,Y,Z)
hold on
p = plot3(xvalue(:,1),yvalue(:,1),fitnessValue(:,1),'o','MarkerFaceColor','red','Markersize',4);
hold off
axis manual
for k = 2:size(xvalue,1)
    p.XData = xvalue(k,:);
    p.YData = yvalue(k,:);
    p.ZData = fitnessValue(k,:);
    drawnow
end

pos=find(fitnessValue==min(fitnessValue(M,:)),1);
fprintf('first angle is %.1f degree\n',xvalue(pos)/pi*180);
fprintf('second angle is %.1f degree\n',yvalue(pos)/pi*180);
E = [40*cos(xvalue(pos)) 40*sin(xvalue(pos))];
F =[100-2*cos(yvalue(pos)) 2*sin(yvalue(pos))];
D =[0 100];
C =[100 100];
fprintf('distnce between 3 points are  C(%.1f)|D(%.1f)|F(%.1f) km\n',sqrt(sum((E-C).^2)),sqrt(sum((E-D).^2)),sqrt(sum((E-F).^2)));
figure
subplot(2,1,1)
loglog(1:generation, best_fitness(1:generation), 'linewidth',2)
xlabel('Generation','fontsize',15);
ylabel('Best Fitness','fontsize',15);
set(gca,'fontsize',15,'ticklength',get(gca,'ticklength')*2);
subplot(2,1,2)
semilogx(1 : generation, 2 * elite(1 : generation, :) - 1)
xlabel('Generation','fontsize',15);
ylabel('Best Solution','fontsize',15);
set(gca,'fontsize',15,'ticklength',get(gca,'ticklength')*2);