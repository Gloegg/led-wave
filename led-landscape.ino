#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

const char* ssid = "fnordeingang";
const char* password = "R112Zr11ch3353burger";

const int ESP_BUILTIN_LED = 2;


#include <FastLED.h>
#include "Utils.hpp"

#define FADE_TO_BLACK_FACTOR 50


CRGB leds[ NUM_LEDS ];

int frames = 0;
int hue = 0;

void setup()
{
  //---------------------------------------------------------
  WiFi.mode( WIFI_STA );
  WiFi.begin( ssid, password );
  while ( WiFi.waitForConnectResult() != WL_CONNECTED )
  {
    Serial.println( "Connection Failed! Rebooting..." );
    delay( 5000 );
    ESP.restart();
  }

  ArduinoOTA.onStart( []()
                      {
                        Serial.println( "Start" );
                      } );
  ArduinoOTA.onEnd( []()
                    {
                      Serial.println( "\nEnd" );
                    } );
  ArduinoOTA.onProgress( []( unsigned int progress, unsigned int total )
                         {
                           Serial.printf( "Progress: %u%%\r", ( progress / ( total / 100 ) ) );
                         } );
  ArduinoOTA.onError( []( ota_error_t error )
                      {
                        Serial.printf( "Error[%u]: ", error );
                        if ( error == OTA_AUTH_ERROR ) Serial.println( "Auth Failed" );
                        else if ( error == OTA_BEGIN_ERROR ) Serial.println( "Begin Failed" );
                        else if ( error == OTA_CONNECT_ERROR ) Serial.println( "Connect Failed" );
                        else if ( error == OTA_RECEIVE_ERROR ) Serial.println( "Receive Failed" );
                        else if ( error == OTA_END_ERROR ) Serial.println( "End Failed" );
                      } );
  ArduinoOTA.begin();
  Serial.println( "Ready" );
  Serial.print( "IP address: " );
  Serial.println( WiFi.localIP() );

  //---------------------------------------------------------

  FastLED.addLeds<NEOPIXEL, PIN_LED>( leds, NUM_LEDS );
  FastLED.setBrightness( 63 );
  randomSeed( 0 );
}

void loop()
{
  ArduinoOTA.handle();
  //---------------------------------------------------------

  FastLED.show();
  FastLED.delay( 1000 / FRAMES_PER_SECOND );
  fadeToBlackBy( leds, NUM_LEDS, FADE_TO_BLACK_FACTOR );

  for ( int t = 0; t < LED_ROWS; t++ )
  {
    float rad = float( t + frames ) * 1000.0 / 57296.0;
    int height = ( sin( rad * 15.0 ) + 1.0 ) / 2.0 * 16.0;
    for ( int y = 0; y < LED_COLUMNS; y++ )
    {
      if ( y <= height / 2 )
      {
        leds[ Utils::getIndexFromPos( y, t ) ].setHSV( (hue + 127) % 255, 255, 127 );
      }
      else if ( y <= height )
      {
        leds[ Utils::getIndexFromPos( y, t ) ].setHSV( hue, 255, 127 );
      }
    }
  }
  frames++;
  if ( frames >= 360 )
  {
    frames = 0;
  }
  hue += 2;
  if ( hue >= 256 )
  {
    hue = 0;
  }
}
