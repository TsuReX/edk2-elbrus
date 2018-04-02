/** @file
 C functions in SEC

 **/

#include "SecMain.h"

EFI_PEI_TEMPORARY_RAM_SUPPORT_PPI gSecTemporaryRamSupportPpi =
									{ SecTemporaryRamSupport };

EFI_PEI_PPI_DESCRIPTOR mPeiSecPlatformInformationPpi[] = { {
		(EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
		&gEfiTemporaryRamSupportPpiGuid, &gSecTemporaryRamSupportPpi } };

//
// These are IDT entries pointing to 10:FFFFFFE4h.
//
UINT64 mIdtEntryTemplate = 0xffff8e000010ffe4ULL;

/**
 Caller provided function to be invoked at the end of InitializeDebugAgent().

 Entry point to the C language phase of SEC. After the SEC assembly
 code has initialized some temporary memory and set up the stack,
 the control is transferred to this function.

 @param[in] SecCoreData    The first input parameter of InitializeDebugAgent().

 **/
VOID EFIAPI SecStartupPhase2( IN VOID *SecCoreData);

/**

 Entry point to the C language phase of SEC. After the SEC assembly
 code has initialized some temporary memory and set up the stack,
 the control is transferred to this function.


 @param SizeOfRam           Size of the temporary memory available for use.
 @param TempRamBase         Base address of tempory ram
 @param BootFirmwareVolume  Base address of the Boot Firmware Volume.
 **/
VOID EFIAPI SecStartup( IN UINT32 SizeOfRam,
						IN UINT32 TempRamBase,
		 				IN VOID *BootFirmwareVolume ) {

	EFI_SEC_PEI_HAND_OFF SecCoreData;
	IA32_DESCRIPTOR IdtDescriptor;
	SEC_IDT_TABLE IdtTableInStack;
	UINT32 Index;
	UINT32 PeiStackSize;

	PeiStackSize = (SizeOfRam >> 1);

	ASSERT(PeiStackSize < SizeOfRam);

	//
	// Process all libraries constructor function linked to SecCore.
	//
	ProcessLibraryConstructorList();

	//
	// Initialize floating point operating environment
	// to be compliant with UEFI spec.
	//
	InitializeFloatingPointUnits();

	// |-------------------|---->
	// |Idt Table          |
	// |-------------------|
	// |PeiService Pointer |    PeiStackSize
	// |-------------------|
	// |                   |
	// |      Stack        |
	// |-------------------|---->
	// |                   |
	// |                   |
	// |      Heap         |    PeiTemporayRamSize
	// |                   |
	// |                   |
	// |-------------------|---->  TempRamBase

	IdtTableInStack.PeiService = 0;
	for (Index = 0; Index < SEC_IDT_ENTRY_COUNT; Index++) {
		CopyMem((VOID*) &IdtTableInStack.IdtTable[Index],
				(VOID*) &mIdtEntryTemplate, sizeof(UINT64));
	}

	IdtDescriptor.Base = (UINTN) & IdtTableInStack.IdtTable;
	IdtDescriptor.Limit = (UINT16)(sizeof(IdtTableInStack.IdtTable) - 1);

	AsmWriteIdtr(&IdtDescriptor);

	//
	// Update the base address and length of Pei temporary memory
	//
	SecCoreData.DataSize = (UINT16) sizeof(EFI_SEC_PEI_HAND_OFF);
	SecCoreData.BootFirmwareVolumeBase = BootFirmwareVolume;
	SecCoreData.BootFirmwareVolumeSize = (UINTN)(
			0x100000000ULL - (UINTN) BootFirmwareVolume); // 4GB - BFVPosition
	SecCoreData.TemporaryRamBase = (VOID*) (UINTN) TempRamBase;
	SecCoreData.TemporaryRamSize = SizeOfRam;
	SecCoreData.PeiTemporaryRamBase = SecCoreData.TemporaryRamBase;
	SecCoreData.PeiTemporaryRamSize = SizeOfRam - PeiStackSize;
	SecCoreData.StackBase = (VOID*) (UINTN)(
			TempRamBase + SecCoreData.PeiTemporaryRamSize);
	SecCoreData.StackSize = PeiStackSize;

	//
	// Initialize Debug Agent to support source level debug in
	// SEC/PEI phases before memory ready.
	//
	InitializeDebugAgent(DEBUG_AGENT_INIT_PREMEM_SEC,
						 &SecCoreData,
						 SecStartupPhase2);

}

/**
 Caller provided function to be invoked at the end of InitializeDebugAgent().

 Entry point to the C language phase of SEC. After the SEC assembly
 code has initialized some temporary memory and set up the stack,
 the control is transferred to this function.

 @param[in] SecCoreData    The first input parameter of InitializeDebugAgent().

 **/
VOID EFIAPI SecStartupPhase2( IN VOID *SecCoreData) {

	EFI_PEI_CORE_ENTRY_POINT PeiCoreEntryPoint;
	EFI_SEC_PEI_HAND_OFF *SecCoreData = (EFI_SEC_PEI_HAND_OFF *) SecCoreData;

	//
	// Find Pei Core entry point.
	// It will report SEC and Pei Core debug information if remote debug
	// is enabled.
	//
	FindAndReportEntryPoints(
			(EFI_FIRMWARE_VOLUME_HEADER *) SecCoreData->BootFirmwareVolumeBase,
			&PeiCoreEntryPoint);

	if (PeiCoreEntryPoint == NULL) {
		CpuDeadLoop();
	}

	//
	// Transfer the control to the PEI core
	//
	ASSERT(PeiCoreEntryPoint != NULL);
	(*PeiCoreEntryPoint)(SecCoreData,
			(EFI_PEI_PPI_DESCRIPTOR *) &mPeiSecPlatformInformationPpi);

	//
	// Should not come here.
	//
	return;
}

/**
 This service of the TEMPORARY_RAM_SUPPORT_PPI that migrates temporary RAM into
 permanent memory.

 @param PeiServices            Pointer to the PEI Services Table.
 @param TemporaryMemoryBase    Source Address in temporary memory from which the SEC or PEIM will copy the
 	 	 	 	 	 	 	   Temporary RAM contents.
 @param PermanentMemoryBase    Destination Address in permanent memory into which the SEC or PEIM will copy the
 	 	 	 	 	 	 	   Temporary RAM contents.
 @param CopySize               Amount of memory to migrate from temporary to permanent memory.

 @retval EFI_SUCCESS           The data was successfully returned.
 @retval EFI_INVALID_PARAMETER PermanentMemoryBase + CopySize > TemporaryMemoryBase when
 	 	 	 	 	 	 	   TemporaryMemoryBase > PermanentMemoryBase.

 **/
EFI_STATUS EFIAPI SecTemporaryRamSupport( IN CONST EFI_PEI_SERVICES **PeiServices,
										  IN EFI_PHYSICAL_ADDRESS TemporaryMemBase,
										  IN EFI_PHYSICAL_ADDRESS PermanentMemBase,
										  IN UINTN CopySize) {

	IA32_DESCRIPTOR IdtDescriptor;
	VOID* OldHeap;
	VOID* NewHeap;
	VOID* OldStack;
	VOID* NewStack;
	DEBUG_AGENT_CONTEXT_POSTMEM_SEC DebugAgentContext;
	BOOLEAN OldStatus;
	UINTN PeiStackSize;

	PeiStackSize = (CopySize >> 1);

	ASSERT(PeiStackSize < CopySize);

	//
	// |-------------------|---->
	// |      Stack        |    PeiStackSize
	// |-------------------|---->
	// |      Heap         |    PeiTemporayRamSize
	// |-------------------|---->  TempRamBase
	//
	// |-------------------|---->
	// |      Heap         |    PeiTemporayRamSize
	// |-------------------|---->
	// |      Stack        |    PeiStackSize
	// |-------------------|---->  PermanentMemoryBase
	//

	OldHeap = (VOID*) (UINTN) TemporaryMemBase;
	NewHeap = (VOID*) ((UINTN) PermanentMemBase + PeiStackSize);

	OldStack = (VOID*) ((UINTN) TemporaryMemBase + CopySize - PeiStackSize);
	NewStack = (VOID*) (UINTN) PermanentMemBase;

	DebugAgentContext.HeapMigrateOffset = (UINTN) NewHeap - (UINTN) OldHeap;
	DebugAgentContext.StackMigrateOffset = (UINTN) NewStack - (UINTN) OldStack;

	OldStatus = SaveAndSetDebugTimerInterrupt(FALSE);
	//
	// Initialize Debug Agent to support source level debug
	// in PEI phase after memory ready.
	// It will build HOB and fix up the pointer in IDT table.
	//
	InitializeDebugAgent(DEBUG_AGENT_INIT_POSTMEM_SEC,
						 (VOID *) &DebugAgentContext, NULL);

	//
	// Migrate Heap
	//
	CopyMem(NewHeap, OldHeap, CopySize - PeiStackSize);

	//
	// Migrate Stack
	//
	CopyMem(NewStack, OldStack, PeiStackSize);

	//
	// We need *not* fix the return address because currently,
	// The PeiCore is executed in flash.
	//

	//
	// Rebase IDT table in permanent memory
	//
//	AsmReadIdtr(&IdtDescriptor); // TODO Remove or implement analog for Elbrus
	IdtDescriptor.Base = IdtDescriptor.Base - (UINTN) OldStack + (UINTN) NewStack;
//	AsmWriteIdtr(&IdtDescriptor); // TODO Remove or implement analog for Elbrus

	//
	// Program MTRR
	//

	//
	// SecSwitchStack function must be invoked after the memory migration
	// immediatly, also we need fixup the stack change caused by new call into
	// permenent memory.
	//
	SecSwitchStack((UINT32) (UINTN) OldStack, (UINT32) (UINTN) NewStack);

	SaveAndSetDebugTimerInterrupt(OldStatus);

	return EFI_SUCCESS;
}

// TODO REMOVE
void _ModuleEntryPoint() {

}
