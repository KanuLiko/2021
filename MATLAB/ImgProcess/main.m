tic
clear all;
clc
path_origin='C:\Users\kanu\Documents\MATLAB\ImgProcess\cal_00000_0.bmp';
path2='C:\Users\kanu\Documents\MATLAB\ImgProcess\cal_00219_0.bmp';
img1=double(imread(path_origin));
img2=double(imread(path2));
[m,n]=size(img1);
h=0.01;
startc=50;spacec=10;endc=200;startl=50;spacel=10;endl=200;
[y,x]=meshgrid(startc:spacec:endc,startl:spacel:endl);
[s1,s2]=size(x);
dx=31;dy=31;dpx=(dx-1)/2;dpy=(dy-1)/2;
stepx=2;stepy=1;
rigidx=0;rigidy=0;

sourcesubset=zeros(size(x));
targetsubset=zeros(size(x));
xdisold=zeros(s1,s2);
ydisold=zeros(s1,s2);
R=zeros(s1,s2);
for i=1:s1
   for j=1:s2
      xc=x(i,j);yc=y(i,j);
      for ik=1:dy
          for jk=1:dx
                sourcesubset(ik,jk)=getbilinear(img1,(xc-dpy+ik),(yc-dpx+jk));
          end
      end
      xdisnew=rigidx*ones(s1,s2);
      ydisnew=rigidy*ones(s1,s2);
      ups=rigidx-stepx;upt=rigidx+stepx;
      vps=rigidy-stepy;vpt=rigidy+stepy;
      upj=(upt-ups)/5;vpi=(vpt-vps)/5;
      while(abs(upj*5/2)>h||abs(vpi*5/2)>h)
          coemax=-10e10;
          xdisold(i,j)=xdisnew(i,j);
          ydisold(i,j)=ydisnew(i,j);
          for vp=vps:vpi:vpt
             for up=ups:upj:upt
                for ik=1:dx
                   for jk=1:dy
                      targetsubset(ik,jk)=getbilinear(img2,(xc+up+ik-dpx),(yc+vp-dpy+jk));
                   end
                end
                    RR=R5(sourcesubset,targetsubset);
                    R(i,j)=RR;
                    if(RR>coemax)
                       coemax=RR;
                       xdisnew(i,j)=up;
                       ydisnew(i,j)=vp;
                    end
              end
          end
        ups=xdisnew(i,j)-upj;upt=xdisnew(i,j)+upj;
        vps=ydisnew(i,j)-vpi;vpt=ydisnew(i,j)+vpi;
        upj=upj*2/5;
        vpi=vpi*2/5;
      end      
         elu=sqrt((xdisnew-xdisold).^2+(ydisnew-ydisold).^2);
    end
end
subplot(1,2,1)
surf(x,y,R)
title('coefficient at EPO');
shading interp;
subplot(1,2,2)
surf(x,y,elu);
title('deformation at EPO');
shading interp;
toc





