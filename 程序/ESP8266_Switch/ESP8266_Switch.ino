#define BLINKER_WIFI 
#define BLINKER_PRINT Serial
#define BLINKER_ALIGENIE_LIGHT
#define BLINKER_MIOT_OUTLET

#include <Blinker.h>

char auth[] = "你的APP的设备密钥";
char ssid[] = "你的WIFI名称";
char pswd[] = "你的WIFI密码";

BlinkerButton Button1("k123");  //绑定按键，APP上按键的数据键名
BlinkerText Text1("t123");  //绑定文字组件，APP上按键的数据键名

#define int1  0

bool oState = false;

void setup()
{
    Serial.begin(115200);
    BLINKER_DEBUG.stream(Serial);
    BLINKER_DEBUG.debugAll();
    pinMode(int1, OUTPUT);
    digitalWrite(int1, LOW);

    Blinker.begin(auth, ssid, pswd);
    Button1.attach(button1_callback);
    BlinkerAliGenie.attachPowerState(aligeniePowerState);
    BlinkerAliGenie.attachQuery(aligenieQuery);
    BlinkerMIOT.attachPowerState(miotPowerState);
    BlinkerMIOT.attachQuery(miotQuery);
}

void loop()
{
    Blinker.run();
}

void button1_callback(const String & state) //向上
{
   BLINKER_LOG("get button state: ", state);
   if (state == BLINKER_CMD_ON) 
   {
    digitalWrite(int1,LOW); 
    Text1.print("已开");
    Button1.color("#00FF00");
    Button1.text("ON");
    Button1.print("on");
    oState = true;
   }
  else if (state == BLINKER_CMD_OFF) 
  {
    digitalWrite(int1,HIGH); 
    Text1.print("已关");
    Button1.color("#FF0000");
    Button1.text("OFF");
    Button1.print("off");
    oState = false;
  }
}

void aligeniePowerState(const String & state)
{
    BLINKER_LOG("need set power state: ", state);

    if (state == BLINKER_CMD_ON) 
    {
        digitalWrite(int1, LOW);
        Text1.print("已开");
        Button1.color("#00FF00");
        Button1.text("ON");
        Button1.print("on");
        BlinkerAliGenie.powerState("on");
        BlinkerAliGenie.print();
        oState = true;
    }
    else if (state == BLINKER_CMD_OFF) 
    {
        digitalWrite(int1, HIGH);
        Text1.print("已关");
        Button1.color("#FF0000");
        Button1.text("OFF");
        Button1.print("off");
        BlinkerAliGenie.powerState("off");
        BlinkerAliGenie.print();
        oState = false;
    }
}

void aligenieQuery(int32_t queryCode)
{
    BLINKER_LOG("AliGenie Query codes: ", queryCode);

    switch (queryCode)
    {
        case BLINKER_CMD_QUERY_ALL_NUMBER :
            BLINKER_LOG("AliGenie Query All");
            BlinkerAliGenie.powerState(oState ? "on" : "off");
            BlinkerAliGenie.print();
            break;
        case BLINKER_CMD_QUERY_POWERSTATE_NUMBER :
            BLINKER_LOG("AliGenie Query Power State");
            BlinkerAliGenie.powerState(oState ? "on" : "off");
            BlinkerAliGenie.print();
            break;
        default :
            BlinkerAliGenie.powerState(oState ? "on" : "off");
            BlinkerAliGenie.print();
            break;
    }
}

void miotPowerState(const String & state)
{
    BLINKER_LOG("need set power state: ", state);

    if (state == BLINKER_CMD_ON) 
    {
        digitalWrite(int1, LOW);
        Text1.print("已开");
        Button1.color("#00FF00");
        Button1.text("ON");
        Button1.print("on");
        BlinkerMIOT.powerState("on");
        BlinkerMIOT.print();
        oState = true;
    }
    else if (state == BLINKER_CMD_OFF) 
    {
        digitalWrite(int1, HIGH);
        Text1.print("已关");
        Button1.color("#FF0000");
        Button1.text("OFF");
        Button1.print("off");
        BlinkerMIOT.powerState("off");
        BlinkerMIOT.print();
        oState = false;
    }
}

void miotQuery(int32_t queryCode)
{
    BLINKER_LOG("AliGenie Query codes: ", queryCode);

    switch (queryCode)
    {
        case BLINKER_CMD_QUERY_ALL_NUMBER :
            BLINKER_LOG("AliGenie Query All");
            BlinkerMIOT.powerState(oState ? "on" : "off");
            BlinkerMIOT.print();
            break;
        case BLINKER_CMD_QUERY_POWERSTATE_NUMBER :
            BLINKER_LOG("AliGenie Query Power State");
            BlinkerMIOT.powerState(oState ? "on" : "off");
            BlinkerMIOT.print();
            break;
        default :
            BlinkerMIOT.powerState(oState ? "on" : "off");
            BlinkerMIOT.print();
            break;
    }
}
