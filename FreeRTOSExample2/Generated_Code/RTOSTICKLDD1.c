/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : RTOSTICKLDD1.c
**     Project     : FreeRTOSExample2
**     Processor   : MK64FN1M0VLQ12
**     Component   : TimerUnit_LDD
**     Version     : Component 01.164, Driver 01.11, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2018-09-18, 20:48, # CodeGen: 1
**     Abstract    :
**          This TimerUnit component provides a low level API for unified hardware access across
**          various timer devices using the Prescaler-Counter-Compare-Capture timer structure.
**     Settings    :
**          Component name                                 : RTOSTICKLDD1
**          Module name                                    : SysTick
**          Counter                                        : SYST_CVR
**          Counter direction                              : Down
**          Counter width                                  : 24 bits
**          Value type                                     : Optimal
**          Input clock source                             : Internal
**            Counter frequency                            : Auto select
**          Counter restart                                : On-match
**            Period device                                : SYST_RVR
**            Period                                       : 10 ms
**            Interrupt                                    : Enabled
**              Interrupt                                  : INT_SysTick
**              Interrupt priority                         : medium priority
**          Channel list                                   : 0
**          Initialization                                 : 
**            Enabled in init. code                        : yes
**            Auto initialization                          : no
**            Event mask                                   : 
**              OnCounterRestart                           : Enabled
**              OnChannel0                                 : Disabled
**              OnChannel1                                 : Disabled
**              OnChannel2                                 : Disabled
**              OnChannel3                                 : Disabled
**              OnChannel4                                 : Disabled
**              OnChannel5                                 : Disabled
**              OnChannel6                                 : Disabled
**              OnChannel7                                 : Disabled
**          CPU clock/configuration selection              : 
**            Clock configuration 0                        : This component enabled
**            Clock configuration 1                        : This component disabled
**            Clock configuration 2                        : This component disabled
**            Clock configuration 3                        : This component disabled
**            Clock configuration 4                        : This component disabled
**            Clock configuration 5                        : This component disabled
**            Clock configuration 6                        : This component disabled
**            Clock configuration 7                        : This component disabled
**     Contents    :
**         Init            - LDD_TDeviceData* RTOSTICKLDD1_Init(LDD_TUserData *UserDataPtr);
**         Deinit          - void RTOSTICKLDD1_Deinit(LDD_TDeviceData *DeviceDataPtr);
**         Enable          - LDD_TError RTOSTICKLDD1_Enable(LDD_TDeviceData *DeviceDataPtr);
**         Disable         - LDD_TError RTOSTICKLDD1_Disable(LDD_TDeviceData *DeviceDataPtr);
**         GetCounterValue - RTOSTICKLDD1_TValueType RTOSTICKLDD1_GetCounterValue(LDD_TDeviceData...
**
**     Copyright : 1997 - 2014 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file RTOSTICKLDD1.c
** @version 01.11
** @brief
**          This TimerUnit component provides a low level API for unified hardware access across
**          various timer devices using the Prescaler-Counter-Compare-Capture timer structure.
*/         
/*!
**  @addtogroup RTOSTICKLDD1_module RTOSTICKLDD1 module documentation
**  @{
*/         

/* MODULE RTOSTICKLDD1. */

#include "FRTOS1.h"
#include "RTOSTICKLDD1.h"
#include "FreeRTOS.h" /* FreeRTOS interface */
#include "IO_Map.h"

#ifdef __cplusplus
extern "C" {
#endif 


typedef struct {
  LDD_TUserData *UserDataPtr;          /* RTOS device data structure */
} RTOSTICKLDD1_TDeviceData;

typedef RTOSTICKLDD1_TDeviceData *RTOSTICKLDD1_TDeviceDataPtr; /* Pointer to the device data structure. */

/* {FreeRTOS RTOS Adapter} Global variable used for passing a parameter into ISR */
static RTOSTICKLDD1_TDeviceDataPtr INT_SysTick__BAREBOARD_RTOS_ISRPARAM;

#define AVAILABLE_EVENTS_MASK (LDD_TEventMask)(LDD_TIMERUNIT_ON_COUNTER_RESTART)

/* Internal method prototypes */
/*
** ===================================================================
**     Method      :  RTOSTICKLDD1_Init (component TimerUnit_LDD)
*/
/*!
**     @brief
**         Initializes the device. Allocates memory for the device data
**         structure, allocates interrupt vectors and sets interrupt
**         priority, sets pin routing, sets timing, etc. If the
**         property ["Enable in init. code"] is set to "yes" value then
**         the device is also enabled (see the description of the
**         [Enable] method). In this case the [Enable] method is not
**         necessary and needn't to be generated. This method can be
**         called only once. Before the second call of Init the [Deinit]
**         must be called first.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer will be
**                           passed as an event or callback parameter.
**     @return
**                         - Pointer to the dynamically allocated private
**                           structure or NULL if there was an error.
*/
/* ===================================================================*/
LDD_TDeviceData* RTOSTICKLDD1_Init(LDD_TUserData *UserDataPtr)
{
  /* Allocate device structure */
  RTOSTICKLDD1_TDeviceData *DeviceDataPrv;
  /* {FreeRTOS RTOS Adapter} Driver memory allocation: RTOS function call is defined by FreeRTOS RTOS Adapter property */
  DeviceDataPrv = (RTOSTICKLDD1_TDeviceData *)pvPortMalloc(sizeof(RTOSTICKLDD1_TDeviceData));
  #if FreeRTOS_CHECK_MEMORY_ALLOCATION_ERRORS
  if (DeviceDataPrv == NULL) {
    return (NULL);
  }
  #endif
  DeviceDataPrv->UserDataPtr = UserDataPtr; /* Store the RTOS device structure */
  /* Interrupt vector(s) allocation */
  /* {FreeRTOS RTOS Adapter} Set interrupt vector: IVT is static, ISR parameter is passed by the global variable */
  INT_SysTick__BAREBOARD_RTOS_ISRPARAM = DeviceDataPrv;
  /* SYST_CSR: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,COUNTFLAG=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,CLKSOURCE=0,TICKINT=0,ENABLE=0 */
  SYST_CSR = 0x00U;                    /* Clear control register */
  /* SYST_RVR: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,RELOAD=0x00033332 */
  SYST_RVR = SysTick_RVR_RELOAD(0x00033332); /* Setup reload value */
  /* SYST_CVR: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,CURRENT=0 */
  SYST_CVR = SysTick_CVR_CURRENT(0x00); /* Clear current value */
  /* SCB_SHPR3: PRI_15&=~0x80,PRI_15|=0x70 */
  SCB_SHPR3 = (uint32_t)((SCB_SHPR3 & (uint32_t)~(uint32_t)(
               SCB_SHPR3_PRI_15(0x80)
              )) | (uint32_t)(
               SCB_SHPR3_PRI_15(0x70)
              ));
  /* SYST_CSR: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,COUNTFLAG=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,CLKSOURCE=1,TICKINT=1,ENABLE=1 */
  SYST_CSR = SysTick_CSR_CLKSOURCE_MASK |
             SysTick_CSR_TICKINT_MASK |
             SysTick_CSR_ENABLE_MASK;  /* Set up control register */
  /* Registration of the device structure */
  PE_LDD_RegisterDeviceStructure(PE_LDD_COMPONENT_RTOSTICKLDD1_ID,DeviceDataPrv);
  return ((LDD_TDeviceData *)DeviceDataPrv); /* Return pointer to the device data structure */
}

/*
** ===================================================================
**     Method      :  RTOSTICKLDD1_Deinit (component TimerUnit_LDD)
*/
/*!
**     @brief
**         Deinitializes the device. Switches off the device, frees the
**         device data structure memory, interrupts vectors, etc.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by Init method
*/
/* ===================================================================*/
void RTOSTICKLDD1_Deinit(LDD_TDeviceData *DeviceDataPtr)
{
  RTOSTICKLDD1_TDeviceData *DeviceDataPrv = (RTOSTICKLDD1_TDeviceData *)DeviceDataPtr;

  (void)DeviceDataPrv;
  SysTick_PDD_EnableDevice(SysTick_BASE_PTR, PDD_DISABLE);
  /* Interrupt vector(s) deallocation */
  /* {FreeRTOS RTOS Adapter} Restore interrupt vector: IVT is static, no code is generated */
  /* Unregistration of the device structure */
  PE_LDD_UnregisterDeviceStructure(PE_LDD_COMPONENT_RTOSTICKLDD1_ID);
  /* Deallocation of the device structure */
  /* {FreeRTOS RTOS Adapter} Driver memory deallocation: RTOS function call is defined by FreeRTOS RTOS Adapter property */
  #if FRTOS_MEMORY_SCHEME != 1 /* scheme 1 has no deallocate */
  vPortFree(DeviceDataPrv);
  #endif
}

/*
** ===================================================================
**     Method      :  RTOSTICKLDD1_Enable (component TimerUnit_LDD)
*/
/*!
**     @brief
**         Enables the component - it starts the signal generation.
**         Events may be generated (see SetEventMask). The method is
**         not available if the counter can't be disabled/enabled by HW.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - The component does not work in
**                           the active clock configuration
*/
/* ===================================================================*/
LDD_TError RTOSTICKLDD1_Enable(LDD_TDeviceData *DeviceDataPtr)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  SysTick_PDD_EnableDevice(SysTick_BASE_PTR, PDD_ENABLE); /* Enable the device */
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  RTOSTICKLDD1_Disable (component TimerUnit_LDD)
*/
/*!
**     @brief
**         Disables the component - it stops signal generation and
**         events calling. The method is not available if the counter
**         can't be disabled/enabled by HW.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - The component does not work in
**                           the active clock configuration
*/
/* ===================================================================*/
LDD_TError RTOSTICKLDD1_Disable(LDD_TDeviceData *DeviceDataPtr)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  SysTick_PDD_EnableDevice(SysTick_BASE_PTR, PDD_DISABLE);
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  RTOSTICKLDD1_GetCounterValue (component TimerUnit_LDD)
*/
/*!
**     @brief
**         Returns the content of counter register. This method can be
**         used both if counter is enabled and if counter is disabled.
**         The method is not available if HW doesn't allow reading of
**         the counter.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - Counter value (number of counted ticks).
*/
/* ===================================================================*/
RTOSTICKLDD1_TValueType RTOSTICKLDD1_GetCounterValue(LDD_TDeviceData *DeviceDataPtr)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  return (RTOSTICKLDD1_TValueType)SysTick_PDD_ReadCurrentValueReg(SysTick_BASE_PTR);
}

/*
** ===================================================================
**     Method      :  RTOSTICKLDD1_Interrupt (component TimerUnit_LDD)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         and eventually invokes event(s) of the component.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(RTOSTICKLDD1_Interrupt)
{
  /* {FreeRTOS RTOS Adapter} ISR parameter is passed through the global variable */
  RTOSTICKLDD1_TDeviceDataPtr DeviceDataPrv = INT_SysTick__BAREBOARD_RTOS_ISRPARAM;

  SysTick_PDD_ClearInterruptFlag(SysTick_BASE_PTR); /* Clear interrupt flag */
  RTOSTICKLDD1_OnCounterRestart(DeviceDataPrv->UserDataPtr); /* Invoke OnCounterRestart event */
}

/* END RTOSTICKLDD1. */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
