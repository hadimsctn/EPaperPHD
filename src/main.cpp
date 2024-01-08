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
#include <ArduinoJson.h>
#include <update.h>

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

const char *ssid = "Bún đậu";          // Enter your WiFi name
const char *password = "phaicomamtom"; // Enter WiFi password
const char *mqtt_broker = "0.tcp.ap.ngrok.io";
const char *topicGetDefaultData = "EpaperPHD/UpdateAll";
const char *topicImage = "EpaperPHD/UpdateImage";
const char *topicMajor = "EpaperPHD/UpdateMajor";
const char *topicClass = "EpaperPHD/UpdateClass";
const char *topicName = "EpaperPHD/UpdateName";
const char *topicDateOfBirth = "EpaperPHD/UpdateDateOfBirth";
const char *mqtt_username = "nguyenha";
const char *mqtt_password = "12345678";
const int mqtt_port = 15354;

WiFiClient espClient;
PubSubClient client(espClient);

const char *studentInformation = "STUDENT INFORMATION";
String nameDefault = "Full Name";
String majorDefault = "Major";
String dateOfBirthDefault = "Date of Birth";
String classDefault = "Major code";
unsigned char imageInformationDefault[863] = {};

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
  uint16_t x = 74;
  uint16_t y = 123;
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.fillRect(0, 32, 72, 96, GxEPD_BLACK);
    display.drawBitmap(0, 32, imageInformationDefault, 72, 96, GxEPD_WHITE);
    display.getTextBounds(studentInformation, 0, 0, &tbx, &tby, &tbw, &tbh);
    uint16_t six = ((display.width() - tbw) / 2) - tbx;
    display.setCursor(six, 15);
    display.print(studentInformation);
    display.setCursor(x, y);
    display.print(classDefault);
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
  Serial.println("Start update Name");
  nameDefault = name;
  myInfo();
}

void updateImage(unsigned char *image)
{
  Serial.println("Update image");
  memcpy(imageInformationDefault, image, sizeof(imageInformationDefault));
  myInfo();
}

void updateDateOfBirth(String dateOfBirth)
{
  dateOfBirthDefault = dateOfBirth;
  myInfo();
}

void updateClass(String Class)
{
  Serial.println("Start update class");
  classDefault = Class;
  myInfo();
}
void updateMajor(String major)
{
  Serial.println("Start update class");
  majorDefault = major;
  myInfo();
}

void parseJsonPayloadUpdateName(String jsonStr)
{
  DynamicJsonDocument doc(8192); // Kích thước đối tượng JSON tương ứng với payload

  // Phân tích chuỗi JSON
  deserializeJson(doc, jsonStr);

  // Trích xuất giá trị từ các trường JSON
  const char *idDevice = doc["IdDevice"];

  // Xử lý dữ liệu
  JsonArray idDeviceArray = doc["IdDevice"];
  for (const auto &value : idDeviceArray)
  {
    if (value == "string")
    {
      const char *name = doc["Name"];
      updateName(String(name));
      break; // Nếu đã tìm thấy giá trị "string", thoát khỏi vòng lặp
    }
  }
}

void parseJsonPayloadUpdateDateOfBirth(String jsonStr)
{
  DynamicJsonDocument doc(8192); // Kích thước đối tượng JSON tương ứng với payload

  // Phân tích chuỗi JSON
  deserializeJson(doc, jsonStr);

  // Trích xuất giá trị từ các trường JSON
  const char *idDevice = doc["IdDevice"];

  // Xử lý dữ liệu
  JsonArray idDeviceArray = doc["IdDevice"];
  for (const auto &value : idDeviceArray)
  {
    if (value == "string")
    {
      const char *dateOfBirth = doc["DateOfBirth"];
      updateDateOfBirth(String(dateOfBirth));
      break; // Nếu đã tìm thấy giá trị "string", thoát khỏi vòng lặp
    }
  }
}

void parseJsonPayloadUpdateClass(String jsonStr)
{
  DynamicJsonDocument doc(8192); // Kích thước đối tượng JSON tương ứng với payload

  // Phân tích chuỗi JSON
  deserializeJson(doc, jsonStr);

  // Trích xuất giá trị từ các trường JSON
  const char *idDevice = doc["IdDevice"];

  // Xử lý dữ liệu
  JsonArray idDeviceArray = doc["IdDevice"];
  for (const auto &value : idDeviceArray)
  {
    if (value == "string")
    {
      const char *Class = doc["Class"];
      updateClass(String(Class));
      break; // Nếu đã tìm thấy giá trị "string", thoát khỏi vòng lặp
    }
  }
}

void parseJsonPayloadUpdateMajor(String jsonStr)
{
  DynamicJsonDocument doc(8192); // Kích thước đối tượng JSON tương ứng với payload

  Serial.println(jsonStr);
  // Phân tích chuỗi JSON
  deserializeJson(doc, jsonStr);

  // Trích xuất giá trị từ các trường JSON
  const char *idDevice = doc["IdDevice"];

  // Xử lý dữ liệu
  JsonArray idDeviceArray = doc["IdDevice"];
  for (const auto &value : idDeviceArray)
  {
    if (value == "string")
    {
      const char *major = doc["Major"];
      updateMajor(String(major));
      break; // Nếu đã tìm thấy giá trị "string", thoát khỏi vòng lặp
    }
  }
}
void parseJsonPayloadUpdateImage(String jsonStr){
  DynamicJsonDocument doc(8192); // Kích thước đối tượng JSON tương ứng với payload

  Serial.println(jsonStr);
  // Phân tích chuỗi JSON
  deserializeJson(doc, jsonStr);

  // Trích xuất giá trị từ các trường JSON
  const char *idDevice = doc["IdDevice"];

  // Xử lý dữ liệu
  JsonArray idDeviceArray = doc["IdDevice"];
  for (const auto &value : idDeviceArray)
  {
    if (value == "string")
    {
      const char *major = doc["Major"];
      updateMajor(String(major));
      break; // Nếu đã tìm thấy giá trị "string", thoát khỏi vòng lặp
    }
  }
}

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  if (strcmp(topic, topicDateOfBirth) == 0)
  {
    payload[length] = '\0';
    String jsonStr = String((char *)payload);
    parseJsonPayloadUpdateDateOfBirth(jsonStr);
  }
  if (strcmp(topic, topicName) == 0)
  {
    payload[length] = '\0';
    String jsonStr = String((char *)payload);
    parseJsonPayloadUpdateName(jsonStr);
  }
  if (strcmp(topic, topicClass) == 0)
  {
    payload[length] = '\0';
    String jsonStr = String((char *)payload);
    parseJsonPayloadUpdateClass(jsonStr);
  }
  if (strcmp(topic, topicMajor) == 0)
  {
    payload[length] = '\0';
    String jsonStr = String((char *)payload);
    parseJsonPayloadUpdateMajor(jsonStr);
  }
  if (strcmp(topic, topicImage) == 0)
  {
    payload[length] = '\0';
    String jsonStr = String((char *)payload);
    DynamicJsonDocument doc(8192); // Kích thước đối tượng JSON tương ứng với payload
    // Phân tích chuỗi JSON
    deserializeJson(doc, jsonStr);

    // Trích xuất giá trị từ các trường JSON
    const char *idDevice = doc["IdDevice"];

    // Xử lý dữ liệu
    JsonArray idDeviceArray = doc["IdDevice"];
    for (const auto &value : idDeviceArray)
    {
      if (value == "string")
      {
        int lengthImage = doc["ImageLength"];
        Serial.println(lengthImage);
        unsigned char image[lengthImage];
        for (int i = 0; i < lengthImage; i++)
        {
          image[lengthImage-1-i] = static_cast<unsigned char>(payload[length-1-i]);
        }
        updateImage(image);
        break; // Nếu đã tìm thấy giá trị "string", thoát khỏi vòng lặp
      }
    }
    // unsigned char image[length + 1];
    // for (int i = 0; i < length; i++)
    // {
    //   Serial.print(static_cast<unsigned char>(payload[i]));
    //   Serial.print(",");
    //   image[i] = static_cast<unsigned char>(payload[i]);
    // }
    // updateImage(image);
  }
  if (strcmp(topic, topicGetDefaultData) == 0)
  {
    String name = "";
    for (int i = 0; i < length; i++)
    {
      name = name + (char)payload[i];
    }
  }
  if (strcmp(topic, "EpaperPHD/UpdateImage1") == 0)
  {
    unsigned char image[length + 1];
    for (int i = 0; i < length; i++)
    {
      Serial.println(length);
      image[i] = static_cast<unsigned char>(payload[i]);
    }
    updateImage(image);
  }
  Serial.println();
  Serial.println("-----------------------");
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
  client.setBufferSize(4096);
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
  client.subscribe(topicGetDefaultData);
  client.subscribe(topicDateOfBirth);
  client.subscribe(topicName);
  client.subscribe(topicImage);
  client.subscribe(topicMajor);
  client.subscribe(topicClass);
  client.publish(topicGetDefaultData, "Dcm cuoc doi");
  Serial.println(client.getBufferSize());
  display.hibernate();
}

void loop()
{
  client.loop();
}