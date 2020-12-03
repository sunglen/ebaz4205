OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm","elf32-littlearm")
OUTPUT_ARCH(arm)

MEMORY {
	DDR : ORIGIN = 0x100000, LENGTH = 0x1ff00000
	OCM : ORIGIN = 0xfffc0000, LENGTH = 0x40000
}

PROVIDE(hardware_init_hook = 0);
PROVIDE(software_init_hook = 0);
PROVIDE(software_term_hook = 0);

SECTIONS {
	.discard (NOLOAD) : {
		start.o(.discard) tXUartPs_rKernelDomain_tecsgen.o(.discard) tXUartPs.o(.discard) tSIOPortZynq7000Main_rKernelDomain_tecsgen.o(.discard) tISR_rKernelDomain_tecsgen.o(.discard) tISR.o(.discard) tInterruptRequest_rKernelDomain_tecsgen.o(.discard) tTerminateRoutine_rKernelDomain_tecsgen.o(.discard) tTerminateRoutine.o(.discard) tPutLogSIOPort_rKernelDomain_tecsgen.o(.discard) tPutLogSIOPort.o(.discard) tSysLog_rKernelDomain_tecsgen.o(.discard) tSysLog.o(.discard) tSemaphore_rKernelDomain_tecsgen.o(.discard) tSerialPortMain_rKernelDomain_tecsgen.o(.discard) tSerialPortMain.o(.discard) tLogTaskMain_rKernelDomain_tecsgen.o(.discard) tLogTaskMain.o(.discard) tTask_rKernelDomain_tecsgen.o(.discard) tBannerMain_rKernelDomain_tecsgen.o(.discard) tBannerMain.o(.discard) tInitializeRoutine_rKernelDomain_tecsgen.o(.discard) tInitializeRoutine.o(.discard) tCyclicNotifier_rKernelDomain_tecsgen.o(.discard) tCyclicNotifier.o(.discard) tTimeEventHandler_rKernelDomain_tecsgen.o(.discard) tTimeEventHandler.o(.discard) tCpuExceptionHandler_rKernelDomain_tecsgen.o(.discard) tCpuExceptionHandler.o(.discard) tHRPSVCPlugin_sSysLogSVCBody_SysLog_eSysLog_rKernelDomain_tecsgen.o(.discard) tHRPSVCPlugin_sSysLogSVCBody_SysLog_eSysLog.o(.discard) tHRPSVCPlugin_sSerialPortSVCBody_SerialPort1_eSerialPort_rKernelDomain_tecsgen.o(.discard) tHRPSVCPlugin_sSerialPortSVCBody_SerialPort1_eSerialPort.o(.discard) prb_str.o(.discard) init_tecs.o(.discard) kernel_cfg.o(.discard) kernel_mem.o(.discard) tTask_rDomain1_tecsgen.o(.discard) tAlarmNotifier_rDomain1_tecsgen.o(.discard) tAlarmNotifier.o(.discard) tTask_rDomain2_tecsgen.o(.discard) tSysLogAdapter_tecsgen.o(.discard) tSysLogAdapter.o(.discard) tTask_tecsgen.o(.discard) tTask.o(.discard) tSample2_tecsgen.o(.discard) tSample2.o(.discard) tKernel_tecsgen.o(.discard) tHRPSVCPlugin_sSysLogSVCCaller_SysLog_eSysLog_tecsgen.o(.discard) tHRPSVCPlugin_sSysLogSVCCaller_SysLog_eSysLog.o(.discard) tHRPSVCPlugin_sSerialPortSVCCaller_SerialPort1_eSerialPort_tecsgen.o(.discard) tHRPSVCPlugin_sSerialPortSVCCaller_SerialPort1_eSerialPort.o(.discard) log_output.o(.discard) vasyslog.o(.discard) t_perror.o(.discard) strerror.o(.discard) libkernel.a(.discard) libc.a(.discard) libgcc.a(.discard) libxil.a(.discard) 
	}

	.text_kernel 0x100000 : ALIGN(4) {
		__start_mp_text_kernel = .;
		__start_mo_text_kernel = .;
		__start_text_kernel = .;
		start.o(.text .text.*) tXUartPs_rKernelDomain_tecsgen.o(.text .text.*) tXUartPs.o(.text .text.*) tSIOPortZynq7000Main_rKernelDomain_tecsgen.o(.text .text.*) tISR_rKernelDomain_tecsgen.o(.text .text.*) tISR.o(.text .text.*) tInterruptRequest_rKernelDomain_tecsgen.o(.text .text.*) tTerminateRoutine_rKernelDomain_tecsgen.o(.text .text.*) tTerminateRoutine.o(.text .text.*) tPutLogSIOPort_rKernelDomain_tecsgen.o(.text .text.*) tPutLogSIOPort.o(.text .text.*) tSysLog_rKernelDomain_tecsgen.o(.text .text.*) tSysLog.o(.text .text.*) tSemaphore_rKernelDomain_tecsgen.o(.text .text.*) tSerialPortMain_rKernelDomain_tecsgen.o(.text .text.*) tSerialPortMain.o(.text .text.*) tLogTaskMain_rKernelDomain_tecsgen.o(.text .text.*) tLogTaskMain.o(.text .text.*) tTask_rKernelDomain_tecsgen.o(.text .text.*) tBannerMain_rKernelDomain_tecsgen.o(.text .text.*) tBannerMain.o(.text .text.*) tInitializeRoutine_rKernelDomain_tecsgen.o(.text .text.*) tInitializeRoutine.o(.text .text.*) tCyclicNotifier_rKernelDomain_tecsgen.o(.text .text.*) tCyclicNotifier.o(.text .text.*) tTimeEventHandler_rKernelDomain_tecsgen.o(.text .text.*) tTimeEventHandler.o(.text .text.*) tCpuExceptionHandler_rKernelDomain_tecsgen.o(.text .text.*) tCpuExceptionHandler.o(.text .text.*) tHRPSVCPlugin_sSysLogSVCBody_SysLog_eSysLog_rKernelDomain_tecsgen.o(.text .text.*) tHRPSVCPlugin_sSysLogSVCBody_SysLog_eSysLog.o(.text .text.*) tHRPSVCPlugin_sSerialPortSVCBody_SerialPort1_eSerialPort_rKernelDomain_tecsgen.o(.text .text.*) tHRPSVCPlugin_sSerialPortSVCBody_SerialPort1_eSerialPort.o(.text .text.*) prb_str.o(.text .text.*) init_tecs.o(.text .text.*) kernel_cfg.o(.text .text.*) kernel_mem.o(.text .text.*) libkernel.a(.text .text.*) *(.vector) 
		__end_text_kernel = .;
		__end_mo_text_kernel = .;
		__aend_mo_text_kernel = ALIGN(4K);
		__aend_mp_text_kernel = ALIGN(4K);
	} > DDR

	.rodata_kernel ALIGN(4K) : ALIGN(4) {
		__start_mp_rodata_kernel = .;
		__start_mo_rodata_kernel = .;
		__start_rodata_kernel = .;
		start.o(.rodata .rodata.*) tXUartPs_rKernelDomain_tecsgen.o(.rodata .rodata.*) tXUartPs.o(.rodata .rodata.*) tSIOPortZynq7000Main_rKernelDomain_tecsgen.o(.rodata .rodata.*) tISR_rKernelDomain_tecsgen.o(.rodata .rodata.*) tISR.o(.rodata .rodata.*) tInterruptRequest_rKernelDomain_tecsgen.o(.rodata .rodata.*) tTerminateRoutine_rKernelDomain_tecsgen.o(.rodata .rodata.*) tTerminateRoutine.o(.rodata .rodata.*) tPutLogSIOPort_rKernelDomain_tecsgen.o(.rodata .rodata.*) tPutLogSIOPort.o(.rodata .rodata.*) tSysLog_rKernelDomain_tecsgen.o(.rodata .rodata.*) tSysLog.o(.rodata .rodata.*) tSemaphore_rKernelDomain_tecsgen.o(.rodata .rodata.*) tSerialPortMain_rKernelDomain_tecsgen.o(.rodata .rodata.*) tSerialPortMain.o(.rodata .rodata.*) tLogTaskMain_rKernelDomain_tecsgen.o(.rodata .rodata.*) tLogTaskMain.o(.rodata .rodata.*) tTask_rKernelDomain_tecsgen.o(.rodata .rodata.*) tBannerMain_rKernelDomain_tecsgen.o(.rodata .rodata.*) tBannerMain.o(.rodata .rodata.*) tInitializeRoutine_rKernelDomain_tecsgen.o(.rodata .rodata.*) tInitializeRoutine.o(.rodata .rodata.*) tCyclicNotifier_rKernelDomain_tecsgen.o(.rodata .rodata.*) tCyclicNotifier.o(.rodata .rodata.*) tTimeEventHandler_rKernelDomain_tecsgen.o(.rodata .rodata.*) tTimeEventHandler.o(.rodata .rodata.*) tCpuExceptionHandler_rKernelDomain_tecsgen.o(.rodata .rodata.*) tCpuExceptionHandler.o(.rodata .rodata.*) tHRPSVCPlugin_sSysLogSVCBody_SysLog_eSysLog_rKernelDomain_tecsgen.o(.rodata .rodata.*) tHRPSVCPlugin_sSysLogSVCBody_SysLog_eSysLog.o(.rodata .rodata.*) tHRPSVCPlugin_sSerialPortSVCBody_SerialPort1_eSerialPort_rKernelDomain_tecsgen.o(.rodata .rodata.*) tHRPSVCPlugin_sSerialPortSVCBody_SerialPort1_eSerialPort.o(.rodata .rodata.*) prb_str.o(.rodata .rodata.*) init_tecs.o(.rodata .rodata.*) kernel_cfg.o(.rodata .rodata.*) kernel_mem.o(.rodata .rodata.*) libkernel.a(.rodata .rodata.*) *(.page_table) 
		__end_rodata_kernel = .;
		__end_mo_rodata_kernel = .;
		__aend_mo_rodata_kernel = ALIGN(4K);
		__aend_mp_rodata_kernel = ALIGN(4K);
	} > DDR

	.text_rDomain1 ALIGN(4K) : ALIGN(4) {
		__start_mp_text_rDomain1 = .;
		__start_mo_text_rDomain1 = .;
		__start_text_rDomain1 = .;
		tTask_rDomain1_tecsgen.o(.text .text.*) tAlarmNotifier_rDomain1_tecsgen.o(.text .text.*) tAlarmNotifier.o(.text .text.*) 
		__end_text_rDomain1 = .;
		__end_mo_text_rDomain1 = .;
		__aend_mo_text_rDomain1 = ALIGN(4K);
		__aend_mp_text_rDomain1 = ALIGN(4K);
	} > DDR

	.rodata_rDomain1 ALIGN(4K) : ALIGN(4) {
		__start_mp_rodata_rDomain1 = .;
		__start_mo_rodata_rDomain1 = .;
		__start_rodata_rDomain1 = .;
		tTask_rDomain1_tecsgen.o(.rodata .rodata.*) tAlarmNotifier_rDomain1_tecsgen.o(.rodata .rodata.*) tAlarmNotifier.o(.rodata .rodata.*) 
		__end_rodata_rDomain1 = .;
		__end_mo_rodata_rDomain1 = .;
		__aend_mo_rodata_rDomain1 = ALIGN(4K);
		__aend_mp_rodata_rDomain1 = ALIGN(4K);
	} > DDR

	.text_rDomain2 ALIGN(4K) : ALIGN(4) {
		__start_mp_text_rDomain2 = .;
		__start_mo_text_rDomain2 = .;
		__start_text_rDomain2 = .;
		tTask_rDomain2_tecsgen.o(.text .text.*) 
		__end_text_rDomain2 = .;
		__end_mo_text_rDomain2 = .;
		__aend_mo_text_rDomain2 = ALIGN(4K);
		__aend_mp_text_rDomain2 = ALIGN(4K);
	} > DDR

	.rodata_rDomain2 ALIGN(4K) : ALIGN(4) {
		__start_mp_rodata_rDomain2 = .;
		__start_mo_rodata_rDomain2 = .;
		__start_rodata_rDomain2 = .;
		tTask_rDomain2_tecsgen.o(.rodata .rodata.*) 
		__end_rodata_rDomain2 = .;
		__end_mo_rodata_rDomain2 = .;
		__aend_mo_rodata_rDomain2 = ALIGN(4K);
		__aend_mp_rodata_rDomain2 = ALIGN(4K);
	} > DDR

	.text_shared ALIGN(4K) : ALIGN(4) {
		__start_mp_text_shared = .;
		__start_mo_text_shared = .;
		__start_text_shared = .;
		tSysLogAdapter_tecsgen.o(.text .text.*) tSysLogAdapter.o(.text .text.*) tTask_tecsgen.o(.text .text.*) tTask.o(.text .text.*) tSample2_tecsgen.o(.text .text.*) tSample2.o(.text .text.*) tKernel_tecsgen.o(.text .text.*) tHRPSVCPlugin_sSysLogSVCCaller_SysLog_eSysLog_tecsgen.o(.text .text.*) tHRPSVCPlugin_sSysLogSVCCaller_SysLog_eSysLog.o(.text .text.*) tHRPSVCPlugin_sSerialPortSVCCaller_SerialPort1_eSerialPort_tecsgen.o(.text .text.*) tHRPSVCPlugin_sSerialPortSVCCaller_SerialPort1_eSerialPort.o(.text .text.*) log_output.o(.text .text.*) vasyslog.o(.text .text.*) t_perror.o(.text .text.*) strerror.o(.text .text.*) libc.a(.text .text.*) libgcc.a(.text .text.*) libxil.a(.text .text.*) *(.shared_code) 
		__end_text_shared = .;
		__end_mo_text_shared = .;
		__aend_mo_text_shared = ALIGN(4K);
		__aend_mp_text_shared = ALIGN(4K);
	} > DDR

	.rodata_shared ALIGN(4K) : ALIGN(4) {
		__start_mp_rodata_shared = .;
		__start_mo_rodata_shared = .;
		__start_rodata_shared = .;
		tSysLogAdapter_tecsgen.o(.rodata .rodata.*) tSysLogAdapter.o(.rodata .rodata.*) tTask_tecsgen.o(.rodata .rodata.*) tTask.o(.rodata .rodata.*) tSample2_tecsgen.o(.rodata .rodata.*) tSample2.o(.rodata .rodata.*) tKernel_tecsgen.o(.rodata .rodata.*) tHRPSVCPlugin_sSysLogSVCCaller_SysLog_eSysLog_tecsgen.o(.rodata .rodata.*) tHRPSVCPlugin_sSysLogSVCCaller_SysLog_eSysLog.o(.rodata .rodata.*) tHRPSVCPlugin_sSerialPortSVCCaller_SerialPort1_eSerialPort_tecsgen.o(.rodata .rodata.*) tHRPSVCPlugin_sSerialPortSVCCaller_SerialPort1_eSerialPort.o(.rodata .rodata.*) log_output.o(.rodata .rodata.*) vasyslog.o(.rodata .rodata.*) t_perror.o(.rodata .rodata.*) strerror.o(.rodata .rodata.*) libc.a(.rodata .rodata.*) libgcc.a(.rodata .rodata.*) libxil.a(.rodata .rodata.*) 
	} > DDR

	.preinit_array ALIGN(4) : {
		PROVIDE_HIDDEN (__preinit_array_start = .);
		KEEP (*(.preinit_array))
		PROVIDE_HIDDEN (__preinit_array_end = .);
	} > DDR
	.init_array ALIGN(4) : {
		PROVIDE_HIDDEN (__init_array_start = .);
		KEEP (*(SORT(.init_array.*)))
		KEEP (*(.init_array))
		PROVIDE_HIDDEN (__init_array_end = .);
	} > DDR
	.fini_array ALIGN(4) : {
		PROVIDE_HIDDEN (__fini_array_start = .);
		KEEP (*(SORT(.fini_array.*)))
		KEEP (*(.fini_array))
		PROVIDE_HIDDEN (__fini_array_end = .);
	} > DDR
	.ARM.exidx ALIGN(4) : {
		__exidx_start = .;
		*(.ARM.exidx* .gnu.linkonce.armexidx.*)
		__exidx_end = .;
	} > DDR
	.jcr ALIGN(4) : {
		KEEP (*(.jcr))
	} > DDR

	__end_rodata_shared = .;
	__end_mo_rodata_shared = .;
	__aend_mo_rodata_shared = ALIGN(4K);
	__aend_mp_rodata_shared = ALIGN(4K);

	.data_kernel ALIGN(4K) : ALIGN(4) {
		__start_mp_rwdata_kernel = .;
		__start_mo_rwdata_kernel = .;
		__start_data_kernel = .;
		start.o(.data .data.*) tXUartPs_rKernelDomain_tecsgen.o(.data .data.*) tXUartPs.o(.data .data.*) tSIOPortZynq7000Main_rKernelDomain_tecsgen.o(.data .data.*) tISR_rKernelDomain_tecsgen.o(.data .data.*) tISR.o(.data .data.*) tInterruptRequest_rKernelDomain_tecsgen.o(.data .data.*) tTerminateRoutine_rKernelDomain_tecsgen.o(.data .data.*) tTerminateRoutine.o(.data .data.*) tPutLogSIOPort_rKernelDomain_tecsgen.o(.data .data.*) tPutLogSIOPort.o(.data .data.*) tSysLog_rKernelDomain_tecsgen.o(.data .data.*) tSysLog.o(.data .data.*) tSemaphore_rKernelDomain_tecsgen.o(.data .data.*) tSerialPortMain_rKernelDomain_tecsgen.o(.data .data.*) tSerialPortMain.o(.data .data.*) tLogTaskMain_rKernelDomain_tecsgen.o(.data .data.*) tLogTaskMain.o(.data .data.*) tTask_rKernelDomain_tecsgen.o(.data .data.*) tBannerMain_rKernelDomain_tecsgen.o(.data .data.*) tBannerMain.o(.data .data.*) tInitializeRoutine_rKernelDomain_tecsgen.o(.data .data.*) tInitializeRoutine.o(.data .data.*) tCyclicNotifier_rKernelDomain_tecsgen.o(.data .data.*) tCyclicNotifier.o(.data .data.*) tTimeEventHandler_rKernelDomain_tecsgen.o(.data .data.*) tTimeEventHandler.o(.data .data.*) tCpuExceptionHandler_rKernelDomain_tecsgen.o(.data .data.*) tCpuExceptionHandler.o(.data .data.*) tHRPSVCPlugin_sSysLogSVCBody_SysLog_eSysLog_rKernelDomain_tecsgen.o(.data .data.*) tHRPSVCPlugin_sSysLogSVCBody_SysLog_eSysLog.o(.data .data.*) tHRPSVCPlugin_sSerialPortSVCBody_SerialPort1_eSerialPort_rKernelDomain_tecsgen.o(.data .data.*) tHRPSVCPlugin_sSerialPortSVCBody_SerialPort1_eSerialPort.o(.data .data.*) prb_str.o(.data .data.*) init_tecs.o(.data .data.*) kernel_cfg.o(.data .data.*) kernel_mem.o(.data .data.*) libkernel.a(.data .data.*) 
		__end_data_kernel = .;
	} > DDR

	.bss_kernel ALIGN(4) (NOLOAD) : ALIGN(4) {
		__start_bss_kernel = .;
		start.o(.bss .bss.* COMMON) tXUartPs_rKernelDomain_tecsgen.o(.bss .bss.* COMMON) tXUartPs.o(.bss .bss.* COMMON) tSIOPortZynq7000Main_rKernelDomain_tecsgen.o(.bss .bss.* COMMON) tISR_rKernelDomain_tecsgen.o(.bss .bss.* COMMON) tISR.o(.bss .bss.* COMMON) tInterruptRequest_rKernelDomain_tecsgen.o(.bss .bss.* COMMON) tTerminateRoutine_rKernelDomain_tecsgen.o(.bss .bss.* COMMON) tTerminateRoutine.o(.bss .bss.* COMMON) tPutLogSIOPort_rKernelDomain_tecsgen.o(.bss .bss.* COMMON) tPutLogSIOPort.o(.bss .bss.* COMMON) tSysLog_rKernelDomain_tecsgen.o(.bss .bss.* COMMON) tSysLog.o(.bss .bss.* COMMON) tSemaphore_rKernelDomain_tecsgen.o(.bss .bss.* COMMON) tSerialPortMain_rKernelDomain_tecsgen.o(.bss .bss.* COMMON) tSerialPortMain.o(.bss .bss.* COMMON) tLogTaskMain_rKernelDomain_tecsgen.o(.bss .bss.* COMMON) tLogTaskMain.o(.bss .bss.* COMMON) tTask_rKernelDomain_tecsgen.o(.bss .bss.* COMMON) tBannerMain_rKernelDomain_tecsgen.o(.bss .bss.* COMMON) tBannerMain.o(.bss .bss.* COMMON) tInitializeRoutine_rKernelDomain_tecsgen.o(.bss .bss.* COMMON) tInitializeRoutine.o(.bss .bss.* COMMON) tCyclicNotifier_rKernelDomain_tecsgen.o(.bss .bss.* COMMON) tCyclicNotifier.o(.bss .bss.* COMMON) tTimeEventHandler_rKernelDomain_tecsgen.o(.bss .bss.* COMMON) tTimeEventHandler.o(.bss .bss.* COMMON) tCpuExceptionHandler_rKernelDomain_tecsgen.o(.bss .bss.* COMMON) tCpuExceptionHandler.o(.bss .bss.* COMMON) tHRPSVCPlugin_sSysLogSVCBody_SysLog_eSysLog_rKernelDomain_tecsgen.o(.bss .bss.* COMMON) tHRPSVCPlugin_sSysLogSVCBody_SysLog_eSysLog.o(.bss .bss.* COMMON) tHRPSVCPlugin_sSerialPortSVCBody_SerialPort1_eSerialPort_rKernelDomain_tecsgen.o(.bss .bss.* COMMON) tHRPSVCPlugin_sSerialPortSVCBody_SerialPort1_eSerialPort.o(.bss .bss.* COMMON) prb_str.o(.bss .bss.* COMMON) init_tecs.o(.bss .bss.* COMMON) kernel_cfg.o(.bss .bss.* COMMON) kernel_mem.o(.bss .bss.* COMMON) libkernel.a(.bss .bss.* COMMON) 
		__end_bss_kernel = .;
	} > DDR

	.noinit_kernel ALIGN(4) (NOLOAD) : ALIGN(4) {
		__start_noinit_kernel = .;
		start.o(.noinit) tXUartPs_rKernelDomain_tecsgen.o(.noinit) tXUartPs.o(.noinit) tSIOPortZynq7000Main_rKernelDomain_tecsgen.o(.noinit) tISR_rKernelDomain_tecsgen.o(.noinit) tISR.o(.noinit) tInterruptRequest_rKernelDomain_tecsgen.o(.noinit) tTerminateRoutine_rKernelDomain_tecsgen.o(.noinit) tTerminateRoutine.o(.noinit) tPutLogSIOPort_rKernelDomain_tecsgen.o(.noinit) tPutLogSIOPort.o(.noinit) tSysLog_rKernelDomain_tecsgen.o(.noinit) tSysLog.o(.noinit) tSemaphore_rKernelDomain_tecsgen.o(.noinit) tSerialPortMain_rKernelDomain_tecsgen.o(.noinit) tSerialPortMain.o(.noinit) tLogTaskMain_rKernelDomain_tecsgen.o(.noinit) tLogTaskMain.o(.noinit) tTask_rKernelDomain_tecsgen.o(.noinit) tBannerMain_rKernelDomain_tecsgen.o(.noinit) tBannerMain.o(.noinit) tInitializeRoutine_rKernelDomain_tecsgen.o(.noinit) tInitializeRoutine.o(.noinit) tCyclicNotifier_rKernelDomain_tecsgen.o(.noinit) tCyclicNotifier.o(.noinit) tTimeEventHandler_rKernelDomain_tecsgen.o(.noinit) tTimeEventHandler.o(.noinit) tCpuExceptionHandler_rKernelDomain_tecsgen.o(.noinit) tCpuExceptionHandler.o(.noinit) tHRPSVCPlugin_sSysLogSVCBody_SysLog_eSysLog_rKernelDomain_tecsgen.o(.noinit) tHRPSVCPlugin_sSysLogSVCBody_SysLog_eSysLog.o(.noinit) tHRPSVCPlugin_sSerialPortSVCBody_SerialPort1_eSerialPort_rKernelDomain_tecsgen.o(.noinit) tHRPSVCPlugin_sSerialPortSVCBody_SerialPort1_eSerialPort.o(.noinit) prb_str.o(.noinit) init_tecs.o(.noinit) kernel_cfg.o(.noinit) kernel_mem.o(.noinit) libkernel.a(.noinit) *(.system_stack) 
		__end_noinit_kernel = .;
		__end_mo_rwdata_kernel = .;
		__aend_mo_rwdata_kernel = ALIGN(4K);
		__aend_mp_rwdata_kernel = ALIGN(4K);
	} > DDR

	.ustack_TSKID_tTask_rDomain1_Task1 ALIGN(4K) (NOLOAD) : ALIGN(4) {
		__start_ustack_TSKID_tTask_rDomain1_Task1 = .;
		kernel_cfg.o(.ustack_TSKID_tTask_rDomain1_Task1) 
		__end_ustack_TSKID_tTask_rDomain1_Task1 = .;
		__aend_ustack_TSKID_tTask_rDomain1_Task1 = ALIGN(4K);
	} > DDR

	.ustack_TOPPERS_DDR_DUMMY1 ALIGN(4K) (NOLOAD) : ALIGN(4) {
		__start_ustack_TOPPERS_DDR_DUMMY1 = .;
		kernel_cfg.o(.ustack_TOPPERS_DDR_DUMMY1) 
		__end_ustack_TOPPERS_DDR_DUMMY1 = .;
		__aend_ustack_TOPPERS_DDR_DUMMY1 = ALIGN(4K);
	} > DDR

	.ustack_TSKID_tTask_rDomain1_Task2 ALIGN(4K) (NOLOAD) : ALIGN(4) {
		__start_ustack_TSKID_tTask_rDomain1_Task2 = .;
		kernel_cfg.o(.ustack_TSKID_tTask_rDomain1_Task2) 
		__end_ustack_TSKID_tTask_rDomain1_Task2 = .;
		__aend_ustack_TSKID_tTask_rDomain1_Task2 = ALIGN(4K);
	} > DDR

	.ustack_TSKID_tTask_rDomain2_Task3 ALIGN(4K) (NOLOAD) : ALIGN(4) {
		__start_ustack_TSKID_tTask_rDomain2_Task3 = .;
		kernel_cfg.o(.ustack_TSKID_tTask_rDomain2_Task3) 
		__end_ustack_TSKID_tTask_rDomain2_Task3 = .;
		__aend_ustack_TSKID_tTask_rDomain2_Task3 = ALIGN(4K);
	} > DDR

	.ustack_TSKID_tTask_rDomain1_AlarmTask ALIGN(4K) (NOLOAD) : ALIGN(4) {
		__start_ustack_TSKID_tTask_rDomain1_AlarmTask = .;
		kernel_cfg.o(.ustack_TSKID_tTask_rDomain1_AlarmTask) 
		__end_ustack_TSKID_tTask_rDomain1_AlarmTask = .;
		__aend_ustack_TSKID_tTask_rDomain1_AlarmTask = ALIGN(4K);
	} > DDR

	.data_rDomain1 ALIGN(4K) : ALIGN(4) {
		__start_mp_rwdata_rDomain1 = .;
		__start_mo_rwdata_rDomain1 = .;
		__start_data_rDomain1 = .;
		tTask_rDomain1_tecsgen.o(.data .data.*) tAlarmNotifier_rDomain1_tecsgen.o(.data .data.*) tAlarmNotifier.o(.data .data.*) 
		__end_data_rDomain1 = .;
	} > DDR

	.bss_rDomain1 ALIGN(4) (NOLOAD) : ALIGN(4) {
		__start_bss_rDomain1 = .;
		tTask_rDomain1_tecsgen.o(.bss .bss.* COMMON) tAlarmNotifier_rDomain1_tecsgen.o(.bss .bss.* COMMON) tAlarmNotifier.o(.bss .bss.* COMMON) 
		__end_bss_rDomain1 = .;
	} > DDR

	.noinit_rDomain1 ALIGN(4) (NOLOAD) : ALIGN(4) {
		__start_noinit_rDomain1 = .;
		tTask_rDomain1_tecsgen.o(.noinit) tAlarmNotifier_rDomain1_tecsgen.o(.noinit) tAlarmNotifier.o(.noinit) 
		__end_noinit_rDomain1 = .;
		__end_mo_rwdata_rDomain1 = .;
		__aend_mo_rwdata_rDomain1 = ALIGN(4K);
		__aend_mp_rwdata_rDomain1 = ALIGN(4K);
	} > DDR

	.data_rDomain2 ALIGN(4K) : ALIGN(4) {
		__start_mp_rwdata_rDomain2 = .;
		__start_mo_rwdata_rDomain2 = .;
		__start_data_rDomain2 = .;
		tTask_rDomain2_tecsgen.o(.data .data.*) 
		__end_data_rDomain2 = .;
	} > DDR

	.bss_rDomain2 ALIGN(4) (NOLOAD) : ALIGN(4) {
		__start_bss_rDomain2 = .;
		tTask_rDomain2_tecsgen.o(.bss .bss.* COMMON) 
		__end_bss_rDomain2 = .;
	} > DDR

	.noinit_rDomain2 ALIGN(4) (NOLOAD) : ALIGN(4) {
		__start_noinit_rDomain2 = .;
		tTask_rDomain2_tecsgen.o(.noinit) 
		__end_noinit_rDomain2 = .;
		__end_mo_rwdata_rDomain2 = .;
		__aend_mo_rwdata_rDomain2 = ALIGN(4K);
		__aend_mp_rwdata_rDomain2 = ALIGN(4K);
	} > DDR

	.data_shared ALIGN(4K) : ALIGN(4) {
		__start_mp_rwdata_shared = .;
		__start_mo_rwdata_shared = .;
		__start_data_shared = .;
		tSysLogAdapter_tecsgen.o(.data .data.*) tSysLogAdapter.o(.data .data.*) tTask_tecsgen.o(.data .data.*) tTask.o(.data .data.*) tSample2_tecsgen.o(.data .data.*) tSample2.o(.data .data.*) tKernel_tecsgen.o(.data .data.*) tHRPSVCPlugin_sSysLogSVCCaller_SysLog_eSysLog_tecsgen.o(.data .data.*) tHRPSVCPlugin_sSysLogSVCCaller_SysLog_eSysLog.o(.data .data.*) tHRPSVCPlugin_sSerialPortSVCCaller_SerialPort1_eSerialPort_tecsgen.o(.data .data.*) tHRPSVCPlugin_sSerialPortSVCCaller_SerialPort1_eSerialPort.o(.data .data.*) log_output.o(.data .data.*) vasyslog.o(.data .data.*) t_perror.o(.data .data.*) strerror.o(.data .data.*) libc.a(.data .data.*) libgcc.a(.data .data.*) libxil.a(.data .data.*) 
		__end_data_shared = .;
	} > DDR

	.bss_shared ALIGN(4) (NOLOAD) : ALIGN(4) {
		__start_bss_shared = .;
		tSysLogAdapter_tecsgen.o(.bss .bss.* COMMON) tSysLogAdapter.o(.bss .bss.* COMMON) tTask_tecsgen.o(.bss .bss.* COMMON) tTask.o(.bss .bss.* COMMON) tSample2_tecsgen.o(.bss .bss.* COMMON) tSample2.o(.bss .bss.* COMMON) tKernel_tecsgen.o(.bss .bss.* COMMON) tHRPSVCPlugin_sSysLogSVCCaller_SysLog_eSysLog_tecsgen.o(.bss .bss.* COMMON) tHRPSVCPlugin_sSysLogSVCCaller_SysLog_eSysLog.o(.bss .bss.* COMMON) tHRPSVCPlugin_sSerialPortSVCCaller_SerialPort1_eSerialPort_tecsgen.o(.bss .bss.* COMMON) tHRPSVCPlugin_sSerialPortSVCCaller_SerialPort1_eSerialPort.o(.bss .bss.* COMMON) log_output.o(.bss .bss.* COMMON) vasyslog.o(.bss .bss.* COMMON) t_perror.o(.bss .bss.* COMMON) strerror.o(.bss .bss.* COMMON) libc.a(.bss .bss.* COMMON) libgcc.a(.bss .bss.* COMMON) libxil.a(.bss .bss.* COMMON) 
		__end_bss_shared = .;
	} > DDR

	.noinit_shared ALIGN(4) (NOLOAD) : ALIGN(4) {
		__start_noinit_shared = .;
		tSysLogAdapter_tecsgen.o(.noinit) tSysLogAdapter.o(.noinit) tTask_tecsgen.o(.noinit) tTask.o(.noinit) tSample2_tecsgen.o(.noinit) tSample2.o(.noinit) tKernel_tecsgen.o(.noinit) tHRPSVCPlugin_sSysLogSVCCaller_SysLog_eSysLog_tecsgen.o(.noinit) tHRPSVCPlugin_sSysLogSVCCaller_SysLog_eSysLog.o(.noinit) tHRPSVCPlugin_sSerialPortSVCCaller_SerialPort1_eSerialPort_tecsgen.o(.noinit) tHRPSVCPlugin_sSerialPortSVCCaller_SerialPort1_eSerialPort.o(.noinit) log_output.o(.noinit) vasyslog.o(.noinit) t_perror.o(.noinit) strerror.o(.noinit) libc.a(.noinit) libgcc.a(.noinit) libxil.a(.noinit) 
		__end_noinit_shared = .;
		__end_mo_rwdata_shared = .;
		__aend_mo_rwdata_shared = ALIGN(4K);
		__aend_mp_rwdata_shared = ALIGN(4K);
	} > DDR

	.DDR_align (NOLOAD) : {
		. = ALIGN(4K);
	} > DDR

	/* Stabs debugging sections.  */
	.stab          0 : { *(.stab) }
	.stabstr       0 : { *(.stabstr) }
	.stab.excl     0 : { *(.stab.excl) }
	.stab.exclstr  0 : { *(.stab.exclstr) }
	.stab.index    0 : { *(.stab.index) }
	.stab.indexstr 0 : { *(.stab.indexstr) }
	.comment       0 : { *(.comment) }
	/* DWARF debug sections.
	   Symbols in the DWARF debugging sections are relative to the beginning
	   of the section so we begin them at 0.  */
	/* DWARF 1 */
	.debug          0 : { *(.debug) }
	.line           0 : { *(.line) }
	/* GNU DWARF 1 extensions */
	.debug_srcinfo  0 : { *(.debug_srcinfo) }
	.debug_sfnames  0 : { *(.debug_sfnames) }
	/* DWARF 1.1 and DWARF 2 */
	.debug_aranges  0 : { *(.debug_aranges) }
	.debug_pubnames 0 : { *(.debug_pubnames) }
	/* DWARF 2 */
	.debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
	.debug_abbrev   0 : { *(.debug_abbrev) }
	.debug_line     0 : { *(.debug_line) }
	.debug_frame    0 : { *(.debug_frame) }
	.debug_str      0 : { *(.debug_str) }
	.debug_loc      0 : { *(.debug_loc) }
	.debug_macinfo  0 : { *(.debug_macinfo) }
	/* SGI/MIPS DWARF 2 extensions */
	.debug_weaknames 0 : { *(.debug_weaknames) }
	.debug_funcnames 0 : { *(.debug_funcnames) }
	.debug_typenames 0 : { *(.debug_typenames) }
	.debug_varnames  0 : { *(.debug_varnames) }
	/* DWARF 3 */
	.debug_pubtypes 0 : { *(.debug_pubtypes) }
	.debug_ranges   0 : { *(.debug_ranges) }
	/* DWARF Extension.  */
	.debug_macro    0 : { *(.debug_macro) }
	.ARM.attributes 0 : { KEEP (*(.ARM.attributes)) KEEP (*(.gnu.attributes)) }
	.note.gnu.arm.ident 0 : { KEEP (*(.note.gnu.arm.ident)) }

	/DISCARD/ : {
		*(.*)
	}
}
