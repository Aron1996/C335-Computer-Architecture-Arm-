	.text
	.syntax unified
	.thumb
	.global	regName	
	.type regName, %function
regName:
	push {r4-r7}
	cmp r0, 15 // check if out of boundary 
	bgt .Error
	ldr r1, .labA   @ load contents of memory at labA (address of global_name)
	lsls r0, #2  // multiply r0 by 4 
	ldr r0, [r1, r0] // set the r0 to the position with offset
	b .END
.Error:
	movs r0, #0 // return 0 if out of range
.END:
	pop {r4-r7}
	bx	lr
	.align 2
.labA:
	.word names
