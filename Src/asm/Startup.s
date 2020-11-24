.syntax	unified
.cpu	cortex-m4
.fpu	softvfp
.thumb

.section	.text.reset_handler
.weak		Reset_Handler
.type		Reset_Handler, %function
.thumb_func
Reset_Handler:
	ldr		sp, = stack_end

	movs	r1, #0
	b		DataInitLoop

DataInit:
	ldr		r3, = _sidata
	ldr		r3, [r3, r1]
	str		r3, [r0, r1]
	adds	r1, r1, #4

DataInitLoop:
	ldr		r0, = _sdata
	ldr		r3, = _edata
	adds	r2, r0, r1
	cmp		r2, r3
	bcc		DataInit

	ldr		r2, =_sbss
	b		BssInitLoop

BssInit:
	movs	r3, #0
	str		r3, [r2], #4

BssInitLoop:
	ldr		r3, = _ebss
	cmp		r2, r3
	bcc		BssInit

	// Enable FPU and FPU access
	bl		Enable_FPU
	
	bl		_mainCRTStartup

	bl		main

	// main should not return. If it does, trap in infinite loop.
	b		Infinite_Loop


.section	.text.enable_fpu
.type 		Enable_FPU, %function
.thumb_func
Enable_FPU:
	ldr		r0, =0xe000ed88
	ldr		r1, [r0]
	orr		r1, r1, #(0xf << 20)
	str		r1, [r0]
	dsb
	isb
	bx		lr

.section	.text.infinite_loop
.type		Infinite_Loop, %function
.global		Infinite_Loop
.thumb_func
Infinite_Loop:
	b		Infinite_Loop

.section	.text.exit
.type 		exit, %function
.weak 		exit
.thumb_func
exit:
	b		Infinite_Loop