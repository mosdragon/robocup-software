`include "phase_driver.vh"
`include "Hall_Effect_Sensor.v"
`include "Phase_Driver.v"


module robocup(clock, h, phaseHInv, phaseLInv); //re-add "duty_cycle,"  as port 2 after done testing

parameter ENC_COUNT_WIDTH = 15;
parameter DUTY_CYCLE_EIDTH = 10;
parameter HALL_COUNT_WIDTH = 7;

input clock;
input [2:0] h;
//input [`DUTY_CYCLE_WIDTH - 1 : 0] duty_cycle; re-add this line when done testing //TODO make FPGA read dutycycle
wire [2:0] z;
wire [2:0] u;

output [2:0] phaseHInv, phaseLInv;
wire [2:0] phaseHInv, phaseLInv, phaseH, phaseL;
reg [DUTY_CYCLE_WIDTH-1:0] duty_cycle = 10'h00F;


// Not actually used
reg [ENC_COUNT_WIDTH-1:0] enc_count;
reg [HALL_COUNT_WIDTH-1:0] hall_count;
reg fault;

// Dummy registers for synthesis right now
reg enable = 1'b1;
reg counts_reset = 1'b0;
reg enc = 2'b00;

    BLDC_Motor #(
        .MIN_DUTY_CYCLE             ( 0 ) ,
        .MAX_DUTY_CYCLE             ( 1<<DUTY_CYCLE_WIDTH ) ,
        .MAX_DUTY_CYCLE_COUNTER     ( 1<<DUTY_CYCLE_WIDTH ) ,
        .ENCODER_COUNT_WIDTH        ( ENC_COUNT_WIDTH ) ,
        .HALL_COUNT_WIDTH           ( HALL_COUNT_WIDTH )
        reg fault;)
        ) bldc_motor (
        .clk            ( clock ) ,
        .en             ( enable ) ,
        .reset_counts   ( counts_reset ) ,
        .duty_cycle     ( duty_cycle ) ,
        .enc            ( enc ) ,
        .hall           ( h ) ,
        .phaseH         ( phaseHInv ) ,
        .phaseL         ( phaseLInv ) ,
        .enc_count      ( encoder_count ) ,
        .hall_count     ( hall_count ) ,
        .hall_fault     ( fault ) 
    );

endmodule