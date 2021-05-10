/*
 * my_accessory.c
 * 
 * 用于定义一个配件的类型、参数等信息
 * 
 * 在一个文件中可以定义多个配件（accessory）
 * 其中每个配件（accessory）由若干个服务（service）组成
 * 服务（service）则由对应的变量（characteristic）组成
 * 
 * 注意：
 * 1.尽管此文件支持同时定义多个配件（accessory），但是为了便于管理与设置建议不要这么做
 */
#include <homekit/homekit.h>
#include <homekit/characteristics.h>

//配对成功时调用此方法
void my_accessory_identify(homekit_value_t_value){
    printf("accessory identify\n");
}

/*
 * 定义配件相关的若干个变量
 * ｜变量名｜
 * 自定义一个变量的名字
 * ｜变量类型｜
 * 每个服务（service）都有若干种类型的变量，其中分为必须（required）和可选（optional）两种
 * 具体的变量类型以及是否必须可在下面的链接中查看（p158）
 * https://github.com/ColdeZhang/Esp8266_Homekit_Template/blob/main/HAP-Specification-Non-Commercial-Version.pdf
 * 如：ON
 * ｜初始值｜
 * 对应变量类型的说明赋予其一个初始值
*/
homrkit_characteristic_t /*变量名*/ = HOMEKIT_CHARACTERISTIC_(/*变量类型*/,/*变量初始值*/);

/*
 * 定义配件们的属性
 * 存储在accessories[]中
*/
homekit_accessory_t *accessories[] = {
    /*
     * 定义第一个配件的属性
     * ｜编号｜从1开始，每个配件需要一个单独的编号
     * 如：1
     * ｜种类｜即配件所属的类别可在如下链接的文件中查看（p252）
     * https://github.com/ColdeZhang/Esp8266_Homekit_Template/blob/main/HAP-Specification-Non-Commercial-Version.pdf
     * 如：homekit_accessory_category_switch
     * 
     * 注意：种类需要使用大写字母，空格使用下划线（_）代替
    */
    HOMEKIT_ACCESSORY(.id=/*编号*/, .category=homekit_accessory_category_/*种类*/, .services=(homekit_service_t*[]) {
        /*
         * 配件基本信息定义
         * 从上到下依次为：
         * ｜配件名称｜引号内可以随便写，但是同一个局域网内不能出现同样名字的配件
         * ｜制造商名｜引号内可以随便写
         * ｜序列号码｜引号内可以随便写
         * ｜硬件型号｜引号内可以随便写
         * ｜固件版本｜引号内可以随便写
        */
        HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "未命名配件"),
            HOMEKIT_CHARACTERISTIC(MANUFACTURER, "Arduino HomeKit"),
            HOMEKIT_CHARACTERISTIC(SERIAL_NUMBER, "0123456"),
            HOMEKIT_CHARACTERISTIC(MODEL, "ESP8266/ESP32"),
            HOMEKIT_CHARACTERISTIC(FIRMWARE_REVISION, "1.0"),
            HOMEKIT_CHARACTERISTIC(IDENTIFY, my_accessory_identify),
            NULL
        }),
        /*
         * 定义配件的服务
         * ｜服务名｜可在下面链接的文件中查看（p134）
         * https://github.com/ColdeZhang/Esp8266_Homekit_Template/blob/main/HAP-Specification-Non-Commercial-Version.pdf
         * 如：SWITCH
         * ｜是否为主服务｜每个配件除信息服务外有且仅有一个主服务，如果是主服务则填写true，否则可不填（删除.primmary）
         * 如：true
         * 
         * 注意：服务的变量名前需要加&
        */
        HOMEKIT_SERVICE(/*服务名*/, .primary=/*是否为主服务*/, .characteristics=(homekit_characteristic_t*[]) {
            &/*变量名*/,
            NULL
        }),
        NULL
    }),
    NULL
};

/*
 * 将上述设置打包成config方便在主函数中调用
 * .password 为连接设备时需要输入的配对码，可随便填写
 * 
 * 注意：配对码必须为八位数
*/
homekit_server_config_t config = {
		.accessories = accessories,
		.password = "111-11-111"
};
