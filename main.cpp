#include "pollard_strassen.h"
#include "probedivision.h"
#include "testzahlen.h"
#include <chrono>
#include <gmpxx.h>
#include <iostream>
#include <list>

int main() {
  int choice;
  std::string str;
  mpz_class N("0");
  mpz_class B("100000");

  do {
    std::cout << "Welche Zahl soll faktorisiert werden?\n";
    std::cout << "-------------------------------------\n";
    std::cout << "1. Manuelle Eingabe\n";
    std::cout << "2. Fermat-Zahl (0<=k<=30)\n";
    std::cout << "3. Cunningham-Zahl (0<k<10000)\n";
    std::cout << "4. Testzahl (1<=k<=10)\n";
    std::cout << "5. RSA-Zahl (k ∈ "
                 "{9,10,13,15,18,20,25,30,33,36,40,45,50,55,60,70,100})\n";

    std::cin >> choice;

    switch (choice) {
    case 1:
      std::cout << "\nManuelle Eingabe: ";
      std::cin >> str;
      N = mpz_class(str);
      break;
    case 2:
      std::cout << "\nWelche Fermat-Zahl: ";
      std::cin >> str;
      N = Fermat(std::stoi(str));
      break;
    case 3:
      std::cout << "\nWelche Cunningham-Zahl: ";
      std::cin >> str;
      N = Cunningham(std::stoi(str));
      break;
    case 4:
      std::cout << "\nWelche Testzahl: ";
      std::cin >> str;
      N = TestzahlB(std::stoi(str));
      break;
    case 5:
      std::cout << "\nWelche RSA-Zahl: ";
      std::cin >> str;
      N = RSAZahl(std::stoi(str));
      break;
    default:
      std::cout << "\nUngültige Auswahl, Zahl muss in {1,2,3,4,5} liegen!\n\n";
    }
  } while (choice < 1 || choice > 5);

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
  B = mpz_class("100000000");

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

  return 0;
}
