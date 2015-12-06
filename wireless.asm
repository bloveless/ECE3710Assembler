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
