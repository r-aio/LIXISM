from z3 import *

def verify_no_flapping():
    # 1. Inicjalizacja Solvera
    solver = Solver()

    # 2. Definicja zmiennych symbolicznych (Fizyka układu)
    P_t1 = Int('Pressure_Time1') # Ciśnienie w chwili T1 (krok w górę)
    P_t2 = Int('Pressure_Time2') # Ciśnienie w chwili T2 (krok w dół)
    
    # 3. Definicja progów przejść z Histerezą dla matrycy L0-ISM
    # Zamiast jednego progu (np. 3000), definiujemy dwa różne:
    THRESHOLD_5_TO_6 = 3050  # Ciśnienie rośnie - wchodzimy w +6
    THRESHOLD_6_TO_5 = 2950  # Ciśnienie spada - wracamy do +5
    
    # Parametr fizyczny: maksymalny szum/wibracja instalacji (np. od falownika pompy)
    # Zakładamy, że fizycznie ciśnienie nie skacze samo z siebie o więcej niż 60 mbar bez powodu.
    MAX_PHYSICAL_NOISE = 60 

    # 4. Definicja warunków przejścia (Reguły Matrycy)
    # Przejście 5 -> 6 następuje tylko gdy ciśnienie przekroczy górny próg
    transition_up = P_t1 >= THRESHOLD_5_TO_6
    
    # Przejście 6 -> 5 następuje tylko gdy ciśnienie spadnie poniżej dolnego progu
    transition_down = P_t2 <= THRESHOLD_6_TO_5

    # 5. Definicja "Flappingu" (Błędu, którego szukamy)
    # Flapping to sytuacja, w której zmiana ciśnienia (P_t1 - P_t2) jest mniejsza lub 
    # równa fizycznemu szumowi instalacji, a MIMO TO wywołuje przeskok stanów 5 -> 6 -> 5.
    
    # Z3 absolute value workaround (Z3 nie ma wbudowanego abs() dla Int)
    delta_P = If(P_t1 > P_t2, P_t1 - P_t2, P_t2 - P_t1)
    flapping_condition = delta_P <= MAX_PHYSICAL_NOISE

    # 6. Wstrzyknięcie założeń do Solvera (Szukamy błędu!)
    solver.add(transition_up)
    solver.add(transition_down)
    solver.add(flapping_condition)

    # 7. Weryfikacja
    print("Rozpoczynam Formalny Audyt Z3 dla przejść +5 <-> +6...")
    result = solver.check()

    if result == sat:
        print("❌ Z3 znalazł BŁĄD (Flapping jest możliwy)!")
        print("Model (kontrprzykład fizyczny):")
        m = solver.model()
        print(f"Ciśnienie T1 (5->6): {m[P_t1]} mbar")
        print(f"Ciśnienie T2 (6->5): {m[P_t2]} mbar")
    elif result == unsat:
        print("✅ UNSAT! Z3 udowodnił matematycznie: Flapping jest NIEMOŻLIWY.")
        print("Rozstęp histerezy (100 mbar) jest większy niż szum (60 mbar).")
    else:
        print("Solver nie był w stanie rozstrzygnąć problemu.")

if __name__ == "__main__":
    verify_no_flapping()
