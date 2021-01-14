%二进制转化成十进制函数
%输入变量：
%二进制种群
%输出变量
%十进制数值
function depop = binary2decimal(pop)
[px,py]=size(pop);
depop=zeros(px,py);
for i = 1:py
    depop(:,i) = 2.^(py-i).*pop(:,i);
end
depop = sum(depop,2)*pi/2/1023;
