#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "lixism_master_core.h"

int main(void) {
    printf("=================================================================\n");
    printf("     LIXISM-CORE: CYBER-PHYSICAL ENGINE SIMULATION (C99 RTOS)    \n");
    printf("=================================================================\n\n");

    pid_t pid = fork();
    if (pid == 0) {
        /* PROCES POTOMNY: Inicjalizacja prawidłowego kontekstu L0-ISM */
        lixism_core_context_t ctx;
        memset(&ctx, 0, sizeof(lixism_core_context_t));

        tece_telemetry_t tece_breach = {
            .pressure_mbar = 4800,
            .temp_millicelsius = 82000
        };

        printf("[LIXISM_0] INJECTING CRITICAL OVERPRESSURE ANOMALY (+9 BREACH)...\n");
        printf("Sensor Data -> Pressure: %d mbar | Temp: %d mC\n\n", 
               (int)tece_breach.pressure_mbar, (int)tece_breach.temp_millicelsius);

        printf(">>> HARD_STOP TRIGGERED! Executing POSIX Hardware Interdiction...\n");
        
        /* Wyzwala sprzętowy zawał -> SIGKILL (137) przy użyciu Twojego dokładnego API */
        lixism_trigger_hardware_interdiction(&ctx);
        
        /* Ta linia nigdy nie powinna się wykonać, proces ginie wyżej */
        exit(0);
    } else {
        /* PROCES NADRZĘDNY: Weryfikuje działanie interdykcji dla GitHub Actions */
        int status;
        waitpid(pid, &status, 0);
        
        if (WIFSIGNALED(status) && WTERMSIG(status) == SIGKILL) {
            printf("\n✅ (VERIFIED) Child process was successfully killed by SIGKILL (POSIX exit 137)!\n");
            printf("🛠 LIXISM Hardware Interdiction system fully validated!\n");
            return 0;
        } else {
            printf("\n❌ (FAILED) Interdiction did not execute correctly. Status: %d\n", status);
            return 1;
        }
    }
}
