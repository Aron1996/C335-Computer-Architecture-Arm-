	.text
	.syntax unified
	.thumb
	.global	stringLength
	.type stringLength, %function
stringLength:
	push {r4-r7}
	movs r1, #0 // set len to 0
.WHILE:
	ldrb r2, [r0, r1] // load length to r2
	cmp r2, #0 // check if it's null
 	beq .END 
	adds r1, #1 // length increment
	bal .WHILE   // return to while loop
.END:
	mov r0, r1
	pop {r4-r7}
	bx	lr
