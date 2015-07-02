//
// Created by matt on 6/22/15.
//
#include <iostream>
#include "mbed.h"
#include "BaseStationDevice.h"

#define ENDL "\r\n"

using namespace std;

int main(void)
{
  cout << "Power on." << ENDL;
  DigitalOut light(LED1);
  light = 1;

  cout << "LIGHT INIT" << ENDL;

  BaseStationDevice usb;

  cout << "Connected!" << ENDL;

  while (1) {
    light = !light;
    wait(0.5);
  }
}
