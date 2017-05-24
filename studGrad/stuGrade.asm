; Name: Eranus Thompson
; A program that assigns a letter grade

INCLUDE Irvine32.inc 

 .data 
	numb byte 90	
	;numb byte 80	;alternate test data
	;numb byte 70	;alternate test data
	;numb byte 60	;alternate test data
	;numb byte 50	;alternate test data
	;numb byte 110	;alternate test data
	;numb byte 40	;alternate test data
	 
	varA byte 'A'
	varB byte 'B'
	varC byte 'C'
	varD byte 'D'
	varE byte 'E'

.code 

main PROC
		
	mov al, numb	

	mov bl, 100
	cmp al, bl
	ja errCheck

	mov bl, 0
	cmp al, bl
	jl errCheck
	jmp comp_label
		
	comp_label:
		mov bl, 90
		cmp al, bl
		jge labelA

		mov bl, 80
		cmp al, bl
		jge labelB

		mov bl, 70
		cmp al, bl
		jge labelC

		mov bl, 60
		cmp al, bl
		jge labelD

		mov bl, 50
		cmp al, bl
		jge labelE

	errCheck:
		jmp endProg

	labelA:
		mov dl,varA
		jmp myGrade

	labelB:
		mov dl,varB
		jmp myGrade

	labelC:
		mov dl,varC
		jmp myGrade

	labelD:
		mov dl,varD
		jmp myGrade

	labelE:
		mov dl,varE
		jmp myGrade

	myGrade:
		mov ah,2
		jmp endProg

	endProg:			
		INVOKE ExitProcess,0 

   main ENDP
 END main 