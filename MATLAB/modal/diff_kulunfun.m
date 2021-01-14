function f=diff_kulunfun(t)
    m=4;
    a0=25;
    g=9.8;
    N = m*g;
    fs=0.15;
    K=32;
    Wn=sqrt(K/m);
    r=N*fs/m;
    for e = 1:100
        if (t>=(e-1)*pi/Wn && t<e*pi/Wn)
                f = -Wn*(a0-(2*e-1)*r)*sin(Wn*t);
        end
    end
end