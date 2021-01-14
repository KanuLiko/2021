clear,clc;
POP_SIZE = 20;
DNA_SIZE = 20;
CROSS_RATE = 0.8;
MUTATION_RATE = 0.03;
N_GENERATIONS = 300;
pop1 = round(rand(POP_SIZE,DNA_SIZE));
pop2 = round(rand(POP_SIZE,DNA_SIZE));
for e =1:N_GENERATIONS
    adaptValue = getAdaptValue(pop1,pop2,POP_SIZE);
    disp(adaptValue)
    [pop1,pop2] = popSelect(pop1,pop2,adaptValue);
    pop1_copy = pop1;
    pop2_copy = pop2;
    for r =1:length(pop1)
        childPop1 = crossOver(pop1(r,:),pop1_copy,CROSS_RATE,POP_SIZE,DNA_SIZE);
        childPop2 = crossOver(pop2(r,:),pop2_copy,CROSS_RATE,POP_SIZE,DNA_SIZE);
        childPop1 = mutatePop(childPop1);
        childPop2 = mutatePop(childPop2);
    end
end
function n=dna2dec(m)
    limit = 2*pi;
    n=bin2dec(num2str(m))/(2^length(m)-1)*limit;
end
function adaptValue=getAdaptValue(pop1,pop2,POP_SIZE)
    syms x y
    E = [40*cos(x) 40*sin(x)];F=[100-2*cos(y) 2*sin(y)];D=[0 100];C=[100 100];
    x0 = zeros(1,POP_SIZE);
    y0 = zeros(1,POP_SIZE);
    for e =1:POP_SIZE
        x0(e)=dna2dec(pop1(e,:));
        y0(e)=dna2dec(pop2(e,:));
    end
    adaptValue =zeros(1,POP_SIZE);
    for e =1:POP_SIZE
        adaptfun=@(x,y)(sqrt(sum((E-D).^2))+sqrt(sum((E-C).^2))+sqrt(sum((E-F).^2)));
        adaptValue(e)=eval(subs(adaptfun,[x,y],[x0(e),y0(e)]));
    end
end
function [popx,popy]=popSelect(pop1,pop2,adaptValue)
    fitness=adaptValue/sum(adaptValue);
    disp(fitness);
    random = rand(1)/length(adaptValue);
    index = find(fitness>random);
    disp('index:')
    disp(index)
    popx = pop1(index,:);
    popy=pop2(index,:);
end
function parentPop = crossOver(parentPop,pop,CROSS_RATE,POP_SIZE,DNA_SIZE)
    if rand(1)<CROSS_RATE
        crossMem = round(rand(1)*POP_SIZE);
        crossPos = unique(round(rand(1,DNA_SIZE)*DNA_SIZE)+1);
        parentPop(crossPos) = pop(crossMem,crossPos).*parentPop(crossPos);
    end
end
function childPop=mutatePop(childPop,MUTATION_RATE)
    for e = 1:DNA_SIZE
        if rand(1)<MUTATION_RATE
            childPop(e) = ~childPop;
        end
    end
end