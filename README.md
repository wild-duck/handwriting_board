# 手写板

## 这是为了准备2021年电赛，训练时练的一道题目。

最终实现了写字，并且能在屏幕上实时显示的功能。使用的是正点原子的stm32f103zet6的那块开发板。

data文件夹中存放的是当时校准设备时，单片机采集的数据，用串口发回，上位机将数据保存为csv格式。

拟合是使用matlab的线性拟合工具进行拟合的，matlab的代码再information文件夹中。

