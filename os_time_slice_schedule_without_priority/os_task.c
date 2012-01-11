#include "os_task.h"

#define OS_TASK_VOLUME (8)

os_task_ctrl_t os_task_ctrl[OS_TASK_VOLUME];
os_task_ctrl_t* pos_task_ctrl_current;

static tffa_int32 os_task_volume_limit = 0;
static tffa_uint32 os_task_current_task_index = 0;
static tffa_uint32 os_task_memory_pool_current_address = 0;

os_task_ctrl_t*  os_task_create(os_task_function_pointer func_ptr,
					tffa_uint32 task_stack_start_address,
					tffa_uint32 task_stack_size,
					tffa_uint32 task_state,
					tffa_int32 task_time_slice)
{
	os_task_ctrl_t* pret = &os_task_ctrl[os_task_volume_limit];

	os_task_ctrl[os_task_volume_limit].task_state = task_state;
	os_task_ctrl[os_task_volume_limit].task_id = os_task_volume_limit;
	os_task_ctrl[os_task_volume_limit].task_stack_start_address = task_stack_start_address;
	os_task_ctrl[os_task_volume_limit].task_stack_size = task_stack_size;
	os_task_ctrl[os_task_volume_limit].task_time_slice = task_time_slice;
	os_task_ctrl[os_task_volume_limit].task_time_slice_counter = task_time_slice;
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
	os_task_memory_pool_current_address = memory_pool_start_address;
}

void os_task_schedule(void)
{
	tffa_uint32 i;
	tffa_uint32 task_index = os_task_current_task_index;
	tffa_bool find_active_task_flag = TFFA_FALSE;

	do
	{
		i = 0;

		while((os_task_ctrl[task_index].task_state != OS_TASK_STATE_RUNNING)&&
			(i < os_task_volume_limit))
		{
			i++;
			task_index++;
			if(task_index >= os_task_volume_limit)
			{
				task_index = 0;
			}
		}

		if(os_task_ctrl[task_index].task_time_slice_counter > 0)
		{
			os_task_ctrl[task_index].task_time_slice_counter--;
			os_task_current_task_index = os_task_ctrl[task_index].task_id;
			find_active_task_flag = TFFA_TRUE;
		}
		else
		{
			os_task_ctrl[task_index].task_time_slice_counter = os_task_ctrl[task_index].task_time_slice;

			task_index++;
			if(task_index >= os_task_volume_limit)
			{
				task_index = 0;
			}

			find_active_task_flag = TFFA_FALSE;
		}
	}while(find_active_task_flag == TFFA_FALSE);

	pos_task_ctrl_current = &os_task_ctrl[os_task_current_task_index];
}

