`timescale 100ns/1ps

`include "BLDC_Motor.v"

module main;

    localparam DUTY_CYCLE_WIDTH = 10;
    localparam ENC_COUNT_WIDTH = 15;
    localparam HALL_COUNT_WIDTH = 7;


    reg SYS_CLK = 0;
    reg enable, counts_reset = 0;
    reg [2:0] hall = 0;
    reg [1:0] enc = 0;
    reg [DUTY_CYCLE_WIDTH-1:0] duty_cycle = 0;
    wire [2:0] phase_high, phase_low;
    wire [ENC_COUNT_WIDTH-1:0] encoder_count;
    wire [HALL_COUNT_WIDTH-1:0] hall_count;
    wire fault;


    BLDC_Motor #(
        .MIN_DUTY_CYCLE             ( 0 ) ,
        .MAX_DUTY_CYCLE             ( 1<<DUTY_CYCLE_WIDTH ) ,
        .MAX_DUTY_CYCLE_COUNTER     ( 1<<DUTY_CYCLE_WIDTH ) ,
        .ENCODER_COUNT_WIDTH        ( ENC_COUNT_WIDTH ) ,
        .HALL_COUNT_WIDTH           ( HALL_COUNT_WIDTH )
        ) bldc_motor (
        .clk            ( SYS_CLK ) ,
        .en             ( enable ) ,
        .reset_counts   ( counts_reset ) ,
        .duty_cycle     ( duty_cycle ) ,
        .enc            ( enc ) ,
        .hall           ( hall ) ,
        .phaseH         ( phase_high ) ,
        .phaseL         ( phase_low ) ,
        .enc_count      ( encoder_count ) ,
        .hall_count     ( hall_count ) ,
        .hall_fault     ( fault ) 
    );


    // Clock
    initial begin
        #0.5;
        forever begin
            #0.5 SYS_CLK = ~SYS_CLK;
        end
    end


    initial begin
        forever begin
            #15 enc = 2'b00;
            #15 enc = 2'b01;
            #15 enc = 2'b11;
            #15 enc = 2'b10;
        end
    end


    // Used to simulate a properly functioning hall effect sensor with all valid values.
    initial begin
        forever begin
            hall = 3'b001;
            #3000 hall = 3'b101;
            #3000 hall = 3'b100;
            #3000 hall = 3'b110;
            #3000 hall = 3'b010;
            #3000 hall = 3'b011;
            #3000;
        end
    end

    initial begin
        forever begin
            #100000 counts_reset = 1;
            #1 counts_reset = 0;
        end
    end


/*
    // Used to simulate a connected hall effect sensor that is disconnected and reconnected then runs through every valid value.
    initial begin
        forever begin
            hall = 3'b001;
            #3000 hall = 3'b101;
            #3000 hall = 3'b100;
            #3000 hall = 3'b110;
            #3000 hall = 3'b010;
            #3000 hall = 3'b011;
            #3000 hall = 3'b111;
            #75000;
            #10 hall = 3'b100;  // simulated noise upon plugging in
            #14 hall = 3'b110;
            #12 hall = 3'b010;
            #125 hall = 3'b100;
            #203 hall = 3'b011;
            #30000;
        end
    end
*/


/*
    // Used to simulate a hall effect sensor that is broken and shorting all of the input pins to ground.
    initial begin
        forever begin
            hall = 3'b000;
            #70000;
            hall = 3'b010;
            #70000;
        end
    end
*/


/*
    initial begin
        forever begin
            #100000 duty_cycle = 0;
            #10000 duty_cycle = 120;
            #10000000;
        end
    end
*/

    initial begin
        forever begin
            #30000; duty_cycle <= duty_cycle + 4;
        end
    end


    initial begin
        forever begin
            #10 enable = 1;
        end
    end

    initial begin
        forever begin
            #1000000 $stop;
        end
    end

endmodule
