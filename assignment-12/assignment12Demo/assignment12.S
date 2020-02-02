#include <avr/io.h>
#include "asmMacros.s"  // Include macros to print log messages or a single register

.data

globalVariable: .byte 0

.text



.global updateGlobal
updateGlobal:
  // TODO: void updateGlobal(byte a)
  ldi  r26, lo8(globalVariable)
  ldi  r27, hi8(globalVariable)
  push r28
  ld   r28, X
  add  r28, r24
  st   X, r28
  pop  r28
  ret


.global getGlobal
getGlobal:
  // TODO: uint8_t getGlobal()
  ldi r26, lo8(globalVariable)
  ldi r27, hi8(globalVariable)
  ld  r24, X
  ret


.global cStringLength
cStringLength:
  // TODO: uint8_t cStringLength(const char aString[])
              mov r26, r24
              mov r27, r25
              ldi r22, 0
              ldi r21, 0
testString:
              ld r24, X+
              cp r24, r21
              breq returnLength
              inc r22
              jmp testString
returnLength:
              mov r24, r22
              ret

.global sumArrays
sumArrays:
  // TODO: void sumArrays(uint8_t *a, uint8_t *b, uint8_t *c, byte length)
          push r28
          push r29
          mov r26,r24 //-------
          mov r27,r25 //*a -> X
          mov r28,r22 //-------
          mov r29,r23 //*b -> Y
          mov r30,r20 //-------
          mov r31,r21 //*c -> Z
sumLoop:
          cp r18, r1
          breq returnSum
          ld r20, X+
          ld r22, Y+
          add r20,r22
          st Z+, r20
          dec r18
          jmp sumLoop
returnSum:
          pop r29
          pop r28
          ret   

.global dot
dot:
  // TODO uint16_t dot(uint8_t *a, uint8_t *b, byte length)
          mov r26, r24 // ------
          mov r27, r25 //*a -> X
          mov r30, r22 // ------
          mov r31, r23 //*b -> Z
          clr r24
          clr r25
dotLoop:
          cp r20, r1
          breq returnDot
          ld r22, X+
          ld r18, Z+
          mul r22, r18
          add r24, r0
          adc r25, r1
          clr r1
          dec r20
          jmp dotLoop
returnDot:          
          ret
