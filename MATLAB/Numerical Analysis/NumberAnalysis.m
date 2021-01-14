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
m=1000;
% generation of coordinates and connectivities
[nodeCoordinates,numberElements]=coordinategenerate(m);
numberElements=numberElements-1;
xx=nodeCoordinates;
for i=1:numberElements
elementNodes(i,1)=i;
elementNodes(i,2)=i+1;
end
numberNodes=size(nodeCoordinates,1);
xx=nodeCoordinates(:,1);
yy=nodeCoordinates(:,2);
% for structure:
% displacements: displacement vector
% force : force vector
% stiffness: stiffness matrix
% GDof: global number of degrees of freedom
GDof=3*numberNodes;
U=zeros(GDof,1);
force=zeros(GDof,1);
stiffness=zeros(GDof);
%force vector
force(m+1)=15000;
force(numberNodes*2+m+1)=10e6;
% stiffness matrix
[stiffness]=...
formStiffness2Dframe(GDof,numberElements,...
elementNodes,numberNodes,xx,yy,EI,EA);
% boundary conditions and solution
prescribedDof=[1 numberNodes numberNodes+1 numberNodes*2 numberNodes*2+1 numberNodes*3]';
% solution
displacements=solution(GDof,prescribedDof,stiffness,force);
% output displacements/reactions
outputDisplacementsReactions(displacements,stiffness,...
GDof,prescribedDof)
%drawing mesh and deformed shape
U=displacements;
clf
hold on
U=displacements;
scaleFact=500;
drawingTrussMesh(nodeCoordinates+scaleFact*[U(1:numberNodes)...
U(numberNodes+1:2*numberNodes)],elementNodes,'g.',20,'k',2);
drawingTrussMesh(nodeCoordinates,elementNodes,'r.',20,'b',2);