%................................................................
% MATLAB codes for Finite Element Analysis
% problem11b.m
% 2D frame
% antonio ferreira 2008
% clear memory
clear
% E; modulus of elasticity
% I: second moment of area
% L: length of bar
E=210000; A=200; I=2e8; EA=E*A; EI=E*I;
m=1000;
% generation of coordinates and connectivities
% for structure:
% displacements: displacement vector
% force : force vector
% stiffness: stiffness matrix
% GDof: global number of degrees of freedom
GDof=2*Nodes;
force=zeros(GDof,1);
%force vector
% force(m+1)=15000;
% force(numberNodes*2+m+1)=10e6;
force(4) = 1000;
force(2) = 1000;
force(1) = 1000;
% stiffness matrix
[stiffness]=formStiffness2Dframe(GDof,numberElements,elementNodes,numberNodes,xx,yy,EI,EA);
% boundary conditions and solution
prescribedDof = [4 5 6 10 11 12]';
% solution
displacements=solution(GDof,prescribedDof,stiffness,force);
% output displacements/reactions
outputDisplacementsReactions(displacements,stiffness,GDof,prescribedDof)
%drawing mesh and deformed shape;
clf
hold on
U=displacements;
scaleFact=500;
drawingTrussMesh(nodeCoordinates+scaleFact*[U(1:numberNodes)...
U(numberNodes+1:2*numberNodes)],elementNodes,'g.',20,'k',2);
drawingTrussMesh(nodeCoordinates,elementNodes,'r.',20,'b',2);

