function [ coordinates, nodenumber] = coordinategenerate( x )
%COORDINATEGENERATE Summary of this function goes here
%   Detailed explanation goes here
a1 = linspace(0,6000,x+1);%101
b1 = zeros(1,x+1);
c1 = [b1',a1'];
a2 =linspace(6000/x,6000,x);%100
b2 = zeros(1,x)+6000;
c2 = [a2',b2'];
a3 =linspace(6000-6000/x,0,x);
c3 = [b2',a3'];
coordinates = [c1;c2;c3];
nodenumber = size(coordinates,1);
end

