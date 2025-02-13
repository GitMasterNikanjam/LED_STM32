#pragma once

// ##############################################################################################
// MCU Select:

#include "mcu_select.h"

/*
    If there is not exist mcu_select.h at beside of this header file, Create it and put this bellow following content. 
    Then select your desired MCU that want work with.
*/
// ----------------------------------------------------------------
// mcu_select.h file:

// Define the target MCU family here
// Uncomment the desired MCU family definition below:

// #define STM32F1
// #define STM32F4
// #define STM32H7

// ----------------------------------------------------------------

// ##############################################################################################
// Include libraries:

#if defined(STM32F1)
#include "stm32f1xx_hal.h"
#elif defined(STM32F4)
#include "stm32f4xx_hal.h"
#elif defined(STM32H7)
#include "stm32h7xx_hal.h"
#endif

// ###############################################################################################
// LED class:

/**
 * @class LED
 * @brief The class for manage LED function. 
 * @note - Maximum output speed GPIO config is LOW.
 * @note - GPIO mode is output push-pull.
 *  */ 
class LED
{
    public:

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

    private:

        /**
         * @struct ParametersStructure
         * @brief Parameters structure
         */
        struct ParametersStructure
        {
            /// @brief GPIO port for led pin.
            GPIO_TypeDef* GPIO_PORT;

            /**
             * @brief GPIO pin number for led. 
             * @note It shoude be GPIO_PIN_0, GPIO_PIN_1, ...
             *  */ 
            uint16_t GPIO_PIN;

            /// @brief Active mode of led control. 0: Active low, 1: Active high.
            uint8_t ACTIVE_MODE;
        }parameters;

        /// @brief The time update for led blinking in non blocking mode.
        uint32_t _T;

        /// @brief GPIO_PinState value for LED turn on state.
        GPIO_PinState _on;

        /// @brief GPIO_PinState value for LED turn off state.
        GPIO_PinState _off;

        /// @brief Counter for blink led in non blocking mode.
        uint8_t _blinkCounter;

        /// @brief The flag for blink led state in non blocking mode.
        bool _blinkFlag;

        /// @brief The delay of time for one blink led in non blocking mode. [ms]
        uint16_t _blinkDelay;

        /// @brief The number of blink led in non blocking mode.
        uint8_t _blinkNumber;

        /// @brief The flag for LED.init() is succeeded or not.
        bool _initFlag;

        /**
         * @brief Enable RCC GPIO PORT for certain port.
         * @return true if successful.
         */
        bool RCC_GPIO_CLK_ENABLE(GPIO_TypeDef *GPIO_PORT);
};




