/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : App/usbd_desc.c
 * @version        : v2.0_Cube
 * @brief          : This file implements the USB device descriptors.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_conf.h"

/* USER CODE BEGIN INCLUDE */

/* USER CODE END INCLUDE */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
 * @{
 */

/** @addtogroup USBD_DESC
 * @{
 */

/** @defgroup USBD_DESC_Private_TypesDefinitions USBD_DESC_Private_TypesDefinitions
 * @brief Private types.
 * @{
 */

/* USER CODE BEGIN PRIVATE_TYPES */

/* USER CODE END PRIVATE_TYPES */

/**
 * @}
 */

/** @defgroup USBD_DESC_Private_Defines USBD_DESC_Private_Defines
 * @brief Private defines.
 * @{
 */

#define USBD_VID 0x9527
#define USBD_LANGID_STRING 1033
#define USBD_MANUFACTURER_STRING "ChengduEbyte"
#define USBD_PID_FS 0x959A
#define USBD_PRODUCT_STRING_FS "STM32 WINUSB"
#define USBD_CONFIGURATION_STRING_FS "WINUSB Config"
#define USBD_INTERFACE_STRING_FS "WINUSB Interface"

/* USER CODE BEGIN PRIVATE_DEFINES */

// USBD_LANGID_STRING 0x1404-ZH //0x0409-EN

uint8_t *USBD_WinUSBOSFeatureDescriptor(uint16_t *length);
uint8_t *USBD_WinUSBOSPropertyDescriptor(uint16_t *length);

/* USER CODE END PRIVATE_DEFINES */

/**
 * @}
 */

/* USER CODE BEGIN 0 */

#if defined(__ICCARM__) /* IAR Compiler */
#pragma data_alignment = 4
#endif /* defined ( __ICCARM__ ) */
/* Internal string descriptor. */
__ALIGN_BEGIN uint8_t USBD_StrDesc[USBD_MAX_STR_DESC_SIZ] __ALIGN_END;



#if (USBD_SUPPORT_WINUSB == 1)   // desc_define

#define USB_LEN_OS_FEATURE_DESC 0x28
#if defined(__ICCARM__) /* IAR Compiler */
#pragma data_alignment = 4
#endif /* defined ( __ICCARM__ ) */
__ALIGN_BEGIN uint8_t USBD_WINUSB_OSFeatureDesc[USB_LEN_OS_FEATURE_DESC] __ALIGN_END =
    {
        0x28, 0, 0, 0,                      // length
        0, 1,                               // bcd version 1.0
        4, 0,                               // windex: extended compat ID descritor
        1,                                  // no of function
        0, 0, 0, 0, 0, 0, 0,                // reserve 7 bytes
                                            // function
        0,                                  // interface no
        0,                                  // reserved
        'W', 'I', 'N', 'U', 'S', 'B', 0, 0, //  first ID
        0, 0, 0, 0, 0, 0, 0, 0,             // second ID
        0, 0, 0, 0, 0, 0                    // reserved 6 bytes
};


const uint8_t USBD_OS_STRING[8] = { 'M', 'S', 'F', 'T', '1', '0', '0', USB_REQ_MS_VENDOR_CODE };

#define USB_LEN_OS_PROPERTY_DESC 0x8E
#if defined(__ICCARM__) /* IAR Compiler */
#pragma data_alignment = 4
#endif /* defined ( __ICCARM__ ) */
__ALIGN_BEGIN uint8_t USBD_WINUSB_OSPropertyDesc[USB_LEN_OS_PROPERTY_DESC] __ALIGN_END =
    {
        0x8E,
        0,
        0,
        0, // length 246 byte
        0x00,
        0x01, // BCD version 1.0
        0x05,
        0x00, // Extended Property Descriptor Index(5)
        0x01,
        0x00, // number of section (1)
              //; property section
        0x84,
        0x00,
        0x00,
        0x00, // size of property section
        0x1,
        0,
        0,
        0, //; property data type (1)
        0x28,
        0, //; property name length (42)
        'D',        0,
        'e',         0,
        'v',         0,
        'i',        0,
        'c',         0,
        'e',        0,
        'I',        0,
        'n',        0,
        't',         0,
        'e',        0,
        'r',        0,
        'f',        0,
        'a',        0,
        'c',        0,
        'e',        0,
        'G',         0,
        'U',        0,
        'I',        0,
        'D',        0,
        0,         0,
        // {13EB360B-BC1E-46CB-AC8B-EF3DA47B4062}
        0x4E, 0, 0, 0, // ; property data length
        '{',        0,
        '1',        0,
        '3',        0,
        'E',        0,
        'B',        0,
        '3',         0,
        '6',        0,
        '0',        0,
        'B',        0,
        '-',        0,
        'B',         0,
        'C',         0,
        '1',         0,
        'E',         0,
        '-',         0,
        '4',        0,
        '6',        0,
        'C',        0,
        'B',        0,
        '-',        0,
        'A',        0,
        'C',        0,
        '8',        0,
        'B',        0,
        '-',        0,
        'E',        0,
        'F',        0,
        '3',        0,
        'D',        0,
        'A',        0,
        '4',        0,
        '7',        0,
        'B',        0,
        '4',        0,
        '0',        0,
        '6',        0,
        '2',        0,
        '}',        0,
        0,          0,
};
#endif

/* USER CODE END 0 */

/** @defgroup USBD_DESC_Private_Macros USBD_DESC_Private_Macros
 * @brief Private macros.
 * @{
 */

/* USER CODE BEGIN PRIVATE_MACRO */

/* USER CODE END PRIVATE_MACRO */

/**
 * @}
 */

/** @defgroup USBD_DESC_Private_FunctionPrototypes USBD_DESC_Private_FunctionPrototypes
 * @brief Private functions declaration.
 * @{
 */

static void Get_SerialNum(void);
static void IntToUnicode(uint32_t value, uint8_t *pbuf, uint8_t len);

/**
 * @}
 */

/** @defgroup USBD_DESC_Private_FunctionPrototypes USBD_DESC_Private_FunctionPrototypes
 * @brief Private functions declaration for FS.
 * @{
 */

uint8_t *USBD_FS_DeviceDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
uint8_t *USBD_FS_LangIDStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
uint8_t *USBD_FS_ManufacturerStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
uint8_t *USBD_FS_ProductStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
uint8_t *USBD_FS_SerialStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
uint8_t *USBD_FS_ConfigStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
uint8_t *USBD_FS_InterfaceStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);

/**
 * @}
 */

/** @defgroup USBD_DESC_Private_Variables USBD_DESC_Private_Variables
 * @brief Private variables.
 * @{
 */

USBD_DescriptorsTypeDef FS_Desc =
    {
        USBD_FS_DeviceDescriptor,
		USBD_FS_LangIDStrDescriptor,
		USBD_FS_ManufacturerStrDescriptor,
		USBD_FS_ProductStrDescriptor,
		USBD_FS_SerialStrDescriptor,
		USBD_FS_ConfigStrDescriptor,
		USBD_FS_InterfaceStrDescriptor,
#if (USBD_SUPPORT_WINUSB == 1)   //class
        USBD_WinUSBOSFeatureDescriptor,
		USBD_WinUSBOSPropertyDescriptor
#endif
};

#if defined(__ICCARM__) /* IAR Compiler */
#pragma data_alignment = 4
#endif /* defined ( __ICCARM__ ) */
/** USB standard device descriptor. */
__ALIGN_BEGIN uint8_t USBD_FS_DeviceDesc[USB_LEN_DEV_DESC] __ALIGN_END =
    {
        0x12,                 /*bLength */
        USB_DESC_TYPE_DEVICE, /*bDescriptorType*/
        0x00,                 /*bcdUSB */
        0x02,
        0xFE,                /*bDeviceClass*/   //0x02 == CDC  0xFE == undefine未定义的杂项类别 
        0x02,                /*bDeviceSubClass*/
        0x00,                /*bDeviceProtocol*/
        USB_MAX_EP0_SIZE,    /*bMaxPacketSize*/
        LOBYTE(USBD_VID),    /*idVendor*/
        HIBYTE(USBD_VID),    /*idVendor*/
        LOBYTE(USBD_PID_FS), /*idProduct*/
        HIBYTE(USBD_PID_FS), /*idProduct*/
        0x00,                /*bcdDevice rel. 2.00*/
        0x02,
        USBD_IDX_MFC_STR,          /*Index of manufacturer  string*/
        USBD_IDX_PRODUCT_STR,      /*Index of product string*/
        USBD_IDX_SERIAL_STR,       /*Index of serial number string*/
        USBD_MAX_NUM_CONFIGURATION /*bNumConfigurations*/
};

/* USB_DeviceDescriptor */

/**
 * @}
 */

/** @defgroup USBD_DESC_Private_Variables USBD_DESC_Private_Variables
 * @brief Private variables.
 * @{
 */

#if defined(__ICCARM__) /* IAR Compiler */
#pragma data_alignment = 4
#endif /* defined ( __ICCARM__ ) */

/** USB lang identifier descriptor. */
__ALIGN_BEGIN uint8_t USBD_LangIDDesc[USB_LEN_LANGID_STR_DESC] __ALIGN_END =
    {
        USB_LEN_LANGID_STR_DESC,
        USB_DESC_TYPE_STRING,
        LOBYTE(USBD_LANGID_STRING),
        HIBYTE(USBD_LANGID_STRING)};

#if defined(__ICCARM__) /* IAR Compiler */
#pragma data_alignment = 4
#endif /* defined ( __ICCARM__ ) */
/* Internal string descriptor. */
__ALIGN_BEGIN uint8_t USBD_StrDesc[USBD_MAX_STR_DESC_SIZ] __ALIGN_END;

#if defined(__ICCARM__) /*!< IAR Compiler */
#pragma data_alignment = 4
#endif
__ALIGN_BEGIN uint8_t USBD_StringSerial[USB_SIZ_STRING_SERIAL] __ALIGN_END = {
    USB_SIZ_STRING_SERIAL,
    USB_DESC_TYPE_STRING,
};

/**
 * @}
 */

/** @defgroup USBD_DESC_Private_Functions USBD_DESC_Private_Functions
 * @brief Private functions.
 * @{
 */

 #if (USBD_SUPPORT_WINUSB == 1)   //function
uint8_t *USBD_WinUSBOSStrDescriptor(uint16_t *length)
{
	printf("USBD_WinUSBOSStrDescriptor\r\n");
	USBD_GetString((uint8_t *)USBD_OS_STRING, USBD_StrDesc, length);
	return USBD_StrDesc;
}
uint8_t *USBD_WinUSBOSFeatureDescriptor(uint16_t *length)
{
	printf("USBD_WinUSBOSFeatureDescriptor\r\n");
	*length = USB_LEN_OS_FEATURE_DESC;
	return USBD_WINUSB_OSFeatureDesc;
}
uint8_t *USBD_WinUSBOSPropertyDescriptor(uint16_t *length)
{
	printf("USBD_WinUSBOSPropertyDescriptor\r\n");
	*length = USB_LEN_OS_PROPERTY_DESC;
	return USBD_WINUSB_OSPropertyDesc;
}
#endif

/**
 * @brief  Return the device descriptor
 * @param  speed : Current device speed
 * @param  length : Pointer to data length variable
 * @retval Pointer to descriptor buffer
 */
uint8_t *USBD_FS_DeviceDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
  UNUSED(speed);
  printf("USBD_FS_DeviceDescriptor.\n");
  *length = sizeof(USBD_FS_DeviceDesc);
  return USBD_FS_DeviceDesc;
}

/**
 * @brief  Return the LangID string descriptor
 * @param  speed : Current device speed
 * @param  length : Pointer to data length variable
 * @retval Pointer to descriptor buffer
 */
uint8_t *USBD_FS_LangIDStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
  printf("USBD_FS_LangIDStrDescriptor.\n");
  UNUSED(speed);
  *length = sizeof(USBD_LangIDDesc);
  return USBD_LangIDDesc;
}

/**
 * @brief  Return the product string descriptor
 * @param  speed : Current device speed
 * @param  length : Pointer to data length variable
 * @retval Pointer to descriptor buffer
 */
uint8_t *USBD_FS_ProductStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{	
	UNUSED(speed);
	printf("USBD_FS_ProductStrDescriptor.\n");
	USBD_GetString((uint8_t *)USBD_PRODUCT_STRING_FS, USBD_StrDesc, length);
    return USBD_StrDesc;
}

/**
 * @brief  Return the manufacturer string descriptor
 * @param  speed : Current device speed
 * @param  length : Pointer to data length variable
 * @retval Pointer to descriptor buffer
 */
uint8_t *USBD_FS_ManufacturerStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
	printf("USBD_FS_ManufacturerStrDescriptor.\n");
  UNUSED(speed);
  USBD_GetString((uint8_t *)USBD_MANUFACTURER_STRING, USBD_StrDesc, length);
  return USBD_StrDesc;
}

/**
 * @brief  Return the serial number string descriptor
 * @param  speed : Current device speed
 * @param  length : Pointer to data length variable
 * @retval Pointer to descriptor buffer
 */
uint8_t *USBD_FS_SerialStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
  UNUSED(speed);
  *length = USB_SIZ_STRING_SERIAL;

  /* Update the serial number string descriptor with the data from the unique
   * ID */
  Get_SerialNum();
  /* USER CODE BEGIN USBD_FS_SerialStrDescriptor */
  printf("USBD_FS_SerialStrDescriptor.\n");
  /* USER CODE END USBD_FS_SerialStrDescriptor */
  return (uint8_t *)USBD_StringSerial;
}

/**
 * @brief  Return the configuration string descriptor
 * @param  speed : Current device speed
 * @param  length : Pointer to data length variable
 * @retval Pointer to descriptor buffer
 */
uint8_t *USBD_FS_ConfigStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
	 printf("USBD_FS_ConfigStrDescriptor.\n");
  if (speed == USBD_SPEED_HIGH)
  {
    USBD_GetString((uint8_t *)USBD_CONFIGURATION_STRING_FS, USBD_StrDesc, length);
  }
  else
  {
    USBD_GetString((uint8_t *)USBD_CONFIGURATION_STRING_FS, USBD_StrDesc, length);
  }
  return USBD_StrDesc;
}

/**
 * @brief  Return the interface string descriptor
 * @param  speed : Current device speed
 * @param  length : Pointer to data length variable
 * @retval Pointer to descriptor buffer
 */
uint8_t *USBD_FS_InterfaceStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
	printf("USBD_FS_InterfaceStrDescriptor.\n");
  if (speed == 0)
  {
    USBD_GetString((uint8_t *)USBD_INTERFACE_STRING_FS, USBD_StrDesc, length);
  }
  else
  {
    USBD_GetString((uint8_t *)USBD_INTERFACE_STRING_FS, USBD_StrDesc, length);
  }
  return USBD_StrDesc;
}

/**
 * @brief  Create the serial number string descriptor
 * @param  None
 * @retval None
 */
static void Get_SerialNum(void)
{
  uint32_t deviceserial0;
  uint32_t deviceserial1;
  uint32_t deviceserial2;

  deviceserial0 = *(uint32_t *)DEVICE_ID1;
  deviceserial1 = *(uint32_t *)DEVICE_ID2;
  deviceserial2 = *(uint32_t *)DEVICE_ID3;

  deviceserial0 += deviceserial2;

  if (deviceserial0 != 0)
  {
    IntToUnicode(deviceserial0, &USBD_StringSerial[2], 8);
    IntToUnicode(deviceserial1, &USBD_StringSerial[18], 4);
  }
}

/**
 * @brief  Convert Hex 32Bits value into char
 * @param  value: value to convert
 * @param  pbuf: pointer to the buffer
 * @param  len: buffer length
 * @retval None
 */
static void IntToUnicode(uint32_t value, uint8_t *pbuf, uint8_t len)
{
  uint8_t idx = 0;

  for (idx = 0; idx < len; idx++)
  {
    if (((value >> 28)) < 0xA)
    {
      pbuf[2 * idx] = (value >> 28) + '0';
    }
    else
    {
      pbuf[2 * idx] = (value >> 28) + 'A' - 10;
    }

    value = value << 4;

    pbuf[2 * idx + 1] = 0;
  }
}
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
