clc;
clear;
adc = xlsread('filter_data2.xlsx');

figure('color',[1,1,1]);
subplot(2,1,1);
plot(adc(100:800));
title('滤波前波形');

y = filter(fir,adc);  
subplot(2,1,2);
plot(y(100:800));
title('滤波后波形');
