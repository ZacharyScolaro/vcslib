#ifndef VCSLIB_H
#define VCSLIB_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MP_SYSTEM_TYPE 		0
#define MP_CLOCK_HZ			1
#define MP_FEATURE_FLAGS 	2

#define ST_NTSC_2600	0
#define ST_PAL_2600		1
#define ST_PAL60_2600	2
#define ST_NTSC_7800	3
#define ST_PAL_7800		4

#define FF_MULTI_CART	1 // Indicates elf is loaded by multicart and should allow exiting (return from main() function)


// Defines for VCS/2600 memory mapped registers
#define  VSYNC 0x00
#define  VBLANK 0x01
#define  WSYNC 0x02
#define  RSYNC 0x03
#define  NUSIZ0 0x04
#define  NUSIZ1 0x05
#define  COLUP0 0x06
#define  COLUP1 0x07
#define  COLUPF 0x08
#define  COLUBK 0x09
#define  CTRLPF 0x0A
#define  REFP0 0x0B
#define  REFP1 0x0C
#define  PF0 0x0D
#define  PF1 0x0E
#define  PF2 0x0F
#define  RESP0 0x10
#define  POSH2 0x11
#define  RESPONE 0x11
#define  RESM0 0x12
#define  RESM1 0x13
#define  RESBL 0x14
#define  AUDC0 0x15
#define  AUDC1 0x16
#define  AUDF0 0x17
#define  AUDF1 0x18
#define  AUDV0 0x19
#define  AUDV1 0x1A
#define  GRP0 0x1B
#define  GRP1 0x1C
#define  ENAM0 0x1D
#define  ENAM1 0x1E
#define  ENABL 0x1F
#define  HMP0 0x20
#define  HMP1 0x21
#define  HMM0 0x22
#define  HMM1 0x23
#define  HMBL 0x24
#define  VDELP0 0x25
#define  VDELP1 0x26
#define  VDELBL 0x27
#define  RESMP0 0x28
#define  RESMP1 0x29
#define  HMOVE 0x2A
#define  HMCLR 0x2B
#define  CXCLR 0x2C

#define CXP0FB 0x02


#define INPT4 0x000c
#define INPT5 0x000d
#ifndef SWCHA
#define SWCHA 0x0280
#endif


// 7800 Registers
#define INPTCTRL 0x01 // Write Only D3-D0: TIA, BIOS, MARIA, LOCK
// ******20 - 3F * ********MARIA REGISTERS * **************
#define BACKGRND 0x20 // Background Color                             write - only
#define P0C1 0x21 // Palette 0 - Color 1                          write - only
#define P0C2 0x22 // Palette 0 - Color 2                          write - only
#define P0C3 0x23 // Palette 0 - Color 3                          write - only
#define MARIA_WSYNC 0x24 // Wait For Sync                                write - only
#define P1C1 0x25 // Palette 1 - Color 1                          write - only
#define P1C2 0x26 // Palette 1 - Color 2                          write - only
#define P1C3 0x27 // Palette 1 - Color 3                          write - only
#define MSTAT 0x28 // Maria Status                                 read - only
#define P2C1 0x29 // Palette 2 - Color 1                          write - only
#define P2C2 0x2A // Palette 2 - Color 2                          write - only
#define P2C3 0x2B // Palette 2 - Color 3                          write - only
#define DPPH 0x2C // Display List List Pointer High               write - only
#define P3C1 0x2D // Palette 3 - Color 1                          write - only
#define P3C2 0x2E // Palette 3 - Color 2                          write - only
#define P3C3 0x2F // Palette 3 - Color 3                          write - only
#define DPPL 0x30 // Display List List Pointer Low                write - only
#define P4C1 0x31 // Palette 4 - Color 1                          write - only
#define P4C2 0x32 // Palette 4 - Color 2                          write - only
#define P4C3 0x33 // Palette 4 - Color 3                          write - only
#define CHARBASE 0x34 // Character Base Address                       write - only
#define P5C1 0x35 // Palette 5 - Color 1                          write - only
#define P5C2 0x36 // Palette 5 - Color 2                          write - only
#define P5C3 0x37 // Palette 5 - Color 3                          write - only
#define OFFSET 0x38 // Unused - Store zero here                     write - only
#define P6C1 0x39 // Palette 6 - Color 1                          write - only
#define P6C2 0x3A // Palette 6 - Color 2                          write - only
#define P6C3 0x3B // Palette 6 - Color 3                          write - only
#define CTRL 0x3C // Maria Control Register                       write - only
#define P7C1 0x3D // Palette 7 - Color 1                          write - only
#define P7C2 0x3E // Palette 7 - Color 2                          write - only
#define P7C3 0x3F // Palette 7 - Color 3                          write - only


// For firmware use only
void vcsLibInit(int initBusStuffing);

// For firmware or game use
extern const uint8_t ColorLookup[256];
extern const uint8_t ReverseByte[256]; // Reverses the order of the bits. 7..0 becomes 0..7. Useful for PF0, PF2, and reflecting sprites in software.

uint32_t randint();
void vcsJmp3();
void vcsLda2(uint8_t data);
void vcsSta3(uint8_t zeroPage);
uint8_t vcsRead4(uint16_t address);
void vcsCopyOverblankToRiotRam();
void vcsStartOverblank();
void vcsEndOverblank();
void vcsLdaForBusStuff2();
void vcsLdxForBusStuff2();
void vcsLdyForBusStuff2();
void vcsWrite3(uint8_t ZP, uint8_t data);
void vcsWrite5(uint8_t ZP, uint8_t data);
void vcsWrite6(uint16_t address, uint8_t data);
void vcsLdx2(uint8_t data);
void vcsLdy2(uint8_t data);
void vcsSta4(uint8_t ZP);
void vcsSax3(uint8_t ZP);
void vcsStx3(uint8_t ZP);
void vcsStx4(uint8_t ZP);
void vcsSty3(uint8_t ZP);
void vcsSty4(uint8_t ZP);
void vcsTxs2();
void vcsJsr6(uint16_t target);
void vcsNop2();
void vcsNop2n(uint16_t n);
void vcsPhp3();
void vcsPlp4();
void vcsPla4();
void vcsPlp4Ex(uint8_t data); // SP must point to TIA, only D5:D0 are driven because D7:D6 is TIA driven
void vcsPla4Ex(uint8_t data); // SP must point to TIA, only D5:D0 are driven because D7:D6 is TIA driven

// 7800
void vcsWaitForAddress(uint16_t address);
void vcsJmpToRam3(uint16_t addr);
void injectDmaData(int address, int count, const uint8_t* pBuffer);

#ifdef __cplusplus
}
#endif

#endif // VCSLIB_H
