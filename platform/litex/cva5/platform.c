/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) Reconfigurable Computing Lab, Simon Fraser University
 */

#include <sbi/riscv_asm.h>
#include <sbi/riscv_encoding.h>
#include <sbi/riscv_io.h>
#include <sbi/sbi_const.h>
#include <sbi/sbi_hart.h>
#include <sbi/sbi_platform.h>
#include <sbi_utils/fdt/fdt_helper.h>
#include <sbi_utils/fdt/fdt_fixup.h>
#include <sbi_utils/ipi/aclint_mswi.h>
#include <sbi_utils/irqchip/plic.h>
#include <sbi_utils/serial/litex-uart.h>
#include <sbi_utils/timer/aclint_mtimer.h>

/*
 * Include these files as needed.
 * See objects.mk PLATFORM_xxx configuration parameters.
 */
#include <sbi_utils/ipi/aclint_mswi.h>
#include <sbi_utils/irqchip/plic.h>
#include <sbi_utils/serial/uart8250.h>
#include <sbi_utils/timer/aclint_mtimer.h>

#define CVA5_HART_COUNT		1
#define CVA5_CLINT_ADDR		0x2000000
#define CVA5_ACLINT_MTIMER_FREQ	10000000
#define CVA5_ACLINT_MSWI_ADDR	(CVA5_CLINT_ADDR + \
					 CLINT_MSWI_OFFSET)
#define PLATFORM_ACLINT_MTIMER_ADDR	(CVA5_CLINT_ADDR + \
					 CLINT_MTIMER_OFFSET)
#define PLATFORM_UART_ADDR		0x82001000
#define PLATFORM_UART_INPUT_FREQ	10000000
#define PLATFORM_UART_BAUDRATE		115200
#define CVA5_DEFAULT_PLATFORM_FEATURES	SBI_PLATFORM_HAS_MFAULTS_DELEGATION
#define CVA5_DEFAULT_HARDWARE_STACK_SIZE 8192

static struct aclint_mtimer_data mtimer = {
	.mtime_freq = CVA5_ACLINT_MTIMER_FREQ,
	.mtime_addr = PLATFORM_ACLINT_MTIMER_ADDR +
		      ACLINT_DEFAULT_MTIME_OFFSET,
	.mtime_size = ACLINT_DEFAULT_MTIME_SIZE,
	.mtimecmp_addr = PLATFORM_ACLINT_MTIMER_ADDR +
			 ACLINT_DEFAULT_MTIMECMP_OFFSET,
	.mtimecmp_size = ACLINT_DEFAULT_MTIMECMP_SIZE,
	.first_hartid = 0,
	.hart_count = CVA5_HART_COUNT,
	.has_64bit_mmio = true,
};

/*
 * CVA5 early initialization.
 */
static int CVA5_early_init(bool cold_boot)
{
	return 0;
}

/*
 * CVA5 final initialization.
 */
static int CVA5_final_init(bool cold_boot)
{
	void *fdt;

	if (!cold_boot)
		return 0;

	fdt = fdt_get_address();
	fdt_fixups(fdt);

	return 0;
}

/*
 * Initialize the CVA5 console.
 */
static int CVA5_console_init(void)
{
	return litex_uart_init(VEX_DEFAULT_UART_ADDR);
}

/*
 * Initialize the platform interrupt controller for current HART.
 */
static int CVA5_irqchip_init(bool cold_boot)
{
	return 0;
}

/*
 * Initialize IPI for current HART.
 */
static int CVA5_ipi_init(bool cold_boot)
{
	int ret;

	return 0;
}

/*
 * Initialize CVA5 timer for current HART.
 */
static int CVA5_timer_init(bool cold_boot)
{
	return 0;
}

/*
 * Platform descriptor.
 */
const struct sbi_platform_operations platform_ops = {
	.early_init		= CVA5_early_init,
	.final_init		= CVA5_final_init,
	.console_init		= CVA5_console_init,
	.irqchip_init		= CVA5_irqchip_init,
	.ipi_init		= CVA5_ipi_init,
	.timer_init		= CVA5_timer_init
};
const struct sbi_platform platform = {
	.opensbi_version	= OPENSBI_VERSION,
	.platform_version	= SBI_PLATFORM_VERSION(0x0, 0x01),
	.name			= "LiteX / CVA5",
	.features		= CVA5_DEFAULT_PLATFORM_FEATURES,
	.hart_count		= CVA5_HART_COUNT,
	.hart_stack_size	= CVA5_DEFAULT_HARDWARE_STACK_SIZE,
	.heap_size		= SBI_PLATFORM_DEFAULT_HEAP_SIZE(CVA5_HART_COUNT),
	.platform_ops_addr	= (unsigned long)&platform_ops
};