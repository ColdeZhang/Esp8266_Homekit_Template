/*
 * my_accessory.c
 * 
 * 用于定义一个配件的类型、参数等信息
 */
#include <homeKit-ESP8266/homekit.h>
#include <HomeKit-ESP8266/characteristics.h>

//配对成功时调用此方法
void my_accessory_identify(homekit_value_t_value){
    printf("accessory identify\n");
}

//定义配件相关的变量 ｜ 变量名自定义 ｜ ｜ 变量类型可在 ｜
homrkit_characteristic_t /*变量名*/ = HOMEKIT_CHARACTERISTIC_(/*变量类型*/,/*变量初始值*/);