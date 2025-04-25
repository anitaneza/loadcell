#include "configuration.h"

WiFiClient client;

const char* PARAM_INPUT_1 = "ssid";
const char* PARAM_INPUT_2 = "pass";
const char* PARAM_INPUT_3 = "ip";
const char* PARAM_INPUT_4 = "gateway";

String ssid;
String pass;
String ip;
String gateway;
String init_tare;

const char* ssidPath = "/ssid.txt";
const char* passPath = "/pass.txt";
const char* ipPath = "/ip.txt";
const char* gatewayPath = "/gateway.txt";
const char* tarePath = "/init_tare.txt";

IPAddress localIP;
IPAddress localGateway;
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);
IPAddress secondaryDNS(8, 8, 4, 4);

const char *mqtt_broker = "mqtt.tagsamurai.com";
const char *mqtt_topic = "tes/esp32/in";
const char *mqtt_sub_topic = "tes/esp32/out";
const char *mqtt_username = "johnwick";
const char *mqtt_password = "BXe0FIrgy4ZTLbSWMZkeoUiit5XrR05W2";
const int mqtt_port = 1883;

const int dout = 4;
const int sck = 2;
const int ping_button = 14;
const float calibration_factor = 455.1;

const int lcd_addr = 0x3C;
const int screen_width = 128;
const int screen_height = 64;
