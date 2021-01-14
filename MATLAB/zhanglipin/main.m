clear;
clc;
%种群大小
popsize=500;
%二进制编码长度,这里填计算出来的L值
chromlength=20;
%交叉概率
pc = 0.8;
%变异概率
pm = 0.05;
%初始种群
pop = initpop(popsize,chromlength);
for i = 1:1000
    %计算适应度值（函数值）
    objvalue = cal_objvalue(pop,chromlength);
    fitvalue = objvalue;
    %选择操作
    newpop = selection(pop,fitvalue);
    %交叉操作
    newpop = crossover(newpop,pc);
    %变异操作
    newpop = mutation(newpop,pm);
    %更新种群
    pop = newpop; 
    %寻找最优解
    [bestindividual,bestfit] = best(pop,fitvalue);
    bsi1 = bestindividual( :, 1:1:chromlength/2);
    bsi2 = bestindividual( :, chromlength/2 + 1:1:end);
    popA = newpop( :, end:-1:chromlength/2 + 1);
    popB = newpop( :, chromlength/2:-1:1);
    x1= binary2decimal(popA);
    x2= binary2decimal(popB);
    y1=sqrt(40*cos(x1).^2+(100-40*sin(x1)).^2)+sqrt((100-40*sin(x1)).^2+(100-40*cos(x1)).^2)...
        +sqrt((40*cos(x1)+2*cos(x2)-100).^2+(40*sin(x1)-2*sin(x2)).^2);
    %转化二进制数为x变量的变化域范围的数值
    x0 = binary2decimal(bsi1);
    y0 = binary2decimal(bsi2);
    z0=sqrt(40*cos(x0).^2+(100-40*sin(x0)).^2)+sqrt((100-40*sin(x0)).^2+(100-40*cos(x0)).^2)...
        +sqrt((40*cos(x0)+2*cos(y0)-100).^2+(40*sin(y0)-2*sin(y0)).^2);
    if mod(i,200) == 0
                figure;
                o1 = linspace(0,pi/2,100);
                o2 = o1;
                [O1,O2] = meshgrid(o1);
                k = sqrt(40*cos(O1).^2+(100-40*sin(O1)).^2)+sqrt((100-40*sin(O1)).^2+(100-40*cos(O1)).^2)...
                    +sqrt((40*cos(O1)+2*cos(O2)-100).^2+(40*sin(O1)-2*sin(O2)).^2);
                surf(o1,o2,k)
                hold on;
                title(['迭代次数为n=' num2str(i)]);
                plot3(x1,x2,y1,'*');
     end
end
fprintf('The best x0,y0 is --->>%5.3f\n >>%5.3f\n',180*x0/pi,180*y0/pi);
fprintf('The best z0 is --->>%6.3f\n',bestfit);