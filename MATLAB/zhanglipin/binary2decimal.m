%������ת����ʮ���ƺ���
%���������
%��������Ⱥ
%�������
%ʮ������ֵ
function depop = binary2decimal(pop)
[px,py]=size(pop);
depop=zeros(px,py);
for i = 1:py
    depop(:,i) = 2.^(py-i).*pop(:,i);
end
depop = sum(depop,2)*pi/2/1023;
