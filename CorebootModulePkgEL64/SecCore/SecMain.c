/** @file
 C functions in SEC

**/

#include "SecMain.h"
#include "SecDebug.h"
#include "Library/DebugLib.h"

EFI_PEI_TEMPORARY_RAM_SUPPORT_PPI gSecTemporaryRamSupportPpi = {
	SecTemporaryRamSupport
};

EFI_PEI_PPI_DESCRIPTOR mPeiSecPlatformInformationPpi[] = {
	{
/*FLAGS*/	(EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
/*GUID*/	&gEfiTemporaryRamSupportPpiGuid,
/*PPI_PTR*/	&gSecTemporaryRamSupportPpi
	}
};

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

//	UINT32 Index;
	UINT32 PeiStackSize;

	PeiStackSize = (SizeOfRam >> 1);

	ASSERT(PeiStackSize < SizeOfRam);

	//
	// Process all libraries constructor function linked to SecCore.
	//
	ProcessLibraryConstructorList();

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

	SecCoreData.StackBase = (VOID*) (UINTN)(TempRamBase +
									 SecCoreData.PeiTemporaryRamSize);
	SecCoreData.StackSize = PeiStackSize;

	SecStartupPhase2(&SecCoreData);
}

/**
 Caller provided function to be invoked at the end of InitializeDebugAgent().

 Entry point to the C language phase of SEC. After the SEC assembly
 code has initialized some temporary memory and set up the stack,
 the control is transferred to this function.

 @param[in] SecCoreData    The first input parameter of InitializeDebugAgent().

 **/
VOID EFIAPI SecStartupPhase2( IN VOID *_SecCoreData) {

	EFI_PEI_CORE_ENTRY_POINT PeiCoreEntryPoint;
	EFI_SEC_PEI_HAND_OFF *SecCoreData = (EFI_SEC_PEI_HAND_OFF *) _SecCoreData;

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

	dbg_write('P');
	dbg_write('o');
	dbg_write('i');
	dbg_write('n');
	dbg_write('t');
	dbg_write('1');
	dbg_write('\n');
	dbg_write('\r');

//	DEBUG( (0, "Point2\n\r\0") );								// It doesn't work

//	DebugPrint(0, "Point2\n\r\0");								// It doesn't work

//	UINT8 Data[] = "Point2\n\r\0"; 								// It doesn't work

//	UINT8 Data[10] = {'P','o','i','n','t','2','\n','\r','\0'};	// It doesn't work


	UINT8 Data[9];	// It works normal
	Data[0] = 'P';
	Data[1] = 'o';
	Data[2] = 'i';
	Data[3] = 'n';
	Data[4] = 't';
	Data[5] = '2';
	Data[6] = '\n';
	Data[7] = '\r';
	Data[8] = '\0';


	DebugPrint(0, Data);

	dbg_write('P');
	dbg_write('o');
	dbg_write('i');
	dbg_write('n');
	dbg_write('t');
	dbg_write('3');
	dbg_write('\n');
	dbg_write('\r');


	(*PeiCoreEntryPoint)( SecCoreData,
						 (EFI_PEI_PPI_DESCRIPTOR *)&mPeiSecPlatformInformationPpi
						);

	// Should not come here.
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

	return EFI_SUCCESS;
}
