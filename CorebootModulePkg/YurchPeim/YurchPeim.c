
#include "YurchPeim.h"

/**
  This is the entrypoint of PEIM

  @param  FileHandle  Handle of the file being invoked.
  @param  PeiServices Describes the list of possible PEI Services.

  @retval EFI_SUCCESS if it completed successfully.
**/
EFI_STATUS
EFIAPI
YurchPeimEntryPoint (
		IN       EFI_PEI_FILE_HANDLE  FileHandle,
		IN CONST EFI_PEI_SERVICES     **PeiServices
)
{
	DEBUG ((EFI_D_INFO, "YurchPeimEntryPoint(): Hello from PEI phase \n"));

	return EFI_SUCCESS;
}

