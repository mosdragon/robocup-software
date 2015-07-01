/*
*  SPI_Comm.v
*  
*  The frontend communication interface for distribution and management of data requests.
*  
*/

// lots of things to sort out over the next week, but here's the start of it.

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


// SPI_Comm module
module SPI_Comm ( clk, sck, d_in, d_out, n_cs);

// Module parameters - passed parameters will overwrite the values here
parameter RX_BUFFER_LEN =       ( 14 );
parameter BITS_IN_TRANSFER =    ( 8 );

// Module inputs/outputs
input clk, sck, d_in, n_cs;
output d_out;
// ===============================================


// Local parameters - can not be altered outside this module
// ===============================================
localparam BYTE_COUNT_WIDTH =   $clog2( RX_BUFFER_LEN );
localparam BIT_COUNT_WIDTH =    $clog2( BITS_IN_TRANSFER );

// State machine declarations for readability
// ===============================================
localparam STATE_RX_START =     0;
localparam STATE_RX_EXECUTE =   1;
localparam STATE_RX_END =       2;

localparam STATE_TX_START =     0;
localparam STATE_TX_EXECUTE =   1;
localparam STATE_TX_END =       2;


// // Register and Wire declarations
// ===============================================

// Register for holding the current RX/TX states
reg [1:0] rx_state = STATE_RX_START;
reg [1:0] tx_state = STATE_TX_START;

// Synced inputs declarations
reg sck_s =     0 ,
    n_cs_s =    0 ,
    d_in_s =    0 ;

// Delayed inputs declarations
reg sck_d =     0 ,
    n_cs_d =    0 ;

// Holds the values for the current RX/TX lines in the SCK domain
reg rx_bit = 0;
reg tx_bit = 0;

// holds the values for the current RX/TX bytes
reg [BITS_IN_TRANSFER-1:0] rx_byte = 0;
reg [BITS_IN_TRANSFER-1:0] tx_byte = 0;

// Counters for tracking the current bit in the current byte
reg [BIT_COUNT_WIDTH-1:0] bit_count = 0;      // resets every byte_count change
reg [BYTE_COUNT_WIDTH-1:0] byte_count = 0;

// RX buffer for storing the incoming bytes
reg [BITS_IN_TRANSFER-1:0] rx_buffer [0:RX_BUFFER_LEN];

// Flags to set the beginning and end of an SPI transfer
wire start_strobe = ( ( n_cs_s == 1 ) && ( n_cs_d == 0 ) );
wire end_strobe =   ( ( n_cs_s == 0 ) && ( n_cs_d == 1 ) );

// Flags to indicate transitions for the SCK line
wire sck_rising_edge =   ( ( sck_d == 0 ) && ( sck_s == 1 ) );
wire sck_falling_edge =  ( ( sck_d == 1 ) && ( sck_s == 0 ) );


always @ (posedge clk) begin : SPI_SYNC_IO
    // Sync the inputs and outputs
    sck_s <= sck;
    d_in_s <= d_in;
    n_cs_s <= n_cs;
    d_out <= d_out_s;

    // The inputs delayed by one clock cycle
    sck_d <= sck_s;
    n_cs_d <= n_cs_s;
endmodule


/* 
*  Sample the RX bit on the rising of of SCK. This means the transmitting end of the interface should setup for an
*  SPI configuration where the data is valid on the rising end of SCK. [ CPOL = 0; CPHA = 0 ]
*/
always @ (sck_rising_edge) begin : SPI_RX

    // Only do something if the chip select line is active (active low here).
    if ( n_cs_s == 0 ) begin
        case (rx_state)

            STATE_RX_START: begin
                // Reset everything
                bit_count <= 0;
                byte_count <= 0;
                rx_state <= STATE_RX_EXECUTE;
            end    // STATE_RX_START

            STATE_RX_EXECUTE: begin
                rx_byte[bit_count] <= d_in_s;

                // Increment the byte counter once fully received
                if ( bit_count == ( BITS_IN_TRANSFER - 1 ) ) begin
                    bit_count <= 0;
                    byte_count <= byte_count + 1;
                    rx_buffer[byte_count] <= rx_byte;
                end

                // This state exits when `end_strobe` is true
            end    // STATE_RX_EXECUTE

            STATE_RX_END: begin

                // Do things here that need to be done when an SPI RX transfer is over.
            end    // STATE_RX_END

        endcase
    end
end


/* 
*  Set the TX bit on the falling of of SCK. This means the receiving end of the interface should setup for an
*  SPI configuration where the data is sampled on the leading edge of the clock. [ CPOL = 0; CPHA = 0 ]
*/
always @ (sck_falling_edge) begin : SPI_TX
    // Only do something if the chip select line is active (active low here).
    if ( n_cs_s == 0 ) begin
        case (tx_state)

            STATE_TX_START: begin
                d_out_s <= tx_bit;
                tx_state <= STATE_TX_EXECUTE;
            end    // STATE_TX_START

            STATE_TX_EXECUTE: begin
                
            end    // STATE_TX_EXECUTE

            STATE_TX_END: begin
                
                // Do things here that need to be done when an SPI TX transfer is over.
            end    // STATE_TX_END

        endcase
    end
end


// Set the RX/TX states according to an SPI tranfer beginning or ending
always @(start_strobe) begin
    rx_state <= STATE_RX_START;
    tx_state <= STATE_TX_START;
end


always @(end_strobe) begin : 
    rx_state <= STATE_RX_END;
    tx_state <= STATE_TX_START;
end


endmodule