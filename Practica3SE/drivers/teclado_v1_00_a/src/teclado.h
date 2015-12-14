/*****************************************************************************
* Filename:          C:\hlocal\SE\p3\Practica3SE\Practica3SE/drivers/teclado_v1_00_a/src/teclado.h
* Version:           1.00.a
* Description:       teclado Driver Header File
* Date:              Wed Nov 25 12:56:12 2015 (by Create and Import Peripheral Wizard)
*****************************************************************************/

#ifndef TECLADO_H
#define TECLADO_H

/***************************** Include Files *******************************/

#include "xbasic_types.h"
#include "xstatus.h"
#include "xil_io.h"

/************************** Constant Definitions ***************************/


/**
 * User Logic Slave Space Offsets
 * -- SLV_REG0 : user logic slave module register 0
 * -- SLV_REG1 : user logic slave module register 1
 * -- SLV_REG2 : user logic slave module register 2
 * -- SLV_REG3 : user logic slave module register 3
 */
#define TECLADO_USER_SLV_SPACE_OFFSET (0x00000000)
#define TECLADO_SLV_REG0_OFFSET (TECLADO_USER_SLV_SPACE_OFFSET + 0x00000000)
#define TECLADO_SLV_REG1_OFFSET (TECLADO_USER_SLV_SPACE_OFFSET + 0x00000004)
#define TECLADO_SLV_REG2_OFFSET (TECLADO_USER_SLV_SPACE_OFFSET + 0x00000008)
#define TECLADO_SLV_REG3_OFFSET (TECLADO_USER_SLV_SPACE_OFFSET + 0x0000000C)

/**************************** Type Definitions *****************************/


/***************** Macros (Inline Functions) Definitions *******************/

/**
 *
 * Write a value to a TECLADO register. A 32 bit write is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is written.
 *
 * @param   BaseAddress is the base address of the TECLADO device.
 * @param   RegOffset is the register offset from the base to write to.
 * @param   Data is the data written to the register.
 *
 * @return  None.
 *
 * @note
 * C-style signature:
 * 	void TECLADO_mWriteReg(Xuint32 BaseAddress, unsigned RegOffset, Xuint32 Data)
 *
 */
#define TECLADO_mWriteReg(BaseAddress, RegOffset, Data) \
 	Xil_Out32((BaseAddress) + (RegOffset), (Xuint32)(Data))

/**
 *
 * Read a value from a TECLADO register. A 32 bit read is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is read from the register. The most significant data
 * will be read as 0.
 *
 * @param   BaseAddress is the base address of the TECLADO device.
 * @param   RegOffset is the register offset from the base to write to.
 *
 * @return  Data is the data from the register.
 *
 * @note
 * C-style signature:
 * 	Xuint32 TECLADO_mReadReg(Xuint32 BaseAddress, unsigned RegOffset)
 *
 */
#define TECLADO_mReadReg(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (RegOffset))


/**
 *
 * Write/Read 32 bit value to/from TECLADO user logic slave registers.
 *
 * @param   BaseAddress is the base address of the TECLADO device.
 * @param   RegOffset is the offset from the slave register to write to or read from.
 * @param   Value is the data written to the register.
 *
 * @return  Data is the data from the user logic slave register.
 *
 * @note
 * C-style signature:
 * 	void TECLADO_mWriteSlaveRegn(Xuint32 BaseAddress, unsigned RegOffset, Xuint32 Value)
 * 	Xuint32 TECLADO_mReadSlaveRegn(Xuint32 BaseAddress, unsigned RegOffset)
 *
 */
#define TECLADO_mWriteSlaveReg0(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (TECLADO_SLV_REG0_OFFSET) + (RegOffset), (Xuint32)(Value))
#define TECLADO_mWriteSlaveReg1(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (TECLADO_SLV_REG1_OFFSET) + (RegOffset), (Xuint32)(Value))
#define TECLADO_mWriteSlaveReg2(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (TECLADO_SLV_REG2_OFFSET) + (RegOffset), (Xuint32)(Value))
#define TECLADO_mWriteSlaveReg3(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (TECLADO_SLV_REG3_OFFSET) + (RegOffset), (Xuint32)(Value))

#define TECLADO_mReadSlaveReg0(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (TECLADO_SLV_REG0_OFFSET) + (RegOffset))
#define TECLADO_mReadSlaveReg1(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (TECLADO_SLV_REG1_OFFSET) + (RegOffset))
#define TECLADO_mReadSlaveReg2(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (TECLADO_SLV_REG2_OFFSET) + (RegOffset))
#define TECLADO_mReadSlaveReg3(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (TECLADO_SLV_REG3_OFFSET) + (RegOffset))

/************************** Function Prototypes ****************************/


/**
 *
 * Run a self-test on the driver/device. Note this may be a destructive test if
 * resets of the device are performed.
 *
 * If the hardware system is not built correctly, this function may never
 * return to the caller.
 *
 * @param   baseaddr_p is the base address of the TECLADO instance to be worked on.
 *
 * @return
 *
 *    - XST_SUCCESS   if all self-test code passed
 *    - XST_FAILURE   if any self-test code failed
 *
 * @note    Caching must be turned off for this function to work.
 * @note    Self test may fail if data memory and device are not on the same bus.
 *
 */
XStatus TECLADO_SelfTest(void * baseaddr_p);

#endif /** TECLADO_H */
