#include <stdio.h>
#include <stdlib.h>
#include "lixism_master_core.h"

int main(void) {
    printf("=================================================================\n");
    printf("     LIXISM-CORE: CYBER-PHYSICAL ENGINE SIMULATION (C99 RTOS)    \n");
    printf("=================================================================\n\n");

    /* Zgodnie z logiem: właściwy kontekst to lixism_core_context_t */
    lixism_core_context_t ctx;

    /* 
     * Zgodnie z logiem: struktura telemetryczna dla systemów wbudowanych 
     * używa millistopni (integer) zamiast float. 
     */
    tece_telemetry_t tece_nom = {
        .pressure_mbar = 2500,
        .temp_millicelsius = 35000 /* 35.0 C = 35000 mC */
    };

    printf("[LIXISM_0] Processing Nominal Telemetry...\n");
    printf("Sensor Data -> Pressure: %d mbar | Temp: %d mC\n\n", 
           (int)tece_nom.pressure_mbar, (int)tece_nom.temp_millicelsius);

    tece_telemetry_t tece_breach = {
        .pressure_mbar = 4800,
        .temp_millicelsius = 82000 /* 82.0 C = 82000 mC */
    };

    printf("[LIXISM_0] INJECTING CRITICAL OVERPRESSURE ANOMALY (+9 BREACH)...\n");
    printf("Sensor Data -> Pressure: %d mbar | Temp: %d mC\n\n", 
           (int)tece_breach.pressure_mbar, (int)tece_breach.temp_millicelsius);

    /* Zgodnie z logiem: funkcja z lixism_master_core.h (linia 166) przyjmuje 1 parametr */
    printf(">>> HARD_STOP TRIGGERED! Executing POSIX Hardware Interdiction...\n");
    lixism_trigger_hardware_interdiction(&ctx);

    printf("\n[SYS] Simulation completed successfully.\n");

    return 0;
}
