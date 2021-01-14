function f=kulunfun(a0,m,k,fs,v,t)
    g=9.8;
    N = m*g;
    Wn=sqrt(k/m);
    r=N*fs/m;
    for e = 1:100
        if (t>=(e-1)*pi/Wn && t<e*pi/Wn)
            if v>=0
                f = v/Wn*sin(Wn*t)+(a0-(2*e-1)*r)*cos(Wn*t)+(-1)^(e+1)*r;
            else
                f = v/Wn*sin(Wn*t)+(a0-(2*e-1)*r)*cos(Wn*t)+(-1)^(e+1)*r;
            end
        end
    end
end