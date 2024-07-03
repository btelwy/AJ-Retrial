;Add assembly code to play title music
;Replace instruction at 208AE98, mov r2, #0x3 with b 20B8E18

;There:
ldr r11, [r15,#-0xC] ;Load 20ED50A into r11
mov r2, #0x4
strb r2, [r11]
stmdb r13!, {r0-12}
sub r0, r11, #0x4A ;set r0 to 20ED4C0
mov r1, #0x1
mov r2, #0x50
bl 201C43C ;readText, with parameters r0, r1, r2
ldmia r13!, {r0-r12}
mov r2, #0x3 ;putting back instruction replaced earlier
b 208AE9C ;branch back