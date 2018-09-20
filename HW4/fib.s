	.text
	.syntax unified
	.thumb
	.global	fib	
	.type fib, %function
fib:
	push {r4-r7}
/*
	Your implementation goes here. 
*/
	cmp r0, #2
	blt .END
	movs r2, #0 //r2 = prev2
	movs r1, #1 //r1 = prev1
	movs r3, #0 //r3 = val
.LOOP:
	adds r3, r1, r2 // val = prev1 + prev2
	movs r2, r1 // prev2 = prev1 
	movs r1, r3 // prev1 = val
	subs r0,#1
	cmp r0,#1
	bne .LOOP
.END:
	movs r0, r3
	pop {r4-r7}
	bx	lr			
