@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@                                                                             @
@ Cabecera de los cartuchos                                                   @
@                                                                             @
@    Los primeros 192 bytes del cartucho contienen una cabecera que es        @
@    obligatoria para que la consola arranque el programa                     @
@                                                                             @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

@ La primera instrucción es un salto que se salta la cabecera
                b	fin_cabecera

@ Nintendo Logo (156 bytes)
.fill   156, 1, 0

@ Game Title (12 caracteres en mayúsculas)
.byte   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
.byte   0x00, 0x00, 0x00, 0x00

@ Game Code (4 caracteres en mayúsculas)
.byte   0x00, 0x00, 0x00, 0x00

@ Maker code (2 caracteres en mayúsculas, ej. "01" -> Nintendo)
.byte   0x30, 0x31

@ Fixed value (debe se 0x96)
.byte   0x96

@ Main Unit Code (Identifica el HW requerido. Debería ser 0x00)
.byte   0x00

@ Device Type (Tipo de cartucho)
.byte   0x00

@ Reserved Area (7 Bytes a 0)
.byte   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

@ Software Version Number (Número de versión del juego)
.byte   0x00

@ Complement Check (Checksum de la cabecera)
@ Se debe calcular como:
@ chk=0:for i=0A0h to 0BCh:chk=chk-[i]:next:chk=(chk-19h) and 0FFh
.byte   0xf0

@ Reserved Area (2 Bytes a 0)
.byte   0x00, 0x00

.align

fin_cabecera:
