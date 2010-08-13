#!/bin/sh
# Read and write ATmega8 fuses connected to /dev/parport0 with a stk200
# programmer.  These values seem to work
#  lfuse = 0xdf
#  hfuse = 0xd9

# read fuses
uisp -dprog=stk200 -dpart=atmega8 --rd_fuses
# write fuses
avrdude -c stk200 -p m8 -P /dev/parport0 -U lfuse:w:0xdf:m -U hfuse:w:0xd9:m
