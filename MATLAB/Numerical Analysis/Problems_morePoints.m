%................................................................
% MATLAB codes for Finite Element Analysis
% problem11b.m
% 2D frame
% antonio ferreira 2008
% clear memory
clear all
% E; modulus of elasticity
% I: second moment of area
% L: length of bar
E=210000; A=200; I=2e8; EA=E*A; EI=E*I;
% generation of coordinates and connectivities
nodeCoordinates = [0 2;0 1.5;0.5 1.5;0 1;0.5 1;1 1;0 0.5;0.5 0.5;1 0.5;1.5 0.5;0 0;0.5 0;1 0;1.5 0;2 0]*1000;
numberElements = 18;
elementNodes = [1 2;1 3;2 4;3 6;4 5;5 6;4 7;4 8;6 9;6 10;7 11;8 13;9 13;10 15;11 12;12 13;13 14;14 15];
numberNodes=length(nodeCoordinates);
xx=nodeCoordinates(:,1);
yy=nodeCoordinates(:,2);
% for structure:
% displacements: displacement vector
% force : force vector
% stiffness: stiffness matrix
% GDof: global number of degrees of freedom
GDof=3*numberNodes;
force=zeros(GDof,1);
%force vector
% force(m+1)=15000;
% force(numberNodes*2+m+1)=10e6;
force(1) = 4000;
force(2) = 4000;
force(4) = 4000;
force(7) = 4000;
force(11) = 4000;
% stiffness matrix
[stiffness]=formStiffness2Dframe(GDof,numberElements,elementNodes,numberNodes,xx,yy,EI,EA);
% boundary conditions and solution
prescribedDof = [11 12 13 14 15 26 27 28 29 30]';
% solution
displacements=solution(GDof,prescribedDof,stiffness,force);
% output displacements/reactions
outputDisplacementsReactions(displacements,stiffness,...
GDof,prescribedDof)
%drawing mesh and deformed shape;
clf
hold on
U=displacements;
scaleFact=500;
drawingTrussMesh(nodeCoordinates+scaleFact*[U(1:numberNodes)...
U(numberNodes+1:2*numberNodes)],elementNodes,'g.',20,'k',2);
drawingTrussMesh(nodeCoordinates,elementNodes,'r.',20,'b',2);

