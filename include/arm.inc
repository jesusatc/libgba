@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@                                                                             @
@ Sistemas operativos empotrados                                              @
@                                                                             @
@ Constantes útiles para el manejo del procesador de la GBA                   @
@                                                                             @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Modos de ejecución y bits de estado                                         @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

.set ARM_MODE_USER,            0x10
.set ARM_MODE_FIQ,             0x11
.set ARM_MODE_IRQ,             0x12
.set ARM_MODE_SVC,             0x13
.set ARM_MODE_ABORT,           0x17
.set ARM_MODE_UNDEF,           0x1b
.set ARM_MODE_SYS,             0x1f

.set ARM_I_BIT,                0x80
.set ARM_F_BIT,                0x40
.set ARM_T_BIT,                0x20

