clear
clc
close all;
N=7;
Result = zeros(1,N);
for i = 1:N
    % generation of coordinates and connectivities
    [coordinate,Nodes]=CoordinateNodeGenerate(i);
    % A matrix
    A=formA(Nodes,coordinate);
    disp('A')
    disp(det(A))
    ucons = uconstraints(Nodes);
    b=bapply(Nodes);
    % solution
    u=solution(Nodes,ucons,A,b);
%     disp('u')
%     disp(u(~isnan(u))')
    Result(i)=u(1);
end
%display 1-point u-value
x= 1:N;
plot(x,Result,'-bo','MarkerFaceColor','k')
hold on

function b=bapply(Nodes)
    b=zeros(Nodes,1);
    rows = (sqrt(8*Nodes+1)-1)/2;
    b(1)=1/(2*(rows-1));
    b(rows*(rows-1)/2+1)=1/(2*(rows-1));
    for e = 2:rows-1
        b(e*(e-1)/2+1)=1/(rows-1);
    end
%     disp('b')
%     disp(b')
end

function constraints = uconstraints(Nodes)
    rows = (sqrt(8*Nodes+1)-1)/2;
    constraints = rows*(rows-1)/2+1:rows*(rows-1)/2+rows;
end

function U=solution(Nodes,ucons,A,b)
%     nocons=setdiff(transpose(1:Nodes),ucons);
    for e = 1:Nodes
        A(e,e)=A(e,e)*10^10;
        b(e)=b(e)*10^10;
    end
    b(ucons)=0;
    U=A\b;
end

%generate MatrixA
function A=formA(Nodes,coordinate)
syms x y is real
rows = (sqrt(8*Nodes+1)-1)/2;
triangleElements = zeros((rows-1)*(rows-1),3);
triangleIndex = 1;
triangleElementsNum = size(triangleElements,1);
for row=1:rows-1
    for rownum=1:row
        %calculate every triangle
        trianglenode = row*(row-1)/2+rownum;
        triangleElements(triangleIndex,:) = [trianglenode,trianglenode+row,trianglenode+row+1];
        triangleIndex=triangleIndex+1;
        %disp([trianglenode,trianglenode+colnum,trianglenode+colnum+1]);
        if trianglenode-row*(row-1)/2+1<=row
           triangleElements(triangleIndex,:) = [trianglenode,trianglenode+1,trianglenode+row+1];
           triangleIndex=triangleIndex+1;
%            disp([trianglenode,trianglenode+1,trianglenode+colnum+1]);
        end
    end
end
fprintf('total %d triangles\n',(rows-1)^2);
A=zeros(Nodes);
%calculate A of everyTriangleElements
Ke = zeros(3,3);
for e = 1:triangleElementsNum
    %disp(triangleElements(e,:))
    [S,AT]=coeffients(coordinate(triangleElements(e,:),:)); 
    for row = 1:3
        for col = 1:3
            Ke(row,col)=sum(sum(AT(row,:)'*AT(col,:)));
        end
    end
    % computation of the A matrix
    indice=triangleElements(e,:);
    A(indice,indice)=A(indice,indice)+Ke/(4*S);
end
end

function [S,aT]=coeffients(T)
    M = [1 1 1;T'];
    S=1/2*det(M);
    aT = [M(3,2)-M(3,3),M(2,3)-M(2,2);M(3,1)-M(3,3),M(2,3)-M(2,1);M(3,1)-M(3,2),M(2,2)-M(2,1)];
end

%generate the nodes and coordinate of nodes
function [coordinate,Nodes] = CoordinateNodeGenerate(N)
rows = 0;
if N<1 || mod(N,1)~=0
    warning('wrong input!');
elseif N==1
    rows = 2;
else
    p = 2;
    for i = 2:N
        p=2*p-1;
    rows = p;
    end
end
Nodes = rows*(rows+1)/2;
coordinate = zeros(Nodes,2);
    for row=1:rows
        for i=1:row
            coordinate(row*(row-1)/2+i,:)= [(i-1)/(rows-1),1-(row-1)/(rows-1)];
        end        
    end
end