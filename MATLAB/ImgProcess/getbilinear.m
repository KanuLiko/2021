%gray's interpolation func
function f=getbilinear(img,y,x)
%[sline,scolumn]=size(img);
i1=floor(x);i2=i1+1;
j1=floor(y);j2=j1+1;
   f1=img(j1,i1);
   f2=img(j1,i2);
   f3=img(j2,i1);
   f4=img(j2,i2);
i1=double(i1);
j1=double(j1);
f12=f1+(x-i1)*(f2-f1);
f34=f3+(x-i1)*(f4-f3);
f=f12+(y-j1)*(f34-f12);
end

