	import |Image$$RO$$Limit|
	import |Image$$RW$$Base|
	import |Image$$ZI$$Base|
	import |Image$$ZI$$Limit|
	import pos_task_ctrl_current
	import os_task_init
	import os_task_schedule
	import demo_application_init

	area boot,code,readonly
	code32

	ldr pc,poweron_reset
	nop
	nop
	nop
	nop
	nop
	nop
	nop

poweron_reset dcd poweron_reset_handler
task_ctrl_current dcd pos_task_ctrl_current

usr_mode equ 0x10
svc_mode equ 0x13
sys_mode equ 0x1f
irq_mode equ 0x12
fiq_mode equ 0x11
irq_disable equ 0x80
fiq_disable equ 0x40

	entry
poweron_reset_handler
	ldr r0,=|Image$$RO$$Limit|
	ldr r1,=|Image$$RW$$Base|
	ldr r2,=|Image$$ZI$$Base|
	ldr r3,=|Image$$ZI$$Limit|

	cmp r0,r1
	beq zeroinit
rwcopy
	cmp r1,r2
	ldrcc r4,[r0],#4
	strcc r4,[r1],#4
	bcc rwcopy

zeroinit
	cmp r2,r3
	mov r4,#0
	strcc r4,[r2],#4
	bcc zeroinit

	ldr r0,=|Image$$ZI$$Limit|
	msr cpsr_c,#(svc_mode|fiq_disable|irq_disable)
	mov r1,#1024
	add r2,r0,r1
	bic r2,r2,#3
	mov sp,r2
	add sp,r2,#1024

	mov r0,sp
	bl os_task_init
	bl demo_application_init
	bl os_task_schedule
	b task_schedule

	export assemble_schedule
assemble_schedule
	str r0,[sp,#4*-1]
	ldr r0,task_ctrl_current
	ldr r0,[r0]
	add r0,r0,#4
	stmia r0,{r1-r13,lr}
	sub r0,r0,#4
	ldr r1,[sp,#4*-1]
	str r1,[r0]
	bl os_task_schedule

	export task_schedule
task_schedule
	ldr r0,task_ctrl_current
	ldr r0,[r0]
	add r0,r0,#4
	ldmia r0,{r1-r13,lr}
	sub r0,r0,#4
	ldr r0,[r0]
	mov pc,r14
	
	end




