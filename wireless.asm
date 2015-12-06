.data
    @file character_memory.txt

.text
	//Setup comparison register to test which pane you are on,
	//initialize to 0, the first pane
	SETI $13 0 // pane number
	SETI $1 0 // bubbler state
	SETI $2 0 // heater state


:begin
	//compare register 13 to 1, if it is 1, then we branch to the section for pane 2
	CMPI $13 1
	BGE :pane_two //NUMBER this number needs to go down to the pane 2 section

	//Want to check each button, start with upper left
	//Use $14 to compare to X and $15 to compare to y
	SETI    $14 0x76
	LSH     $14 8
	ADDI    $14 0x16

	SETI    $15 0x78
	LSH     $15 8
	ADDI    $15 0x18

	TCHBRCH :bubbler //NUMBER need to go down to wireless section if touched else proceed

	//upper right button (2)
	//X offset by 28, Y offset by 0
	SETI    $14 0xE8
	LSHIL   $14 8
	ADDI    $14 0x87

	SETI    $15 0x78
	LSHIL   $15 8
	ADDI    $15 0x18

	TCHBRCH :heater //NUMBER need to go down to wireless section if touched else proceed

	//lower left (3)
	//X offset will be 0, Y offset will be -5
	SETI    $14 0x76
	LSHIL   $14 8
	ADDI    $14 0x16

	SETI    $15 0xE5
	LSHIL   $15 8
	ADDI    $15 0x87

	TCHBRCH :pump //NUMBER need to go down to wireless section if touched else proceed

	//Lower right (4) if pressed need to proceed to pane 2
	//X offset by 28, Y offset by -5
	SETI    $14 0xE8
	LSHIL   $14 8
	ADDI    $14 0x87

	SETI    $15 0xE5
	LSHIL   $15 8
	ADDI    $15 0x87

	TCHBRCH :lights ////NUMBER this will branch to a location where the pane register is added by 1
	//If no button touched then go back and check button 1
	SETI $12 :begin
	JMP $12

:pane_two
	//PANE 2 Section basically the same code
	//upper left
	SETI    $14 0x76
	LSH     $14 8
	ADDI    $14 0x16

	SETI    $15 0x78
	LSH     $15 8
	ADDI    $15 0x18

	TCHBRCH :morning //NUMBER need to go down to wireless section if touched else proceed

	//upper right button (2)
	//X offset by 28, Y offset by 0
	SETI    $14 0xE8
	LSHIL   $14 8
	ADDI    $14 0x87

	SETI    $15 0x78
	LSHIL   $15 8
	ADDI    $15 0x18

	TCHBRCH :noon //NUMBER need to go down to wireless section if touched else proceed

	//lower left (3)
	//X offset will be 0, Y offset will be -5
	SETI    $14 0x76
	LSHIL   $14 8
	ADDI    $14 0x16

	SETI    $15 0xE5
	LSHIL   $15 8
	ADDI    $15 0x87

	TCHBRCH :evening //NUMBER need to go down to wireless section if touched else proceed

	//Lower right (4) if pressed need to proceed to pane 2
	//X offset by 28, Y offset by -5
	SETI    $14 0xE8
	LSHIL   $14 8
	ADDI    $14 0x87

	SETI    $15 0xE5
	LSHIL   $15 8
	ADDI    $15 0x87

	TCHBRCH :night //wireless section

	//Need to loop back to top of Pane 2 if nothing is pressed
	SETI $12 :pane_two
	JMP $12 //NUMBER needs to change

:bubbler
	CMPI $1 0
	BGE :bubbler_on
	SETI $12 :bubbler_off
	JMP $12

:heater
	CMPI $2 0
	BGE :heater_on
	SETI $12 :bubbler_off
	JMP $12

//This section of instructions gives the 8 wireless commands, each with a jump instruction back to reinitializing the pane register
//Button 1 (bubbler on/off) wireless command
:bubbler_on
	WLS 1

	//[LETTER N] Need to change blank space or F to letter N
    //initialize register to holder letter N
    SETI    $10 0x00
    LSH     $10 8
    ADDI    $10 0x17

    //[BLANK SPACE] Need to change F or preserve bank space
    SETI    $8 0x00
    LSH     $8 8
    ADDI    $8 0x24

    //this is the address of Bubbler O[_]_ 260 =261-1
    //change to N
    SETI    $9 0x00
    LSH     $9 8
    ADDI    $9 0x104

    //this is the address of Bubbler O_[_] 261 =262-1
    //change to blank space
    SETI    $11 0x00
    LSH     $11 8
    ADDI    $11 0x105
    //store N at that address 260
    STOR $10 $9
    //store _ at that address 261
    STOR $8 $11

	SETI $12 :begin
	JMP $12 //jump back to the top of the stackthis is (TOPOFSTACK-C)

:bubbler_off
	WLS 2

	//Need to change blank space or letter N to letter FF
	//initialize register to holder letter F
    SETI    $10 0x00
    LSH     $10 8
    ADDI    $10 0x0F
    //this is the address of Bubbler O[_]_ 260 =261-1
    SETI    $9 0x00
    LSH     $9 8
    ADDI    $9 0x104

    //this is the address of Bubbler O_[_] 261 =262-1
    SETI    $11 0x00
    LSH     $11 8
    ADDI    $11 0x105

    //store F at address 260
    STOR $10 $11

    //store F at address 261
    STOR $10 $9

	SETI $12 :begin
	JMP $12 //jump back to the top of the stackthis is (TOPOFSTACK-C)

:heater_on
	//Button 2 (heater on/off) wireless command
	WLS 2

	//[LETTER N] Need to change blank space or F to letter N
    //initialize register to holder letter N
    SETI    $10 0x00
    LSH     $10 8
    ADDI    $10 0x17

    //[BLANK SPACE] Need to change F or preserve bank space
    SETI    $8 0x00
    LSH     $8 8
    ADDI    $8 0x24

    //this is the address of Bubbler O[_]_ 287 =288-1
    //change to N
    SETI    $9 0x00
    LSH     $9 8
    ADDI    $9 0x11F

    //this is the address of Bubbler O_[_] 288 =289-1
    //change to blank space
    SETI    $11 0x00
    LSH     $11 8
    ADDI    $11 0x120
    //store N at that address 287
    STOR $10 $9
    //store _ at that address 288
    STOR $8 $11

	SETI $12 :begin
	JMP $12 //jump back to the top of the stackthis is (TOPOFSTACK-C)

:heater_off
	WLS 3

	//Need to change blank space or letter N to letter FF
    //initialize register to holder letter F
     SETI    $10 0x00
     LSH     $10 8
     ADDI    $10 0x0F
     //this is the address of Bubbler O[_]_ 287 =288-1
     SETI    $9 0x00
     LSH     $9 8
     ADDI    $9 0x11F

     //this is the address of Bubbler O_[_] 288 =289-1
     SETI    $11 0x00
     LSH     $11 8
     ADDI    $11 0x120

     //store F at address 288
     STOR $10 $11

     //store F at address 289
     STOR $10 $9

	SETI $12 :begin
	JMP $12 //jump back to the top of the stackthis is (TOPOFSTACK-C)

:pump
	//Button 3 (pump on/off) wireless command
	WLS 9
	SETI $12 :begin
	JMP $12 //jump back to the top of the stackthis is (TOPOFSTACK-C)

:lights
	//Button 4, need to add 1 to compare register and jump to compare statement
	ADDI $13 1
	SETI $12 :begin
	JMP $12 //jump back to the top of the stackthis is (TOPOFSTACK-C)

:morning
	//LIGHT 1 (Morning) wireless command
	WLS 6
	SETI $12 :begin
	JMP $12 //jump back to the top of the stackthis is (TOPOFSTACK-C)

:noon
	//LGIHT 2 (NOON) wireless command
	WLS 5
	SETI $12 :begin
	JMP $12 //jump back to the top of the stackthis is (TOPOFSTACK-C)

:evening
	//LIGHT 3 (EVENING) wireless command
	WLS 7
	SETI $12 :begin
	JMP $12 //jump back to the top of the stackthis is (TOPOFSTACK-C)

:night
	//LIGHT 4 (NIGHT) need to add 1 to compare register and jump to compare statement
	WLS 8
	SETI $12 :begin
	JMP $12 //jump back to the top of the stackthis is (TOPOFSTACK-C)