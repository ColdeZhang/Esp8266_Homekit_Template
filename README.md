# Esp8266_Homekit_Template
Template of Homekit for the Esp8266 based on Arduino

基于Esp8266的Homekit固件编写方法

## 入门知识：

### 一、名词定义

#### 1.配件（Accessories）

##### 官方文档（2.3.1）解释：

> Accessories are comprised of services and characteristics. An example of an accessory is a ceiling fan with a light and a mister that sprays cool water.

并非是指硬件，而是一个概念（一个配件在HomeApp上就是一个开关之类的）。所以可以在同一个硬件上可以配置多个配件（比方带有温度检测功能的电风扇），但是除非有特殊需求（比方带有温度检测功能的电风扇），否则一般情况下不建议将许多配件揉杂在一个硬件上。

### 2.服务（Services）

##### 官方文档（2.3.2）解释：

> Services group functionality in order to provide context. In the aforementioned example accessory there are three services: a fan service to interact with the ceiling fan, a light service to interact with the light, and a mister service to interact with the spray mister.

服务定义了一个配件的实际功能，比方同样是属于开关（Switch）类别（Category）的配件，除了具有开关的基本（必须）功能，对于电风扇而言他可以具有调速的功能，对于电灯而言他可以有调整亮度或者颜色的功能。

### 3.特征（Characteristics）

##### 官方文档（2.3.3）解释：

> A characteristic is a feature that represents data or an associated behavior of a service. The characteristic is defined by a universally unique type, and has additional properties that determine how the value of the characteristic can be accessed.

特征在固件中也可以看作是变量，不同的服务要求有不同类型的特征（变量）。



### 二、定义一个完整的配件

一个完整的配件（Accessory）由若干个服务（Service）组成，其中必须包含一个“配件信息服务”（ACCESSORY_INFORMATION）与一个主服务（Primary Service），而主服务包含了若干的特征（Characteristic），并且分为必须（required）与可选（optional）。



### 三、程序结构

完整的固件程序由三个文件构成：

#### 1.template.ino

该文件为主程序，用于发送接收处理数据、操作IO口等等。

#### 2.my_accessory.c

该文件用于定义配件的属性。

#### 3.wifi_info.h

该文件专用于保存与处理wifi连接方法。



## 模板使用方法：


 * 使用此模板的方法：
 * 1.确定你所需要的智能配件功能
 * 2.前往 https://github.com/ColdeZhang/Esp8266_Homekit_Template/blob/main/HAP-Specification-Non-Commercial-Version.pdf 在p134查找对应的服务（service）
 * 3.根据文档中服务（service）对变量（characteristic）的要求，创建变量（characteristic）