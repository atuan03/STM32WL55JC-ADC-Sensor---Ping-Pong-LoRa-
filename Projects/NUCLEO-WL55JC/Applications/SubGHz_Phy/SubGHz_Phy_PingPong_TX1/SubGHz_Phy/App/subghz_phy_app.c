/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    subghz_phy_app.c
  * @author  MCD Application Team
  * @brief   Application of the SubGHz_Phy Middleware
  ******************************************************************************
  * @attention
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms found in the LICENSE file.
  * If no LICENSE file, it is provided AS-IS.
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "platform.h"
#include "sys_app.h"
#include "subghz_phy_app.h"
#include "radio.h"
#include "main.h" // Thêm để sử dụng SystemClock_Config()

/* USER CODE BEGIN Includes */
#include "stm32_timer.h"
#include "stm32_seq.h"
#include "utilities_def.h"
#include "app_version.h"
#include "subghz_phy_version.h"
#include "adc.h"
#include <stdio.h>
/* USER CODE END Includes */

/* External variables --------------------------------------------------------*/
/* USER CODE BEGIN EV */
uint8_t BufferTx[100];
extern ADC_HandleTypeDef hadc;
/* USER CODE END EV */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef enum {
    RX,
    RX_TIMEOUT,
    RX_ERROR,
    TX,
    TX_TIMEOUT,
} States_t;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
// Cấu hình
#define BUFFER_SIZE          64
//#define PAYLOAD_LEN          2

// Timeout
#define RX_TIMEOUT_VALUE     3000
#define TX_TIMEOUT_VALUE     3000

// Payload nội dung
#define PING                 "PING"
#define PONG                 "PONG"
#define TUAN                 "TUAN"

// Payload tối đa
#define MAX_APP_BUFFER_SIZE  50
#if (PAYLOAD_LEN > MAX_APP_BUFFER_SIZE)
//#error PAYLOAD_LEN must be less or equal than MAX_APP_BUFFER_SIZE
#endif

// Các tham số khác
#define RX_TIME_MARGIN       2000
#define FSK_AFC_BANDWIDTH    83333
#define LED_PERIOD_MS        2000
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
static RadioEvents_t RadioEvents;

/* USER CODE BEGIN PV */
static uint8_t pvd_triggered = 0; // Để kiểm tra PVD có kích hoạt không
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
static void OnTxDone(void);
static void OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t LoraSnr_FskCfo);
static void OnTxTimeout(void);
static void OnRxTimeout(void);
static void OnRxError(void);

/* USER CODE BEGIN PFP */
static void PingPong_Process(void);
static void MX_PVD_Init(void);
static void ReInit_Peripherals(void);
/* USER CODE END PFP */

/* Exported functions --------------------------------------------------------*/
void SubghzApp_Init(void)
{
    /* USER CODE BEGIN SubghzApp_Init_1 */
    /* USER CODE END SubghzApp_Init_1 */

    /* Khởi tạo Radio */
    RadioEvents.TxDone    = OnTxDone;
    RadioEvents.RxDone    = OnRxDone;
    RadioEvents.TxTimeout = OnTxTimeout;
    RadioEvents.RxTimeout = OnRxTimeout;
    RadioEvents.RxError   = OnRxError;
    Radio.Init(&RadioEvents);

    /* Cấu hình tần số */
    Radio.SetChannel(RF_FREQUENCY);

    /* Cấu hình giao thức */
#if ((USE_MODEM_LORA == 1) && (USE_MODEM_FSK == 0))
    APP_LOG(TS_OFF, VLEVEL_M, "---------------\n\r");
    APP_LOG(TS_OFF, VLEVEL_M, "LORA_MODULATION\n\r");
    APP_LOG(TS_OFF, VLEVEL_M, "LORA_BW=%d kHz\n\r", (1 << LORA_BANDWIDTH) * 125);
    APP_LOG(TS_OFF, VLEVEL_M, "LORA_SF=%d\n\r", LORA_SPREADING_FACTOR);

    Radio.SetTxConfig(MODEM_LORA, TX_OUTPUT_POWER, 0, LORA_BANDWIDTH,
                      LORA_SPREADING_FACTOR, LORA_CODINGRATE,
                      LORA_PREAMBLE_LENGTH, LORA_FIX_LENGTH_PAYLOAD_ON,
                      true, 0, 0, LORA_IQ_INVERSION_ON, TX_TIMEOUT_VALUE);
    Radio.SetMaxPayloadLength(MODEM_LORA, MAX_APP_BUFFER_SIZE);

#elif ((USE_MODEM_LORA == 0) && (USE_MODEM_FSK == 1))
    APP_LOG(TS_OFF, VLEVEL_M, "---------------\n\r");
    APP_LOG(TS_OFF, VLEVEL_M, "FSK_MODULATION\n\r");
    APP_LOG(TS_OFF, VLEVEL_M, "FSK_BW=%d Hz\n\r", FSK_BANDWIDTH);
    APP_LOG(TS_OFF, VLEVEL_M, "FSK_DR=%d bits/s\n\r", FSK_DATARATE);

    Radio.SetTxConfig(MODEM_FSK, TX_OUTPUT_POWER, FSK_FDEV, 0,
                      FSK_DATARATE, 0,
                      FSK_PREAMBLE_LENGTH, FSK_FIX_LENGTH_PAYLOAD_ON,
                      true, 0, 0, 0, TX_TIMEOUT_VALUE);
    Radio.SetMaxPayloadLength(MODEM_FSK, MAX_APP_BUFFER_SIZE);

#else
#error "Please define a modulation in subghz_phy_app.h"
#endif

    /* Khởi tạo ADC */
    hadc.Instance = ADC;
    hadc.Init.Resolution = ADC_RESOLUTION_12B;
    if (HAL_ADC_Init(&hadc) != HAL_OK) {
        Error_Handler();
    }

    /* Khởi tạo PVD */
    MX_PVD_Init();

    /* Làm sạch buffer truyền */
    memset(BufferTx, 0x0, MAX_APP_BUFFER_SIZE);

    /* Đăng ký và khởi chạy tiến trình PingPong */
    UTIL_SEQ_RegTask((1 << CFG_SEQ_Task_SubGHz_Phy_App_Process), UTIL_SEQ_RFU, PingPong_Process);
    UTIL_SEQ_SetTask((1 << CFG_SEQ_Task_SubGHz_Phy_App_Process), CFG_SEQ_Prio_0);
}

/* Private functions ---------------------------------------------------------*/
static void OnTxDone(void)
{
    APP_LOG(TS_ON, VLEVEL_L, "OnTxDone\n\r");

    HAL_ADC_DeInit(&hadc);
    Radio.Sleep();
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_All);

    HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
    SystemClock_Config();
    ReInit_Peripherals();
}

static void OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t LoraSnr_FskCfo)
{
    /* Không xử lý thêm */
}

static void OnTxTimeout(void)
{
    APP_LOG(TS_ON, VLEVEL_L, "OnTxTimeout\n\r");

    HAL_ADC_DeInit(&hadc);
    Radio.Sleep();
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_All);

    HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
    SystemClock_Config();
    ReInit_Peripherals();
}

static void OnRxTimeout(void)
{
    /* Không xử lý thêm */
}

static void OnRxError(void)
{
    /* Không xử lý thêm */
}

static void PingPong_Process(void)
{
    HAL_ADC_Start(&hadc);
    HAL_ADC_PollForConversion(&hadc, 1000);
    uint16_t adcValue = HAL_ADC_GetValue(&hadc);
    HAL_ADC_Stop(&hadc);

    BufferTx[0] = (adcValue >> 8) & 0xFF;
    BufferTx[1] = adcValue & 0xFF;

    Radio.Send(BufferTx, PAYLOAD_LEN);
}

static void MX_PVD_Init(void)
{
    PWR_PVDTypeDef sConfigPVD = {0};
    sConfigPVD.PVDLevel = PWR_PVDLEVEL_5; // Cài mức ~2.8V
    sConfigPVD.Mode = PWR_PVD_MODE_IT_RISING;
    HAL_PWR_ConfigPVD(&sConfigPVD);
    HAL_PWR_EnablePVD();

    HAL_NVIC_SetPriority(PVD_PVM_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(PVD_PVM_IRQn);
}

void PVD_IRQHandler(void)
{
    HAL_PWR_PVD_PVM_IRQHandler();
    pvd_triggered = 1;
    APP_LOG(TS_ON, VLEVEL_L, "PVD Triggered: Voltage > 2.8V\n\r");

    UTIL_SEQ_SetTask((1 << CFG_SEQ_Task_SubGHz_Phy_App_Process), CFG_SEQ_Prio_0);
}

static void ReInit_Peripherals(void)
{
    /* Re-init ADC */
    hadc.Instance = ADC;
    hadc.Init.Resolution = ADC_RESOLUTION_12B;
    if (HAL_ADC_Init(&hadc) != HAL_OK) {
        Error_Handler();
    }

    /* Re-init Radio */
    Radio.Init(&RadioEvents);
    Radio.SetChannel(RF_FREQUENCY);

#if ((USE_MODEM_LORA == 1) && (USE_MODEM_FSK == 0))
    Radio.SetTxConfig(MODEM_LORA, TX_OUTPUT_POWER, 0, LORA_BANDWIDTH,
                      LORA_SPREADING_FACTOR, LORA_CODINGRATE,
                      LORA_PREAMBLE_LENGTH, LORA_FIX_LENGTH_PAYLOAD_ON,
                      true, 0, 0, LORA_IQ_INVERSION_ON, TX_TIMEOUT_VALUE);
    Radio.SetMaxPayloadLength(MODEM_LORA, MAX_APP_BUFFER_SIZE);
#elif ((USE_MODEM_LORA == 0) && (USE_MODEM_FSK == 1))
    Radio.SetTxConfig(MODEM_FSK, TX_OUTPUT_POWER, FSK_FDEV, 0,
                      FSK_DATARATE, 0,
                      FSK_PREAMBLE_LENGTH, FSK_FIX_LENGTH_PAYLOAD_ON,
                      true, 0, 0, 0, TX_TIMEOUT_VALUE);
    Radio.SetMaxPayloadLength(MODEM_FSK, MAX_APP_BUFFER_SIZE);
#endif
}
