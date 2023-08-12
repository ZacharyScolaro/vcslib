#include "vcsLib.h"

// for mock builds
int main() { return 0; }

// For firmware use only
void vcsLibInit(int initBusStuffing) {}

// For firmware or game use
const uint8_t ColorLookup[256] = { 0 };
const uint8_t ReverseByte[256] = { 0 }; // Reverses the order of the bits. 7..0 becomes 0..7. Useful for PF0, PF2, and reflecting sprites in software.

uint32_t randint() { return 0; }
void vcsJmp3(){ }
void vcsLda2(uint8_t data){ }
void vcsSta3(uint8_t zeroPage){ }
uint8_t vcsRead4(uint16_t address) { return 0; }
void vcsCopyOverblankToRiotRam(){ }
void vcsStartOverblank(){ }
void vcsEndOverblank(){ }
void vcsLdaForBusStuff2(){ }
void vcsLdxForBusStuff2(){ }
void vcsLdyForBusStuff2(){ }
void vcsWrite3(uint8_t ZP, uint8_t data){ }
void vcsWrite5(uint8_t ZP, uint8_t data){ }
void vcsWrite6(uint16_t address, uint8_t data){ }
void vcsLdx2(uint8_t data){ }
void vcsLdy2(uint8_t data){ }
void vcsSta4(uint8_t ZP){ }
void vcsSax3(uint8_t ZP){ }
void vcsStx3(uint8_t ZP){ }
void vcsStx4(uint8_t ZP){ }
void vcsSty3(uint8_t ZP){ }
void vcsSty4(uint8_t ZP){ }
void vcsTxs2(){ }
void vcsJsr6(uint16_t target){ }
void vcsNop2(){ }
void vcsNop2n(uint16_t n){ }
void vcsPhp3(){ }
void vcsPlp4(){ }
void vcsPla4(){ }
void vcsPlp4Ex(uint8_t data){ } // SP must point to TIA, only D5:D0 are driven because D7:D6 is TIA driven
void vcsPla4Ex(uint8_t data){ } // SP must point to TIA, only D5:D0 are driven because D7:D6 is TIA driven

// 7800
void vcsWaitForAddress(uint16_t address){ }
void vcsJmpToRam3(uint16_t addr){ }
void injectDmaData(int address, int count, const uint8_t* pBuffer){ }
