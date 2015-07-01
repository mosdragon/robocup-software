/*
*  SPI_Comm.v
*  
*  The frontend communication interface for distribution and management of data requests.
*  
*/

// lots of things to sort out over the next week, but here's that start of it.

// Status Byte
// bit [7]: Not Ready
// bit [6]: No Motor Board
// bit [5]: RESERVED
// bit [4]: M4 Fault
// bit [3]: M3 Fault
// bit [2]: M2 Fault
// bit [1]: M1 Fault
// bit [0]: Dribbler Fault


// Address 0x00 - Motor Update
//
// Status Byte
// Encoder 1 Change
// Encoder 2 Change
// Encoder 3 Change
// Encoder 4 Change


// Address 0x01 through 0x04 - Motor Details
//
// Status Byte


// Address 0x05 - Get Version
//
// Status Byte
// Version Number