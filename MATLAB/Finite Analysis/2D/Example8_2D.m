%................................................................
% MATLAB codes for truss analysis
% Example 2 in 2D 
clear all  % clear memory
clc  % Clear Command Window
close all  % Remove all figures
% E; modulus of elasticity
% A: area of cross section
% L: length of bar
E=70; A=60; EA=E*A;
% generation of coordinates and connectivities
elementNodes=[1 2;1 3;1 4];
nodeCoordinates=[0 0;-100 100;0 100;100 100];
numberElements=size(elementNodes,1);
numberNodes=size(nodeCoordinates,1);
xx=nodeCoordinates(:,1);
yy=nodeCoordinates(:,2);
% for structure:
% displacements: displacement vector
% force : force vector
% stiffness: stiffness matrix
GDof=2*numberNodes;
U=zeros(GDof,1);
force=zeros(GDof,1);
% applied load at node 2
force(2)=-100;
% computation of the system stiffness matrix
[stiffness]=...
formStiffness2Dtruss(GDof,numberElements,...
elementNodes,numberNodes,nodeCoordinates,xx,yy,EA);
% boundary conditions and solution
prescribedDof=[1 3:8]';
% solution
displacements=solution(GDof,prescribedDof,stiffness,force);
us=1:2:2*numberNodes-1;
vs=2:2:2*numberNodes;
% drawing displacements
% figure
L=xx(2)-xx(1);
%L=node(2,1)-node(1,1);
XX=displacements(us);YY=displacements(vs);
dispNorm=max(sqrt(XX.^2+YY.^2));
scaleFact=2*dispNorm;
% clf
hold on
drawingTrussMesh(nodeCoordinates+scaleFact*[XX YY],elementNodes,'g.',20,'k',2);
drawingTrussMesh(nodeCoordinates,elementNodes,'r.',20,'b',2);
% output displacements/reactions
outputDisplacementsReactions(displacements,stiffness,...
GDof,prescribedDof)
% stresses at elements
stresses2Dtruss(numberElements,elementNodes,...
xx,yy,displacements,E)
