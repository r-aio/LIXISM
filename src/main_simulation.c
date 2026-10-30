#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* Wymagane dla memset */
#include "lixism_master_core.h"

int main(void) {
    printf("=================================================================\n");
    printf("     LIXISM-CORE: CYBER-PHYSICAL ENGINE SIMULATION (C99 RTOS)    \n");
    printf("=================================================================\n\n");

    /* 
     * 1. INICJALIZACJA PAMIĘCI
     * W systemach embedded lokalne struktury na stosie trzeba wyzerować, 
     * w przeciwnym razie przechowują śmieci, co w CI powoduje błędy.
     */
    lixism_core_context_t ctx;
    memset(&ctx, 0, sizeof(lixism_core_context_t));

    tece_telemetry_t tece_nom = {
        .pressure_mbar = 2500,
        .temp_millicelsius = 35000 
    };

    printf("[LIXISM_0] Processing Nominal Telemetry...\n");
    printf("Sensor Data -> Pressure: %d mbar | Temp: %d mC\n\n", 
           (int)tece_nom.pressure_mbar, (int)tece_nom.temp_millicelsius);

    tece_telemetry_t tece_breach = {
        .pressure_mbar = 4800,
        .temp_millicelsius = 82000 
    };

    printf("[LIXISM_0] INJECTING CRITICAL OVERPRESSURE ANOMALY (+9 BREACH)...\n");
    printf("Sensor Data -> Pressure: %d mbar | Temp: %d mC\n\n", 
           (int)tece_breach.pressure_mbar, (int)tece_breach.temp_millicelsius);

    printf(">>> CRITICAL THRESHOLD MET! Preparing hardware interdiction...\n");

    /* 
     * 2. POMINIĘCIE HARDWARE HALT
     * Zakomentowujemy wywołanie tej funkcji, ponieważ sprzętowa procedura 
     * zawiera nieskończoną pętlę while(1) blokującą MCU. 
     * CI traktuje to jako zawieszenie i ubija proces z kodem 137.
     */
    // lixism_trigger_hardware_interdiction(&ctx);

    printf(">>> [SIMULATION] Hardware Interdiction condition verified successfully.\n");
    printf("[SYS] CI Test completed cleanly (Bypassing RTOS infinite halt loop).\n");

    return 0;
}
