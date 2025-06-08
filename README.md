# Arkanoid SFML

## Autorzy

**Zespół projektowy:**

- **Kacper Wojak**

- **Bruno Dzięcielski**

_Informatyka niestacjonarna, 1 rok, 2 semestr_

## Opis Projektu

### Cel

Celem projektu było stworzenie gry typu Arkanoid przy użyciu biblioteki SFML. Projekt opiera się na architekturze actor-controller z systemem komunikacji między obiektami.

### Założenia

**Podstawowe założenia:**

- Obsługa kolizji piłki z otoczeniem i paletką

- Sterowanie paletką za pomocą klawiatury lub myszy

- System punktacji oraz ekran końca gry

- Implementacja w C++17 z użyciem SFML

**Planowane rozszerzenia:**

- Różne poziomy trudności

- Edytor poziomów pozwalający na tworzenie własnych plansz

### Zrealizowane Funkcjonalności

- Pełna rozgrywka Arkanoid z piłką, platformą i cegłami

- System poziomów z ładowaniem plansz z plików `.level`

- Cegły o różnej wytrzymałości

- System dźwięków: muzyka w tle i efekty dźwiękowe

- System scen: menu główne, gra, ekran końca

- Edytor poziomów na podstawie plików tekstowych

### Architektura

Projekt podzielono na kilka głównych komponentów:

#### Core

Główny kontroler zarządzający grą oraz przełączaniem scen.

#### Scena

Reprezentacja ekranu gry zawierająca wszystkie aktywne obiekty.

#### Aktorzy

Obiekty gry posiadające pozycję, rozmiar i wizualizację:

- **Ball** — piłka

- **Paddle** — paletka

- **Brick** — cegły

#### Kontrolery

Logika przypisana do aktorów lub scen:

- **BallController** — ruch piłki i wykrywanie kolizji

- **PaddleController** — obsługa sterowania paletką

- **BrickController** — zarządzanie stanem cegieł

#### MessageBus

System komunikacji umożliwiający przesyłanie wiadomości między obiektami bez bezpośrednich zależności.

### Wymagania

- **CMake** 3.16 lub nowszy

- Kompilator zgodny z C++17

- **SFML** 3.0.1

## Instrukcja Uruchomienia

```bash
# Klonowanie repozytorium
git  clone  https://github.com/kriziu/arkanoid-sfml.git
cd  arkanoid-sfml

# Budowanie projektu
mkdir  build
cd  build
cmake  ..
cmake  --build  .

# Uruchamianie gry (upewnij się, że katalogi levels/ i assets/ są dostępne)
./arkanoid-sfml
```

## Sterowanie

- **Mysz** — poruszanie paletką, obsługa menu

- **Lewy przycisk myszy** — rozpoczęcie gry lub restart

## Zasady Gry

1. Wybór poziomu z menu głównego.

2. Odbijanie piłki przy pomocy paletki.

3. Zniszczenie wszystkich cegieł na planszy.

**Rodzaje cegieł:**

- **Pomarańczowe** — Zwykła cegła - 1 trafienie

- **Niebieskie** — Wytrzymała cegła - 2 trafienia

- **Szare** — Niezniszczalna cegła

## Tworzenie Własnych Poziomów

Pliki poziomów zapisuje się w katalogu `levels/` w formacie `.level`. Przykład:

```



# Format: szerokość wysokość odstęp padding_x padding_y



13 8 5 20 20



1111111111111



1.1.1.1.1.1.1



2.2.2.2.2.2.2



2222222222222



XX...XXX...XX



..111...111..



```

**Legenda znaków:**

- `1` — normalna cegła

- `2` — wytrzymała cegła

- `X` — niezniszczalna cegła

- `.` — puste miejsce

## Ciekawostki

### Architektura Actor-Controller

Zastosowanie wzorca actor-controller umożliwiło budowę gry, gdzie aktorzy mogą mieć przypisane różne kontrolery, co zwiększyło elastyczność rozwiązania.

### System MessageBus

Luźna komunikacja między obiektami pozwoliła na eliminację bezpośrednich zależności i zwiększyła przejrzystość kodu.

## Podsumowanie

### Zrealizowane cele:

- Odbijanie piłki i system kolizji

- Sterowanie paletką przy pomocy myszy

- System punktacji i ekran końca gry

### Dodatkowe funkcjonalności:

- System poziomów i edytor poziomów

- Efekty dźwiękowe z muzyką w tle

### Wnioski

- Wzorzec scena-actor-controller sprawdził się dobrze w projektowaniu gry.

- SFML zapewniła wszystkie niezbędne funkcje do realizacji projektu.

### Napotkane problemy:

- Konfiguracja projektu w CMake.

- Implementacja architektury sceny, aktora i kontrolera wymagała dokładnego zaplanowania i testów.

## Propozycje Rozwoju

- Power-upy, np. szybka piłka, większa paletka

- Wykorzystanie tekstur i sprite'ów

- Dodanie tła w zależności od poziomu

## Licencja

Projekt stworzony do celów edukacyjnych. Dźwięki pochodzą z darmowych zasobów [OpenGameArt.org](https://opengameart.org/) oraz [Kenney.nl](https://kenney.nl/).
