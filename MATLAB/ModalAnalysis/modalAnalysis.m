syms w x1 x2 x3 x4 is real
format short g
M=[0.5 0 0;0 1 0;0 0 1.5];
K=[3 -1 -1;-1 3 -1;-1 -1 3]*1000;
Fre=eval(solve(det(K-w^2.*M)));
Fre=Fre(Fre>0);
Fre=sort(Fre.^2);
modeshape=zeros(size(K));
for i=1:length(Fre)
%     K-Fre(i)*Mmod
    [A,B]=eig((K-Fre(i)*M));
    modeshape(:,i)=A(:,i);
end
disp('modeshape is:');
disp(modeshape)
Kr=matround0(modeshape'*K*modeshape);
disp('modestiff is:');
disp(Kr)
Mr=matround0(modeshape'*M*modeshape);
disp('modemass is:');
disp(Mr)