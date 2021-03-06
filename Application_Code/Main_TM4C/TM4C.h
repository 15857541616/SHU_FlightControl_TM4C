/*
************************************************************************************************************************
*                                                TI-TM4C Flight Control
*                                               SCIE/Shanghai University
*                                              
* File    : TM4C.h
* By      : Bicbrv
* Note    : 
*
* TERMS OF USE:
* ---------------
*           We provide ALL the source code for your convenience and to help you 
*           keep developing our flight control firmware.  
*
*           Please help us continue to provide our project with the finest software available.
*           Your dedicated work is greatly appreciated. Feel free to ameliorate any 
*           part of our code without any restriction to pursue maximum performance.
*
************************************************************************************************************************
*/
/*
**********************************************************************************************************
*UCOSIII中以下优先级用户程序不能使用
*将这些优先级分配给了UCOSIII的5个系统内部任务
*优先级0：中断服务服务管理任务 OS_IntQTask()
*优先级1：时钟节拍任务 OS_TickTask()
*优先级2：定时任务 OS_TmrTask()
*优先级OS_CFG_PRIO_MAX-2：统计任务 OS_StatTask()
*优先级OS_CFG_PRIO_MAX-1：空闲任务 OS_IdleTask()
**********************************************************************************************************
*/ 
#ifndef __CORE_MAIN_H
#define __CORE_MAIN_H

#include <chiplevel_includes.h>
#include <includes.h>

#include "data_common.h"
#include "param_common.h"
#include "driverlib/eeprom.h"
#include "attitudesolving.h"
#include "stabilization.h"
#include "motor_control.h"
#include "sensorfetch.h"
#include "PX4Flow.h"
#include "KS103.h"

#include "common.h"
#include "include.h"
#include "flight_routine.h"

#include "core_uart.h"
#include "core_camera.h"
#include "core_autopilot.h"

/*
************************************************************************************************************************
*                                               Start task
************************************************************************************************************************
*/
#define START_TASK_PRIO      3
#define START_STK_SIZE       512
extern OS_TCB	StartTaskTCB;
extern CPU_STK	START_TASK_STK[START_STK_SIZE];
static void start_task(void *p_arg);

/*
************************************************************************************************************************
*                                               Flight init module
************************************************************************************************************************
*/
#define FLIGHT_INIT_TASK_PRIO      3
#define FLIGHT_INIT_STK_SIZE       512
extern OS_TCB	FlightINITTCB;
extern CPU_STK	FLIGHT_INIT_TASK_STK[FLIGHT_INIT_STK_SIZE];
static void flight_init_task(void *p_arg);
/*
************************************************************************************************************************
*                                               Flight routine
************************************************************************************************************************
*/
#define FLIGHT_ROUTINE_TASK_PRIO      4
#define FLIGHT_ROUTINE_STK_SIZE       1536
extern OS_TCB	FlightRoutineTCB;
extern CPU_STK	FLIGHT_ROUTINE_TASK_STK[FLIGHT_ROUTINE_STK_SIZE];
void flight_routine_task(void *p_arg);
/*
************************************************************************************************************************
*                                               Flight flow
************************************************************************************************************************
*/
#define FLIGHT_ROUTINE_CONTROL_TASK_PRIO      5
#define FLIGHT_ROUTINE_CONTROL_STK_SIZE       128
extern OS_TCB	FlightRoutineControlTCB;
extern CPU_STK	FLIGHT_ROUTINE_CONTROL_TASK_STK[FLIGHT_ROUTINE_CONTROL_STK_SIZE];
void flight_routine_control_task(void *p_arg);
/*
************************************************************************************************************************
*                                               Ultra sonic senor
************************************************************************************************************************
*/
#define FLIGHT_ROUTINE_KS103_TASK_PRIO        6
#define FLIGHT_ROUTINE_KS103_STK_SIZE       128
extern OS_TCB	FlightRoutineKS103TCB;
extern CPU_STK	FLIGHT_ROUTINE_KS103_TASK_STK[FLIGHT_ROUTINE_KS103_STK_SIZE];
void flight_routine_ks103_task(void *p_arg);

/*
************************************************************************************************************************
*                                               Gimbal
************************************************************************************************************************
*/
#define CAMERA_TASK_PRIO        11
#define CAMERA_STK_SIZE       128
extern OS_TCB	CameraTCB;
extern CPU_STK	CAMERA_TASK_STK[CAMERA_STK_SIZE];
void camera_task(void *p_arg);
/*
************************************************************************************************************************
*                                               Radio telemetry
************************************************************************************************************************
*/
#define UART_REPORT_TASK_PRIO        10
#define UART_REPORT_TASK_SIZE       128
extern OS_TCB	UARTReportTCB;
extern CPU_STK	UART_REPORT_TASK_STK[UART_REPORT_TASK_SIZE];
void uart_report_task(void *p_arg);
/*
************************************************************************************************************************
*                                               GCS instruction receiver
************************************************************************************************************************
*/ 
#define UART_ADJUST_TASK_PRIO        9
#define UART_ADJUST_TASK_SIZE       128
extern OS_TCB	UARTAdjustTCB;
extern CPU_STK	UART_Adjust_TASK_STK[UART_ADJUST_TASK_SIZE];
void uart_adjust_task(void *p_arg);
/*
************************************************************************************************************************
*                                               Autopilot
************************************************************************************************************************
*/
#define AUTO_TEST_FLIGHT_TASK_PRIO        7
#define AUTO_TEST_FLIGHT_TASK_SIZE       128
extern OS_TCB	AUTOtestflight;
extern CPU_STK	AUTO_TEST_FLIGHT_TASK_STK[AUTO_TEST_FLIGHT_TASK_SIZE];
void auto_test_flight_task(void *p_arg);
/*
************************************************************************************************************************
*                                               Auto takeoff
************************************************************************************************************************
*/
#define AUTO_TAKEOFF_TASK_PRIO        7
#define AUTO_TAKEOFF_TASK_SIZE       128
extern OS_TCB	AUTOtakeoff;
extern CPU_STK	AUTO_TAKEOFF_TASK_STK[AUTO_TAKEOFF_TASK_SIZE];
void auto_takeoff_task(void *p_arg);
/*
************************************************************************************************************************
*                                               Auto landing
************************************************************************************************************************
*/
#define AUTO_LANDING_TASK_PRIO        7
#define AUTO_LANDIND_TASK_SIZE       128
extern OS_TCB	AUTOlanding;
extern CPU_STK	AUTO_LANDIND_TASK_STK[AUTO_LANDIND_TASK_SIZE];
void auto_landing_task(void *p_arg);

/*
========================================================================================================================
*                                               Defines
========================================================================================================================
*/
#define MOTORRESET       0u << 0u
#define NRF              1u << 1u
/*
========================================================================================================================
*                                               Function Prototypes
========================================================================================================================
*/
static void FlightAPPInit(CPU_INT08U set);

#endif  //__MAIN_H__