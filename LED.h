#pragma once

// ##############################################################################################
// Define the target MCU family here

#define STM32F1
// #define STM32F4
// #define STM32H7

// ##############################################################################################
// Include libraries:

#if defined(STM32F1)
#include "stm32f1xx_hal.h"
#elif defined(STM32F4)
#include "stm32f4xx_hal.h"
#elif defined(STM32H7)
#include "stm32h7xx_hal.h"
#endif

#include <string>

// ###############################################################################################
// LED class:

/**
 * @class LED
 *  */ 
class LED
{
    public:

        /**
         * @brief Constructor. Set LED pin and its active low/high mode. Not apply setting.
         * @param activeMode: is the gpio output value when LED state is on.
         * @note begin() method needs after this for apply setting on hardware.
         */
        LED(GPIO_TypeDef* gpioPort, uint16_t gpioPin, uint8_t activeMode = 1); 

        /**
         * @brief Apply setting on hardware. Start LED action.
         * @return true if successed.
         */
        bool begin(void);

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
         * @brief Blink the LED in blocking mode process.
         * @param period: is the period time for toggle LED.
         * @param number: is the number of toggling.
         */
        void blink(uint16_t period, uint8_t number);

        /**
         * @brief Blink the LED in non-blocking mode process.
         * @param period: is the period time for toggle LED.
         * @param time: is the current time for manage of toggling.
         */
        void blink(uint16_t period, uint32_t time);

    private:

        /**
         * @struct ParametersStructure
         * @brief Parameters structure
         */
        struct ParametersStructure
        {
            GPIO_TypeDef* GPIO_PORT;

            uint16_t GPIO_PIN;

            uint8_t ACTIVE_MODE;
        }parameters;
        uint32_t _T;

        /// @brief GPIO_PinState value for LED turn on state.
        GPIO_PinState _on;

        /// @brief GPIO_PinState value for LED turn off state.
        GPIO_PinState _off;

};




