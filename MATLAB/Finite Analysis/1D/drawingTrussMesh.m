function drawingTrussMesh(xCoord,ElemInfor,dotStayle,dotSize,lineStyle,lineSize,yCoord)
elemNumb=size(ElemInfor);
nodNumb=length(xCoord);
%plot the nodes
for nod=1:nodNumb
   plot(xCoord(nod),yCoord,dotStayle,'MarkerSize',dotSize) ;
end


%plot the truss element
for elm=1:elemNumb(1)
   if  elemNumb(2)==2
       plot([xCoord(ElemInfor(elm,1)) xCoord(ElemInfor(elm,2))],[yCoord yCoord],lineStyle,'LineWidth',lineSize) ; 
   elseif elemNumb(2)==3
       
   
   else
       error('mesh information is in wrong format')
   end
    
end

