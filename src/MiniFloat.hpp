/* Set the FPU control word as cw = (cw & ~unMask) | (unNew & unMask),
 * i.e. change the bits in unMask to have the values they have in unNew,
 * leaving other bits unchanged. */
_CRTIMP unsigned int __cdecl _controlfp (unsigned int unNew, unsigned int unMask);
#define _MCW_PC     0x00030000  /* Precision */
#define _PC_24      0x00020000
#define _PC_53      0x00010000