function drawingTrussMesh(nodeInfor,ElemInfor,dotStayle,dotSize,lineStyle,lineSize)
elemNumb=size(ElemInfor);
nodNumb=size(nodeInfor);
%plot the nodes
if nodNumb(2)==2
    for nod=1:nodNumb(1)
       plot(nodeInfor(nod,1),nodeInfor(nod,2),dotStayle,'MarkerSize',dotSize) ;
    end
elseif nodNumb(2)==3
    for nod=1:nodNumb(1)
       plot(nodeInfor(nod,2),nodeInfor(nod,3),dotStayle,'MarkerSize',dotSize) ;
    end
else
    error('node information is in wrong format')
end

%plot the truss element
for elm=1:elemNumb(1)
   if  elemNumb(2)==2
        if nodNumb(2)==2
            plot([nodeInfor(ElemInfor(elm,1),1) nodeInfor(ElemInfor(elm,2),1)],[nodeInfor(ElemInfor(elm,1),2) nodeInfor(ElemInfor(elm,2),2)],lineStyle,'LineWidth',lineSize) ;
        elseif nodNumb(2)==3
            plot(nodeInfor(nod,2),nodeInfor(nod,3),lineStyle,'MarkerSize',lineSize) ;
        else
            error('node information is in wrong format')
        end       
   else
       error('mesh information is in wrong format')
   end 
end
hold on
title('deformation model','fontname','Times New Roman italic','fontSize',12);
xlabel('x-position','fontname','Times New Roman italic');
ylabel('y-position','fontname','Times New Roman italic');

