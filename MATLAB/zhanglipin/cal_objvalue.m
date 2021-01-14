%���㺯��Ŀ��ֵ
%�����������������ֵ
%���������Ŀ�꺯��ֵ
function [objvalue] = cal_objvalue(pop,chromlength)
    popA = pop( :,end:-1:chromlength/2+1);
    popB = pop( :,chromlength/2:-1:1);
    x1 = binary2decimal(popA);
    x2 = binary2decimal(popB);
    %ת����������Ϊx�����ı仯��Χ����ֵ
    objvalue = sqrt(40*cos(x1).^2+(100-40*sin(x1)).^2)+sqrt((100-40*sin(x1)).^2+(100-40*cos(x1)).^2)...
        +sqrt((40*cos(x1)+2*cos(x2)-100).^2+(40*sin(x1)-2*sin(x2)).^2);
end
