	.text
	.syntax unified
	.thumb
	.global	gcd	
	.type gcd, %function
gcd:
	push {r4-r7}
/*
	Your implementation goes here. 
*/
	movs r3, #0 // int d
	
.FirstWHILE:
	movs r4, #1
	tst r0, r4 // a & 1
	bne .SecondWHILE
	tst r1, r4 // b & 1
	bne .SecondWHILE
	lsrs r0, 1
	lsrs r1 ,1
	adds r3, 1
	bal .FirstWHILE

.SecondWHILE:
	cmp r0,r1
	beq .END

.FirstIF:
	movs r4, #1
	tst r0, r4 // if (!(a & 1))
	bne .SecondIF
	lsrs r0, r4
	bal .SecondWHILE

.SecondIF:	// if !(b & 1)
	movs r4 ,#1
	tst r1, r4
	bne .ThirdIF
	lsrs r1, r4
	bal .SecondWHILE

.ThirdIF:	//if a > b
	cmp r0 ,r1
	blt .ELSE
	subs r0 ,r0, r1
	lsrs r0 ,#1
	bal .SecondWHILE

.ELSE:  // a < b
	subs r1, r1, r0
	lsrs r1, 1
	bal .SecondWHILE
.END:
	lsls r0, r0, r3
	pop {r4-r7}
	bx	lr
