# Dungeon Crawler

A (for now) text-based dungeon crawler developed for the Programming 2 practicum.
The goal is to apply object-oriented programming principles such as inheritance, polymorphism, and dynamic memory management.
This project is still in development.

## Overview

The game displays a small dungeon grid with different tile types:
- Floor (.) – can be entered
- Wall (#) – blocks movement
- Portal (O) – teleports the player to another portal
- Player (X) – controlled character

Each tile reacts differently when entered (onEnter) or left (onLeave).

## Features
- Object-oriented class design (Tile, Floor, Wall, Portal, Character, Level, DungeonCrawler, AbstractUI, TerminalUI)
- Separation of game logic and user interface
- Turn-based movement using numeric keypad input (1–9, 5 = stay, 0 = quit)
- Safe memory management and clear event flow (moveTo, onEnter, onLeave)

### Controls
- Move with 1–9 (numpad)
- Stay with 5
- Quit with 0

