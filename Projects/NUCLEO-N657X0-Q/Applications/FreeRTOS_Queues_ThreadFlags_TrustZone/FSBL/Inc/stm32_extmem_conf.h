/**
  ******************************************************************************
  * @file    stm32_extmem_conf.h
  * @author  GPM Application Team
  * @brief   Header configuration for extmem module
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef EXTMEM_CONF_H_
#define EXTMEM_CONF_H_

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup EXTMEN_CONF
  * @{
  */
 
/*
  @brief management of the driver layer enable
*/
#define EXTMEM_DRIVER_NOR_SFDP   1
#define EXTMEM_DRIVER_PSRAM  0

/*
  @brief management of the driver layer enable
*/
#define EXTMEM_SAL_XSPI      1

/* Includes ------------------------------------------------------------------*/
#include "stm32n6xx_hal.h"
#include "stm32_extmem.h"
#include "stm32_extmem_type.h"
#include "boot/stm32_boot_lrun.h"

/*
  @brief import of the HAL handles for MEMORRY_SERIAL_0
*/
extern XSPI_HandleTypeDef       hxspi2;

/*
  @brief import of the HAL handles for MEMORY_PSRAM_0
*/
extern XSPI_HandleTypeDef       hxspi1;

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup EXTMEM_CONF_Exported_constants EXTMEM_CONF exported constante
  * @{
  */
enum {
  EXTMEMORY_1  = 0, /*!< ID 0 of extmem_list_config */
  EXTMEMORY_2  = 1, /*!< ID 1 of extmem_list_config */
};
/**
  * @}
  */

#define EXTMEM_LRUN_DESTINATION_INTERNAL
#define EXTMEM_LRUN_DESTINATION_ADDRESS  0x34000000


#define EXTMEM_LRUN_SOURCE EXTMEMORY_1
#define EXTMEM_LRUN_SOURCE_ADDRESS 0x00100000
#define EXTMEM_LRUN_SOURCE_SIZE 0x00010000

#define EXTMEM_LRUN_TZ_ENABLE_NS
#define EXTMEM_LRUN_DESTINATION_ADDRESS_NS 0x34100000
#define EXTMEM_LRUN_SOURCE_ADDRESS_NS 0x180000

#define EXTMEM_HEADER_OFFSET 0x400

/* Exported configuration --------------------------------------------------------*/
/** @defgroup EXTMEM_CONF_Exported_configuration EXTMEM_CONF exported configuration definition
  * @{
  */
extern EXTMEM_DefinitionTypeDef extmem_list_config[1];
#if defined(EXTMEM_C)
EXTMEM_DefinitionTypeDef extmem_list_config[1] =
{
  /* MEMORY_SERIAL_0 */
  {
    .MemType = EXTMEM_NOR_SFDP,
    .Handle = (void*)&hxspi2,
    .ConfigType = EXTMEM_LINK_CONFIG_8LINES,
    .NorSfdpObject =
    {
      {0}
    }
  },
//////////  /* MEMORY_PSRAM_0 */
//////////  {
//////////    .MemType = EXTMEM_PSRAM,
//////////    .Handle = (void*)&hxspi1,
//////////    .ConfigType = EXTMEM_LINK_CONFIG_16LINES,
//////////    .PsramObject =
//////////    {
//////////      .psram_public = {
//////////        .MemorySize = HAL_XSPI_SIZE_256MB,  /* memory size is 256Mbit */
//////////        .FreqMax = 200000000u, /* 200Mhz */
//////////        .NumberOfConfig = 1,
//////////        /* Config */
//////////        {
//////////          {.WriteMask = 0x40, .WriteValue = 0x40, .REGAddress = 8}
//////////        },
//////////        
//////////        /* Memory command configuration */
//////////        .ReadREG           = 0x40u,
//////////        .WriteREG          = 0xC0u,
//////////        .ReadREGSize       = 2u,
//////////        .REG_DummyCycle    = 4u,
//////////        
//////////        .Write_command     = 0xA0u,
//////////        .Write_DummyCycle  = 4u,
//////////        .Read_command      = 0x20u,
//////////        .Read_DummyCycle   = 4u,
//////////      }
//////////    }
//////////  }
};
#endif /* EXTMEM_C */
/**
  * @}
  */

/* Exported trace --------------------------------------------------------*/
/** @defgroup EXTMEM_CONF_Exported_debug EXTMEM_CONF exported debug definition
  * @{
  */


/*
 * @brief debug level of the different layers
 */
#define EXTMEM_DEBUG_LEVEL                   0

#define EXTMEM_DRIVER_NOR_SFDP_DEBUG_LEVEL   0
#define EXTMEM_DRIVER_PSRAM_DEBUG_LEVEL      0

#define EXTMEM_SAL_XSPI_DEBUG_LEVEL          0
/**
  * @}
  */

/**
  * @}
  */


#ifdef __cplusplus
}
#endif

#endif /* EXTMEM_CONF_H_ */
