#include "stm32f4xx.h"
#include "stm32f4xx_dac.h"
#include "stm32f4xx_ADC.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include <math.h>
#include <stdint.h>

/* ================= Constantes ================= */
#define PI2       6.283185307f
#define VREF      3.3f
#define DAC_MAX   4095.0f
#define FS        20000.0f        // SysTick = 20 kHz
#define NPOINTS   256
/* ================= Variables globales ================= */
uint16_t sin_table[NPOINTS];

volatile uint16_t dac_val;
volatile uint16_t adc_val;

volatile uint16_t index_sin = 0;
volatile uint32_t freq_cnt = 0;
volatile uint32_t diviseur_freq = 1;

/* RMS */
volatile float s = 0.0f;          // somme des carrés
volatile uint16_t rms_cnt = 0;
volatile float tension_eff = 0.0f;

/* Debug Logic Analyzer */
volatile float dbg_sin_norm;

/* ================= Prototypes ================= */
void config(void);
void dac_init(void);
void adc_init(void);
uint16_t readADC1(uint8_t channel);
void init_sin_table(void);

/* ================= Table sinus ================= */
void init_sin_table(void)
{
    for (int i = 0; i < NPOINTS; i++)
    {
        sin_table[i] = (uint16_t)(
            (sinf(PI2 * i / NPOINTS) + 1.0f) * (DAC_MAX / 2.0f)
        );
    }
}

/* ================= MAIN ================= */
int main(void)
{
    config();
    dac_init();
    adc_init();
    init_sin_table();

    SysTick_Config(SystemCoreClock / FS);

    while (1)
    {
        // Tout est géré dans SysTick_Handler
    }
}

/* ================= SysTick ================= */
void SysTick_Handler(void)
{
    uint16_t pot_amp, pot_freq;
    float amplitude, freq;

    /* ===== Lecture potentiomètres ===== */
    pot_amp  = readADC1(11);   // PC1 ? amplitude
    pot_freq = readADC1(12);   // PC2 ? fréquence

    amplitude = (float)pot_amp / 4095.0f;        // 0 ? 1
    freq = 1.0f + ((float)pot_freq / 4095.0f) * 99.0f; // 1 ? 100 Hz

    diviseur_freq = (uint32_t)(FS / (freq * NPOINTS));
    if (diviseur_freq < 1) diviseur_freq = 1;

    /* ===== Génération sinus ===== */
    freq_cnt++;
    if (freq_cnt >= diviseur_freq)
    {
        freq_cnt = 0;

        // Sinus normalisé [-1 ; +1]
        float sin_norm =
            ((float)sin_table[index_sin] / (DAC_MAX / 2.0f)) - 1.0f;

        dbg_sin_norm = sin_norm;   // pour Logic Analyzer

        // Application amplitude + offset DAC
        float dac_float =
            (DAC_MAX / 2.0f) + (DAC_MAX / 2.0f) * amplitude * sin_norm;

        if (dac_float < 0.0f) dac_float = 0.0f;
        if (dac_float > DAC_MAX) dac_float = DAC_MAX;

        dac_val = (uint16_t)dac_float;
        DAC_SetChannel1Data(DAC_Align_12b_R, dac_val);

        index_sin++;
        if (index_sin >= NPOINTS) index_sin = 0;
    }

    /* ===== Calcul RMS (méthode somme des carrés) ===== */

    adc_val = readADC1(4);   // PA4 ? retour DAC

    // ADC ? tension
    float v_adc = ((float)adc_val * VREF) / 4095.0f;

    // Suppression offset 1.65 V
    float v_ac = v_adc - (VREF / 2.0f);

    // Somme des carrés
    s += v_ac * v_ac;
    rms_cnt++;

    if (rms_cnt >= NPOINTS)
    {
        tension_eff = sqrtf(s / rms_cnt);
        s = 0.0f;
        rms_cnt = 0;
    }
}
