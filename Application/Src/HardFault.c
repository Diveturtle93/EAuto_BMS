//----------------------------------------------------------------------
// Titel	:	HardFault.c
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	16.05.2025
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Hardfault
//----------------------------------------------------------------------

// Einfuegen der standard Include-Dateien
//----------------------------------------------------------------------

//----------------------------------------------------------------------

// Einfuegen der STM Include-Dateien
//----------------------------------------------------------------------

//----------------------------------------------------------------------

// Einfuegen der eigenen Include Dateien
//----------------------------------------------------------------------
#include "HardFault.h"
#include "BasicUart.h"
//----------------------------------------------------------------------

void ReportHardFault(uint32_t *hard_fault_values, uint32_t exc);

//----------------------------------------------------------------------
void HardFault_Handler(void)
{
  __asm volatile
  (
      "TST    LR, #0b0100;      "
      "ITE    EQ;               "
      "MRSEQ  R0, MSP;          "
      "MRSNE  R0, PSP;          "
      "MOV    R1, LR;           "
      "B      ReportHardFault;  "
  );
}
//----------------------------------------------------------------------

//----------------------------------------------------------------------
void ReportHardFault(uint32_t *stack_frame, uint32_t exc)
{
	uint32_t r0   = stack_frame[0];
	uint32_t r1   = stack_frame[1];
	uint32_t r2   = stack_frame[2];
	uint32_t r3   = stack_frame[3];
	uint32_t r12  = stack_frame[4];
	uint32_t lr   = stack_frame[5];
	uint32_t pc   = stack_frame[6];
	uint32_t psr  = stack_frame[7];
	uint32_t hfsr = SCB->HFSR;
	uint32_t cfsr = SCB->CFSR;
	uint32_t mmar = SCB->MMFAR;
	uint32_t bfar = SCB->BFAR;
	uint32_t afsr = SCB->AFSR;

	uartTransmit("\n!!!Hard Fault detected!!!\n", 27);

	uartTransmit("\nStack frame:\n", 14);
	uartTransmit("R0 :        0x", 14);
	uartTransmitNumber(r0, 16);
	uartTransmit("\n", 1);
	uartTransmit("R1 :        0x", 14);
	uartTransmitNumber(r1, 16);
	uartTransmit("\n", 1);
	uartTransmit("R2 :        0x", 14);
	uartTransmitNumber(r2, 16);
	uartTransmit("\n", 1);
	uartTransmit("R3 :        0x", 14);
	uartTransmitNumber(r3, 16);
	uartTransmit("\n", 1);
	uartTransmit("R12:        0x", 14);
	uartTransmitNumber(r12, 16);
	uartTransmit("\n", 1);
	uartTransmit("LR :        0x", 14);
	uartTransmitNumber(lr, 16);
	uartTransmit("\n", 1);
	uartTransmit("PC :        0x", 14);
	uartTransmitNumber(pc, 16);
	uartTransmit("\n", 1);
	uartTransmit("PSR:        0x", 14);
	uartTransmitNumber(psr, 16);
	uartTransmit("\n", 1);

	uartTransmit("\nFault status:\n", 15);
	uartTransmit("HFSR:       0x", 14);
	uartTransmitNumber(hfsr, 16);
	uartTransmit("\n", 1);
	uartTransmit("CFSR:       0x", 14);
	uartTransmitNumber(cfsr, 16);
	uartTransmit("\n", 1);
	uartTransmit("MMAR:       0x", 14);
	uartTransmitNumber(mmar, 16);
	uartTransmit("\n", 1);
	uartTransmit("BFAR:       0x", 14);
	uartTransmitNumber(bfar, 16);
	uartTransmit("\n", 1);
	uartTransmit("AFSR:       0x", 14);
	uartTransmitNumber(afsr, 16);
	uartTransmit("\n", 1);

	uartTransmit("\nOther:\n", 8);
	printf("EXC_RETURN: 0x%08lX\n", exc);

	uartTransmit("\nDetails of the fault status:\n", 30);
	uartTransmit("Hard fault status:\n", 19);

	if (CHECK_BIT(hfsr, FORCED))
	{
		uartTransmit(" - Forced Hard fault.\n", 22);
	}

	if (CHECK_BIT(hfsr, VECTTBL))
	{
		uartTransmit(" - Bus fault on vector table read.\n", 35);
	}

	uartTransmit("MemManage fault status:\n", 24);
	if (CHECK_BIT(cfsr, MMARVALID))
	{
		uartTransmit(" - MMAR holds a valid address.\n", 31);
	}
	else
	{
		uartTransmit(" - MMAR holds an invalid address.\n", 34);
	}

	if (CHECK_BIT(cfsr, MLSPERR))
	{
		uartTransmit(" - Fault occurred during floating-point lazy state preservation.\n", 65);
	}

	if (CHECK_BIT(cfsr, MSTKERR))
	{
		uartTransmit(" - Stacking has caused an access violation.\n", 44);
	}

	if (CHECK_BIT(cfsr, MUNSTKERR))
	{
		uartTransmit(" - Unstacking has caused an access violation.\n", 46);
	}

	if (CHECK_BIT(cfsr, DACCVIOL))
	{
		uartTransmit(" - Load or store at a location that does not permit the operation.\n", 67);
	}

	if (CHECK_BIT(cfsr, IACCVIOL))
	{
		uartTransmit(" - Instruction fetch from a location that does not permit execution.\n", 69);
	}

	uartTransmit("Bus fault status:\n", 18);
	if (CHECK_BIT(cfsr, BFARVALID))
	{
		uartTransmit(" - BFAR holds a valid address.\n", 31);
	}
	else
	{
		uartTransmit(" - BFAR holds an invalid address.\n", 34);
	}

	if (CHECK_BIT(cfsr, LSPERR))
	{
		uartTransmit(" - Fault occurred during floating-point lazy state preservation.\n", 65);
	}

	if (CHECK_BIT(cfsr, STKERR))
	{
		uartTransmit(" - Stacking has caused a Bus fault.\n", 36);
	}

	if (CHECK_BIT(cfsr, UNSTKERR))
	{
		uartTransmit(" - Unstacking has caused a Bus fault.\n", 38);
	}

	if (CHECK_BIT(cfsr, IMPRECISERR))
	{
		uartTransmit(" - Data bus error has occurred, but the return address in the stack is not related to the fault.\n", 97);
	}

	if (CHECK_BIT(cfsr, PRECISERR))
	{
		uartTransmit(" - Data bus error has occurred, and the return address points to the instruction that caused the fault.\n", 104);
	}

	if (CHECK_BIT(cfsr, IBUSERR))
	{
		uartTransmit(" - Instruction bus error.\n", 26);
	}

	uartTransmit("Usage fault status:\n", 20);
	if (CHECK_BIT(cfsr, DIVBYZERO))
	{
		uartTransmit(" - The processor has executed an SDIV or UDIV instruction with a divisor of 0.\n", 79);
	}

	if (CHECK_BIT(cfsr, UNALIGNED))
	{
		uartTransmit(" - The processor has made an unaligned memory access.\n", 54);
	}

	if (CHECK_BIT(cfsr, NOCP))
	{
		uartTransmit(" - Attempted to access a coprocessor.\n", 38);
	}

	if (CHECK_BIT(cfsr, INVPC))
	{
		uartTransmit(" - Illegal attempt to load of EXC_RETURN to the PC.\n", 52);
	}

	if (CHECK_BIT(cfsr, INVSTATE))
	{
		uartTransmit(" - Attempted to execute an instruction that makes illegal use of the EPSR.\n", 75);
	}

	if (CHECK_BIT(cfsr, UNDEFINSTR))
	{
		uartTransmit(" - The processor has attempted to execute an undefined instruction.\n", 68);
	}

	// Software breakpoint
	__asm volatile("BKPT #0");

	// Endlosschleife nach HardFault
	while(1);
}
//----------------------------------------------------------------------
