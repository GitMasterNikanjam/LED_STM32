#include "LED.h"

    LED::LED(GPIO_TypeDef* gpioPort, uint16_t gpioPin, uint8_t activeMode)
    {
        parameters.GPIO_PORT = gpioPort;
        parameters.GPIO_PIN = gpioPin;
        parameters.ACTIVE_MODE = activeMode;

        if(parameters.ACTIVE_MODE == 0)
        {
            _on = GPIO_PIN_RESET;
            _off = GPIO_PIN_SET;
        }
        else
        {
            _on = GPIO_PIN_SET;
            _off = GPIO_PIN_RESET;
        }
    }

    bool LED::begin(void)
    {
        GPIO_InitTypeDef GPIO_InitStruct = {0};
        
        /*Configure GPIO pin */
        GPIO_InitStruct.Pin = parameters.GPIO_PIN;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        HAL_GPIO_Init(parameters.GPIO_PORT, &GPIO_InitStruct);

        /*Configure GPIO pin Output Level */
        off();

        return true;
    }

    void LED::on(void)
    {
        HAL_GPIO_WritePin(parameters.GPIO_PORT, parameters.GPIO_PIN, _on);
    }

    void LED::off(void)
    {
        HAL_GPIO_WritePin(parameters.GPIO_PORT, parameters.GPIO_PIN, _off);
    }

    void LED::toggle(void)
    {
        HAL_GPIO_TogglePin(parameters.GPIO_PORT, parameters.GPIO_PIN);
    }

    void LED::clean(void)
    {
        off();

        GPIO_InitTypeDef GPIO_InitStruct = {0};
        
        /*Configure GPIO pin */
        GPIO_InitStruct.Pin = parameters.GPIO_PIN;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        HAL_GPIO_Init(parameters.GPIO_PORT, &GPIO_InitStruct);
    }

    void LED::blink(uint16_t period, uint8_t number)
    {
        for(int i=1; i<=number; i++)
        {
            on();
            HAL_Delay(period/2);
            off();
            HAL_Delay(period/2);
        }
    }

    void LED::blink(uint16_t period, uint32_t time)
    {
        if(period == 0)
        {
            _T = 0;
            off();
        }

        if(time <= _T)
        {
            return;
        }

        uint32_t hp = period/2;
        if( (time - _T) >= hp)
        {
            toggle();
        }
    }
