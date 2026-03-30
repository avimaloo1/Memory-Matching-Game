# Card-Matching-Game

# 🎮 Memory Match Game (FEH Proteus)

An interactive touchscreen-based memory matching game built in C++ using the FEH Proteus embedded system. Players flip cards to find matching pairs while tracking time and moves.

---

## 🚀 Overview

This project implements a fully interactive **memory card matching game** with a graphical user interface, touch input, randomized gameplay, and performance tracking.

The game challenges users to match all 12 pairs of cards in the shortest time and fewest moves possible.

---

## ✨ Features

* 🖥️ **Graphical User Interface**

  * Custom backgrounds, buttons, and card images
  * Interactive menu system (Play, Stats, Instructions, Credits)

* 🎯 **Core Gameplay**

  * 24 cards (12 matching pairs)
  * Flip-based matching logic
  * Prevents double-click matching exploits

* 🔀 **Randomized Board**

  * Cards are shuffled each game using a custom randomization system
  * Ensures only two of each card exist

* ⏱️ **Performance Tracking**

  * Tracks:

    * Time to complete game
    * Number of moves made
  * Displays stats in menu

* 🧠 **Game Logic Enforcement**

  * Only two cards can be flipped at a time
  * Non-matching cards flip back after delay
  * Matching cards remain visible

* 🎉 **Win Animation**

  * Animated end screen with moving graphics upon completion

---

## 🛠️ Tech Stack

* **Language:** C++
* **Platform:** FEH Proteus Robot Controller
* **Libraries:**

  * `FEHLCD` – display and UI rendering
  * `FEHImages` – image loading and drawing
  * `FEHUtility` – timing and delays
  * `FEHRandom` – random number generation

---

## 🧩 How It Works

### 1. Menu System

* Displays main menu with:

  * Play
  * Statistics
  * Instructions
  * Credits
* Uses touch input to navigate between screens

---

### 2. Card Randomization

* Generates random numbers (0–11) to assign card images
* Ensures:

  * Each card appears exactly twice
  * Positions are randomized every game

---

### 3. Gameplay Logic

* User taps cards to flip them

* After two selections:

  * ✅ If match → cards stay face up
  * ❌ If not → cards flip back after 1.5 seconds

* Tracks:

  * `press_counter` → total clicks
  * `match` → number of successful matches

---

### 4. State Management

* Game state stored in `Card` class:

  * Card image assignments
  * Match count
  * Move count
  * Elapsed time

---

### 5. Win Condition

* Game ends when:

  * `match == 12`

* Displays:

  * Completion message
  * Animated graphics (sun + worm movement)
  * Final time

---

## 🗂️ Code Structure

* `Card Class`

  * Stores all card data and game state
  * Handles:

    * Randomization (`RandomizeCard`)
    * Gameplay logic (`userFlip`)

* `Menu Function`

  * UI navigation and screen transitions

* `main()`

  * Initializes system and launches menu

---

## 🎮 Controls

* Tap cards to flip them
* Tap menu buttons to navigate
* Match all pairs to win

---

## 📊 Example Gameplay Flow

1. Start game from menu
2. Cards are randomized and displayed face down
3. Player selects two cards
4. System checks for match
5. Repeat until all pairs are matched
6. View stats and replay

---

## ⚠️ Limitations

* Code is repetitive for each card (manual handling of 24 cards)
* No dynamic data structures (arrays/vectors could improve scalability)
* UI tied specifically to FEH Proteus hardware

---

## 🔮 Future Improvements

* Refactor using arrays or structs for cleaner card handling
* Add difficulty levels (grid size variations)
* Implement sound effects
* Add high score tracking
* Improve animations and transitions

---

## 🧠 Key Learning Outcomes

* Event-driven programming with touch input
* GUI design in embedded systems
* State management in interactive applications
* Randomization and game logic design
* Debugging large-scale conditional logic

---

## 👥 Credits

* Avi Maloo
* Malia Weatherbie

---

## 📄 License

This project is for educational purposes.

---
