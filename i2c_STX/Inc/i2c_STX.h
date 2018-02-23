#define I2Cx_RCC				RCC_APB1Periph_I2C1
#define I2Cx						I2C1
#define I2C_GPIO_RCC		RCC_APB2Periph_GPIOB
#define I2C_GPIO				GPIOB
#define I2C_PIN_SDA			GPIO_Pin_7
#define I2C_PIN_SCL			GPIO_Pin_6
#define I2Cx_EV_IRQn	  I2C1_EV_IRQn
#define bufferlength 3

#define I2CSLAVE_ADDR	0x4E
#define ADC_ADDR_START		0x00

/*******************************************************************/
#define I2C_CLOCK_FRQ   100000    // I2C-Frq in Hz (100 kHz)
#define I2C_MODE_WAITING		0    // Waiting for commands
#define I2C_MODE_SLAVE_ADR_WR	1	 // Received slave address (writing)
#define I2C_MODE_ADR_BYTE		2    // Received ADR byte
#define I2C_MODE_DATA_BYTE_WR	3    // Data byte (writing)
#define I2C_MODE_SLAVE_ADR_RD	4 	 // Received slave address (to read)
#define I2C_MODE_DATA_BYTE_RD	5    // Data byte (to read)
/*******************************************************************/
void i2c_init(void);
