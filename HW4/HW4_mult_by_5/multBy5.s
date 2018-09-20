	.text
	.syntax unified
	.thumb
	.global	multBy5	
	.type multBy5, %function
multBy5:
	push {r4-r7}
/*
	Your implementation goes here. 
*/
	movs r1, r0
	lsls r0, #2
	adds r0, r1
.END:
	pop {r4-r7}	
	bx	lr
