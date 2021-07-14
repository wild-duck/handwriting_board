%f(x,y) = p00 + p10*x + p01*y + p20*x^2 + p11*x*y + p02*y^2 + p30*x^3 + p21*x^2*y  + p12*x*y^2 + p03*y^3
% %% Y作为函数值
% clear
% auto = xlsread("071401data.xlsx");  % 读取表中数据
% 
% % 整理数据至各变量
% adc1 = auto(2:end,1);
% adc2 = auto(2:end,2);
% adc3 = auto(2:end,3);
% m = adc1 - adc3; 
% y = auto(2:end,5);
% 
% % 用regress函数计算
% X = [ones(117,1), m, adc2, m.*m, m.*adc2, adc2.*adc2, (m).^3,(m).^2.*adc2, (adc2).^2.*m, (adc2).^3];
% Y = y;
% [b,bint.r,rint,s] = regress(Y,X);
%% X作为函数值
clear
auto = xlsread("071401data.xlsx");     % 读取表中数据

% 整理数据至各变量
adc1 = auto(2:end,1);
adc2 = auto(2:end,2);
adc3 = auto(2:end,3);
m = adc1 - adc3; 
x = auto(2:end,4);

% 用regress函数计算
X = [ones(117,1), m, adc2, m.*m, m.*adc2, adc2.*adc2, (m).^3,(m).^2.*adc2, (adc2).^2.*m, (adc2).^3];
Y = x;
[b,bint.r,rint,s] = regress(Y,X);