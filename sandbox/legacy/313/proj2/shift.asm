%define STDOUT 1
%define SYSCALL_EXIT 60	
%define SYSCALL_WRITE 1
	section .data
shiftEr: db	10, "that is an invalid value (0-25) ", 10, 0
newLine: db	10, 0
shiftMsg: db	10, "Here is your shifted message: " , 10, 0
numMsg:	db	10, "please enter the amount of bits to shift by", 10, 0

	section .bss
useS:	resb	6
	section .text
	global	shift


;;; the start
shift:
	mov	rbx, rdi	;copy the input pointer to rbx
	call	getShift
	mov	rdi, rbx	;copy back to rdi for the shifting loop
	xor	rdx, rdx	;start at 0

;;; the shifting loop, move through our string and for each alphabetical, apply a shift, re copy the bit shift with each loop back into rcx just to be safe 
looper:			;start our loop function

	xor	r10, r10
	xor	r8, r8
	xor 	rcx, rcx
	cmp	[rdi], byte 0
	je 	end_counter
	cmp	rdx, 31
	je	end_counter
	mov	rcx, [useS]
	call	distinguish	;to check for lower case v upper case
	inc	rdx
	inc	rdi
	jmp	looper


;;; the end of our shift encrypt, we dont need to pass anything to rax since we we've already done our modifications
end_counter:
       
	mov	rdi, newLine
	call	print
        ret
	
distinguish:
	cmp	[rdi], byte 60	;see if we are above A
	jge	upperCase	;if so move to the next check
	ret
	
upperCase:
	cmp	[rdi], byte 90	;check to see if we are between A and Z
	jbe	checkUpper	;if so run the standard check for applying the shift
	jmp	lowerCase	;if not then it must be greater in ASCII value so we should see if its lower case

lowerCase:
	cmp	[rdi], byte 97	;make sure that its at a
	jge	evenLowerCase	;if so move to the upper bounding check
	ret			;if not then its a bracket of some kind and we should return

evenLowerCase:
	cmp	[rdi], byte 122	;make sure that its below or equal to lower z
	jbe	checkLower	; if so we can proceed to applying the shift
	ret

;;; after all is said and done, we now apply our offeste to the current character in the string
applyOffset:
	
	sub	r10, r8
	add	[rdi], r10
	ret
;;; see if we are within range for the lower case alphabet, first check starting at lower case a
checkLower:
	cmp	[rdi], byte 97
	jge	checkLowerMax
	ret

;;; second part of the lower case check, if we are above lower case z then we are out of bounds and must "correct" our offset
checkLowerMax:
	movsx	r10, byte [rdi]
	movsx	r8, byte [rdi]
	add	r10, rcx
	cmp	r10, 122
	jg	lowerCorrect
	jmp	applyOffset

;;; correcting the offset, we just subtract out 25 so that we can "start" back at lower case A
lowerCorrect:
	sub	r10, 25
	jmp	applyOffset

;;; check to see if we are in range of the upper case alphabet, if above or equal to upper case A , continue
checkUpper:	
	
	cmp     [rdi], byte 65
        jge     checkUpperMax
	ret
;;; second check to see if we are within range of the upper case alphabet, if we are above captial Z then we are out of bounds and must apply a correction to our offset
checkUpperMax:
	movsx   r10, byte [rdi]
	movsx   r8, byte [rdi]
	add     r10, rcx
        cmp     r10, 90
        jg      lowerCorrect
	jmp	applyOffset

;;; standard error for if user entered an offset greater than 25 or ower than 0
shiftError:
	mov	rdi, shiftEr
	call	print
	jmp	getShift

	
;;; getting our useres desired shift amount, we read in the string version of the number they desire, then move into the loop portion to convert it into a number
getShift:
	mov 	rdi, numMsg
	call 	print
	
        mov     rax, 0
        mov     rdi, 0
        mov     rsi, useS
        mov     rdx, 3
	syscall
	mov	rsi, useS
	xor 	rdx, rdx

;;; this loop works on the way contents are stored in a register, and that is by LSB to MSB, so when we move '26'for example into our register, it gets stored as '62', meaning we can apply a formula where we subtract out 48 to grab the integer version of each character, then multiply by a factor of 10 for each character and add it to the result, once the loop finishes executing, we end up with a double digit integer version of our input
shiftLoop:
	movsx	rax, byte [rsi] ;grab the character
	inc	rsi
	cmp	rax, 10 	;see if its a new line, if it is, we are done
	je	endShift
	sub	rax, 48		;offset the value to make it a regular 1-9 int
	imul	rdx, 10		;multiply by our factor of 10
	add	rdx, rax	;add everything to our running total
	jmp	shiftLoop

	
;;; the end of getting our shift amount, if its above 25, or below 0, then its illegal and will reprompt the user for input
endShift:
	cmp	rdx, 25
	jg	shiftError
	cmp	rdx, 0
	jl	shiftError
	mov	[useS], rdx
	ret


;;; standard print loop for static messages
print:
        mov     rax, rdi	;95;0c
        xor     rdx, rdx

count:
        cmp     [rdi], byte 0   ;null character?
        je      end_count
        inc     rdx
        inc     rdi
        jmp     count

end_count:
        mov     rsi, rax
        mov     rax, SYSCALL_WRITE
        mov     rdi, STDOUT
        syscall

        ret
breaker:
	ret
