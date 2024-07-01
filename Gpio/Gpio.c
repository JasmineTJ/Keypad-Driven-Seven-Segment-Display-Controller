/**
 * Gpio.c
 *
 *  Created on: Tue Apr 11 2023
 *  Author    : Abdullah Darwish
 */

#include "Gpio.h"
#include "Gpio_Private.h"

void Gpio_ConfigPin(uint8 PortName, uint8 PinNum, uint8 PinMode,
		uint8 DefaultState) {
	uint8 OutputState = DefaultState & 0x1;
	uint8 InputState = DefaultState >> 1;
	switch (PortName) {
	case GPIO_A:
		GPIOA_MODER &= ~(0x3 << (2 * PinNum));
		GPIOA_MODER |= (PinMode << (2 * PinNum));
		GPIOA_OTYPER &= ~(0x01 << PinNum);
		GPIOA_OTYPER |= (OutputState << PinNum);
		GPIOA_PUPDR &= ~(0x3 << (2 * PinNum));
		GPIOA_PUPDR |= (InputState << (2 * PinNum));
		break;
	case GPIO_B:
		GPIOB_MODER &= ~(0x3 << (2 * PinNum));
		GPIOB_MODER |= (PinMode << (2 * PinNum));
		GPIOB_OTYPER &= ~(0x01 << PinNum);
		GPIOB_OTYPER |= (OutputState << PinNum);
		GPIOB_PUPDR &= ~(0x3 << (2 * PinNum));
		GPIOB_PUPDR |= (InputState << (2 * PinNum));
		break;
	}
}

void Gpio_WritePin(uint8 PortName, uint8 PinNum, uint8 Data) {
	switch (PortName) {
	case GPIO_A:
		GPIOA_ODR &= ~(0x01 << PinNum);
		GPIOA_ODR |= (Data << PinNum);
		break;
	case GPIO_B:
		GPIOB_ODR &= ~(0x01 << PinNum);
		GPIOB_ODR |= (Data << PinNum);
		break;
	}
}

uint8 Gpio_ReadPin(uint8 PortName, uint8 PinNum) {
	uint8 data = 0;
	switch (PortName){
	case GPIO_A:
		data =(GPIOA_IDR & (1 << PinNum))>>PinNum;
		break;
	case GPIO_B:
		data =(GPIOB_IDR & (1 << PinNum))>>PinNum;
		break;
	default:
		break;
	}
	return data;


}
