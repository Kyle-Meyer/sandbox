%define STDOUT 1
%define SYSCALL_EXIT 60	;95;0c
%define SYSCALL_WRITE 1
	section .data
newLine: db	10, 0
	
	section .text
	global mirrorAlg


;;; the start
mirrorAlg:
	mov     rbx, rdi
	xor 	rdx, rdx
;;; similar to shift, we move through each character until we encounter the length of string, which is stored in rcx, the null character, or the new line character
mirrorLoop:
	cmp	[rdi], byte 10
	je	mirrorEnd
	cmp	[rdi], byte 0
	je	mirrorEnd
	cmp	rdx, rcx
	je	mirrorEnd
	call	mirrorDistinguish
	call	breaker
	inc	rdx
	inc	rdi
	jmp	mirrorLoop
;;; determine if our character is lower case or upper case, we also copy in our value of the character to r10, and then copy it to r11 for mathematical purposes later
mirrorDistinguish:	
	movsx	r10, byte [rdi]
	mov	r11, r10
        cmp     [rdi], byte 65   
        jge     upperCaseMir
 	ret
;;; second part of checking our upper case, if its within the range of the alphabet then we will set our axiom to the middle M being 77, subtract out our original character value to get the distance to the axiom, then multiply by 2 and add 1 to get the position of our mirrored character in the alphabet, we then add this calculated offset to the original characters position
upperCaseMir:
	cmp	[rdi], byte 90
	jg	mirrorLowerCheck
	mov	r8, 77
	mov	r9, 77
	sub	r8, r10
	add	r8, r8
	jmp	mirrorOffset

;;; checking to see if we are within ange of the lower case alphabet
mirrorLowerCheck:
	cmp	[rdi], byte 97
	jge	mirrorLowerCheckAgane
	ret
;;; if we are then we set our axiom to lower case m (109) and do our calculation from there
mirrorLowerCheckAgane:
	cmp	[rdi], byte 122
	jg	mirrorTooHigh
	mov	r8, 109
	mov	r9, 109
	sub	r8, r10
	add	r8, r8
	jmp	mirrorOffset

;;; if we are out of range of our acceptable characters then we return back to the loop as we do not need to do anything for our function
mirrorTooHigh:
	ret
;;; apply the final offset to our character position
mirrorOffset:
	
	add	r8, 1

	add	[rdi], r8
	ret

;;; the end of our mirror call
mirrorEnd:

	mov	rdi, newLine
	call	print
        ret

;;; standard print function
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
	
