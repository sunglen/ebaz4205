/* This file is generated from kernel_rename.def by genrename. */

#ifndef TOPPERS_KERNEL_RENAME_H
#define TOPPERS_KERNEL_RENAME_H

/*
 *  startup.c
 */
#define barrier_sync				_kernel_barrier_sync
#define exit_kernel					_kernel_exit_kernel
#define dispatch_handler			_kernel_dispatch_handler
#define ext_ker_handler				_kernel_ext_ker_handler

/*
 *  domain.c
 */
#define p_global_cursom				_kernel_p_global_cursom
#define p_global_nxtsom				_kernel_p_global_nxtsom
#define scycprc_bitmap				_kernel_scycprc_bitmap
#define scyc_evttim					_kernel_scyc_evttim
#define initialize_domain			_kernel_initialize_domain
#define twdtimer_start				_kernel_twdtimer_start
#define twdtimer_stop				_kernel_twdtimer_stop
#define twdtimer_control			_kernel_twdtimer_control
#define scyc_start					_kernel_scyc_start
#define scyc_switch					_kernel_scyc_switch
#define twd_start					_kernel_twd_start
#define twd_switch					_kernel_twd_switch
#define set_dspflg					_kernel_set_dspflg
#define start_scyc_handler			_kernel_start_scyc_handler

/*
 *  task.c
 */
#define initialize_task				_kernel_initialize_task
#define search_predtsk				_kernel_search_predtsk
#define update_my_schedtsk			_kernel_update_my_schedtsk
#define update_schedtsk				_kernel_update_schedtsk
#define make_runnable				_kernel_make_runnable
#define make_non_runnable			_kernel_make_non_runnable
#define make_dormant				_kernel_make_dormant
#define make_active					_kernel_make_active
#define change_priority				_kernel_change_priority
#define rotate_ready_queue			_kernel_rotate_ready_queue
#define task_terminate				_kernel_task_terminate
#define migrate_self				_kernel_migrate_self
#define migrate_activate_self		_kernel_migrate_activate_self

/*
 *  taskhook.c
 */
#define mtxhook_check_ceilpri		_kernel_mtxhook_check_ceilpri
#define mtxhook_scan_ceilmtx		_kernel_mtxhook_scan_ceilmtx
#define mtxhook_release_all			_kernel_mtxhook_release_all
#define mbfhook_dequeue_wobj		_kernel_mbfhook_dequeue_wobj

/*
 *  wait.c
 */
#define make_wait_tmout				_kernel_make_wait_tmout
#define wait_dequeue_wobj			_kernel_wait_dequeue_wobj
#define wait_complete				_kernel_wait_complete
#define wait_tmout					_kernel_wait_tmout
#define wait_tmout_ok				_kernel_wait_tmout_ok
#define wobj_make_wait				_kernel_wobj_make_wait
#define wobj_make_wait_tmout		_kernel_wobj_make_wait_tmout
#define init_wait_queue				_kernel_init_wait_queue

/*
 *  memory.c
 */
#define initialize_memory			_kernel_initialize_memory
#define search_meminib				_kernel_search_meminib
#define probe_mem_write				_kernel_probe_mem_write
#define probe_mem_read				_kernel_probe_mem_read
#define initialize_sections			_kernel_initialize_sections

/*
 *  time_event.c
 */
#define boundary_evttim				_kernel_boundary_evttim
#define current_evttim				_kernel_current_evttim
#define current_hrtcnt				_kernel_current_hrtcnt
#define monotonic_evttim			_kernel_monotonic_evttim
#define systim_offset				_kernel_systim_offset
#define initialize_tmevt			_kernel_initialize_tmevt
#define tmevt_up					_kernel_tmevt_up
#define tmevt_down					_kernel_tmevt_down
#define update_current_evttim		_kernel_update_current_evttim
#define set_hrt_event				_kernel_set_hrt_event
#define set_hrt_event_handler		_kernel_set_hrt_event_handler
#define tmevtb_register				_kernel_tmevtb_register
#define tmevtb_enqueue				_kernel_tmevtb_enqueue
#define tmevtb_enqueue_reltim		_kernel_tmevtb_enqueue_reltim
#define tmevtb_dequeue				_kernel_tmevtb_dequeue
#define check_adjtim				_kernel_check_adjtim
#define tmevt_lefttim				_kernel_tmevt_lefttim
#define tmevt_proc_top				_kernel_tmevt_proc_top
#define signal_time					_kernel_signal_time

/*
 *  semaphore.c
 */
#define initialize_semaphore		_kernel_initialize_semaphore

/*
 *  eventflag.c
 */
#define initialize_eventflag		_kernel_initialize_eventflag
#define check_flg_cond				_kernel_check_flg_cond

/*
 *  dataqueue.c
 */
#define initialize_dataqueue		_kernel_initialize_dataqueue
#define enqueue_data				_kernel_enqueue_data
#define force_enqueue_data			_kernel_force_enqueue_data
#define dequeue_data				_kernel_dequeue_data
#define send_data					_kernel_send_data
#define force_send_data				_kernel_force_send_data
#define receive_data				_kernel_receive_data

/*
 *  pridataq.c
 */
#define initialize_pridataq			_kernel_initialize_pridataq
#define enqueue_pridata				_kernel_enqueue_pridata
#define dequeue_pridata				_kernel_dequeue_pridata
#define send_pridata				_kernel_send_pridata
#define receive_pridata				_kernel_receive_pridata

/*
 *  mutex.c
 */
#define initialize_mutex			_kernel_initialize_mutex
#define mutex_check_ceilpri			_kernel_mutex_check_ceilpri
#define mutex_scan_ceilmtx			_kernel_mutex_scan_ceilmtx
#define mutex_drop_priority			_kernel_mutex_drop_priority
#define mutex_acquire				_kernel_mutex_acquire
#define mutex_release				_kernel_mutex_release
#define mutex_release_all			_kernel_mutex_release_all

/*
 *  messagebuf.c
 */
#define initialize_messagebuf		_kernel_initialize_messagebuf
#define enqueue_message				_kernel_enqueue_message
#define dequeue_message				_kernel_dequeue_message
#define send_message				_kernel_send_message
#define messagebuf_signal			_kernel_messagebuf_signal
#define receive_message				_kernel_receive_message
#define messagebuf_dequeue_wobj		_kernel_messagebuf_dequeue_wobj

/*
 *  mempfix.c
 */
#define initialize_mempfix			_kernel_initialize_mempfix
#define get_mpf_block				_kernel_get_mpf_block

/*
 *  spin_lock.c
 */
#define initialize_spin_lock		_kernel_initialize_spin_lock
#define force_unlock_spin			_kernel_force_unlock_spin

/*
 *  cyclic.c
 */
#define initialize_cyclic			_kernel_initialize_cyclic
#define call_cyclic					_kernel_call_cyclic

/*
 *  alarm.c
 */
#define initialize_alarm			_kernel_initialize_alarm
#define call_alarm					_kernel_call_alarm

/*
 *  interrupt.c
 */
#define initialize_interrupt		_kernel_initialize_interrupt

/*
 *  exception.c
 */
#define initialize_exception		_kernel_initialize_exception

/*
 *  svc_table.c
 */
#define svc_table					_kernel_svc_table

/*
 *  kernel_cfg.c
 */
#define kerflg_table				_kernel_kerflg_table
#define p_pcb_table					_kernel_p_pcb_table
#define initialize_object			_kernel_initialize_object
#define inirtnbb_table				_kernel_inirtnbb_table
#define terrtnbb_table				_kernel_terrtnbb_table
#define p_scyc_tmevtb_table			_kernel_p_scyc_tmevtb_table
#define p_schedcb_idle_table		_kernel_p_schedcb_idle_table
#define p_tmevt_heap_idle_table		_kernel_p_tmevt_heap_idle_table
#define tmax_tskid					_kernel_tmax_tskid
#define tinib_table					_kernel_tinib_table
#define torder_table				_kernel_torder_table
#define p_tcb_table					_kernel_p_tcb_table
#define tmax_semid					_kernel_tmax_semid
#define seminib_table				_kernel_seminib_table
#define p_semcb_table				_kernel_p_semcb_table
#define tmax_flgid					_kernel_tmax_flgid
#define flginib_table				_kernel_flginib_table
#define p_flgcb_table				_kernel_p_flgcb_table
#define tmax_dtqid					_kernel_tmax_dtqid
#define dtqinib_table				_kernel_dtqinib_table
#define p_dtqcb_table				_kernel_p_dtqcb_table
#define tmax_pdqid					_kernel_tmax_pdqid
#define pdqinib_table				_kernel_pdqinib_table
#define p_pdqcb_table				_kernel_p_pdqcb_table
#define tmax_mtxid					_kernel_tmax_mtxid
#define mtxinib_table				_kernel_mtxinib_table
#define p_mtxcb_table				_kernel_p_mtxcb_table
#define tmax_mbfid					_kernel_tmax_mbfid
#define mbfinib_table				_kernel_mbfinib_table
#define p_mbfcb_table				_kernel_p_mbfcb_table
#define tmax_mpfid					_kernel_tmax_mpfid
#define mpfinib_table				_kernel_mpfinib_table
#define p_mpfcb_table				_kernel_p_mpfcb_table
#define tmax_spnid					_kernel_tmax_spnid
#define spninib_table				_kernel_spninib_table
#define p_spncb_table				_kernel_p_spncb_table
#define tmax_cycid					_kernel_tmax_cycid
#define cycinib_table				_kernel_cycinib_table
#define p_cyccb_table				_kernel_p_cyccb_table
#define tmax_almid					_kernel_tmax_almid
#define alminib_table				_kernel_alminib_table
#define p_almcb_table				_kernel_p_almcb_table
#define tnum_def_inhno				_kernel_tnum_def_inhno
#define inhinib_table				_kernel_inhinib_table
#define tnum_cfg_intno				_kernel_tnum_cfg_intno
#define intinib_table				_kernel_intinib_table
#define tnum_def_excno				_kernel_tnum_def_excno
#define excinib_table				_kernel_excinib_table
#define tmax_fncd					_kernel_tmax_fncd
#define svcinib_table				_kernel_svcinib_table
#define sysstat_acvct				_kernel_sysstat_acvct
#define istksz_table				_kernel_istksz_table
#define istk_table					_kernel_istk_table
#define istkpt_table				_kernel_istkpt_table
#define idstk_table					_kernel_idstk_table
#define idstkpt_table				_kernel_idstkpt_table
#define initialize_object			_kernel_initialize_object
#define system_cyctim				_kernel_system_cyctim
#define tmax_somid					_kernel_tmax_somid
#define p_inisom					_kernel_p_inisom
#define sominib_table				_kernel_sominib_table
#define tmax_domid					_kernel_tmax_domid
#define dominib_kernel				_kernel_dominib_kernel
#define dominib_table				_kernel_dominib_table
#define twdinib_table				_kernel_twdinib_table

/*
 *  kernel_mem.c
 */
#define tnum_meminib				_kernel_tnum_meminib
#define memtop_table				_kernel_memtop_table
#define meminib_table				_kernel_meminib_table
#define tnum_datasec				_kernel_tnum_datasec
#define datasecinib_table			_kernel_datasecinib_table
#define tnum_bsssec					_kernel_tnum_bsssec
#define bsssecinib_table			_kernel_bsssecinib_table

/*
 *  tTraceLog.c
 */
#define log_dsp_enter				_kernel_log_dsp_enter
#define log_dsp_leave				_kernel_log_dsp_leave
#define log_inh_enter				_kernel_log_inh_enter
#define log_inh_leave				_kernel_log_inh_leave
#define log_exc_enter				_kernel_log_exc_enter
#define log_exc_leave				_kernel_log_exc_leave
#define log_extsvc_enter			_kernel_log_extsvc_enter
#define log_extsvc_leave			_kernel_log_extsvc_leave


#include "target_rename.h"

#endif /* TOPPERS_KERNEL_RENAME_H */
