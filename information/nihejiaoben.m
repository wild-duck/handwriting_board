%f(x,y) = p00 + p10*x + p01*y + p20*x^2 + p11*x*y + p02*y^2 + p30*x^3 + p21*x^2*y  + p12*x*y^2 + p03*y^3
%% Y作为函数值
clear
aoto=xlsread("脚本数据格式.xls");
x = aoto(:,4);
y = aoto(:,5);
vx = aoto(:,6);
vy = aoto(:,7);
X = [ones(117,1),vx,vy,vx.*vx,vx.*vy,vy.*vy,(vx).^3,(vx).^2.*vy,(vy).^2.*vx,(vy).^3];
Y = y;
[b,bint.r,rint,s] = regress(Y,X);
%% X作为函数值
% clear
% aoto=xlsread("数据l.xls");
% x = aoto(:,4);
% y = aoto(:,5);
% vx = aoto(:,6);
% vy = aoto(:,7);
% X = [ones(117,1),vx,vy,vx.*vx,vx.*vy,vy.*vy,(vx).^3,(vx).^2.*vy,(vy).^2.*vx,(vy).^3];
% Y = x;
% [b,bint.r,rint,s] = regress(Y,X);