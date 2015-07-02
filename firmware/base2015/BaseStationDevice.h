//
// Created by matt on 7/1/15.
//

#ifndef GT_ROBOJACKETS_ROBOCUP_BASESTATIONDEVICE_H
#define GT_ROBOJACKETS_ROBOCUP_BASESTATIONDEVICE_H

#include "mbed.h"
#include "USBDevice.h"
#include "USBDevice_Types.h"
#include <string>

class BaseStationDevice : public USBDevice {

public:
  BaseStationDevice();

  virtual bool USBCallback_setConfiguration(uint8_t configuration) override;

protected:

  virtual uint8_t * stringIproductDesc() override;

  virtual uint8_t * stringImanufacturerDesc() override;

  virtual uint8_t * stringIserialDesc() override;

};


#endif //GT_ROBOJACKETS_ROBOCUP_BASESTATIONDEVICE_H
