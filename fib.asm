.data
    1

.text
// Whole line comment
    SETI    $2  0 // After asm comment

    SETI    $15 0xFF        // Tabbed after asm comment

    LSH     $15 8


ADDI    $15 0xF9
    SETI    $0  1
                        // random comment
    SETI    $1  1
ADD     $0  $1
WAIT    500



            STOR    $0  $2
    ADD     $1  $0

    WAIT    500
    STOR    $1  $2

    JMP     $15

