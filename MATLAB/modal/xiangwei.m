% a0=25;
% Wn=2*sqrt(2);
% r=1.47;
% t = linspace(0,3*pi,1000);
% v = zeros(1,1000);
% x = zeros(1,1000);
% C = zeros(1,1000);
% for e =1:1000
%     v(e) = diff_kulunfun(t(e));
%     for k=1:15
%         if (t(e)>=(k-1)*pi/Wn && t(e)<k*pi/Wn)
%             C(k) = a0-2*k*r;
%         end
%     end
% end
% for e =1:1000
%     if v(e)>=0
%         x(e)=sqrt(C(e)^2-(v(e)/Wn)^2)-r;
%     else
%         x(e)=sqrt(C(e)^2-(v(e)/Wn)^2)+r;
%     end
% end
% plot(x,v/Wn)
