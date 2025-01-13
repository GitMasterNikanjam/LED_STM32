# LED Library for STM32

- This libray can be used for LED management.
- LED class is the main class for LED objects.
- LED class can control blinking in blocking or non-blocking mode.
- In non-blocking mode led blink without blocking delay.
-------------------------------------------------------------------------------

## Public Member Functions For LED class

```cpp
 /**
 * @brief Constructor. Set the LED pin and its active low/high mode. Do not apply the settings.
 * @param activeMode: This is the GPIO output value when the LED state is on. Default is active high.
 * @note - The init() method is needed after this to apply the settings on the hardware.
 * @note - Maximum output speed GPIO config is LOW.
 * @note - GPIO mode is output push-pull.
 */
LED(GPIO_TypeDef* gpioPort, uint16_t gpioPin, uint8_t activeMode = 1); 

/**
 * @brief Apply the settings to the hardware. Start the LED action.
 * @return true if successful.
 */
bool init(void);

/// @brief Turn on the LED.
void on(void);

/// @brief Turn off the LED.
void off(void);

/// @brief Toggle the LED.
void toggle(void);

/**
 * @brief Clean setting on hardware. Stop  LED action. 
 */
void clean(void);

/**
 * @brief Blink the LED.
 * @param duration: is the total duration time for toggle LED. [ms]
 * @param number: is the number of toggling in certain duration time.
 * @param blockingMode: is the blink mode for blocking mode enable/disable. Default value is true that means blinking is in blocking mode.
 * @note - Total time duration for toggle operation is: (duration)
 */
void blink(uint16_t duration, uint8_t number, bool blockingMode = true);

/**
 * @brief Return blinking status for non blocking mode.
 * @return - true if blinking proccess is not finished.
 * @return - false if blinking proccess is finished.
 *  */ 
bool isBlinking(void) {return _blinkFlag;};

/**
 * @brief Update blinking status in non blocking mode.
 * @note - This method should be used in the main loop or in a periodic function.
 */
void blinkUpdate(void);
```