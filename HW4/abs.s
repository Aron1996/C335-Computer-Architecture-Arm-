	.text
	.syntax unified
	.thumb
	.global	abs	
	.type abs, %function
abs:
	push {r4-r7}
/*
	Your implementation goes here. 
*/
	bpl .END
	subs r0,r0,#0
.END:
	pop {r4-r7}	
	bx	lr
