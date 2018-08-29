/** @file
**/

#include <Base.h>
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
//#include <Library/PrintLib.h>
//#include <Library/PcdLib.h>
//#include <Library/BaseMemoryLib.h>
//#include <Library/SerialPortLib.h>
//#include <Library/DebugPrintErrorLevelLib.h>

//
// Define the maximum debug and assert message length that this library supports 
//
#define MAX_DEBUG_MESSAGE_LENGTH  0x100

/**
  The constructor function initialize the Serial Port Library

  @retval EFI_SUCCESS   The constructor always returns RETURN_SUCCESS.

**/
RETURN_STATUS
EFIAPI
ElbrusDebugLibSerialPortConstructor (
  VOID
  )
{
  return RETURN_UNSUPPORTED;
}

UINT32 BufferLen(IN CONST CHAR8 *Buffer)
{
	ASSERT (Buffer != NULL);
	UINT32 Length = 0;
	for (; Buffer[Length] != 0 /* != '\0'*/; ++Length);

	return Length;
}

/**
**/
VOID
EFIAPI
DebugPrint (
  IN  UINTN        ErrorLevel,
  IN  CONST CHAR8  *Format,
  ...
  )
{
	SerialPortWrite (Format, BufferLen(Format));
}


/**
**/
VOID
EFIAPI
DebugAssert (
  IN CONST CHAR8  *FileName,
  IN UINTN        LineNumber,
  IN CONST CHAR8  *Description
  )
{
}


/**
**/
VOID *
EFIAPI
DebugClearMemory (
  OUT VOID  *Buffer,
  IN UINTN  Length
  )
{
	return RETURN_UNSUPPORTED;
}


/**
**/
BOOLEAN
EFIAPI
DebugAssertEnabled (
  VOID
  )
{
  return RETURN_UNSUPPORTED;
}


/**  
**/
BOOLEAN
EFIAPI
DebugPrintEnabled (
  VOID
  )
{
  return RETURN_UNSUPPORTED;
}


/**  
 **/
BOOLEAN
EFIAPI
DebugCodeEnabled (
  VOID
  )
{
  return RETURN_UNSUPPORTED;
}


/**  
**/
BOOLEAN
EFIAPI
DebugClearMemoryEnabled (
  VOID
  )
{
  return RETURN_UNSUPPORTED;
}

/**
**/
BOOLEAN
EFIAPI
DebugPrintLevelEnabled (
  IN  CONST UINTN        ErrorLevel
  )
{
  return RETURN_UNSUPPORTED;
}
