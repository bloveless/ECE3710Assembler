.data
    @file character_memory.txt

.text
//Setup comparison register to test which pane you are on,
//initialize to 0, the first pane
SETI $13 0

//compare register 13 to 1, if it is 1, then we branch to the section for pane 2
CMPI $13 1
BGE 34 //NUMBER this number needs to go down to the pane 2 section

//Want to check each button, start with upper left
//Use $14 to compare to X and $15 to compare to y
SETI    $15 0x78
LSHIL   $15 8
ADDI    $15 0x18
SETI    $14 0x76
LSHIL   $14 8
ADDI    $14 0x16
TCHBRCH 0x3C //NUMBER need to go down to wireless section if touched else proceed

//upper right button (2)
//X offset by 28, Y offset by 0
SETI    $15 0x78
LSHIL   $15 8
ADDI    $15 0x18

SETI    $14 0x76
LSHIL   $14 8
ADDI    $14 0x16
//add the offset
ADDI    $14 0x1C
TCHBRCH 0x36 //NUMBER need to go down to wireless section if touched else proceed

//lower left (3)
//X offset will be 0, Y offset will be -5
SETI    $15 0x78
LSHIL   $15 8
ADDI    $15 0x18
SUBI    $15 0xFB //need to subtract so input twos complement of -5 in hex

SETI    $14 0x76
LSHIL   $14 8
ADDI    $14 0x16
TCHBRCH 0x30 //NUMBER need to go down to wireless section if touched else proceed

//Lower right (4) if pressed need to proceed to pane 2
//X offset by 28, Y offset by -5
SETI    $15 0x78
LSHIL   $15 8
ADDI    $15 0x18
SUBI    $15 0xFB //need to subtract so input twos complement of -5 in hex
SETI    $14 0x76
LSHIL   $14 8
ADDI    $14 0x16
ADDI    $14 0x1C
TCHBRCH 0x29 ////NUMBER this will branch to a location where the pane register is added by 1
//If no button touched then go back and check button 1
JMP 0

//PANE 2 Section basically the same code
//upper left
SETI    $15 0x78
LSHIL   $15 8
ADDI    $15 0x18
SETI    $14 0x76
LSHIL   $14 8
ADDI    $14 0x16
TCHBRCH 0x23 //NUMBER need to go down to wireless section if touched else proceed

//upper right button (2)
//X offset by 28, Y offset by 0
SETI    $15 0x78
LSHIL   $15 8
ADDI    $15 0x18

SETI    $14 0x76
LSHIL   $14 8
ADDI    $14 0x16
//add the offset
ADDI    $14 0x1C
TCHBRCH 0x1D //NUMBER need to go down to wireless section if touched else proceed

//lower left (3)
//X offset will be 0, Y offset will be -5
SETI    $15 0x78
LSHIL   $15 8
ADDI    $15 0x18
SUBI    $15 0xFB //need to subtract so input twos complement of -5 in hex

SETI    $14 0x76
LSHIL   $14 8
ADDI    $14 0x16
TCHBRCH 0x17 //NUMBER need to go down to wireless section if touched else proceed

//Lower right (4) if pressed need to proceed to pane 2
//X offset by 28, Y offset by -5
SETI    $15 0x78
LSHIL   $15 8
ADDI    $15 0x18
SUBI    $15 0xFB //need to subtract so input twos complement of -5 in hex
SETI    $14 0x76
LSHIL   $14 8
ADDI    $14 0x16
ADDI    $14 0x1C
TCHBRCH 0x10 //wireless section
//Need to loop back to top of Pane 2 if nothing is pressed
JMP 0x1f //NUMBER needs to change

//This section of instructions gives the 8 wireless commands, each with a jump instruction back to reinitializing the pane register
//Button 1 (bubbler on/off) wireless command
WLS 1
JMP 0 //jump back to the top of the stackthis is (TOPOFSTACK-C)

//Button 2 (heater on/off) wireless command
WLS 2
JMP 0 //jump back to the top of the stackthis is (TOPOFSTACK-C)

//Button 3 (pump on/off) wireless command
WLS 3
JMP 0 //jump back to the top of the stackthis is (TOPOFSTACK-C)

//Button 4, need to add 1 to compare register and jump to compare statement
ADDI $13 1
JMP 1

//LIGHT 1 (Morning) wireless command
WLS 4
JMP 0 //jump back to the top of the stackthis is (TOPOFSTACK-C)

//LGIHT 2 (NOON) wireless command
WLS 5
JMP 0 //jump back to the top of the stackthis is (TOPOFSTACK-C)

//LIGHT 3 (EVENING) wireless command
WLS 6
JMP 0 //jump back to the top of the stackthis is (TOPOFSTACK-C)

//LIGHT 4 (NIGHT) need to add 1 to compare register and jump to compare statement
WLS 6
JMP 0 //jump back to the top of the stackthis is (TOPOFSTACK-C)