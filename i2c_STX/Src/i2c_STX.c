#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_i2c.h"
#include "misc.h"
#include "i2c_STX.h"

unsigned char i2c1_mode=I2C_MODE_WAITING;

void i2c_init(void){
    GPIO_InitTypeDef  GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    I2C_InitTypeDef  I2C_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel                   = I2C1_EV_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = I2C1_ER_IRQn;
    NVIC_Init(&NVIC_InitStructure);

    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStructure.I2C_OwnAddress1 = I2CSLAVE_ADDR << 1;
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStructure.I2C_ClockSpeed = I2C_CLOCK_FRQ;
    I2C_Cmd(I2C1, ENABLE);                  // I2C Peripheral Enable
    I2C_Init(I2C1, &I2C_InitStructure);

    I2C_ITConfig(I2C1, I2C_IT_EVT, ENABLE); //Part of the STM32 I2C driver
    I2C_ITConfig(I2C1, I2C_IT_BUF, ENABLE);
    I2C_ITConfig(I2C1, I2C_IT_ERR, ENABLE); //Part of the STM32 I2C driver
}

void I2C1_ClearFlag(void) {
  // ADDR-Flag clear
  while((I2C1->SR1 & I2C_SR1_ADDR) == I2C_SR1_ADDR) {
    I2C1->SR1;
    I2C1->SR2;
  }

  // STOPF Flag clear
  while((I2C1->SR1&I2C_SR1_STOPF) == I2C_SR1_STOPF) {
    I2C1->SR1;
    I2C1->CR1 |= 0x1;
  }
}

void I2C1_EV_IRQHandler(void) {
  uint32_t event;
  uint8_t wert;

  // Reading last event
  event=I2C_GetLastEvent(I2C1);

  if(event==I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED) {
    // Master has sent the slave address to read data from the slave
    i2c1_mode=I2C_MODE_SLAVE_ADR_RD;
    wert=0xAA;
    I2C_SendData(I2C1, wert);
  }
  else if(event==I2C_EVENT_SLAVE_BYTE_TRANSMITTED) {
    // Master wants to read another byte of data from the slave
    i2c1_mode=I2C_MODE_DATA_BYTE_RD;
		wert=0xC3;
    I2C_SendData(I2C1, wert);
  }
  else if(event==I2C_EVENT_SLAVE_STOP_DETECTED) {
    // Master has STOP sent
		I2C1_ClearFlag();
    i2c1_mode=I2C_MODE_WAITING;
  }
}

void I2C1_ER_IRQHandler(void) {
  if (I2C_GetITStatus(I2C1, I2C_IT_AF)) {
    I2C_ClearITPendingBit(I2C1, I2C_IT_AF);
  }
}
