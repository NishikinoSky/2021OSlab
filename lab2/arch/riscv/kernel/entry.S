.section .text.entry

.global trap_s
.extern handler_s
.equ reg_size, 0x8
.align 2

trap_s:
	#save callee-saved registers and spec
    addi sp, sp, -16
    sd ra, 0(sp)
    sd t0, 1(sp)
    sd t1, 2(sp)
    sd t2, 3(sp)
    sd a0, 4(sp)
    sd a1, 5(sp)
    sd a2, 6(sp)
    sd a3, 7(sp)
    sd a4, 8(sp)
    sd a5, 9(sp)
    sd a6, 10(sp)
    sd a7, 11(sp)
    sd t3, 12(sp)
    sd t4, 13(sp)
    sd t5, 14(sp)
    sd t6, 15(sp)
    csrr t0, sepc
    sd t0, 16(sp)
    
	# call handler_s(scause)
    csrr a0, scause
    call handler_s
    
	# load sepc and callee-saved registers
    ld t0, 16(sp)
    csrw sepc, t0
    ld ra, 0(sp)
    ld t0, 1(sp)
    ld t1, 2(sp)
    ld t2, 3(sp)
    ld a0, 4(sp)
    ld a1, 5(sp)
    ld a2, 6(sp)
    ld a3, 7(sp)
    ld a4, 8(sp)
    ld a5, 9(sp)
    ld a6, 10(sp)
    ld a7, 11(sp)
    ld t3, 12(sp)
    ld t4, 13(sp)
    ld t5, 14(sp)
    ld t6, 15(sp)
    addi sp, sp, 16
    
	sret
