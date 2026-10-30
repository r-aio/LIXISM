#ifndef TACE_ALG_H
#define TACE_ALG_H

#include "lixism_master_core.h"

/*
 * ==============================================================================
 * TACE-Alg (Thermo-Algorithmic Control & Execution Algorithm)
 * Direct piezo-kinematic feedback mapping for L0-ISM.
 * ==============================================================================
 */

/* Prog wyzwolenia sprzetowego (np. 3300 mV dla logiki 3.3V CMOS) */
#define TACE_PIEZO_TRIGGER_MV 3300 

/* Struktura mapujaca fizyke plynow na stany napieciowe (Zero-Heap) */
typedef struct {
    int delta_p_mbar; /* Skok cisnienia (hydro-hammer / mikrokawitacja) */
    int v_piezo_mv;   /* Napiecie wygenerowane przez krysztal w mV */
} tace_alg_sensor_t;

/* 
 * O(1) Hardware Gate
 * Wyzwala operator RESO (HARD_STOP) natychmiast po przekroczeniu progu napiecia,
 * omijajac petle decyzyjne i abstrakcje programowe.
 */
static inline void tace_alg_execute_reso(lixism_core_context_t* ctx, tace_alg_sensor_t* sensor) {
    if (sensor->v_piezo_mv >= TACE_PIEZO_TRIGGER_MV) {
        lixism_trigger_hardware_interdiction(ctx);
    }
}

#endif /* TACE_ALG_H */
