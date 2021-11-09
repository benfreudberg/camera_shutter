/*
 * printf_reroute.c
 *
 *  Created on: Nov 6, 2021
 *      Author: Fongberg
 */

#include "usb_device.h"
#include "usbd_cdc.h"
#include "stm32g4xx_hal_def.h"


int _write(int file, char *data, int len)
{
   uint8_t status = USBD_CDC_SetTxBuffer(&hUsbDeviceFS, (uint8_t*)data, len);
   status += USBD_CDC_TransmitPacket(&hUsbDeviceFS);

   // return # of bytes written - as best we can tell
   return (status == USBD_OK ? len : 0);
}
