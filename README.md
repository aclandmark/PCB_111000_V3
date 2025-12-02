# PCB_111000_V3
This version of PCB_111000 uses a CP2102 USB module
to enable the Atmega devices to communicate with a PC.
This replaces the discreet components used in versions 1 and 2.  
It also makes the PCB cheeper and easier to assemble.

There is one other change: The device that hosts user projects,
an Atmega 168 has been replaced with an Atmega 328.
User projects should not be affected but should be compiled for the
Arduino UNO pcb rather than for the Arduino Nano with an Atmega 168.

Set up procedure for PCB_111000_V3 is the same as that for V2 however
there are slight differences in the programs.
8_UNO_AVR_Programmer_V3 is replaced by UNO_PCB_111000_V3_programmer
5_Project_pcb_168_V2.30_Arduino_V2 is replaced by mini_OS programmer
No changes are expected for the mini-OS, so only the hex files are copied
into this repository.
