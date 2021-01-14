%+-----------------------------------------------------------------------+
%| Description:                                                          |
%| To derive the stiffness matrix in 2D space                            |
%+-----------------------------------------------------------------------+
%+-----------------------------------------------------------------------+
%| Created by Professor Hai Qing                                         |
%| Copyright: Nanjing University of Aeronautics and Astronautics 2016    |
%| Contact: qinghai@nuaa.edu.cn                                          |
%+-----------------------------------------------------------------------+
%| variables                                                             |
%| SF: shape function                                                    |
%| u: displacement                                                       |
%+-----------------------------------------------------------------------+
function [K]=truss3

syms a b c d eta x EA c0 c1 c2 u1 u2 u3 cosA sinA %real
um=[u1 u2 u3];
% eta=x/a;
u=c0+c1*eta+c2*eta^2;  % displacement
% boundary conditions
eq1=subs(u, eta, -1)==u1;       
eq2=subs(u, eta, 0)==u2;
eq3=subs(u, eta, 1)==u3;
% solve the unknown coefficients
s=solve([eq1,eq2,eq3],[c0,c1,c2]);
% substitute the coefficient back into deflection function
b=s.c0;
c=s.c1;
d=s.c2;
un=b+c*eta+d*eta^2;
% reagrange and get the Shape Function: SF
SF=[a,b,c];
for kp=1:length(um)
    C=coeffs(un,um(kp));
    SF(kp)=C(2);   
end
SF1=diff(SF,eta,1);
% calculate the stiffness matrix
Ke=int (EA*transpose(SF1)*SF1,eta,-1,1)/a;

Tmat=[cosA sinA 0 0 0 0;0 0 cosA sinA 0 0;0 0 0 0 cosA sinA];
K=transpose(Tmat)*Ke*Tmat;
K=K*(2*a)/EA;