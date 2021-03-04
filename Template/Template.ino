#include <arduino_homekit_server.h>;
	
//access the config defined in C code
extern "C" homekit_server_config_t config; 
	
void setup() {
	WiFi.begin(ssid, password);
	arduino_homekit_setup(&config);
}
	
void loop() {
	arduino_homekit_loop();
}