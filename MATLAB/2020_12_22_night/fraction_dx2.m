function [v] = fraction_dx2(a0,m,k,fs,x00)
    g=10;
    Wn=sqrt(k/m);
    r = fs*g;
    C1 = x00/Wn;
    current =1000;
    v = zeros(current);
    fprintf('C1=%.2f,C2=%.2f,Wn=%.2f,r=%.2f,m=%.2f,k=%.2f\n',C1,a0+r,Wn,r,m,k);
    t = linspace(0,a0/(2*r)*pi/Wn,current);
    for e = 1:current
       for jj=1:round(a0/(2*r)*pi/Wn)+1
            if (t(e)>=(jj-1)*pi/Wn && t(e)<jj*pi/Wn)
                    C2 = (a0-(2*jj-1)*r);
                    v(e)=-C2*Wn^2*cos(Wn*t(e));
            end
        end
    end
end


