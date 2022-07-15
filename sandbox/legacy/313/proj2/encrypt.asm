	
				;95;0c95;0c95;0crecursive subrou
%define STDOUT 1		;95;0c95;0c
%define SYSCALL_EXIT 60	
%define SYSCALL_WRITE 1
	
EXTERN mirrorAlg
EXTERN shift
EXTERN validate
        section .data

	


	
msg1:   db      "Welcome to Encryptor: here options: ", 10, 0  ;C-style \0 terminated string
							       ;95;0c
msg2:   db      10, "r -  Enter New Message ",10, 0
msg3:	db	10, "d -  Display Current  Message ", 10, 0
msg4:	db	10, "s -  Shift Encrypt ", 10, 0
msg5:	db 	10, "m -  Mirror Encrypt ", 10, 0
msg6:	db	10, "q -  Quit ", 10, 0
msgCmp1: db	"**Original Message: ", 0
msgCmp2: db	"**Encrypted Message: ", 0
msgDf:	db	"This is the original message.", 10, 0
numMsg:	db	10, "please enter the amount of bits to shift by", 10, 0
redMsg:	db	10, "please enter the message you would like to shift", 10, 0
inpMsg:	db	10, "Enter your choice now: ", 10, 0
dpMsg: db	10, "Here is the unencrypted message:", 10, 0
msgEr:	db	10, "Invalid entry, your word must end in '.', '?', or '!'", 10, 0
choiceEr: db	10, "improper choice your selection must be lower case 'r', 'd', 's', 'm', or 'q'", 10, 10, 0
shiftMsg: db	10, "Here is your shifted message: " , 10, 0
shiftEr: db	10, "that is an invalid value (0-25) ", 10, 0
mirrorMsg2: db	10, "here is your mirrored message: ", 10, 0
debug:	db	10, "place holder for stuff", 10, 0
newLine: db	10, 0
debug2:  db      10, "here", 10, 0
start:	db	100		;95;0c
char:   db      10, 0


	section .bss		;95;0c
useL:	resb	14
inp:	resb	255
inpUnencrypt:	resb 255
useS:	resb	6
useLen:	resb	6
mirrorMsg: resb 255

	
        section .text
        global main
;;; the start, load in our default message, and move into the menu
main:				;95;0c
	call    defaultMessage
        call	menu
	call	print
	syscall			;95;0c
;;; standard exit call
exit:
        mov     rax, SYSCALL_EXIT
        xor     rdi, rdi
	syscall

;;; the menu of the program, everytime we return to the menu we copy our unencryped input back into our regular input so we can start from square one each time we apply a shift of some kind, then print the standard messages, get the user choice, and preform the following action based on their choice, if they enter some invalid choice, then they will get an error message
menu:
	call	reCopy
	mov     rdi, msg1
        call    print

        mov     rdi, msg2
        call    print

        mov     rdi, msg3
        call    print
	
        mov     rdi, msg4
        call    print

        mov     rdi, msg5
        call    print

        mov     rdi, msg6
        call    print

	mov	rdi, inpMsg
	call	print
        call    _getNum

        cmp     al, 114
        je      readMsg

        cmp     al, 100
        je      dispMsg

        cmp     al, 115
        je      shiftBase

        cmp     al, 109
        je      mirrorBase
	
	cmp     al, 113
        je      exit

	jmp	choiceError
	ret



breaker:
	ret
;;; standard print call
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
;;; standard print call, but now we check for message length, only used for user based input
print1:
        mov     rax, rdi        ;95;0c                                        
	mov	rcx, [useLen]
	xor     rdx, rdx

count1:
        cmp     [rdi], byte 10   ;null character?                              
        je      end_count1
	cmp	[rdi], byte 0,
	je	end_count1
	cmp	rdx, rcx
	je	end_count1
        inc     rdx
        inc     rdi
        jmp     count1

end_count1:
        mov     rsi, rax
        mov     rax, SYSCALL_WRITE
        mov     rdi, STDOUT
        syscall
	mov	rdi, newLine
	call	print
        ret
;;; a loop to copy character by character the "This is the original message string" into input and unencrypted input, by the end it also makes the uselen 31
defaultMessage:
	mov	rcx, msgDf
	mov	rbx, inp
	mov	rdi, inpUnencrypt
	xor	rdx, rdx
defaultLoop:
	cmp	rdx, 255
	je	defaultEnd
	mov	al, [rcx]
	mov	[rbx], al
	mov	[rdi], al
	inc	rbx
	inc	rdi
	inc	rcx
	inc	rdx
	jmp	defaultLoop
defaultEnd:
	mov	rdx, 31
	mov	[useLen], rdx
	ret

;;; the recopy function simply copies each chaaracter from the unencrypted input back into the regular input so that we can start over each time we apply a shift
reCopy:
	xor	rcx, rcx
	xor	rdi, rdi
	xor	rdx, rdx
	mov	rbx, useLen
	mov	rcx, inpUnencrypt
	mov	rdi, inp
reCopyLoop:
	cmp	rdx, 255
	je	reCopyEnd
	mov	al, [rcx]
	mov	[rdi], al
	inc	rcx
	inc	rdi
	inc	rdx
	jmp	reCopyLoop
reCopyEnd:
	
	ret

;;; get the user choice for the main menu, since it can only be 1 digit long we dont have to worry about any MSB to LSB conversions, just apply the 48 offset and continue on
_getNum:
	mov	rax, 0
	mov	rdi, 0
	mov	rsi, useL
	mov	rdx, 2
	syscall
	mov    	al, [useL]
	call	breaker
	movsx	rbx, al
	mov 	[useL], al
	ret


;;;here we first grab the user input from our buffer using standard system calls, then we copy it to memory, call the copy function so we can store it in the unencrypted input, get the message size, then call on validate to make sure that it is a legal entry
readMsg:
	mov	rdi, redMsg
	call	print
	mov     rax, 0          ;sys_read. Read what user inputs               
	mov     rdi, 0          ;From stdin                                    
	mov     rsi, inp        ;Save user input to buffer
        mov	[inp], rsi	;save it back to memory
        mov     rdx, 255
	syscall
	mov	rdi, [inp]
	call	copy		;copy it to unencrypted input
	call	messageLen	;get the length
	jmp	validateBase	;check to see if its valid

;;; similar to recopy but now we work in reverse, copying from inp to inpEnencrypt, but we first empty out the unencypted string just in case there was something there before
copy:

	xor	rdx, rdx
	call	empty
	xor	rdx, rdx
	mov	rcx, inpUnencrypt
	mov	rdi, inp

copyLoop:

	cmp	[rdi], byte 10
	je	copyEnd
	mov	al, [rdi]
	mov	[rcx], al
	inc	rdx
	inc	rdi
	inc	rcx
	jmp	copyLoop
copyEnd:
	inc	rdx
	inc	rdi
	mov	al, [rdi]
	mov	[rcx], al
	ret
empty:
	mov	rcx, inpUnencrypt
	xor	rdx, rdx

;;; a loop to empty out inp unencrpyt
emptyLoop:
	cmp	rdx, 255
	je	emptyEnd
	mov	al, 10
	mov	[rcx], al
	inc	rcx
	inc	rdx
	ret
emptyEnd:

	ret

;;; iterate over the string until we encounter the new line, signifying the end of our string, then we store the incremented rdx as our length
messageLen:

	mov	rcx, inp
	xor	rdx, rdx
lengthLoop:
	cmp	[rcx], byte 10
	je	lengthEnd
	inc	rdx
	inc	rcx
	jmp	lengthLoop
lengthEnd:
	
	mov	[useLen], rdx
	ret

;;; just a function to display the unencrypted message
dispMsg:
	mov	rdi, dpMsg
	call	print
	mov     rdi, inpUnencrypt
	call    print1
	jmp 	menu

;;; move the appropriate contents to the proper registers then call on the shift subroutine
shiftBase:
	mov	r12, [useLen]
	mov	rdi, inp
	call 	shift
	mov     rdi, msgCmp1
        call    print
        mov     rdi, inpUnencrypt
        call    print1
        mov     rdi, newLine
        call    print
	mov	rdi, msgCmp2
	call	print
	mov	rdi, inp
	call	print1
	mov	rdi, newLine
	call	print
	jmp 	menu

;;; move the appropriate contents to the proper registers then call on the mirror subroutine, then print the results
mirrorBase:
	mov	rcx, [useLen]
	mov     rdi, inp
	call	mirrorAlg
	mov     rdi, msgCmp1
        call    print
        mov     rdi, inpUnencrypt
        call    print1
        mov     rdi, newLine
        call    print
	mov	rdi, msgCmp2
	call	print
	mov	rdi, inp
	call	print1
	mov	rdi, newLine
	call	print
	jmp	menu
	

;;; move the appropriate contents to the proper registers then call on the validate subroutine, and check the binary rax to see if the message was rejected, if it was, copy the defualt message, if not, just go back to the menu	
validateBase:
	mov     rdi, inp
        mov     rax, rdi
        mov     rbx, inpUnencrypt
        xor     rdx, rdx
        call    validate
	cmp     rax, 0
        je      defaultMessageArrange
	jmp     menu
defaultMessageArrange:
	call	defaultMessage
	jmp	menu

;;; if the user entered an incorrect choice in the menu
choiceError:
	mov	rdi, choiceEr
	call	print
	jmp	menu
