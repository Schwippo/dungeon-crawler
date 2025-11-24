# Dungeon Crawler – Programming 2 Practicum

This project is a text-based dungeon crawler developed as part of the Programming 2 practicum.
The focus is on applying object-oriented programming concepts such as inheritance, polymorphism,
dynamic memory management, event-driven behavior, and clean architectural separation (MVC).

The project evolves over multiple practicum stages.  
This version includes all features from Practicum 1 and Practicum 2.

---

## Overview

The dungeon consists of a 2D grid of tile objects.  
Each tile type inherits from the abstract base class `Tile` and implements its own behavior for:

- `onEnter(Character*)`
- `onLeave(Tile*, Character*)`
- `moveTo(Tile*, Character*)`

Movement is turn-based and controlled via keyboard input in the terminal.

---

## Tile Types

### Practicum 1 Tiles
- **Floor (.)**  
  Normal walkable tile.
- **Wall (#)**  
  Blocks movement.
- **Portal (O)**  
  Two portals are paired. Stepping on one instantly teleports the character to the other.

### Practicum 2 Additions
- **Pit (_)**
  - Can always be entered.
  - Can only be left to another Pit or a Ramp.
- **Ramp (<)**
  - Normal walkable tile.
  - Allows leaving Pit areas.
- **Switch (?)**  
  - Walkable tile that triggers an action when entered.
  - Implements the Active role of the Observer pattern.
- **Door (X / /)**  
  - Implements the Passive role.
  - Closed (X): behaves like a wall.
  - Open (/): behaves like a floor.
  - Switches toggle doors on each activation.

---

## Architecture

### Object-Oriented Design
- **Tile hierarchy**  
  `Tile` → `Floor`, `Wall`, `Portal`, `Pit`, `Ramp`, `Switch`, `Door`

- **Events**  
  All movement logic is decomposed into:
  - `onLeave()`
  - `onEnter()`
  - `moveTo()`

- **Observer Pattern (Practicum 2)**  
  - `Active`: can attach/detach `Passive` observers and activate them.
  - `Passive`: reacts to `notify()`.
  - `Switch` activates all connected `Door` objects.

### MVC Separation
- **AbstractView**  
  Defines drawing the Level.
- **AbstractController**  
  Defines how movement input is retrieved.
- **TerminalUI**  
  Implements both to handle console I/O.

### Level
- Loads a predefined map from a string.
- Dynamically allocates all tiles.
- Places the player.
- Connects portal pairs and switch–door relationships.
- Implements:
  - Deep copy constructor
  - Deep assignment operator

### DungeonCrawler
Central game manager:
- Initializes UI and Level
- Assigns controller to the player
- Runs the main loop
- Executes turn-by-turn movement

---

## Controls

Uses WASD movement:
- **w** = up
- **s** = down
- **a** = left
- **d** = right
- **q** = quit game

---

## Status

The project is actively extended throughout the practicum.
Later stages will include NPCs, combat mechanics, inventory systems, and a Qt-based GUI.
