	AREA TEST,CODE,READONLY
	ENTRY
START	LDR R0,=0XEE000000
		LDR R1,=0X12345678
		LDR R4,=0X3000
		STR R1,[R4]
		LDR R3,[R4]
		LDR R4,=0X4000
		MOV R0,R0,LSR #24
		STRB R0,[R4],#1
		MOV R6,#0
LSLR3	MOV R3,R3,LSR #8
		STRB R3,[R4],#1
		ADD R6,R6,#1
		CMP R6,#3
		BNE LSLR3
		LDR R4,=0X4000
		LDR R1,[R4]
;LOOP	B LOOP
	END