/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    adc.c
  * @brief   This file provides code for the configuration
  *          of the ADC instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "adc.h"

/* USER CODE BEGIN 0 */
#include "sys_app.h"  // Bổ sung vào đầu file adc.c

/* USER CODE END 0 */

ADC_HandleTypeDef hadc;

/* ADC init function */
void MX_ADC_Init(void)
{

  /* USER CODE BEGIN ADC_Init 0 */

  /* USER CODE END ADC_Init 0 */

  /* USER CODE BEGIN ADC_Init 1 */

  /* USER CODE END ADC_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc.Instance = ADC;
  hadc.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
  hadc.Init.Resolution = ADC_RESOLUTION_12B;
  hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc.Init.LowPowerAutoWait = DISABLE;
  hadc.Init.LowPowerAutoPowerOff = DISABLE;
  hadc.Init.ContinuousConvMode = ENABLE;
  hadc.Init.NbrOfConversion = 1;
  hadc.Init.DiscontinuousConvMode = DISABLE;
  hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc.Init.DMAContinuousRequests = DISABLE;
  hadc.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc.Init.SamplingTimeCommon1 = ADC_SAMPLETIME_19CYCLES_5;
  hadc.Init.SamplingTimeCommon2 = ADC_SAMPLETIME_19CYCLES_5;
  hadc.Init.OversamplingMode = DISABLE;
  hadc.Init.TriggerFrequencyMode = ADC_TRIGGER_FREQ_HIGH;
  if (HAL_ADC_Init(&hadc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC_Init 2 */
  /* Cấu hình kênh ADC */
  ADC_ChannelConfTypeDef sConfig = {0};
  sConfig.Channel = ADC_CHANNEL_1;  // Chọn kênh ADC 1 (PB14)
  sConfig.Rank = ADC_REGULAR_RANK_1;  // Thiết lập thứ tự chuyển đổi
  sConfig.SamplingTime = ADC_SAMPLINGTIME_COMMON_1;  // Chọn thời gian lấy mẫu

  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();  // Báo lỗi nếu cấu hình thất bại
  }

  /* USER CODE END ADC_Init 2 */

}

void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(adcHandle->Instance==ADC)
  {
  /* USER CODE BEGIN ADC_MspInit 0 */

  /* USER CODE END ADC_MspInit 0 */
    /* ADC clock enable */
    __HAL_RCC_ADC_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**ADC GPIO Configuration
    PB14     ------> ADC_IN1
    */
    GPIO_InitStruct.Pin = GPIO_PIN_14;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* ADC interrupt Init */
    HAL_NVIC_SetPriority(ADC_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(ADC_IRQn);
  /* USER CODE BEGIN ADC_MspInit 1 */

  /* USER CODE END ADC_MspInit 1 */
  }
}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* adcHandle)
{

  if(adcHandle->Instance==ADC)
  {
  /* USER CODE BEGIN ADC_MspDeInit 0 */

  /* USER CODE END ADC_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_ADC_CLK_DISABLE();

    /**ADC GPIO Configuration
    PB14     ------> ADC_IN1
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_14);

    /* ADC interrupt Deinit */
    HAL_NVIC_DisableIRQ(ADC_IRQn);
  /* USER CODE BEGIN ADC_MspDeInit 1 */

  /* USER CODE END ADC_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
uint16_t Read_ADC_Raw(ADC_HandleTypeDef *hadc)
{
    uint16_t adcValue = 0;

    // Bắt đầu chuyển đổi ADC
    HAL_ADC_Start(hadc);

    // Đợi chuyển đổi hoàn thành
    HAL_ADC_PollForConversion(hadc, 50);
    adcValue = HAL_ADC_GetValue(hadc);

    // Tắt ADC sau khi đọc
//    HAL_ADC_Stop(hadc);
//    __HAL_RCC_ADC_CLK_DISABLE();  // Ngắt clock của ADC để tiết kiệm năng lượng

    return adcValue;
}
void Enter_LowPowerMode(void)
{
    HAL_SuspendTick();  // Tạm ngừng SysTick nếu không cần thiết
    HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
    HAL_ResumeTick();  // Kích hoạt lại SysTick khi thức dậy
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    uint16_t adcValue = HAL_ADC_GetValue(hadc);
    APP_LOG(TS_OFF, VLEVEL_M, "ADC IRQ Value: %d\n\r", adcValue);
}

/* USER CODE END 1 */
