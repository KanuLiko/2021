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
function [K]=truss2

syms a b c eta x EA c0 c1 u1 u2 cosA sinA %real
um=[u1 u2];
% eta=x/a;
u=c0+c1*eta;  % displacement
% boundary conditions
eq1=subs(u, eta, -1)==u1;       
eq2=subs(u, eta, 1)==u2;
% solve the unknown coefficients
s=solve([eq1,eq2],[c0,c1]);
% substitute the coefficient back into deflection function
b=s.c0;
c=s.c1;
un=b+c*eta;
% reagrange and get the Shape Function: SF
SF=[b,c];
for kp=1:length(um)
    C=coeffs(un,um(kp));
    SF(kp)=C(2);   
end
SF1=diff(SF,eta,1);
% calculate the stiffness matrix
Ke=int (EA*transpose(SF1)*SF1,eta,-1,1)/a;

Tmat=[cosA sinA 0 0 ;0 0 cosA sinA];
K=transpose(Tmat)*Ke*Tmat;
K=K*(2*a)/EA;