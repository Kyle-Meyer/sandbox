%define STDOUT 1
%define SYSCALL_EXIT 60	;95;0c
%define SYSCALL_WRITE 1
	section .data
msgEr:	db	10, "Invalid entry, your word must START with a capitol letter AND END in '.', '?', or '!'", 10, 0
msgDf:	db	"This is the original message.", 10, 0
newLine: db	10, 0
	section .text
	global	validate

	
validate:			;the opener


	cmp     [rdi], byte 65	;check to see if we are at or "above" capitol A
        jge      capCheck	;if so move on
	jmp	messageFault	;if not, throw an error


	;; this is the message check loop, when we encounter the end of the input, signaled by the new line character we move on to process the final character
messageCheckLoop:
	cmp	[rdi], byte 10		
	je	messageCheckLast
	inc	rdi
	inc	rdx
	jmp	messageCheckLoop

	;; check the last, character, since we are at the new line character, we decrement by 1 so that we can get the second to last character, then we compare to see if its a '.', '?', or '!', if it is we go to the "correct" end if not throw an error
messageCheckLast:
	dec	rdi
	mov	dl, [rdi]
	cmp	[rdi], byte 46
	je	checkEndG
	cmp	[rdi], byte 63
	je	checkEndG
	cmp	[rdi], byte 33
	je	checkEndG
	jmp	messageFault

;; the second part of the cap check, now we see if the character is "above" capital Z, if it is then we throw an error, if not, move onto the message check loop to iterate over the string until the end
capCheck:
	cmp	[rdi], byte 90
	jg	messageFault
	xor	rdx, rdx
	jmp	messageCheckLoop

;; the message fault is for throwing an error, we print the respective message, then we pass a 0 into rax for a binary check back in encrypt.asm
messageFault:
	mov	rdi, msgEr
	call	print
	mov	rdi, newLine
	call	print
	mov	rax, 0
	ret

;;; the standard print function, prints characters until null character is detected
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

;;; the correct ending, if we make it here, then we move a 1 into rax for the binary check and return back into our function
checkEndG:
	mov	rax, 1
	ret
