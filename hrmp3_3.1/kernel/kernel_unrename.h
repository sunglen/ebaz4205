/* This file is generated from kernel_rename.def by genrename. */

/* This file is included only when kernel_rename.h has been included. */
#ifdef TOPPERS_KERNEL_RENAME_H
#undef TOPPERS_KERNEL_RENAME_H

/*
 *  startup.c
 */
#undef barrier_sync
#undef exit_kernel
#undef dispatch_handler
#undef ext_ker_handler

/*
 *  domain.c
 */
#undef p_global_cursom
#undef p_global_nxtsom
#undef scycprc_bitmap
#undef scyc_evttim
#undef initialize_domain
#undef twdtimer_start
#undef twdtimer_stop
#undef twdtimer_control
#undef scyc_start
#undef scyc_switch
#undef twd_start
#undef twd_switch
#undef set_dspflg
#undef start_scyc_handler

/*
 *  task.c
 */
#undef initialize_task
#undef search_predtsk
#undef update_my_schedtsk
#undef update_schedtsk
#undef make_runnable
#undef make_non_runnable
#undef make_dormant
#undef make_active
#undef change_priority
#undef rotate_ready_queue
#undef task_terminate
#undef migrate_self
#undef migrate_activate_self

/*
 *  taskhook.c
 */
#undef mtxhook_check_ceilpri
#undef mtxhook_scan_ceilmtx
#undef mtxhook_release_all
#undef mbfhook_dequeue_wobj

/*
 *  wait.c
 */
#undef make_wait_tmout
#undef wait_dequeue_wobj
#undef wait_complete
#undef wait_tmout
#undef wait_tmout_ok
#undef wobj_make_wait
#undef wobj_make_wait_tmout
#undef init_wait_queue

/*
 *  memory.c
 */
#undef initialize_memory
#undef search_meminib
#undef probe_mem_write
#undef probe_mem_read
#undef initialize_sections

/*
 *  time_event.c
 */
#undef boundary_evttim
#undef current_evttim
#undef current_hrtcnt
#undef monotonic_evttim
#undef systim_offset
#undef initialize_tmevt
#undef tmevt_up
#undef tmevt_down
#undef update_current_evttim
#undef set_hrt_event
#undef set_hrt_event_handler
#undef tmevtb_register
#undef tmevtb_enqueue
#undef tmevtb_enqueue_reltim
#undef tmevtb_dequeue
#undef check_adjtim
#undef tmevt_lefttim
#undef tmevt_proc_top
#undef signal_time

/*
 *  semaphore.c
 */
#undef initialize_semaphore

/*
 *  eventflag.c
 */
#undef initialize_eventflag
#undef check_flg_cond

/*
 *  dataqueue.c
 */
#undef initialize_dataqueue
#undef enqueue_data
#undef force_enqueue_data
#undef dequeue_data
#undef send_data
#undef force_send_data
#undef receive_data

/*
 *  pridataq.c
 */
#undef initialize_pridataq
#undef enqueue_pridata
#undef dequeue_pridata
#undef send_pridata
#undef receive_pridata

/*
 *  mutex.c
 */
#undef initialize_mutex
#undef mutex_check_ceilpri
#undef mutex_scan_ceilmtx
#undef mutex_drop_priority
#undef mutex_acquire
#undef mutex_release
#undef mutex_release_all

/*
 *  messagebuf.c
 */
#undef initialize_messagebuf
#undef enqueue_message
#undef dequeue_message
#undef send_message
#undef messagebuf_signal
#undef receive_message
#undef messagebuf_dequeue_wobj

/*
 *  mempfix.c
 */
#undef initialize_mempfix
#undef get_mpf_block

/*
 *  spin_lock.c
 */
#undef initialize_spin_lock
#undef force_unlock_spin

/*
 *  cyclic.c
 */
#undef initialize_cyclic
#undef call_cyclic

/*
 *  alarm.c
 */
#undef initialize_alarm
#undef call_alarm

/*
 *  interrupt.c
 */
#undef initialize_interrupt

/*
 *  exception.c
 */
#undef initialize_exception

/*
 *  svc_table.c
 */
#undef svc_table

/*
 *  kernel_cfg.c
 */
#undef kerflg_table
#undef p_pcb_table
#undef initialize_object
#undef inirtnbb_table
#undef terrtnbb_table
#undef p_scyc_tmevtb_table
#undef p_schedcb_idle_table
#undef p_tmevt_heap_idle_table
#undef tmax_tskid
#undef tinib_table
#undef torder_table
#undef p_tcb_table
#undef tmax_semid
#undef seminib_table
#undef p_semcb_table
#undef tmax_flgid
#undef flginib_table
#undef p_flgcb_table
#undef tmax_dtqid
#undef dtqinib_table
#undef p_dtqcb_table
#undef tmax_pdqid
#undef pdqinib_table
#undef p_pdqcb_table
#undef tmax_mtxid
#undef mtxinib_table
#undef p_mtxcb_table
#undef tmax_mbfid
#undef mbfinib_table
#undef p_mbfcb_table
#undef tmax_mpfid
#undef mpfinib_table
#undef p_mpfcb_table
#undef tmax_spnid
#undef spninib_table
#undef p_spncb_table
#undef tmax_cycid
#undef cycinib_table
#undef p_cyccb_table
#undef tmax_almid
#undef alminib_table
#undef p_almcb_table
#undef tnum_def_inhno
#undef inhinib_table
#undef tnum_cfg_intno
#undef intinib_table
#undef tnum_def_excno
#undef excinib_table
#undef tmax_fncd
#undef svcinib_table
#undef sysstat_acvct
#undef istksz_table
#undef istk_table
#undef istkpt_table
#undef idstk_table
#undef idstkpt_table
#undef initialize_object
#undef system_cyctim
#undef tmax_somid
#undef p_inisom
#undef sominib_table
#undef tmax_domid
#undef dominib_kernel
#undef dominib_table
#undef twdinib_table

/*
 *  kernel_mem.c
 */
#undef tnum_meminib
#undef memtop_table
#undef meminib_table
#undef tnum_datasec
#undef datasecinib_table
#undef tnum_bsssec
#undef bsssecinib_table

/*
 *  tTraceLog.c
 */
#undef log_dsp_enter
#undef log_dsp_leave
#undef log_inh_enter
#undef log_inh_leave
#undef log_exc_enter
#undef log_exc_leave
#undef log_extsvc_enter
#undef log_extsvc_leave


#include "target_unrename.h"

#endif /* TOPPERS_KERNEL_RENAME_H */
