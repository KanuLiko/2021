%..............................................................
function [reactions]=outputDisplacementsReactions(displacements,stiffness,GDof,prescribedDof)
% output of displacements and reactions in
% tabular form
% GDof: total number of degrees of freedom of
% the problem
% displacements
% disp('Displacements')
%displacements=displacements1;
jj=1:GDof; 
% format 
% disp([jj' displacements])
% reactions
F=stiffness*displacements;
reactions=F(prescribedDof);
% disp('reactions')
% disp([prescribedDof reactions])
if GDof == 18
    disp(displacements([1,2,3]))
elseif GDof == 45
    disp(displacements([1,4,6]))
end