#include <avr/io.h>
//#include <printRegs.h>

.global hasAOne
hasAOne:
         cpse r24, r1
         ldi r24, 1
         ret

.global byteToAscii
byteToAscii:
         adiw r24, 48
         ret

.global int8ToInt
int8ToInt:
         ldi r25, 128
         cp r24, r25
         sbc r25, r25
         com r25
         ret
      
.global addInt8ToInt
addInt8ToInt:
         call int8ToInt
         add r24, r22
         adc r25, r23
         ret

.global add4Int8
add4Int8:
        call int8ToInt
        mov r27, r24
        mov r24, r22
        mov r22, r27
        mov r23, r25
        call addInt8ToInt
        mov r27, r24
        mov r24, r20
        mov r22, r27
        mov r23, r25
        call addInt8ToInt
        mov r27, r24
        mov r24, r18
        mov r22, r27
        mov r23, r25
        call addInt8ToInt
        ret

.global average
average:
       call int8ToInt
       add r24, r22
       ror r24
       ret
       
