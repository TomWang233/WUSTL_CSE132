#include <avr/io.h>
#include "asmMacros.s"  // Include macros to print log messages or a single register
.text


.global slowDivisionUint8
slowDivisionUint8:
  // TODO: uint8_t slowDivisionUint8(uint8_t a, uint8_t b)
  //test division 
  ldi r20, 0 //counter
  while_loop:
  cp r24,r22 // compare r24 to r22, if greater, still in the loop
  brlo after_loop
  //ldi r18, r22 // 22 is the divisor, load to 18
  sub r24, r22 // subtrat the divispr
  inc r20 // increment counter
  jmp while_loop //while loop
  after_loop:
  mov r24, r20
  ret


.global greaterThanOrEqualUInt16
greaterThanOrEqualUInt16:
  sub r24, r22
  sbc r25, r23
  brlo ret_true
  ldi r24, 1 // else return false 
  ret 
  ret_true:
  ldi r24, 0
  ret


.global slowDivisionUint16
slowDivisionUint16:
  //ldi r21, 0
  //ldi r20, 1 // used for comparison in greater than or equal
  ldi r27, 0
  ldi r26, 0 // count 
  ldi r18, 1 // increment
  ldi r19, 0 // high bit of increment, also used for true/false comparison
for_loop2:
  push r24
  push r25
  call greaterThanOrEqualUInt16
  cp r24,r19
  breq end_for
  pop r25 
  pop r24
  sub r24, r22
  sbc r25, r23
  add r26, r18
  adc r27, r19
  jmp for_loop2
end_for:
  pop r25
  pop r24
  mov r24, r26
  mov r25, r27
  ret

.global slowModulusUint8
slowModulusUint8:
  // TODO: uint16_t slowModulusUint8(uint8_t a, uint8_t b)
  mov r26, r24 // dividend 
  mov r27, r25 // higher bit
  call slowDivisionUint8 //output use r24,r25, then use r24
  mul r22, r24 // div result * divisor to get the mod
  movw r24, r0
  sub r26, r24
  mov r24, r26
//  clr r26 
//  clr r27
//  clr r23
//  clr r22
  ret


.global sumOddsUint8
sumOddsUint8:
//  uint16_t sum = 0;
//  while(min<=max) {
//    if(slowModulusAlgorithm(min,2) == 1) {
//      //if odd, will have remainder of 1
//      sum+=min;
//    }
//    min++;
//  }
//  return sum;
  mov r18, r24 // min copy now at r18
  mov r17, r22 // max
  clr r27
  ldi r16, 0
  ldi r22, 2 // mod by 2 
  ldi r26, 0 // sum result
  ldi r23, 1 // mod comp
  while_loop3: //***loop begins 
  cp r17, r18 // compare min max 
  brlo end_loop3
  mov r24, r18
  //push r27
  push r26
  push r27
  push r23
  push r22
  push r21
  push r20
  push r19
  push r18
  push r17
  push r16
  call slowModulusUint8 // now r24 contails mod result
  pop r16
  pop r17
  pop r18
  pop r19
  pop r20
  pop r21
  pop r22
  pop r23
  pop r27
  pop r26
  cp r24, r23
  brne incre // simply increment 
  //printRegs 19
  add r26, r18 // else sum += min
  //ldi r19, 0
  adc r27, r16
  incre:
  inc r18 // min ++
  jmp while_loop3
  end_loop3:
  //ldi r25, 0
  mov r25, r27
  mov r24, r26
  ret
