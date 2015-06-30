//
// Created by matt on 6/22/15.
//
#include "mbed.h"
#include "USBDevice.h"

int main()
{
  DigitalOut power_led(LED1);
  DigitalOut connected_led(LED2);
  DigitalOut endpoint_led(LED3);
  power_led = 0;
  connected_led = 0;
  endpoint_led = 0;

  USBDevice device(0x3141, 0x0004, 0x0001);

  power_led = 1;

  device.connect(true);

  connected_led = 1;

  device.addEndpoint(0x06, 7);

  endpoint_led = 1;

  return 0;
}

//#include <RTP.hpp>
//#include <utility>
//#include <vector>
//#include "mbed.h"
//
//using namespace std;
//
//Serial pc(USBTX, USBRX);
//
//vector< pair<RTP_t, bool> > radioOutBufer; // packet & ready flag
//
//bool serialReceivingPacket = false;
//constexpr unsigned char STX = '$';
//constexpr unsigned char ETX = '#';
//void pcRxHandler()
//{
//  while(pc.readable())
//  {
//    auto c = pc.getc();
//    if(c == STX)
//    {
//      serialReceivingPacket = true;
//    }
//    else if(c == ETX)
//    {
//      if(serialReceivingPacket)
//      {
//        radioOutBufer.rbegin()->second = true;
//        radioOutBufer.push_back(pair<RTP_t, bool>(RTP_t(), false));
//        radioOutBufer.rbegin()->first.payload_size = 0;
//      }
//      serialReceivingPacket = false;
//    }
//    else if(serialReceivingPacket)
//    {
//      radioOutBufer.rbegin()->first.payload[radioOutBufer.rbegin()->first.payload_size] = c;
//      radioOutBufer.rbegin()->first.payload_size++;
//    }
//  }
//}
//
//int main()
//{
//  DigitalOut power_led(LED1);
//  power_led = 1;
//
//  radioOutBufer.push_back(pair<RTP_t, bool>(RTP_t(), false));
//  radioOutBufer.rbegin()->first.payload_size = 0;
//
//  pc.attach(pcRxHandler, Serial::RxIrq);
//
//  pc.attach([]() {
//    NVIC_DisableIRQ(UART0_IRQn);
//    //handle transmission interrupts if necessary here
//    NVIC_EnableIRQ(UART0_IRQn);
//  }, Serial::TxIrq);
//
//  while(true)
//  {
//    wait(0.5);
//    for(auto iter = radioOutBufer.begin(); iter != radioOutBufer.end();)
//    {
//      auto complete = (*iter).second;
//      auto packet = (*iter).first;
//      if(complete)
//      {
//        // send packet
//        for(size_t i = 0; i < packet.payload_size; i++)
//        {
//          pc.putc(packet.payload[i]);
//        }
//        pc.printf("\r\n");
//
//        iter = radioOutBufer.erase(iter);
//      }
//      else
//      {
//        iter++;
//      }
//    }
//  }
//}