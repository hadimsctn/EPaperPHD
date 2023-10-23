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

const char *ssid = "HA HUYEN";          // Enter your WiFi name
const char *password = "hopnguyen"; // Enter WiFi password
const char *mqtt_broker = "broker.emqx.io";
const char *topic = "esp32/test/hello/vietnam";
const char *mqtt_username = "emqx";
const char *mqtt_password = "public";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

#define SpaceOfLine 5;
const char MyName[] = "Nguyen Duc Tien z ts";
const char MyEmail[] = "tiennd@soict.hust.edu.vn";
const char MyHandphone[] = "Tel: 091-313-7399";
const char MyOffice[] = "Adr: B1-801, SoICT";

void HelloWorld(char *string)
{
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);

  int16_t tbx;
  int16_t tby;
  uint16_t tbw; /// Chiều dài của dòng chữ
  uint16_t tbh; /// Độ cao của dòng chữ

  // Trả về kích thước dòng chữ
  display.getTextBounds(string + String(RST), 0, 0, &tbx, &tby, &tbw, &tbh);
  // Cột bắt đầu viết chữ
  uint16_t x = 0;
  // Dòng băt đầu viết chữ
  uint16_t y = 40;
  display.setFullWindow();
  display.firstPage();
  do
  {
    /// Vẽ lại toàn bộ nền trắng
    display.fillScreen(GxEPD_WHITE);

    // Căn lề giữa
    x = ((display.width() - tbw) / 2) - tbx;
    /// Thiết lập điểm vẽ về vị trí trên trái
    display.setCursor(x, y);
    /// Hiển thị dòng chữ
    display.print(string);
    // Chuyển sang dòng tiếp theo và giãn dòng
    y = y + tbh + 2 * SpaceOfLine;

    display.setTextColor(display.epd2.hasColor ? GxEPD_RED : GxEPD_BLACK);
    // Trả về kích thước dòng chữ
    display.getTextBounds(MyEmail, 0, 0, &tbx, &tby, &tbw, &tbh);
    // Căn lề giữa
    x = ((display.width() - tbw) / 2) - tbx;
    /// Thiết lập điểm vẽ về vị trí trên trái
    display.setCursor(x, y);
    /// Hiển thị dòng chữ
    display.print(MyEmail);
    // Chuyển sang dòng tiếp theo và giãn dòng
    y = y + tbh + SpaceOfLine;

    // Trả về kích thước dòng chữ
    display.getTextBounds(MyHandphone, 0, 0, &tbx, &tby, &tbw, &tbh);
    // Căn lề trái
    x = 10;
    /// Thiết lập điểm vẽ về vị trí trên trái
    display.setCursor(x, y);
    /// Hiển thị dòng chữ
    display.print(MyHandphone);
    // Chuyển sang dòng tiếp theo và giãn dòng
    y = y + tbh + SpaceOfLine;

    // Trả về kích thước dòng chữ
    display.getTextBounds(MyOffice, 0, 0, &tbx, &tby, &tbw, &tbh);
    // Căn lề trái
    x = 10;
    /// Thiết lập điểm vẽ về vị trí trên trái
    display.setCursor(x, y);
    /// Hiển thị dòng chữ
    display.print(MyOffice);
    // Chuyển sang dòng tiếp theo và giãn dòng
    y = y + tbh + SpaceOfLine;
  } while (display.nextPage());
}

void helloFullScreenPartialMode(char *string)
{
  // Serial.println("helloFullScreenPartialMode");
  const char fullscreen[] = "full screen update";
  const char fpm[] = "fast partial mode";
  const char spm[] = "slow partial mode";
  const char npm[] = "no partial mode";
  display.setPartialWindow(0, 0, display.width(), display.height());
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  if (display.epd2.WIDTH < 104)
    display.setFont(0);
  display.setTextColor(GxEPD_BLACK);
  const char *updatemode;
  if (display.epd2.hasFastPartialUpdate)
  {
    updatemode = fpm;
  }
  else if (display.epd2.hasPartialUpdate)
  {
    updatemode = spm;
  }
  else
  {
    updatemode = npm;
  }
  // do this outside of the loop
  int16_t tbx, tby;
  uint16_t tbw, tbh;
  // center update text
  display.getTextBounds(fullscreen, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t utx = ((display.width() - tbw) / 2) - tbx;
  uint16_t uty = ((display.height() / 4)- tbh/2) - tby;
  Serial.println(tbx);
  Serial.println(tby);
  Serial.println(tbw);
  Serial.println(tbh);
  Serial.println(display.width());
  Serial.println("test1");
  // center update mode
  display.getTextBounds(updatemode, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t umx = ((display.width() - tbw) / 2) - tbx;
  uint16_t umy = ((display.height() * 3 / 4) - tbh / 2) - tby;
  Serial.println(tbx);
  Serial.println(tby);
  Serial.println(tbw);
  Serial.println(tbh);
  // center MyName
  display.getTextBounds(string, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t hwx = ((display.width() - tbw) / 2) - tbx;
  uint16_t hwy = ((display.height() - tbh) /2) - tby;
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(hwx, hwy);
    display.print(string);
    display.setCursor(utx, uty);
    display.print(fullscreen);
    display.setCursor(umx, umy);
    display.print(updatemode);
  } while (display.nextPage());
  // Serial.println("helloFullScreenPartialMode done");
}

void showPartialUpdate()
{
  // some useful background
  //HelloWorld();
  // use asymmetric values for test
  uint16_t box_x = 10;
  uint16_t box_y = 15;
  uint16_t box_w = 70;
  uint16_t box_h = 20;
  uint16_t cursor_y = box_y + box_h - 6;
  if (display.epd2.WIDTH < 104)
    cursor_y = box_y + 6;
  float value = 13.95;
  uint16_t incr = display.epd2.hasFastPartialUpdate ? 1 : 3;
  display.setFont(&FreeMonoBold9pt7b);
  if (display.epd2.WIDTH < 104)
    display.setFont(0);
  display.setTextColor(GxEPD_BLACK);
  // show where the update box is
  for (uint16_t r = 0; r < 4; r++)
  {
    display.setRotation(r);
    display.setPartialWindow(box_x, box_y, box_w, box_h);
    display.firstPage();
    do
    {
      display.fillRect(box_x, box_y, box_w, box_h, GxEPD_BLACK);
      // display.fillScreen(GxEPD_BLACK);
    } while (display.nextPage());
    delay(2000);
    display.firstPage();
    do
    {
      display.fillRect(box_x, box_y, box_w, box_h, GxEPD_WHITE);
    } while (display.nextPage());
    delay(1000);
  }
  // return;
  //  show updates in the update box
  for (uint16_t r = 0; r < 4; r++)
  {
    display.setRotation(r);
    display.setPartialWindow(box_x, box_y, box_w, box_h);
    for (uint16_t i = 1; i <= 10; i += incr)
    {
      display.firstPage();
      do
      {
        display.fillRect(box_x, box_y, box_w, box_h, GxEPD_WHITE);
        display.setCursor(box_x, cursor_y);
        display.print(value * i, 2);
      } while (display.nextPage());
      delay(500);
    }
    delay(1000);
    display.firstPage();
    do
    {
      display.fillRect(box_x, box_y, box_w, box_h, GxEPD_WHITE);
    } while (display.nextPage());
    delay(1000);
  }
}
void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  char string[length + 1];
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
    string[i] = static_cast<char>(payload[i]);
  }
  string[length] = '\0';
  HelloWorld(string);
  delay(3000);
  helloFullScreenPartialMode(string);
  Serial.println();
  Serial.println("-----------------------");
}
void setup()
{
  pinMode(8, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.begin(9600);
  delay(10000);
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
  Serial.println("HelloWorld");
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
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
  client.subscribe(topic);
  //HelloWorld();
  display.hibernate();
}

void loop()
{
  // put your main code here, to run repeatedly:
  client.loop();
}