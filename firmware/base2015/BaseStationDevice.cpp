//
// Created by matt on 7/1/15.
//

#include "BaseStationDevice.h"
#include "USBEndpoints.h"
#include "USBDevice.h"
#include "USBDescriptor.h"

using namespace std;

BaseStationDevice::BaseStationDevice()
  : USBDevice(0x3141, 0x0004, 0x0002)
{
  USBDevice::connect(false);
}

bool BaseStationDevice::USBCallback_setConfiguration(uint8_t configuration) {
  return false;
}

uint8_t * BaseStationDevice::stringImanufacturerDesc() {
  static uint8_t stringImanufacturerDescriptor[] = {
      24,
      STRING_DESCRIPTOR,
      'R',0,'o',0,'b',0,'o',0,'J',0,'a',0,'c',0,'k',0,'e',0,'t',0,'s',0
  };
  return stringImanufacturerDescriptor;
}

uint8_t * BaseStationDevice::stringIproductDesc() {
  static uint8_t stringIproductDescriptor[] = {
      26,
      STRING_DESCRIPTOR,
      'B',0,'a',0,'s',0,'e',0,' ',0,'S',0,'t',0,'a',0,'t',0,'i',0,'o',0,'n',0
  };
  return stringIproductDescriptor;
}

uint8_t * BaseStationDevice::stringIserialDesc() {
  static uint8_t stringIserialDescriptor[] = {
      4,
      STRING_DESCRIPTOR,
      '0',0
  };
  return stringIserialDescriptor;
}