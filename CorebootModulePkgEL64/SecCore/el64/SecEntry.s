
//.global SecStartup
.global _ModuleEntryPoint, SecStartup
_ModuleEntryPoint:

	setwd wsz = 8, nfx = 1

//	addd 0x0, $SIZE_64KB, %dr10
	addd 0x0, 0x00010000, %dr10

//	addd 0x0, $BASE_512KB, %dr11
	addd 0x0, 0x00080000, %dr11

//	addd 0x0, ASM_PFX(PcdGet32 (PcdPayloadFdMemBase)), %dr12
	addd 0x0, 0x00800000, %dr12


	disp %ctpr1, SecStartup
	call %ctpr1, wbs = 5

