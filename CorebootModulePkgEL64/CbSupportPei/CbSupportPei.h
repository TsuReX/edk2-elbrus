/** @file
  The header file of Coreboot Support PEIM.

Copyright (c) 2014 - 2016, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/


#ifndef __PEI_COREBOOT_SUPPORT_H__
#define __PEI_COREBOOT_SUPPORT_H__

#include <PiPei.h>

#include <Library/PeimEntryPoint.h>
#include <Library/PeiServicesLib.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/HobLib.h>
#include <Library/PcdLib.h>
//#include <Library/MtrrLib.h>
#include <Library/IoLib.h>
#include <Guid/SmramMemoryReserve.h>
#include <Guid/MemoryTypeInformation.h>
#include <Guid/FirmwareFileSystem2.h>
#include <Ppi/MasterBootMode.h>

#include "../../CorebootModulePkgEL64/Include/Coreboot.h"
#include "../../CorebootModulePkgEL64/Include/Guid/AcpiBoardInfoGuid.h"
#include "../../CorebootModulePkgEL64/Include/Guid/FrameBufferInfoGuid.h"
#include "../../CorebootModulePkgEL64/Include/Guid/SystemTableInfoGuid.h"
#include "../../CorebootModulePkgEL64/Include/Library/CbParseLib.h"
#include "../../CorebootModulePkgEL64/Include/Library/CbPlatformSupportLib.h"

typedef struct {
  UINT32  UsableLowMemTop;
  UINT32  SystemLowMemTop;
} CB_MEM_INFO;

#endif
