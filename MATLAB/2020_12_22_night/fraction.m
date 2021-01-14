function [d] = fraction(a0,m,k,fs,x00)
    g=10;
    Wn=sqrt(k/m);
    r = fs*g;
    C1 = x00/Wn;
    current =1000;
    d = zeros(current);
    fprintf('C1=%.2f,C2=%.2f,Wn=%.2f,r=%.2f,m=%.2f,k=%.2f\n',C1,a0+r,Wn,r,m,k);
%     if x00>0
%         syms x is real
%         past = 100;
%         C2=a0+r;
%         t0_past = atan(C1/C2)/Wn;
%         x0_plus = C1*sin(Wn*t0_past)+C2*cos(Wn*t0_past)-r;
%         a0 = a0+x0_plus;
%         t_past = linspace(0,pi,past);
%         for e = 1:past
%             d(e) =C1*sin(Wn*t_past(e))+C2*cos(Wn*t_past(e))-r;
%         end
%     end
    t = linspace(0,a0/(2*r)*pi/Wn,current);
    for e = 1:1000
        for jj=1:round(a0/(2*r)*pi/Wn)+1
            if (t(e)>=(jj-1)*pi/Wn && t(e)<jj*pi/Wn)
                    C2 = (a0-(2*jj-1)*r);
                    d(e) = C1*sin(Wn*t(e))+C2*cos(Wn*t(e))+(-1)^(jj+1)*r;
            end
        end
    end
end

