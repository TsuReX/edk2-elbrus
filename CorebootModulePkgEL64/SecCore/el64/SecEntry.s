/*
#------------------------------------------------------------------------------
# Module Name:
#
#  SecEntry.S
#
# Abstract:
#
#  This is the code that begins in protected mode.
#   It will transfer the control to pei core.
#
#------------------------------------------------------------------------------
*/
//ASM_GLOBAL  ASM_PFX(SecStartup)

//# Pcds
//ASM_GLOBAL  ASM_PFX(PcdGet32 (PcdPayloadFdMemBase))
/*
#
# SecCore Entry Point
#
# Processor is in flat protected mode
#
# @param[in]  EAX   Initial value of the EAX register (BIST: Built-in Self Test)
# @param[in]  DI    'BP': boot-strap processor, or 'AP': application processor
# @param[in]  EBP   Pointer to the start of the Boot Firmware Volume
#
# @return     None  This routine does not return
#
*/
/*ASM_GLOBAL ASM_PFX(_ModuleEntryPoint)
ASM_PFX(_ModuleEntryPoint):
  # Disable all the interrupts
  cli
  
  # Construct the temporary memory at 0x80000, length 0x10000
  movl $(BASE_512KB + SIZE_64KB), %esp

  # Pass BFV into the PEI Core
  pushl ASM_PFX(PcdGet32 (PcdPayloadFdMemBase))
  
  # Pass stack base into the PEI Core
  pushl $BASE_512KB

  # Pass stack size into the PEI Core
  pushl $SIZE_64KB


  # Pass Control into the PEI Core
  call SecStartup
  
  #  # Never return to here
  jmp .
*/
.global SecStartup
.global _ModuleEntryPoint
_ModuleEntryPoint:

	setwd wsz = 2, nfx = 1

	addd 0x0, 0x1, %dr0
	addd 0x0, 0x2, %dr1
	addd 0x0, 0x3, %dr2
	addd 0x0, 0xDEADBEAF, %dr3

	disp %ctpr1, SecStartup
	call %ctpr1, wbs = 0

