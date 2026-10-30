#include <stdio.h>
#include <stdlib.h>
#include "lixism_master_core.h"

int main(void) {
    printf("=================================================================\n");
    printf("     LIXISM-CORE: CYBER-PHYSICAL ENGINE SIMULATION (C99 RTOS)    \n");
    printf("=================================================================\n\n");

    lixism_state_t lixism;
    lixism_init(&lixism);

    raio_governor_t raio;
    raio_init(&raio);

    tece_telemetry_t tece_nom = {
        .pressure_mbar = 2500.0f,
        .temp_celsius = 35.0f,
        .flow_lpm = 120.0f,
        .delta_pressure_mbar = 0.5f,
        .timestamp_ms = 1000001
    };

    printf("[LIXISM_0] Processing Nominal Telemetry...\n");
    lixism_op_code_t op1 = lixism_process_tece(&lixism, &tece_nom);
    printf("Result Action: %s (State P: %d, Delta: %d, Temp: %d)\n\n",
           lixism_op_to_str(op1), lixism.vector.s_P, lixism.vector.delta_s_P, lixism.vector.s_T);

    tece_telemetry_t tece_breach = {
        .pressure_mbar = 4800.0f,
        .temp_celsius = 82.0f,
        .flow_lpm = 210.0f,
        .delta_pressure_mbar = 95.0f,
        .timestamp_ms = 1000050
    };

    printf("[LIXISM_0] INJECTING CRITICAL OVERPRESSURE ANOMALY (+9 BREACH)...\n");
    lixism_op_code_t op2 = lixism_process_tece(&lixism, &tece_breach);

    if (op2 == LIXISM_OP_STOP) {
        printf(">>> HARD_STOP TRIGGERED! Executing POSIX Hardware Interdiction...\n");
        lixism_trigger_hardware_interdiction(&lixism, LIXISM_LAYER_0, "TE-CE mCDU Overpressure Hydro-Hammer Breach");
    }

    return 0;
}
