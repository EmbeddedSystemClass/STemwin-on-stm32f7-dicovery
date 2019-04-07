#include "main.h"
#include "touch.h"
#include "i2c.h"

#define IOE_ADDR  0x82
#define STMPE811_ID  0x0811

uint16_t Touch_ReadID(void);
uint8_t Touch_Config(void);
uint8_t I2C_ReadDeviceRegister(uint8_t addr);
uint8_t I2C_WriteDeviceRegister(uint8_t addr, uint8_t value);
void Touch_Reset(void);
void Touch_FnctCmd(uint8_t Fct, FunctionalState NewState);
void Touch_GITCmd(FunctionalState NewState);
void Touch_GITConfig(uint8_t Global_IT, FunctionalState NewState);
void Touch_TP_Config(void);
void Touch_IOAFConfig(uint8_t IO_Pin, FunctionalState NewState);
static uint16_t IOE_TP_Read_X(void);
static uint16_t IOE_TP_Read_Y(void);
static uint16_t IOE_TP_Read_Z(void);
uint16_t I2C_ReadDataBuffer(uint8_t addr);
uint8_t Touch_ReadVersion(void);


TP_STATE TP_State; 


uint8_t testvalue =0;
void Touch_I2C_Test(void)
{
	 if(Touch_ReadID() != (uint16_t)STMPE811_ID )
   {
			while(1);
   }
	 
	 testvalue = Touch_ReadVersion();
	 
	testvalue = I2C_ReadDeviceRegister(0x04);
	I2C_WriteDeviceRegister(0x04,0x01);
	testvalue = I2C_ReadDeviceRegister(0x04);
	if(testvalue != 0x01)
	{
		while(1);
	}
}

uint8_t Touch_Config(void)
{
    if(Touch_ReadID() != (uint16_t)STMPE811_ID )
    {
      return HAL_ERROR;
    }
    Touch_Reset();
    Touch_FnctCmd(IOE_ADC_FCT,ENABLE);
    Touch_TP_Config();
    return HAL_OK;
}

uint8_t I2C_ReadDeviceRegister(uint8_t addr)
{
  uint8_t tmp = 0;

  HAL_I2C_Mem_Read(&hi2c3,(uint16_t)IOE_ADDR,(uint16_t)addr,1,&tmp,1,1000);
  return tmp;
}

uint8_t I2C_WriteDeviceRegister(uint8_t addr, uint8_t value)
{
  if (HAL_I2C_Mem_Write(&hi2c3, (uint16_t)IOE_ADDR, (uint16_t)addr, 1,&value,1,1000) != HAL_OK)
  {
    return 1;
  }
  return 0;
}

uint16_t I2C_ReadDataBuffer(uint8_t addr)
{
  union
  {
    uint8_t value[2];
    uint16_t data;
  } tmp;

	HAL_I2C_Mem_Read(&hi2c3,(uint16_t)IOE_ADDR,(uint16_t)addr,1,&tmp.value[1],1,1000);
  HAL_I2C_Mem_Read(&hi2c3,(uint16_t)IOE_ADDR,(uint16_t)addr+1,1,&tmp.value[0],1,1000);
  return tmp.data;
}

uint16_t Touch_ReadID(void)
{
  uint16_t tmp = 0;

  /* Read device ID  */
 tmp = I2C_ReadDeviceRegister(0);
 tmp = (uint32_t)(tmp << 8);
 tmp |= (uint32_t)I2C_ReadDeviceRegister(1);

  /* Return the ID */
  return (uint16_t)tmp;
}
uint8_t Touch_ReadVersion(void)
{
	uint8_t tmp = 0;
	tmp = I2C_ReadDeviceRegister(2);
	return tmp;
}

void Touch_Reset(void)
{
  I2C_WriteDeviceRegister(IOE_REG_SYS_CTRL1,0x02);
  HAL_Delay(40);
  I2C_WriteDeviceRegister(IOE_REG_SYS_CTRL1,0x00);
}


void Touch_FnctCmd(uint8_t Fct, FunctionalState NewState)
{
  uint8_t tmp = 0;
  
  /* Get the register value */
  tmp = I2C_ReadDeviceRegister(IOE_REG_SYS_CTRL2);
  
  if (NewState != DISABLE)
  {
    /* Set the Functionalities to be Enabled */    
    tmp &= ~(uint8_t)Fct;
  }
  else
  {
    /* Set the Functionalities to be Disabled */    
    tmp |= (uint8_t)Fct;  
  }
  
  /* Set the register value */
  I2C_WriteDeviceRegister(IOE_REG_SYS_CTRL2, tmp);
}

void Touch_GITCmd(FunctionalState NewState)
{
  uint8_t tmp = 0;
  
  /* Read the Interrupt Control register  */
  tmp = I2C_ReadDeviceRegister(IOE_REG_INT_CTRL);
  
  if (NewState != DISABLE)
  {
    /* Set the global interrupts to be Enabled */    
    tmp |= (uint8_t)IOE_GIT_EN;
  }
  else
  {
    /* Set the global interrupts to be Disabled */    
    tmp &= ~(uint8_t)IOE_GIT_EN;
  }  
  
  /* Write Back the Interrupt Control register */
  I2C_WriteDeviceRegister(IOE_REG_INT_CTRL, tmp);
}

void Touch_GITConfig(uint8_t Global_IT, FunctionalState NewState)
{
  uint8_t tmp = 0;
  
  /* Get the current value of the INT_EN register */
  tmp = I2C_ReadDeviceRegister(IOE_REG_INT_EN);
  
  if (NewState != DISABLE)
  {
    /* Set the interrupts to be Enabled */    
    tmp |= (uint8_t)Global_IT;  
  }
  else
  {
    /* Set the interrupts to be Disabled */    
    tmp &= ~(uint8_t)Global_IT;
  }
  /* Set the register */
  I2C_WriteDeviceRegister(IOE_REG_INT_EN, tmp);
}

void Touch_TP_Config(void)
{ 
  /* Enable touch Panel functionality */
  Touch_FnctCmd(IOE_TP_FCT, ENABLE);
  
  /* Select Sample Time, bit number and ADC Reference */
  I2C_WriteDeviceRegister(IOE_REG_ADC_CTRL1, 0x49);
  
  /* Wait for ~20 ms */
  HAL_Delay(40);  
  
  /* Select the ADC clock speed: 3.25 MHz */
  I2C_WriteDeviceRegister(IOE_REG_ADC_CTRL2, 0x01);
  
  /* Select TSC pins in non default mode */  
  Touch_IOAFConfig((uint8_t)TOUCH_IO_ALL, DISABLE);
  
  /* Select 2 nF filter capacitor */
  I2C_WriteDeviceRegister(IOE_REG_TP_CFG, 0x9A);   
  
  /* Select single point reading  */
  I2C_WriteDeviceRegister(IOE_REG_FIFO_TH, 0x01);
  
  /* Write 0x01 to clear the FIFO memory content. */
  I2C_WriteDeviceRegister(IOE_REG_FIFO_STA, 0x01);
  
  /* Write 0x00 to put the FIFO back into operation mode  */
  I2C_WriteDeviceRegister(IOE_REG_FIFO_STA, 0x00);
  
  /* set the data format for Z value: 7 fractional part and 1 whole part */
  I2C_WriteDeviceRegister(IOE_REG_TP_FRACT_XYZ, 0x01);
  
  /* set the driving capability of the device for TSC pins: 50mA */
  I2C_WriteDeviceRegister(IOE_REG_TP_I_DRIVE, 0x01);
  
  /* Use no tracking index, touch-panel controller operation mode (XYZ) and 
     enable the TSC */
  I2C_WriteDeviceRegister(IOE_REG_TP_CTRL, 0x03);
  
  /*  Clear all the status pending bits */
  I2C_WriteDeviceRegister(IOE_REG_INT_STA, 0xFF); 
  
  /* Initialize the TS structure to their default values */ 
  TP_State.TouchDetected = TP_State.X = TP_State.Y = TP_State.Z = 0;
  
  /* All configuration done */
}

void Touch_IOAFConfig(uint8_t IO_Pin, FunctionalState NewState)
{
  uint8_t tmp = 0;
  
  /* Get the current state of the GPIO_AF register */
  tmp = I2C_ReadDeviceRegister(IOE_REG_GPIO_AF);
  
  if (NewState != DISABLE)
  {
    /* Enable the selected pins alternate function */
    tmp |= (uint8_t)IO_Pin;
  }
  else
  {
    /* Disable the selected pins alternate function */   
    tmp &= ~(uint8_t)IO_Pin;   
  }
  
  /* Write back the new value in GPIO_AF register */  
  I2C_WriteDeviceRegister(IOE_REG_GPIO_AF, tmp);  
}

static uint16_t IOE_TP_Read_X(void)
{
  int32_t x, xr;
  
  /* Read x value from DATA_X register */
  x = I2C_ReadDataBuffer(IOE_REG_TP_DATA_X);
  
  /* x value first correction */
  if(x <= 3000)
  {
  x = 3870 - x;
  }
  else
  {
   x = 3800 - x;
  }
  
  /* x value second correction */  
  xr = x / 15;
  
  /* return x position value */
  if(xr <= 0)
  {
    xr = 0;
  }
  else if (xr > 240)
  {
    xr = 239;
  }
  else 
  {}
  return (uint16_t)(xr); 
}

static uint16_t IOE_TP_Read_Y(void)
{
  int32_t y, yr;
  
  /* Read y value from DATA_Y register */
  y = I2C_ReadDataBuffer(IOE_REG_TP_DATA_Y);
  
  /* y value first correction */

  y -= 360;  
  
  /* y value second correction */
  yr = y / 11;
  
  /* return y position value */
  if(yr <= 0)
  {
    yr = 0;
  }
  else if (yr > 320)
  {
    yr = 319;
  }
  else
  {}
  return (uint16_t)(yr); 
}


static uint16_t IOE_TP_Read_Z(void)
{
  uint32_t z;
  
  /* Read z value from DATA_Z register */
  z = I2C_ReadDeviceRegister(IOE_REG_TP_DATA_Z);

  /* return z position value */
  if(z <= 0)
    z = 0;
  return (uint16_t)(z); 
}

TP_STATE* IOE_TP_GetState(void)
{
  uint32_t xDiff, yDiff , x , y;
  static uint32_t _x = 0, _y = 0;
  
  /* Check if the Touch detect event happened */
  TP_State.TouchDetected = (I2C_ReadDeviceRegister(IOE_REG_TP_CTRL) & 0x80);
  
  if(TP_State.TouchDetected) 
  {
    x = IOE_TP_Read_X();
    y = IOE_TP_Read_Y();
    xDiff = x > _x? (x - _x): (_x - x);
    yDiff = y > _y? (y - _y): (_y - y);       
    if (xDiff + yDiff > 5)
    {
      _x = x;
      _y = y;       
    }
  }  
  /* Update the X position */
  TP_State.X = _x;
    
  /* Update the Y position */  
  TP_State.Y = _y;
  /* Update the Z Pression index */  
  TP_State.Z = IOE_TP_Read_Z();  
  
  /* Clear the interrupt pending bit and enable the FIFO again */
  I2C_WriteDeviceRegister(IOE_REG_FIFO_STA, 0x01);
  I2C_WriteDeviceRegister(IOE_REG_FIFO_STA, 0x00);
  
  /* Return pointer to the updated structure */
  return &TP_State; 
}
