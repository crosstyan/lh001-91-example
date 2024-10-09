/*

Version:
Author: LH Software Group
Copyright
UART Config:
	Baudrate: 115200
	8 bit length, no parity check, 1 bit stop
*/

#include <cstdio>
#include "LH001_91.h"
#include "uart_print.h"


constexpr uint32_t ADC_DATA_LEN = 7500;
uint32_t data_cnt;

ADC_DATA_NOFIFO_t ecg_dat;
volatile uint32_t data_ready_flag;

inline void delay_cycles(uint32_t t) {
	for (uint32_t i = 0; i < t; i++)
		;
}

struct __attribute__((__packed__)) stcsr_t {
	bool ENABLE : 1;
	bool TICKINT : 1;
	bool CLKSOURCE : 1;
	uint16_t _RESERVED_0 : 13;
	bool COUNTFLAG : 1;
	uint16_t _RESERVED_1 : 15;
};

namespace systick {
static volatile uint32_t sys_tick_count = 0;
uint32_t ms() {
	return sys_tick_count;
}
void delay_ms(uint32_t ms) {
	uint32_t start = sys_tick_count;
	while (sys_tick_count < (start + ms))
		;
}
}

// SysTick Control and Status Register
// https://developer.arm.com/documentation/ddi0413/d/system-control/system-control-register-descriptions/systick-control-and-status-register
static uintptr_t STCSR_BASE = 0xE000E010;
// SysTick Reload Value Register
static uintptr_t STRVR_BASE = 0xE000E014;
// SysTick Current Value Register
static uintptr_t STCVR_BASE = 0xE000E018;
// SysTick Calibration Value Register
static uintptr_t STCALIB_BASE = 0xE000E01C;

// https://developer.arm.com/documentation/dui0471/m/handling-processor-exceptions/configuring-systick
// SysTick Control and Status Register
stcsr_t &STCSR = *reinterpret_cast<stcsr_t *>(STCSR_BASE);
// SysTick Reload Value Register
uint32_t &STRVR = *reinterpret_cast<uint32_t *>(STRVR_BASE);
// SysTick Current Value Register
uint32_t &STCVR = *reinterpret_cast<uint32_t *>(STCVR_BASE);


void lh001_91_init() {

	LH001_91_ADC_INIT_t adc_init;
	LH001_91_PGA_INIT_t pga_init;
	LH001_91_LEADOFF_t leadoff_init;

	LH001_91_Spi_Init();
	lh001_91_sw_reset();

	lh001_91_adc_stop();
	lh001_91_rdatac_stop();

	leadoff_init.threshold      = LH001_91_LEADOFF_DELTA_10;
	leadoff_init.current        = LH001_91_LEADOFF_CURRENT_SOURCE_5nA;
	leadoff_init.sink_cfg       = LH001_91_LEADOFF_SINK_AIN0_1;
	leadoff_init.source_cfg     = LH001_91_LEADOFF_SOURCE_CLOSE;
	leadoff_init.rld_sink_en    = 1;
	leadoff_init.ain0_detect_en = 1;
	leadoff_init.ain1_detect_en = 1;
	leadoff_init.rld_detect_en  = 1;
	lh001_91_leadoff_init(&leadoff_init);

	lh001_91_rld_init(1, ENUM_LH001_91_RLD_REF_AVDD_DIV2, ENUM_LH001_91_RLD_CHOP_FMOD_DIV32);

	pga_init.gain          = ENUM_LH001_91_PGA_PGAGAIN_6;
	pga_init.pga_bypass    = 0;
	pga_init.power_mode    = ENUM_LH001_91_PGA_POWER_LP;
	pga_init.comm_sense_en = 1;
	pga_init.pga_chop      = ENUM_LH001_91_PGA_CHOP_DIV16;
	lh001_91_pga_init(&pga_init);

	adc_init.Fmodclk         = ENUM_LH001_91_ADC_FMODCLK_128K;
	adc_init.oversample_rate = ENUM_LH001_91_ADC_DR_DIV512; // update rate = Fmodclk/oversample_rate
	adc_init.conv_mode       = ENUM_LH001_91_ADC_CONTINOUS;
	adc_init.ref_sel         = ENUM_LH001_91_ADC_REF_2V5;
	lh001_91_adc_init(&adc_init);
	// lh001_91_adc_channel(ENUM_LH001_91_ADCCHP_VCM,ENUM_LH001_91_ADCCHN_GND);	//FOR NOISE TEST
	lh001_91_adc_channel(ENUM_LH001_91_ADCCHP_AIN0, ENUM_LH001_91_ADCCHN_AIN1); // FOR NOISE TEST
}

/*check below registers for configuration*/
REG_DUMP_t reg[] =
	{
		{ADDR_LH001_91_PGAGAIN, 0, "ADDR_LH001_91_PGAGAIN"},
		{ADDR_LH001_91_PGACTRL, 0, "ADDR_LH001_91_PGACTRL"},
		{ADDR_LH001_91_PGACTRL1, 0, "ADDR_LH001_91_PGACTRL1"},
		{ADDR_LH001_91_CONFIG1, 0, "ADDR_LH001_91_CONFIG1"},
		{ADDR_LH001_91_ADCCTRL, 0, "ADDR_LH001_91_ADCCTRL"},
		{ADDR_LH001_91_ADCCHCON, 0, "ADDR_LH001_91_ADCCHCON"},
		{ADDR_LH001_91_BUFCON, 0, "ADDR_LH001_91_BUFCON"},
		{ADDR_LH001_91_LOCON1, 0, "ADDR_LH001_91_LOCON1"},
		{ADDR_LH001_91_LOCON2, 0, "ADDR_LH001_91_LOCON2"},
		{ADDR_LH001_91_LOCON3, 0, "ADDR_LH001_91_LOCON3"},
		{ADDR_LH001_91_LOFFSTAT, 0, "ADDR_LH001_91_LOFFSTAT"},
		{ADDR_LH001_91_RLDCON, 0, "ADDR_LH001_91_RLDCON"}};

// https://developer.arm.com/documentation/ddi0439/b/System-Control/Register-summary
// https://github.com/CommunityGD32Cores/ArduinoCore-GD32/blob/0f853a9838b4e0675336c53a6bcaf03788901475/cores/arduino/gd32/systick.c#L43-L59
inline void systick_init() {
	// I doubt if the system clock is really 84MHz

	// User manual page 70
	// AHB、APB2和APB1域的最高时钟频率分别为108MHz、54MHz和54MHz。
	// RCU通过AHB时钟（HCLK）8分频后作为Cortex系统
	// 定时器（SysTick）的外部时钟。通过对SysTick控制与状态寄存器的设置，可选择上述时钟
	// 或Cortex（HCLK）时钟作为SysTick时钟。
	//
	// about 1050ms in real time
	// I'm not sure why
	SysTick_Config(SystemCoreClock / (1'000U * 10U));
	NVIC_SetPriority(SysTick_IRQn, 0x00U);
}

extern "C" [[noreturn]]
int main() {
	data_cnt        = 0;
	data_ready_flag = 0;

	// datasheet page 14 (2.6.2)
	// PA2 (TX) & PA3 (RX)
	// PA14 (TX) & PA15 (RX)
	uart_print_init();
	debug_pin_init();
	systick_init();

	printf("test start\r\n");
	uint32_t count = 0;
	for (;;) {
		printf("[%u]systick=%u\r\n", count, systick::ms());
		systick::delay_ms(1000);
		count++;
	}
	// lh001_91_init();
	//
	// /*dump register to check register configuration*/
	// lh001_91_reg_dump(reg, sizeof(reg) / sizeof(REG_DUMP_t));
	// for (uint32_t i = 0; i < sizeof(reg) / sizeof(REG_DUMP_t); i++) {
	// 	printf("%s:0x%x\r\n", reg[i].reg_name, reg[i].val);
	// }
	//
	// lh001_91_adc_go();
	// lh001_91_rdatac_start();
	// while (true) {
	// 	if (data_ready_flag != 0) {
	// 		data_ready_flag = 0;
	// 		data_cnt++;
	//
	// 		uint8_t val;
	// 		const float volt_mv = lh001_91_adc_code2mv(ecg_dat.data, 2500);
	// 		printf("%d,0x%02x,%.4f\r\n", data_cnt, static_cast<uint8_t>(ecg_dat.loffstat), volt_mv);
	// 		lh001_91_read_regs(ADDR_LH001_91_LOFFSTAT, &val, 1);
	// 		printf("%x\r\n", val);
	// 	}
	// }
}

extern "C" void SysTick_Handler() {
	systick::sys_tick_count++;
}

extern "C" void EXTI4_15_IRQHandler() {
	// ADC interrupt
	if (exti_interrupt_flag_get(EXTI_10) != RESET) {
		/* Clear the EXTI line 0 pending bit */
		exti_interrupt_flag_clear(EXTI_10);

		lh001_91_read_data_nofifo(&ecg_dat);
		data_ready_flag = 1;
	}
}
