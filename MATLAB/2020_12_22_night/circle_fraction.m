function [v,x] = circle_fraction(a0,m,k,fs,x00)
    g=10;
    Wn=sqrt(k/m);
    r = fs*g;
    C1 = x00/Wn;
    current =1000;
    v = fraction_dx(25,4,32,0.15,0);
    
    fprintf('C1=%.1f,C2=%.1f,Wn=%.1f,r=%.1f,m=%.1f,k=%.1f\n',C1,a0+r,Wn,r,m,k);
    x = zeros(1,current);
    for e = 1:current
        if v(e)>=0
            C = (a0+r)^2;
            x(e)=sqrt(C-((v(e)/Wn)^2))-r;
        else
            C = (a0-r)^2;
            x(e)=sqrt(C-((v(e)/Wn)^2))+r;
        end
    end
    v = v/Wn;
end