function [ r,t ] = stressCalu( a,b,c )
%STRESSCALU Summary of this function goes here
%   Detailed explanation goes here
E=72;u=0.33;
r1=E/(1-u^2)*((1+u)/2*(a+c)+(1-u)/sqrt(2)*sqrt((c-b)^2+(b-a)^2));
r3=E/(1-u^2)*((1+u)/2*(a+c)-(1-u)/sqrt(2)*sqrt((c-b)^2+(b-a)^2));
r=round([r1 r3]/1000,2);
t=atan((c-a)/(2*b-a-c))/pi*180;
end

