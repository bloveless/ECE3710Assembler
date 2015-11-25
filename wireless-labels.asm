.data
    @file character_memory.txt

.text
    WLSW   49
    WLSW   3
    WLSW   0
    WLSW   0
    WLSR   $1
    SETI   $14 1
    OR     $14 1
    WLSREG $14
    SETI   $15 :end
:end
    JMP    $15