#include <Arduino.h>
// -----------------------------------------------------------------------------------------------------------------------------
// Dependencies: GxEPD2 của
// Tested:  ESP32-C3 DevKitM-1 dual USB, ESP32-C3 SuperMini
// Result: https://youtu.be/yVmRT403PUM, https://youtu.be/R4bcl01nT94
// Display:
//      -------x----->
//      | ---------------------------------------------------------------------------
//      | |                                                                         |
//      y |                                                                         |
//      | |                                                                         |
//      - |                                                                         |
//        |                                                                         |
//        |                                                                         |
//        |                                                                         |
//        |                                                                         |
//        ---------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
// base class GxEPD2_GFX can be used to pass references or pointers to the display instance as parameter, uses ~1.2k more code
// enable or disable GxEPD2_GFX base class
#define ENABLE_GxEPD2_GFX 0

#include <GxEPD2_BW.h>
// #include <GxEPD2_3C.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <WiFi.h>
#include <PubSubClient.h>

// #define ESP32_C3
#define ESP32_C3_SUPERMINI

#if defined(ESP32_C3)
// #define Porting_Sample
#define Porting_Continous
#if defined(Porting_Sample)
// Cắm y hệt như code mẫu. Như video https://youtu.be/yVmRT403PUM
// ESP32-C3 SS=7,SCL(SCK)=4,SDA(MOSI)=6,BUSY=3,RST=2,DC=1
#define SS 7
#define SCL 4 // SCK
#define SDA 6 // MOSI
#define BUSY 3
#define RST 2
#define DC 1
#elif defined(Porting_Continous)
#define BUSY 2 // configuable test ok: pin 2, 3
#define RST 3  // configuable test ok: pin 0, 2, 3
#define DC 21  // configuable test ok: pin 1, 5, 7, 8 10, 18, 19, 20, 21 Not ok: 9
#define SS 1   // CS         //configuable test ok: pin 0, 1, 2, 3, 7, 8, 10, 18, 19, 20 (la rx0 nen phai rut ra khi nap code), 21. Not ok: 5, 9,11
#define SCL 4  // SCK       //configuable test ok: pin 4. Not ok 0, 5, 7
#define SDA 6  // MOSI
#endif
#elif defined(ESP32_C3_SUPERMINI)
// https://youtu.be/R4bcl01nT94
#define LED_BUILTIN 8
#define SCL 4 // SCK
#define SDA 6 // MOSI

#define SS 7
#define BUSY 3
#define RST 2
#define DC 1
#endif

// 2.13'' EPD Module
// GxEPD2_BW<GxEPD2_213_BN, GxEPD2_213_BN::HEIGHT> display(GxEPD2_213_BN(/*CS=5*/ SS, /*DC=*/ 1, /*RST=*/ 2, /*BUSY=*/ 3)); // DEPG0213BN 122x250, SSD1680
// GxEPD2_3C<GxEPD2_213_Z98c, GxEPD2_213_Z98c::HEIGHT> display(GxEPD2_213_Z98c(/*CS=5*/ SS, /*DC=*/ 1, /*RST=*/ 2, /*BUSY=*/ 3)); // GDEY0213Z98 122x250, SSD1680

// 2.9'' EPD Module
GxEPD2_BW<GxEPD2_290_BS, GxEPD2_290_BS::HEIGHT> display(GxEPD2_290_BS(SS, DC, RST, BUSY)); // DEPG0290BS 128x296, SSD1680
// GxEPD2_3C<GxEPD2_290_C90c, GxEPD2_290_C90c::HEIGHT> display(GxEPD2_290_C90c(/*CS=5*/ SS, /*DC=*/ 1, /*RST=*/ 2, /*BUSY=*/ 3)); // GDEM029C90 128x296, SSD1680

const char *ssid = "Trangbeo";          // Enter your WiFi name
const char *password = "ngocctrang99@"; // Enter WiFi password
const char *mqtt_broker = "broker.hivemq.com";
const char *topicImage = "esp32/test/hello/vietnamhaha/image";
const char *topicMajor = "esp32/test/hello/vietnamhaha/Class";
const char *topicMajor1 = "";
const char *topicName = "";
const char *topicDateOfBirth = "esp32/test/hello/vietnamhaha/dateofbirth";
const char *mqtt_username = "emqx";
const char *mqtt_password = "public";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

const char *studentInformation = "STUDENT INFORMATION";
String nameDefault = "Full Name";
String majorDefault = "Major";
String dateOfBirthDefault = "Date of Birth";
String major1Default = "Major code";
unsigned char imageInformationDefault[] = {
    0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
    0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
    0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
    0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
    0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
    0x55, 0xb5, 0xb5, 0xb5, 0xb5, 0xb5, 0xb5, 0xb5, 0xb5,
    0xad, 0x56, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
    0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
    0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
    0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
    0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
    0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
    0xb6, 0xaa, 0xab, 0x6a, 0xab, 0x6b, 0x6b, 0x6b, 0x6a,
    0x55, 0x55, 0x55, 0x54, 0x04, 0x2d, 0x55, 0x55, 0x55,
    0xaa, 0xad, 0x6a, 0xa0, 0x20, 0x12, 0xaa, 0xaa, 0xaa,
    0x55, 0x55, 0x55, 0x40, 0x80, 0x45, 0x55, 0x55, 0x55,
    0xaa, 0xaa, 0xaa, 0x00, 0x00, 0x01, 0x55, 0x55, 0x56,
    0x55, 0x55, 0x54, 0x00, 0x00, 0x00, 0x55, 0x55, 0x55,
    0xaa, 0xb5, 0x50, 0x00, 0x00, 0x00, 0x2a, 0xaa, 0xaa,
    0x55, 0x55, 0xa0, 0x02, 0x00, 0x00, 0x15, 0xb5, 0xb5,
    0xad, 0xaa, 0xa8, 0x10, 0x11, 0x04, 0x2a, 0xaa, 0xaa,
    0x55, 0x55, 0x40, 0x80, 0x40, 0x10, 0x0d, 0x55, 0x55,
    0xaa, 0xaa, 0xa0, 0x15, 0x25, 0x40, 0x15, 0x55, 0x55,
    0x55, 0x55, 0x50, 0xab, 0xdd, 0x5d, 0x15, 0x55, 0x55,
    0xaa, 0xaa, 0xa2, 0xb6, 0xf7, 0xea, 0x0a, 0xaa, 0xaa,
    0x55, 0x55, 0x51, 0x6f, 0xbe, 0xba, 0x95, 0x55, 0x55,
    0xb6, 0xad, 0xa5, 0xbb, 0xf7, 0xed, 0x4a, 0xab, 0x6a,
    0x55, 0x55, 0x52, 0xde, 0xdf, 0x77, 0x15, 0x55, 0x55,
    0xaa, 0xaa, 0xa5, 0x6f, 0xfd, 0xdd, 0xaa, 0xb5, 0x56,
    0x55, 0x55, 0x56, 0xfb, 0x77, 0xea, 0x95, 0x55, 0x55,
    0xaa, 0xaa, 0xab, 0x4d, 0xff, 0x15, 0x55, 0xaa, 0xaa,
    0x55, 0x5a, 0xa5, 0x6a, 0xdd, 0xed, 0xaa, 0xaa, 0xaa,
    0xaa, 0xaa, 0xad, 0xbf, 0x77, 0x7a, 0xaa, 0xaa, 0xd5,
    0x55, 0x6a, 0xa6, 0xd5, 0xfd, 0xaf, 0x55, 0x55, 0x55,
    0xad, 0x95, 0x6b, 0x6a, 0xae, 0x81, 0xaa, 0xaa, 0xaa,
    0x55, 0x6a, 0xb5, 0x93, 0xfb, 0xfe, 0xda, 0xad, 0x55,
    0xaa, 0x95, 0x6e, 0xfd, 0xbe, 0xab, 0x5d, 0x55, 0x56,
    0x55, 0x6a, 0xb5, 0xaf, 0xd7, 0xff, 0xaa, 0xaa, 0xaa,
    0xaa, 0xab, 0x77, 0xfd, 0xbd, 0xda, 0xd5, 0x6a, 0xb5,
    0x55, 0x55, 0x55, 0x77, 0xf6, 0xff, 0xba, 0xaa, 0xca,
    0xb6, 0xaa, 0xbb, 0xdf, 0x5f, 0xbe, 0xd5, 0x55, 0x55,
    0x55, 0x55, 0x5d, 0xff, 0xfa, 0xf7, 0x55, 0x55, 0x5a,
    0xaa, 0xaa, 0xab, 0x7d, 0x5f, 0x7d, 0xaa, 0xaa, 0xaa,
    0x55, 0x55, 0x55, 0xdf, 0xe9, 0xdf, 0x55, 0x55, 0x55,
    0xaa, 0xab, 0x56, 0xf6, 0xbe, 0xf5, 0xab, 0x6b, 0x55,
    0x55, 0x5a, 0xab, 0x5f, 0xeb, 0x6e, 0xd5, 0x55, 0x55,
    0xaa, 0xaa, 0xb5, 0xfa, 0xbf, 0xbb, 0x5a, 0xaa, 0xaa,
    0x55, 0x55, 0x56, 0xaf, 0xd4, 0xed, 0xaa, 0xaa, 0xad,
    0xad, 0xaa, 0xaa, 0xfa, 0xbb, 0x3a, 0xaa, 0xaa, 0xb2,
    0x55, 0x55, 0x55, 0xaf, 0x6e, 0xef, 0x55, 0x55, 0x55,
    0xaa, 0xaa, 0xaa, 0xfb, 0x5a, 0xb5, 0x55, 0x56, 0xaa,
    0x55, 0x55, 0x55, 0x57, 0xeb, 0xea, 0xaa, 0xaa, 0xab,
    0xaa, 0xab, 0x6a, 0xba, 0xbf, 0x75, 0x55, 0x55, 0x54,
    0x55, 0x55, 0x55, 0xd7, 0xfd, 0xad, 0xaa, 0xda, 0xab,
    0xb6, 0xaa, 0xab, 0x6d, 0x6f, 0xd5, 0x56, 0xaa, 0xb5,
    0x55, 0x5a, 0xab, 0x5b, 0xb5, 0x5a, 0xda, 0xaa, 0xd5,
    0xaa, 0xaa, 0xaf, 0x6d, 0xdd, 0x6d, 0xea, 0xaa, 0xaa,
    0x55, 0x55, 0x7f, 0x5e, 0xb6, 0xb5, 0xfd, 0x55, 0x55,
    0xaa, 0xab, 0xbd, 0x77, 0x6d, 0xdd, 0xff, 0xaa, 0xaa,
    0x55, 0x55, 0xff, 0xbb, 0xfb, 0x77, 0xbf, 0xf5, 0x55,
    0xaa, 0xbf, 0xff, 0xde, 0xaf, 0xdb, 0xff, 0xfe, 0xaa,
    0x55, 0x6f, 0xf7, 0xb7, 0xfa, 0xfd, 0xef, 0xff, 0x55,
    0xad, 0xff, 0xff, 0xfd, 0xbf, 0xab, 0xfe, 0xdd, 0xea,
    0x57, 0xff, 0xdf, 0xef, 0xeb, 0xff, 0xff, 0xff, 0xfb,
    0xbb, 0xfd, 0xff, 0xfa, 0xbe, 0xaf, 0xff, 0xff, 0xfd,
    0x6f, 0xbf, 0xff, 0xff, 0xfb, 0xff, 0xdf, 0xff, 0xfe,
    0xbf, 0xff, 0xff, 0xef, 0xef, 0xff, 0xfd, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xbd, 0xbf, 0x6f, 0x7f, 0xff, 0xef,
    0xff, 0xff, 0xfe, 0xff, 0xfd, 0xff, 0xff, 0xfb, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xf7, 0xff, 0xef, 0xff, 0xff,
    0xff, 0xee, 0xff, 0xff, 0xdf, 0xff, 0xff, 0x7f, 0xff,
    0xff, 0xff, 0xf7, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xdf,
    0xff, 0xff, 0xff, 0xff, 0xf7, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0x7f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef, 0xff,
    0xff, 0xff, 0x7f, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xf7,
    0xfd, 0xff, 0xff, 0x7f, 0xff, 0xf7, 0xff, 0xff, 0xdf,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0xff, 0xfe, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xfe, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xf7, 0xff, 0xff, 0xfb, 0xdf,
    0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0x7f, 0xff, 0xff, 0x7f, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff,
    0xff, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f,
    0xff, 0xf7, 0xff, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xfd, 0xff,
    0xff, 0xff, 0xef, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

unsigned char imageInformationAyaka[] = {
    0xff, 0xff, 0xff, 0xaf, 0xff, 0xf5, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xd7, 0xff, 0xd3, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xeb, 0xff, 0xf7, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xcf, 0xdb, 0xd7, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xef, 0xeb, 0xad, 0xe7, 0xed, 0xff, 0xff,
    0xff, 0xff, 0x55, 0xe5, 0x56, 0xae, 0xb2, 0xff, 0xff,
    0xff, 0xff, 0x85, 0x7a, 0x38, 0x56, 0xc5, 0xff, 0xff,
    0xff, 0xfe, 0x90, 0x93, 0xdf, 0x99, 0x10, 0xff, 0xff,
    0xff, 0xff, 0x24, 0x0f, 0xff, 0xf0, 0x92, 0x7f, 0xff,
    0xff, 0xfd, 0x12, 0xbf, 0xff, 0xfe, 0x24, 0x7f, 0xff,
    0xff, 0xfe, 0x44, 0xff, 0xff, 0xff, 0x11, 0x5f, 0xff,
    0xff, 0xf9, 0x61, 0xff, 0xfe, 0xff, 0xc6, 0x9f, 0xff,
    0xff, 0xf8, 0x1b, 0xff, 0xdf, 0xff, 0xe8, 0x2f, 0xff,
    0xff, 0xf1, 0x47, 0xff, 0xff, 0xff, 0xf2, 0x8f, 0xff,
    0xff, 0xfc, 0x1f, 0xff, 0x7f, 0xff, 0xf0, 0x5f, 0xff,
    0xff, 0xff, 0xcf, 0xff, 0xff, 0xbf, 0xfb, 0xff, 0xff,
    0xff, 0xfb, 0x7f, 0xfb, 0xfe, 0xfb, 0xbe, 0xbf, 0xff,
    0xff, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xdf, 0xff,
    0xff, 0xff, 0xff, 0xdf, 0xf7, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xdf, 0xef, 0xfe, 0xff, 0xff,
    0xff, 0xff, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0x77, 0xff, 0xff,
    0xff, 0xfe, 0xfb, 0xde, 0xff, 0xef, 0xff, 0x7f, 0xff,
    0xff, 0xff, 0xef, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xdf, 0xef, 0xdf, 0xb7, 0xbf, 0xff,
    0xff, 0xfd, 0xdf, 0xff, 0xfe, 0xee, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xfb, 0xdd, 0xdf, 0xf7, 0xb7, 0xbf, 0xff,
    0xff, 0xfd, 0xdf, 0x7f, 0xef, 0xaf, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xfb, 0xdf, 0xfe, 0xff, 0x5f, 0xbf, 0xff,
    0xff, 0xfd, 0xdb, 0xef, 0xcf, 0xdf, 0xbb, 0xdf, 0xff,
    0xff, 0xff, 0xff, 0xdf, 0x7f, 0x76, 0xff, 0xff, 0xff,
    0xff, 0xfb, 0xab, 0xbf, 0xee, 0xdf, 0x77, 0xbf, 0xff,
    0xff, 0xfe, 0xfd, 0xef, 0xdf, 0xbf, 0xbb, 0xdf, 0xff,
    0xff, 0xfd, 0xd7, 0xbe, 0xee, 0xee, 0xf7, 0xff, 0xff,
    0xff, 0xff, 0xdd, 0xd7, 0xdb, 0x5f, 0x3f, 0xdf, 0xff,
    0xff, 0xfa, 0xf6, 0xfe, 0xff, 0xfa, 0xf7, 0x7f, 0xff,
    0xff, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xf7, 0xdf, 0xff,
    0xff, 0xfd, 0x6f, 0x6f, 0xff, 0xf7, 0xff, 0xbf, 0xff,
    0xff, 0xfd, 0x7a, 0x87, 0xff, 0x40, 0x6a, 0x7f, 0xff,
    0xff, 0xfd, 0xac, 0x01, 0xfd, 0xc0, 0x1d, 0xbf, 0xff,
    0xff, 0xfe, 0xb1, 0x35, 0xef, 0xd6, 0xab, 0xbf, 0xff,
    0xff, 0xfc, 0xab, 0x17, 0xff, 0xe2, 0xda, 0x7f, 0xff,
    0xff, 0xfe, 0xbd, 0x4b, 0xff, 0xaa, 0xbd, 0x5f, 0xff,
    0xff, 0xfd, 0x5f, 0xf7, 0xff, 0xf6, 0xf5, 0x7f, 0xff,
    0xff, 0xfd, 0x2f, 0x7f, 0xff, 0xff, 0xf4, 0x9f, 0xff,
    0xff, 0xfd, 0xb7, 0xdf, 0xdf, 0xf7, 0xb6, 0xff, 0xff,
    0xff, 0xfd, 0x2f, 0xff, 0xff, 0xfe, 0xf4, 0x9f, 0xff,
    0xff, 0xfd, 0x17, 0xff, 0xff, 0x7f, 0xf5, 0x7f, 0xff,
    0xff, 0xff, 0x56, 0xfd, 0xff, 0xff, 0xd4, 0xff, 0xff,
    0xff, 0xfe, 0x73, 0xef, 0xff, 0xf7, 0xde, 0xbf, 0xff,
    0xff, 0xfe, 0xbd, 0xff, 0xfb, 0xff, 0xae, 0xff, 0xff,
    0xff, 0xfd, 0x77, 0xff, 0xef, 0xff, 0xbe, 0xbf, 0xff,
    0xff, 0xfe, 0xfa, 0xff, 0xff, 0xff, 0x6d, 0x7f, 0xff,
    0xff, 0xfd, 0x7b, 0x7f, 0xbf, 0xee, 0xbe, 0xbf, 0xff,
    0xff, 0xfd, 0xbd, 0x3e, 0xff, 0xbc, 0x5e, 0xbf, 0xff,
    0xff, 0xfd, 0x7c, 0x1f, 0xfe, 0xf8, 0x5e, 0xdf, 0xff,
    0xff, 0xfb, 0xbc, 0x87, 0xff, 0xf0, 0x9b, 0xbf, 0xff,
    0xff, 0xfa, 0xfc, 0x01, 0xff, 0xc0, 0x3e, 0xcf, 0xff,
    0xff, 0xfb, 0x5d, 0x22, 0xfe, 0x82, 0xbd, 0xbf, 0xff,
    0xff, 0xfa, 0xbc, 0x41, 0x5a, 0xc0, 0x2e, 0xcf, 0xff,
    0xff, 0xfd, 0xf6, 0x03, 0xab, 0x42, 0x3b, 0x7f, 0xff,
    0xff, 0xfd, 0x00, 0xa1, 0xfd, 0x88, 0x80, 0xbf, 0xff,
    0xff, 0xfe, 0x92, 0x05, 0x26, 0xa1, 0x09, 0xdf, 0xff,
    0xff, 0xfb, 0xc4, 0x42, 0x91, 0x40, 0x43, 0x7f, 0xff,
    0xff, 0xfe, 0xa1, 0x06, 0xbd, 0x62, 0x16, 0xff, 0xff,
    0xff, 0xff, 0xf4, 0x4b, 0x4a, 0xd0, 0x8d, 0xbf, 0xff,
    0xff, 0xff, 0x58, 0x1d, 0xd7, 0x78, 0x56, 0xff, 0xff,
    0xff, 0xff, 0xe9, 0x2b, 0x6a, 0xd5, 0x1b, 0xff, 0xff,
    0xff, 0xff, 0xf4, 0xb6, 0xab, 0x6c, 0x37, 0xff, 0xff,
    0xff, 0xff, 0xa6, 0x3b, 0xed, 0xb6, 0x4b, 0xff, 0xff,
    0xff, 0xff, 0xaa, 0x55, 0x56, 0xda, 0x65, 0x7f, 0xff,
    0xff, 0xfe, 0xf3, 0x7e, 0xaa, 0xfe, 0x4f, 0xff, 0xff,
    0xff, 0xfd, 0xad, 0x7f, 0xdb, 0xfe, 0x5a, 0xbf, 0xff,
    0xff, 0xfb, 0x7a, 0x7f, 0xab, 0xdf, 0x57, 0xdf, 0xff,
    0xff, 0xf7, 0xaa, 0xff, 0xdb, 0xff, 0x36, 0xaf, 0xff,
    0xff, 0xfd, 0xb0, 0xff, 0xcb, 0xff, 0x0a, 0xf7, 0xff,
    0xff, 0xd6, 0x44, 0xfd, 0xf7, 0xff, 0x86, 0xdb, 0xff,
    0xff, 0xfb, 0x91, 0xff, 0xff, 0xff, 0x91, 0x75, 0xff,
    0xff, 0xae, 0xb1, 0xff, 0xff, 0xf7, 0x8c, 0xbf, 0xff,
    0xff, 0xf5, 0x29, 0xff, 0xff, 0xbf, 0x8d, 0xd5, 0x7f,
    0xfe, 0xbe, 0xa3, 0xd7, 0xff, 0xf7, 0xc5, 0x3e, 0xff,
    0xff, 0xd5, 0x49, 0x47, 0xbd, 0xe0, 0xc1, 0x57, 0x7f,
    0xfd, 0x7e, 0x82, 0x01, 0xff, 0x88, 0x49, 0x5b, 0xbf,
    0xfa, 0xd4, 0xd0, 0xa8, 0x55, 0x25, 0x03, 0x3d, 0x5f,
    0xfb, 0x7e, 0x42, 0x04, 0x00, 0x50, 0x49, 0x6e, 0xaf,
    0xed, 0x2a, 0xa1, 0x52, 0xaa, 0x8a, 0x82, 0x34, 0x67,
    0xea, 0x5e, 0x48, 0x00, 0x11, 0x20, 0x12, 0xfb, 0x37,
    0xd4, 0xeb, 0x62, 0x55, 0x54, 0x95, 0x26, 0x57, 0x1b,
    0xd8, 0xbb, 0xa1, 0x00, 0x95, 0x24, 0x81, 0x6e, 0x95,
    0xa9, 0xed, 0x88, 0xaa, 0x54, 0x92, 0x24, 0xdd, 0x8d,
    0x73, 0x76, 0xa2, 0x09, 0x43, 0x51, 0x13, 0x37, 0xca,
    0xa3, 0xbf, 0x44, 0x4d, 0xbd, 0x54, 0x81, 0x7d, 0x67,
    0xa6, 0xea, 0x81, 0x22, 0xa5, 0xd2, 0x24, 0xd7, 0xa2,
    0x8f, 0xbf, 0x92, 0x0a, 0xaa, 0xa8, 0x81, 0xfa, 0xf3,
    0xaa, 0xea, 0xc0, 0xa5, 0xb5, 0xa2, 0x22, 0xaf, 0xb8};

#define SpaceOfLine 11;
void myInfo()
{
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  display.setFullWindow();
  int16_t tbx;
  int16_t tby;
  uint16_t tbw;
  uint16_t tbh;
  uint16_t x = 72;
  uint16_t y = 123;
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.fillRect(0, 24, 72, 96, GxEPD_BLACK);
    display.drawBitmap(0, 24, imageInformationDefault, 72, 96, GxEPD_WHITE);
    display.getTextBounds(studentInformation, 0, 0, &tbx, &tby, &tbw, &tbh);
    uint16_t six = ((display.width() - tbw) / 2) - tbx;
    display.setCursor(six, 15);
    display.print(studentInformation);
    display.setCursor(x, y);
    display.print(major1Default);
    y = y - 15 - SpaceOfLine;
    display.setCursor(x, y);
    display.print(majorDefault);
    y = y - 15 - SpaceOfLine;
    display.setCursor(x, y);
    display.print(dateOfBirthDefault);
    y = y - 15 - SpaceOfLine;
    display.setCursor(x, y);
    display.print(nameDefault);
  } while (display.nextPage());
}

void updateName(String name)
{
  nameDefault = name;
  myInfo();
}

void updateImage(unsigned char *image)
{
  Serial.println("Update image");
  memcpy(imageInformationDefault, image, sizeof(imageInformationDefault));
  myInfo();
}

void updateDateOfBirth(char *dateOfBirth)
{
  dateOfBirthDefault = dateOfBirth;
  myInfo();
}

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  if (topic == "esp32/test/hello/vietnamhaha/image")
  {
    unsigned char image[length + 1];
    for (int i = 0; i < length; i++)
    {
      image[i] = static_cast<unsigned char>(payload[i]);
    }
  }
  char string[length + 1];

  string[length] = '\0';
  Serial.println();
  Serial.println("-----------------------");
}
void callbackImage(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived in topic: ");
  // Serial.println(topic);
  for (int i = 0; i < length; i++) {
      Serial.println(payload[i]);
  }
  Serial.println(length);
  display.drawBitmap(50,50,payload,1,1,GxEPD_BLACK,GxEPD_WHITE);
  Serial.println();
  Serial.println("-----------------------");
  //if(==="sendImage")
}
void setup()
{
  pinMode(8, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.begin(9600);

  // connecting to a WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  Serial.println("display.init");
  display.init(115200, true, 50, false);
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  client.setBufferSize(8192);
  while (!client.connected())
  {
    String client_id = "esp32-client-";
    client_id += String(WiFi.macAddress());
    Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
    if (client.connect(client_id.c_str(), mqtt_username, mqtt_password))
    {
      Serial.println("Public emqx mqtt broker connected");
    }
    else
    {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
  myInfo();
  client.subscribe(topicMajor);
  client.publish(topicMajor, "Dcm cuoc doi");
  Serial.println(client.getBufferSize());
  display.hibernate();
}

void loop()
{
  client.loop();
}