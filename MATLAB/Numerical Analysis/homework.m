syms x y positive
CoordinateNode = [0 2;0 1;1 1;0 0;1 0;2 0];
shapeNode=[2 3;4 6;1 6;4 6;1 4;4 6;2 5;1 6;1 4;1 6;1 4;3 5];
xindex = CoordinateNode(:,1);
yindex = CoordinateNode(:,2);
poly = zeros(1,length(CoordinateNode)*2)*x;
for e=1:2*length(CoordinateNode)
    if xindex(shapeNode(e,1))==xindex(shapeNode(e,2))
        poly(e)=xindex(shapeNode(e,1))-x;
%     elseif yindex(shapeNode(e,1))==yindex(shapeNode(e,2))
%         poly(e)=yindex(shapeNode(e,1))-y;     
    else
        k=yindex(shapeNode(e,1))-yindex(shapeNode(e,2))/(xindex(shapeNode(e,1))-xindex(shapeNode(e,2)));
        poly(e)=yindex(shapeNode(e,1))-y+k*(x-xindex(shapeNode(e,1)));
    end
end
disp(poly)
C = zeros(1,length(CoordinateNode));
shapefunc = zeros(1,length(CoordinateNode))*x;
for e = 1:length(CoordinateNode)
    shapefunc(e)=poly(2*e-1)*poly(2*e);
    C(e)=1/eval(subs(shapefunc(e),[x,y],[xindex(e),yindex(e)]));
end
shapefunc =simplify(shapefunc.*C);
simplify(sum(shapefunc))
