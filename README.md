# Arcade

## Overview

The Arcade project is a modular gaming platform that allows developers to create and integrate custom games and graphical libraries. This README provides essential information for contributors and users to get started.

## Features

- Modular architecture for games and graphical libraries.
- Support for custom extensions via defined interfaces.
- Easy integration and execution of new modules.

## How to Contribute

### Adding a New Game
1. Create a directory for your game under `./games/`.
2. Implement the `IGameModule` interface in your `.hpp` and `.cpp` files.
3. Export the proper symbol:
   ```cpp
   extern \"C\" IGameModule *createGame() {
       return new YourGameClass();
   }
   ```

### Adding a New Graphical Library
1. Create a directory for your library under `./graphicals/`.
2. Implement the `IDisplayModule` interface in your `.hpp` and `.cpp` files.
3. Export the proper symbol:
   ```cpp
   extern \"C\" IDisplayModule *createDisplay() {
       return new YourDisplayClass();
   }
   ```

## Compilation and Execution

### General Instructions
1. Compile the program:
   ```bash
   make
   ```
2. Run the program with the desired graphical module:
   ```bash
   ./arcade lib/arcade_sfml.so
   ```
