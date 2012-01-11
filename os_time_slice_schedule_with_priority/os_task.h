#ifndef _OS_TASK_H_
#define _OS_TASK_H_

#define OS_TASK_TIME_SILCE_WITH_PRIORITY_VERSION_NUMBER_MAJOR (0)
#define OS_TASK_TIME_SILCE_WITH_PRIORITY_VERSION_NUMBER_MINOR (1)
#define OS_TASK_TIME_SILCE_WITH_PRIORITY_VERSION_NUMBER_BUILD (3)

typedef unsigned int tffa_uint32;
typedef signed int tffa_int32;
typedef unsigned short int tffa_uint16;
typedef signed short int tffa_int16;
typedef unsigned char tffa_uint8;
typedef signed char tffa_int8;
typedef signed char tffa_bool;
typedef unsigned int register_type;

typedef void(*os_task_function_pointer)(void);

enum
{
	TFFA_FALSE = 0,
	TFFA_TRUE = 1
};

enum
{
	OS_TASK_STATE_STOPED = 0,
	OS_TASK_STATE_SUPPEND = 1,
	OS_TASK_STATE_RUNNING = 2,
	OS_TASK_STATE_ERROR
};

typedef struct _os_task_ctrl_t_
{
	register_type reg[16];
	tffa_uint32 task_state;
	tffa_uint32 task_stack_start_address;
	tffa_uint32 task_stack_size;
	tffa_uint32 task_priority;
}os_task_ctrl_t;

os_task_ctrl_t*  os_task_create(os_task_function_pointer func_ptr,
					tffa_uint32 task_stack_start_address,
					tffa_uint32 task_stack_size,
					tffa_uint32 task_state,
					tffa_uint32 task_priority);
tffa_uint32 os_task_alloc_task_stack(tffa_uint32 task_stack_size);
void os_task_init(tffa_uint32 memory_pool_start_address);
void os_task_schedule(void);

#endif//_OS_TASK_H_

