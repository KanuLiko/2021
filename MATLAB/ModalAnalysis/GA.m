%N:the num of zhongqun
N=100;
M=21;
%Pc:crossProbility
Pc = 0.7;
Pm = 0.1;
eps = 10e-5;
zhongqun_old=round(rand(N,M));
zhongqun = round(rand(N,M));
adaptfun=@(x)(sin(8*pi*x)+3.0);
%calculate the adaption-value of zhongqun
adaptionValue = zeros(1,N);
adaptionValue_old = zeros(1,N);
for e = 1:N
    adaptionValue_old(e)=adaptfun(bin2dec(num2str(zhongqun_old(e,:)))/2097151*0.25);
end
for e = 1:N
    adaptionValue(e)=adaptfun(bin2dec(num2str(zhongqun(e,:)))/2097151*0.25);
end
while abs(adaptionValue(1)-adaptionValue_old(1))<eps
    %Simulation of roulette operation
    p = rand(1);
    if p<Pc
        %CrossOperation
        for e = 1:N
            zhongqun(e,5:M) = zhongqun(e,5:M)&zhongqun(N+1-e,5:M);
        end
    end 
    if p<Pm
            %Mutation operation
            zhongqun(round(rand(0,1)*N),round(rand(0,1)*M)) =~ zhongqun(round(rand(0,1)*N),round(rand(0,1)*M));
    end
    for e = 1:N
        adaptionValue(e)=adaptfun(bin2dec(num2str(zhongqun(e,:)))/2097151*0.25);
    end
    gaProbability=adaptionValue/sum(adaptionValue);
    loop = loop+1;
    fprintf('loop %d\n',loop);
    disp(adaptionValue(1))
end
disp(bin2dec(num2str(zhongqun(1,:)))/2097151*0.25)
%% hasn't get the probility to change the value of zhongqun member