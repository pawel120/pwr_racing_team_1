# Pwr racing team zadanie rekrutacyjne 
# Zadanie 2 - Otoczka wypukła i najbliższa para punktów

Implementacja dwóch algorytmów geometrii obliczeniowej o optymalnej złożoności obliczeniowej.

## Logika działania
1. **Wczytanie i przygotowanie**: Dane pobierane przez `std::cin`. Program weryfikuje poprawność danych i usuwa duplikaty, aby uniknąć błędów w obliczeniach.
2. **Otoczka wypukła (Monotone Chain)**: 
   - Sortowanie punktów po X.
   - Budowa dolnego łańcucha, `std::reverse` i budowa górnego łańcucha.
   - Algorytm automatycznie obsługuje punkty współliniowe.
3. **Najbliższa para (Divide & Conquer)**: 
   - Rekurencyjny podział płaszczyzny.
   - Analiza punktów w pasie środkowym w celu znalezienia najmniejszego dystansu.

## Obsługa Edge Cases
* **Duplikaty i współliniowość**: Kod jest odporny na nakładające się punkty oraz punkty leżące na jednej linii.
* **Minimalna liczba danych**: Program weryfikuje, czy liczba punktów pozwala na wykonanie operacji (minimum 3 dla otoczki), w przeciwnym razie wyrzuca błąd.
* **Stabilność**: Wykorzystanie bibliotek standardowych (`vector`, `algorithm`) zapewnia brak wycieków pamięci i stabilne działanie.

