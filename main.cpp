#include "pollard_strassen.h"
#include "probedivision.h"
#include "testzahlen.h"
#include <chrono>
#include <gmpxx.h>
#include <iostream>
#include <list>

int main() {
  for (int i = 1; i <= 10; i++) {
    mpz_class N = TestzahlB(i);
    mpz_class B("9311");

    // Zeitmessung starten---------
    std::chrono::time_point<std::chrono::high_resolution_clock> start =
        std::chrono::high_resolution_clock::now();

    std::vector<mpz_class> factors = primeFactorisation(N, B);

    // Zeitmessung stoppen----------
    std::chrono::time_point<std::chrono::high_resolution_clock> end =
        std::chrono::high_resolution_clock::now();

    // Vergangene Zeitspanne bestimmen und ausgeben
    std::chrono::duration<double, std::milli> float_pollard_ms = end - start;
    std::cout << "\nPollard Strassen Verfahren...\n";
    std::cout << "Berechnung in " << float_pollard_ms.count()
              << " Millisekunden abgeschlossen" << std::endl;

    std::cout << "Ermittelte Zerlegung von " << N << ":\n";

    for (auto &i : factors) {
      std::cout << i << " ";
    }

    std::cout << "\n";

    // Schranke: Probedivision bis 10^8
    // Kann erhöht werden, die Laufzeit wird aber schnell zu groß

    // Zeitmessung starten---------
    start = std::chrono::high_resolution_clock::now();

    // Probedivision durchführen
    std::list<Factor> factors2 = trial_division_bounded(N, B);

    // Zeitmessung stoppen----------
    end = std::chrono::high_resolution_clock::now();
    // Vergangene Zeitspanne bestimmen und ausgeben
    std::chrono::duration<double, std::milli> float_probedivision_ms =
        end - start;
    std::cout << "\nProbedivision...\n";
    std::cout << "Berechnung in " << float_probedivision_ms.count()
              << " Millisekunden abgeschlossen" << std::endl;

    std::cout << "Ermittelte Zerlegung von " << N << ":\n";

    std::list<Factor>::iterator it;
    for (it = factors2.begin(); it != factors2.end(); it++)
      it->printpp();
    std::cout << "\n";
  }

  return 0;
}
