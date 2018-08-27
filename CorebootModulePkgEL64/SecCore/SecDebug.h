/*
 * SecDebug.h
 *
 *  Created on: 24 Á×Ç. 2018 Ç.
 *      Author: yurchenko_v
 */

#ifndef COREBOOTMODULEPKGEL64_SECCORE_SECDEBUG_H_
#define COREBOOTMODULEPKGEL64_SECCORE_SECDEBUG_H_

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

/* Store 8-bit value with specified MAS. */
#define mas_write8(address, value, mas, channel) \
		mas_write(address, value, mas, b, channel)

#define dbg_write(value) \
		mas_write(0xFFF01001, value, MAS_STORE_IO, b, 2);	\
		for (INT32 i = 0; i < 100;) {						\
			i += 2; 										\
			i -= 1;	 										\
		}


#endif /* COREBOOTMODULEPKGEL64_SECCORE_SECDEBUG_H_ */
