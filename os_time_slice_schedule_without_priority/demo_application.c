#include "os_task.h"
#include "demo_application.h"

#define DEMO_APPLICATION_TASK0_STACK_SIZE (1024)
#define DEMO_APPLICATION_TASK1_STACK_SIZE (1024)
#define DEMO_APPLICATION_TASK2_STACK_SIZE (1024)
#define DEMO_APPLICATION_TASK3_STACK_SIZE (1024)

os_task_ctrl_t* ptask0;
os_task_ctrl_t* ptask1;
os_task_ctrl_t* ptask2;
os_task_ctrl_t* ptask3;

extern void assemble_schedule(void);

void demo_application_init(void)
{
	tffa_uint32 stack_address;

	stack_address = os_task_alloc_task_stack(DEMO_APPLICATION_TASK0_STACK_SIZE);
	ptask0 = os_task_create(
				os_task0,
				stack_address,
				DEMO_APPLICATION_TASK0_STACK_SIZE,
				OS_TASK_STATE_RUNNING,
				5);

	stack_address = os_task_alloc_task_stack(DEMO_APPLICATION_TASK1_STACK_SIZE);
	ptask1 = os_task_create(
			os_task1,
			stack_address,
			DEMO_APPLICATION_TASK1_STACK_SIZE,
			OS_TASK_STATE_RUNNING,
			6);

	stack_address = os_task_alloc_task_stack(DEMO_APPLICATION_TASK2_STACK_SIZE);
	ptask2 = os_task_create(
			os_task2,
			stack_address,
			DEMO_APPLICATION_TASK2_STACK_SIZE,
			OS_TASK_STATE_RUNNING,
			7);

	stack_address = os_task_alloc_task_stack(DEMO_APPLICATION_TASK3_STACK_SIZE);
	ptask3 = os_task_create(
			os_task3,
			stack_address,
			DEMO_APPLICATION_TASK3_STACK_SIZE,
			OS_TASK_STATE_RUNNING,
			8);
}

void os_task0(void)
{
	volatile tffa_uint32 os_task0_current_index = 0;

	while(1)
	{
		os_task0_current_index++;
		assemble_schedule();
		os_task0_current_index++;
		os_task0_current_index++;
	}
}

void os_task1(void)
{
	volatile tffa_uint32 os_task1_current_index = 0;

	while(1)
	{
		os_task1_current_index++;
		assemble_schedule();
		os_task1_current_index++;
		os_task1_current_index++;
	}
}

void os_task2(void)
{
	volatile tffa_uint32 os_task2_current_index = 0;

	while(1)
	{
		os_task2_current_index++;
		assemble_schedule();
		os_task2_current_index++;
		os_task2_current_index++;
	}
}

void os_task3(void)
{
	volatile tffa_uint32 os_task3_current_index = 0;

	while(1)
	{
		os_task3_current_index++;
		assemble_schedule();
		os_task3_current_index++;
		os_task3_current_index++;
	}
}

