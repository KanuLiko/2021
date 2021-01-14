%coefficient func
function coe=R5(x,y)
[m,n]=size(x);sum1=0;sum2=0;mu1=0;m1=0;m2=0;
for i=1:m
  for j=1:n
    sum1=sum1+x(i,j);
    sum2=sum2+y(i,j);
  end
 end
ave1=sum1/(m*n);
ave2=sum2/(m*n);
for i=1:m
  for j=1:n
      x(i,j)=x(i,j)-ave1;
      y(i,j)=y(i,j)-ave2;
  end
end
for i=1:m
    for j=1:n
    mu1=mu1+x(i,j)*y(i,j);
    m1=m1+x(i,j)^2;
    m2=m2+y(i,j)^2;
    end
end
coe=mu1/(sqrt(m1)*sqrt(m2));
coe=coe^2;
end
