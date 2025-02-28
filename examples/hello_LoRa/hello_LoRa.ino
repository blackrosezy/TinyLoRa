// Hello LoRa - ABP TTN Packet Sender (Multi-Channel)
// Tutorial Link: https://learn.adafruit.com/the-things-network-for-feather/using-a-feather-32u4
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Copyright 2015, 2016 Ideetron B.V.
//
// Modified by Brent Rubell for Adafruit Industries, 2018
/************************** Configuration ***********************************/
#include <TinyLoRa.h>
#include <SPI.h>
#include <LoraMessage.h>

// Visit your thethingsnetwork.org device console
// to create an account, or if you need your session keys.

// Network Session Key (MSB)
uint8_t NwkSkey[16] = { 0x6B, 0x37, 0x4A, 0x7A, 0x98, 0xAD, 0x91, 0x93, 0x47, 0xE9, 0x66, 0x1A, 0xBD, 0x3F, 0x57, 0xAF };

// Application Session Key (MSB)
uint8_t AppSkey[16] = { 0x06, 0xB8, 0xFB, 0x13, 0x82, 0xD1, 0x04, 0x17, 0xE5, 0xE7, 0x15, 0x30, 0x96, 0xB0, 0xF2, 0x78 };

// Device Address (MSB)
uint8_t DevAddr[4] = { 0x26, 0x01, 0x16, 0x8C };


/************************** Example Begins Here ***********************************/
// Data Packet to Send to TTN
unsigned char loraData[11] = {"hello LoRa"};

// How many times data transfer should occur, in seconds
const unsigned int sendInterval = 8;

// Pinout for RocketScream Mini Ultra Pro with Lora
TinyLoRa lora = TinyLoRa(2, 5, 3);

// Pinout for Adafruit Feather M0 LoRa
//TinyLoRa lora = TinyLoRa(3, 8, 4);

void setup()
{
  delay(2000);
  Serial.begin(9600);
  while (! Serial);
  
  // Initialize pin LED_BUILTIN as an output
  pinMode(LED_BUILTIN, OUTPUT);
  
  // Initialize LoRa
  Serial.print("Starting LoRa...");
  // define multi-channel sending
  lora.setChannel(MULTI);
  // set datarate
  lora.setDatarate(SF9BW125);
  if(!lora.begin())
  {
    Serial.println("Failed");
    Serial.println("Check your radio");
    while(true);
  }
  Serial.println("OK");
}

void loop()
{
  LoraMessage loraMessage;
  loraMessage.addUint16(7778);
  loraMessage.addTemperature(15.43);
  Serial.println("Sending LoRa Data...");
  lora.sendData(loraMessage.getBytes(), loraMessage.getLength(), lora.frameCounter);
  Serial.print("Frame Counter: ");Serial.println(lora.frameCounter);
  lora.frameCounter++;

  // blink LED to indicate packet sent
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  
  Serial.println("delaying...");
  delay(sendInterval * 1000);
}
