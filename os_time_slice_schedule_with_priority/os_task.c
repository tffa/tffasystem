#include "os_task.h"

#define OS_TASK_VOLUME (8)

os_task_ctrl_t os_task_ctrl[OS_TASK_VOLUME];
os_task_ctrl_t* pos_task_ctrl_current;

static tffa_uint32 os_task_current_task_index = 0;
static tffa_uint32 os_task_volume_limit = 0;
static tffa_uint32 os_task_memory_pool_current_address;

os_task_ctrl_t*  os_task_create(os_task_function_pointer func_ptr,
					tffa_uint32 task_stack_start_address,
					tffa_uint32 task_stack_size,
					tffa_uint32 task_state,
					tffa_uint32 task_priority)
{
	os_task_ctrl_t* pret = &os_task_ctrl[os_task_volume_limit];

	os_task_ctrl[os_task_volume_limit].task_priority = task_priority;
	os_task_ctrl[os_task_volume_limit].task_state = task_state;
	os_task_ctrl[os_task_volume_limit].task_stack_start_address = task_stack_start_address;
	os_task_ctrl[os_task_volume_limit].task_stack_size = task_stack_size;
	os_task_ctrl[os_task_volume_limit].reg[14] = (tffa_uint32)func_ptr;

	os_task_volume_limit++;

	return pret;
}

tffa_uint32 os_task_alloc_task_stack(tffa_uint32 task_stack_size)
{
	os_task_memory_pool_current_address += task_stack_size;

	return os_task_memory_pool_current_address;
}

void os_task_init(tffa_uint32 memory_pool_start_address)
{
	tffa_uint32 i,j;

	for(i = 0; i < OS_TASK_VOLUME; i++)
	{
		os_task_ctrl[i].task_priority = 0xFFFFFFFF;
		os_task_ctrl[i].task_stack_size = 0;
		os_task_ctrl[i].task_stack_start_address = 0xFFFFFFFF;
		os_task_ctrl[i].task_state = OS_TASK_STATE_ERROR;

		for(j = 0; j < 16; j++)
		{
			os_task_ctrl[i].reg[j] = 0;
		}
	}

	os_task_memory_pool_current_address = memory_pool_start_address;
}

void os_task_schedule(void)
{
	tffa_uint32 i;
	tffa_uint32 priority = os_task_ctrl[0].task_priority;

	for(i = 0; i < os_task_volume_limit; i++)
	{
		if(os_task_ctrl[i].task_priority < priority)	
		{
			if(os_task_ctrl[i].task_state == OS_TASK_STATE_RUNNING)
			{
				os_task_current_task_index = i;
			}
		}
	}

	pos_task_ctrl_current = &os_task_ctrl[os_task_current_task_index];
}

