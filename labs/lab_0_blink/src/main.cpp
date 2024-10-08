/**
* @brief Blink: Turns on an LED for one second then off for
* one second and then repeats.
*/

#include "Arduino.h"

//Set LED_BUILTIN if it is not defined by Arduino framework
#define LED_BUILTIN PC13

/**
 * @brief Initialize LED pin as digital write.
 * @param none
 * @retval none
 */
void setup()
{
  //initialize LED digital pin as an output
  pinMode(LED_BUILTIN, OUTPUT);
}

/**
 * @brief Turn LED on for 1 sec and off for 1 sec.
 * @param none
 * @retval none
 */
void loop()
{
  uint32_t delay_ms = 500;

  //turn LED on (HIGH is the voltage level)
  digitalWrite(LED_BUILTIN, HIGH);

  //wait for one second
  delay(delay_ms);

  //turn LED off (LOW sets voltage to GND)
  digitalWrite(LED_BUILTIN, LOW);

  //wait one more second
  delay(delay_ms);
}
