/** @file
  Elbrus UART Serial Port library functions
**/

#include <Base.h>
#include <Library/SerialPortLib.h>
#include <Library/PcdLib.h>
#include <Library/BaseLib.h>

//#include <IndustryStandard/Pci.h>
//#include <Library/IoLib.h>
//#include <Library/PlatformHookLib.h>


#define MAS_MOD_SHIFT		0
#define MAS_MOD_MASK		0x7
#define MAS_OPC_SHIFT		3
#define MAS_OPC_MASK		0xf

#define MAS_BE_SHIFT		3
#define MAS_BE_BIT			(1 << MAS_BE_SHIFT)
#define MAS_DC_SHIFT		5
#define MAS_DC_MASK			0x3

#define MAS(mod, opc)		(((opc) & MAS_OPC_MASK) << MAS_OPC_SHIFT \
							| ((mod) & MAS_MOD_MASK) << MAS_MOD_SHIFT)

#define MAS_MODE_STORE_IO	6
#define MAS_STORE_IO		MAS(MAS_MODE_STORE_IO, 0)

/* Store with specified MAS. */
#define mas_write(address, value, mas, size, channel) \
({ \
  asm volatile ("st" #size "," #channel " 0, %[addr], %[val], mas=%[m]" \
	: /* no outputs */ \
	: [addr] "r" (address), [val] "r" (value), [m] "i" (mas) \
	: "memory"); \
})

#define dbg_write(value)									\
		mas_write(0xFFF01001, value, MAS_STORE_IO, b, 2);	\
		for (INT32 i = 0; i < 100;) {						\
			i += 2; 										\
			i -= 1;	 										\
		}


/**
**/
UINT8
SerialPortReadRegister (
  UINTN  Base,
  UINTN  Offset
  )
{

	return RETURN_UNSUPPORTED;
}

/**
**/
UINT8
SerialPortWriteRegister (
  UINTN  Base,
  UINTN  Offset,
  UINT8  Value
  )
{
}

/**
 **/
UINT16
SerialPortLibUpdatePciRegister16 (
  UINTN   PciAddress,
  UINT16  Value,
  UINT16  Mask
  )
{
	return RETURN_UNSUPPORTED;
}

/**
**/
UINT32
SerialPortLibUpdatePciRegister32 (
  UINTN   PciAddress,
  UINT32  Value,
  UINT32  Mask
  )
{
	return RETURN_UNSUPPORTED;
}

/**
**/
UINTN
GetSerialRegisterBase (
  VOID
  )
{
	return RETURN_UNSUPPORTED;
}

/**
**/
BOOLEAN
SerialPortWritable (
  UINTN  SerialRegisterBase
  )
{
	return RETURN_UNSUPPORTED;
}

/**
 **/
RETURN_STATUS
EFIAPI
SerialPortInitialize (
  VOID
  )
{
	return RETURN_UNSUPPORTED;
}

/**
**/
UINTN
EFIAPI
SerialPortWrite (
  IN UINT8     *Buffer,
  IN UINTN     NumberOfBytes
  )
{

	UINTN i = 0;
	for (; i < NumberOfBytes; ++ i) {
		dbg_write(Buffer[i]);
	}
	return i;
}

/**
**/
UINTN
EFIAPI
SerialPortRead (
  OUT UINT8     *Buffer,
  IN  UINTN     NumberOfBytes
  )
{
	return 0;
}


/**
**/
BOOLEAN
EFIAPI
SerialPortPoll (
  VOID
  )
{
	return RETURN_UNSUPPORTED;
}

/**
**/
RETURN_STATUS
EFIAPI
SerialPortSetControl (
  IN UINT32 Control
  )
{
	return RETURN_UNSUPPORTED;
}

/**
**/
RETURN_STATUS
EFIAPI
SerialPortGetControl (
  OUT UINT32 *Control
  )
{
	return RETURN_UNSUPPORTED;
}

/**
**/
RETURN_STATUS
EFIAPI
SerialPortSetAttributes (
  IN OUT UINT64             *BaudRate,
  IN OUT UINT32             *ReceiveFifoDepth,
  IN OUT UINT32             *Timeout,
  IN OUT EFI_PARITY_TYPE    *Parity,
  IN OUT UINT8              *DataBits,
  IN OUT EFI_STOP_BITS_TYPE *StopBits
  )
{
	return RETURN_UNSUPPORTED;
}

