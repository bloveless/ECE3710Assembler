.data
	@file character_memory.txt

.text

	SETI $2 0
	SETI $0 2
	SETI $14 0x76
	LSH $14 8
	ADDI $14 0x16
	SETI $15 0x78
	LSH $15 8
	ADDI $15 0x18
	TCHBRCH :bubbler
	SETI $14 0xE8
	LSH $14 8
	ADDI $14 0x87
	SETI $15 0x78
	LSH $15 8
	ADDI $15 0x18
	TCHBRCH :heater
	SETI $14 0x76
	LSH $14 8
	ADDI $14 0x16
	SETI $15 0xE5
	LSH $15 8
	ADDI $15 0x87
	TCHBRCH :pump
	SETI $14 0xE8
	LSH $14 8
	ADDI $14 0x87
	SETI $15 0xE5
	LSH $15 8
	ADDI $15 0x87
	TCHBRCH :lights
	SETI $1 0
	STOR  $1 $0
	JMP $0

:bubbler
	SETI $1 1
	STOR  $1 $0
	CMPI $2 0
	BGE :bubbler_on
	SETI $2 0
	WLS 2
	WAIT 512
	JMP $0

:bubbler_on
	SETI $2 1
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

	WAIT 512
	JMP $0

:heater
	SETI $1 2
	STOR  $1 $0
	WLS 3
	WAIT 512
	JMP $0

:pump
	SETI $1 3
	STOR  $1 $0
	JMP $0

:lights
	SETI $1 4
	STOR  $1 $0
	JMP $0
