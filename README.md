# Arkanoid SFML

Implementacja klasycznej gry Arkanoid wykorzystująca bibliotekę SFML 3.0.1.

## Opis Gry

Arkanoid to klasyczna gra zręcznościowa, w której gracz kontroluje platformę (paddle) u dołu ekranu, odbijając piłkę w celu zniszczenia wszystkich cegieł na planszy. Gra zawiera różne typy cegieł o różnej wytrzymałości oraz system poziomów z możliwością tworzenia własnych map.

## Struktura Projektu

```
arkanoid-sfml/
├── include/                    # Pliki nagłówkowe
│   ├── Core/                  # Podstawowe klasy zarządzające grą
│   ├── Actors/                # Obiekty gry (Paddle, Ball, Brick)
│   ├── Controllers/           # Komponenty logiki dołączane do aktorów/scen
│   ├── Scenes/                # Sceny gry (menu, rozgrywka)
│   └── Utils/                 # Klasy narzędziowe (MessageBus, SoundManager)
├── src/                       # Implementacje klas
├── assets/                    # Zasoby gry
│   ├── music/                 # Pliki dźwiękowe
│   └── fonts/                 # Czcionki
├── levels/                    # Pliki poziomów
└── build/                     # Katalog budowania
```

## Wymagania Systemowe

### Wymagania

- CMake 3.16 lub nowszy
- Kompilator zgodny z C++17
- SFML 3.0.1

### Kompilacja

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

Po kompilacji upewnij się, że katalogi `levels/` i `assets/` znajdują się w tym samym katalogu co plik wykonywalny.

## Architektura Gry

Projekt wykorzystuje wzorzec actor-controller z systemem komunikacji opartym na wiadomościach:

### 1. Core (Rdzeń)

- **Główny kontroler gry** zarządzający pętlą gry i scenami
- Odpowiada za przełączanie między scenami
- Może zarządzać wieloma scenami jednocześnie

### 2. Scene (Scena)

- **Kontener dla aktorów** reprezentujący ekran gry
- Przechowuje listę aktorów i kontrolerów na poziomie sceny
- Może wysyłać i odbierać wiadomości przez MessageBus

### 3. Actor (Aktor)

- **Obiekt gry** z pozycją, rozmiarem i reprezentacją wizualną
- Może zawierać wiele kontrolerów (kompozycja)
- Dostępne typy: Ball, Paddle, Brick

### 4. Controller (Kontroler)

- **Klasa abstrakcyjna** definiująca logikę i zachowanie
- Może być dołączony do aktora lub sceny
- Może subskrybować i wysyłać wiadomości przez MessageBus

### 5. MessageBus (Magistrala Wiadomości)

- **Statyczna klasa** obsługująca komunikację między komponentami
- Wspiera publikowanie i subskrybowanie wiadomości
- Używana do rozdzielenia odpowiedzialności (np. Cegła zniszczona → Wynik zaktualizowany)

## Komponenty Gry

### Aktorzy (Actors)

#### Ball (Piłka)

- Porusza się po planszy z określoną prędkością
- Odbija się od ścian, platformy i cegieł
- Zarządzana przez `BallController`

#### Paddle (Platforma)

- Kontrolowana przez gracza
- Porusza się poziomo u dołu ekranu
- Odbija piłkę pod różnymi kątami w zależności od punktu odbicia
- Zarządzana przez `PaddleController`

#### Brick (Cegła)

- Statyczne obiekty do zniszczenia
- Różne typy o różnej wytrzymałości:
  - **Normalna cegła** (czerwona, 1 punkt życia)
  - **Wytrzymała cegła** (niebieska, 2 punkty życia)
  - **Niezniszczalna cegła** (szara, nie można zniszczyć)
- Zarządzana przez `BrickController`

### Kontrolery (Controllers)

#### BallController

- Obsługuje ruch piłki i kolizje
- Wykrywa odbicia od ścian, platformy i cegieł
- Wysyła wiadomości o zdarzeniach kolizji

#### PaddleController

- Obsługuje sterowanie platformą przez gracza
- Reaguje na input z myszy

#### BrickController

- Zarządza stanem cegły i jej zniszczeniem
- Wysyła wiadomość gdy cegła zostanie zniszczona

#### Kontrolery Scen

- **GameplaySceneController**: Zarządza logiką rozgrywki
- **GameOverSceneController**: Obsługuje ekran końca gry
- **LevelSelectorSceneController**: Zarządza wyborem poziomu

### Sceny (Scenes)

#### GameplayScene

- Główna scena rozgrywki
- Zawiera wszystkie obiekty gry i zarządza rozgrywką

#### GameOverScene

- Wyświetlana po zakończeniu gry
- Umożliwia restart lub powrót do menu

#### LevelSelectorScene

- Umożliwia wybór poziomu do gry
- Wyświetla dostępne poziomy

### Narzędzia (Utils)

#### MessageBus

- Centralny system komunikacji
- Typy wiadomości: BrickDestroyed, BallLost, LifeLost, GameOver, LevelComplete

#### SoundManager

- Zarządza dźwiękami gry
- Obsługuje efekty dźwiękowe i muzykę tła

#### LevelLoader

- Ładuje poziomy z plików `.level`
- Tworzy obiekty cegieł na podstawie danych z pliku

## System Poziomów

### Format Pliku Poziomu

Poziomy są przechowywane w plikach `.level` w katalogu `levels/`:

```
<szerokość> <wysokość> <odstęp> <padding_x> <padding_y>
<linia_1_cegieł>
<linia_2_cegieł>
...
```

**Typy cegieł:**

- `1` - Normalna cegła (czerwona, 1 trafienie)
- `2` - Wytrzymała cegła (niebieska, 2 trafienia)
- `X` - Niezniszczalna cegła (szara)
- `.` - Puste miejsce

**Przykład:**

```
13 8 5 20 20
1111111111111
1.1.1.1.1.1.1
2.2.2.2.2.2.2
2222222222222
XX...XXX...XX
..111...111..
```

### Tworzenie Własnych Poziomów

1. Utwórz plik `.level` w katalogu `levels/`
2. Zdefiniuj nagłówek z rozmiarem siatki i właściwościami
3. Zaprojektuj układ cegieł używając kodów znaków
4. Przetestuj poziom w grze

## Dźwięki i Muzyka

Gra zawiera różnorodne efekty dźwiękowe i muzykę tła:

- **background.ogg** - Muzyka tła podczas rozgrywki
- **brick_break.ogg** - Dźwięk niszczenia cegły
- **life_loss.ogg** - Dźwięk utraty życia
- **game_over.ogg** - Dźwięk końca gry
- **win.ogg** - Dźwięk wygranej

**Źródła dźwięków:**

- [OpenGameArt.org](https://opengameart.org)
- [Kenney.nl Assets](https://kenney.nl/assets)

## Sterowanie

- **Strzałki lewo/prawo** lub **A/D** - Poruszanie platformą
- **Spacja** - Start gry/Restart
- **Escape** - Powrót do menu

## Rozszerzanie Gry

Architektura modularna umożliwia łatwe dodawanie nowych funkcji:

1. **Nowe typy cegieł** - Dodaj nowy typ w `BrickController`
2. **Power-upy** - Utwórz nowy `Actor` z odpowiednim `Controller`
3. **Nowe sceny** - Dziedzicz po klasie `Scene`
4. **Dodatkowe efekty** - Użyj `MessageBus` do komunikacji między komponentami

## Licencja

Projekt stworzony do celów edukacyjnych. Dźwięki pochodzą z darmowych zasobów OpenGameArt.org i Kenney.nl.
