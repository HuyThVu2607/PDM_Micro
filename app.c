/***************************************************************************//**
 * @file
 * @brief Top level application functions
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/
#include "sl_mic.h"
#include "SEGGER_RTT.h"

//If need config speed clock PDM please open file mox_v1.slcp --> Search key "micro"->Platform -> Board Driver -> PDM Microphone select config

#define MIC_SAMPLE_RATE            8000
#define MIC_SAMPLE_BUFFER_SIZE     2000
#define MIC_N_CHANNELS             1

float alpha    = 0.1;
float alpha_hp = 0.1;

static int16_t buffer[MIC_SAMPLE_BUFFER_SIZE * MIC_N_CHANNELS];

void low_pass_filter(int16_t *input, int16_t *output, uint32_t num_samples) {
    static int16_t prev_output = 0;
    for (uint32_t i = 0; i < num_samples; i++) {
        output[i] = (int16_t)(alpha * input[i] + (1 - alpha) * prev_output);
        prev_output = output[i];
    }
}

void high_pass_filter(int16_t *input, int16_t *output, uint32_t num_samples) {
    static int16_t prev_input = 0;
    static int16_t prev_output = 0;
    for (uint32_t i = 0; i < num_samples; i++) {
        output[i] = (int16_t)(alpha_hp * (prev_output + input[i] - prev_input));
        prev_input = input[i];
        prev_output = output[i];
    }
}

void band_pass_filter(int16_t *input, int16_t *output, uint32_t num_samples) {
    int16_t low_pass_output[MIC_SAMPLE_BUFFER_SIZE];
    int16_t high_pass_output[MIC_SAMPLE_BUFFER_SIZE];

    low_pass_filter(input, low_pass_output, num_samples);

    high_pass_filter(input, high_pass_output, num_samples);

    for (uint32_t i = 0; i < num_samples; i++) {
        output[i] = (low_pass_output[i] + high_pass_output[i]) / 2;
    }
}

/***************************************************************************//**
 * Initialize application.
 ******************************************************************************/
void app_init(void)
{
  sl_mic_init(MIC_SAMPLE_RATE, MIC_N_CHANNELS);
}

/***************************************************************************//**
 * App ticking function.
 ******************************************************************************/
void app_process_action(void)
{
  //Get data microphone via PDM
  sl_mic_get_n_samples(buffer, MIC_SAMPLE_BUFFER_SIZE);

  while (!sl_mic_sample_buffer_ready()) {
    // Wait until sample buffer ready
  }

  low_pass_filter(buffer, buffer, MIC_SAMPLE_BUFFER_SIZE);

  high_pass_filter(buffer, buffer, MIC_SAMPLE_BUFFER_SIZE);

  band_pass_filter(buffer, buffer, MIC_SAMPLE_BUFFER_SIZE);

  //Data was save in "buffer" after filter

  //Transmit data for debug via RTT
//  for (int i = 0; i < MIC_SAMPLE_BUFFER_SIZE; i++) {
//    SEGGER_RTT_printf(0, "%d ", buffer[i]);
//  }

}
