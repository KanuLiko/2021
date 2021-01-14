clc
clear all;

%%Parameters
syms x
w = 0:0.01:60;
ZD=zeros(size(w));
M = [1 0;0 1];
K = [500 -400;-400 500];
C = [3 0;0 9];
A = K-M.*x.^2+1i*C;

%%Caculate
ComplexA = eval(subs(1/det(A),x,w));
RealA = real(ComplexA);
ImageA = imag(ComplexA);
Phase = atan(ImageA./RealA)/10000;
Amplitude = (RealA.^2+ImageA.^2).^0.5;

%%plot
figure('position',[200 0 950 720])
xlim([0,60]);
ylim([-2e-4,2e-4]);
zlim([-4e-4,4e-4]);
plot3(w,ImageA,RealA,'m-','LineWidth',1.5)
title('Frequency-ImagePart-RealPart Curve','fontname','Times New Roman italic','fontSize',12);
view(45,45);
hold on
grid on
xlabel('Frequency','fontname','Times New Roman italic','Rotation',-35);
ylabel('ImagePart','fontname','Times New Roman italic','Rotation',35);
zlabel('RealPart','fontname','Times New Roman italic');
plot3(w,ZD+(5e-4),RealA,'b-.','lineWidth',0.6)
plot3(ZD,ImageA,RealA,'r--','lineWidth',0.6)
plot3(w,ImageA,ZD-(2e-4),'k-','lineWidth',0.6)

%Amplitude-frequency Curve
plot3(w,Amplitude+(5.5e-4),Amplitude+(5.5e-4),'c','LineWidth',0.8);

%Phase-frequency Curve
plot3(w,Phase+(10e-4),Phase+(10e-4),'LineWidth',0.8);
legendHandle=legend('Frequency-ImagePart-RealPart','Freqency-RealPart',...
'ImagePart-RealPart','Frequency-ImagePart','Amplitude-Frequency','Phase-Frequency');
set(legendHandle,'fontname','Times New Roman italic','fontSize',12); 


%Draw Surf

xx1=linspace(0,60,4);
xx2=linspace(0,60,4);
yy1=linspace(5.0e-4,15e-4,5);
zz2=linspace(-5e-4,5e-4,4);
[X1,Y1]=meshgrid(xx1,yy1);
[X2,Z2]=meshgrid(xx2,zz2);
Z1=Y1;
Y2=zeros(size(X2))+5e-4;
mesh(X1,Y1,Z1,'edgecolor',[0.5 0.5 0.5]);
mesh(X2,Y2,Z2,'edgecolor',[0.5 0.5 0.5]);
grid on
