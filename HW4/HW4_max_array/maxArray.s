	.text
	.syntax unified
	.thumb
	.global	maxArray
	.type maxArray, %function
maxArray:
	push {r4-r7}

	movs r2, #0 //set the largest element
	movs r3, #0

.LARGE:
	cmp r1,#0 //compare the size
	beq .END
	ldr r4, [r0, r3]
	adds r3, #4
	subs r1, #1 // decrement the size
	cmp r2,r4 // compare with largest element
	bgt .LARGE // if it's not continue 
	movs r2, r4 // if it is replace current with largest 
	bal .LARGE

.END:
	movs r0,r2
	pop {r4-r7}
	bx	lr

//Get help on this assembly code from Jiebo Wang
