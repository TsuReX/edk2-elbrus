
#include "YurchDxe.h"

/**
  Main entry

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.
  @param[in] SystemTable    A pointer to the EFI System Table.

  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval other             Some error occurs when executing this entry point.

**/
EFI_STATUS
EFIAPI
YurchDxeEntryPoint (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
	DEBUG ((EFI_D_INFO, "YurchDxeEntryPointPoint(): Hello from DXE phase \n"));

	return EFI_SUCCESS;
}

