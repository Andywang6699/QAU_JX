 	IMPORT sum5
	AREA TEST,CODE,READONLY	
	ENTRY
START
	LDR SP,=0x1000
	MOV R0,#3
	MOV R1,#4
	MOV R2,#5
	MOV R3,#6
	MOV R4,#7
	STR R4,[SP]
	BL sum5
loop
	B loop
	END