set ps7_init_tcl [lindex $argv 0]
set load_obj     [lindex $argv 1]

connect -url tcp:127.0.0.1:3121
source $ps7_init_tcl

targets -set -nocase -filter {name =~"APU*"} -index 0
rst -system
after 1000

targets -set -nocase -filter {name =~"APU*"} -index 0
fpga -file ../../../target/ebaz4205_gcc/xilinx_sdk/ebaz4205_hw/design_1_wrapper.bit

#targets -set -nocase -filter {name =~"APU*"} -index 0
#loadhw -hw ../../../target/ebaz4205_gcc/xilinx_sdk/ebaz4205_hw/system.hdf -mem-ranges [list {0x40000000 0xbfffffff}]

configparams force-mem-access 1

targets -set -nocase -filter {name =~"APU*"} -index 0
ps7_init
ps7_post_config

targets -set -nocase -filter {name =~ "ARM*#0"} -index 0
dow $load_obj
bpadd -addr &_kernel_target_exit

configparams force-mem-access 0

targets -set -nocase -filter {name =~ "ARM*#0"} -index 0
con
