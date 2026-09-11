# Tetris

A Tetris implementation in C++20, built on top of a modular game engine.

> **Work in progress:** the Tetris game itself is still under development.
> The project is currently on hold due to other professional activities, but the underlying game engine is already well advanced.

## Overview

This project started as a training project around game engine architecture and C++ development.

Rather than building a Tetris-specific application from the beginning, the project was designed around a more generic and modular game engine.

The goal is to keep the different parts of the engine decoupled so that input devices, rendering systems and platform-specific implementations can be replaced without having to rewrite the core game logic.

The current implementation mainly targets macOS and uses the terminal as its display, but the architecture is intended to support other platforms and interfaces.

## Project status

The project is **not finished**.

The game engine and its surrounding architecture are already well advanced, but the actual implementation of Tetris still needs to be completed.

Development is currently paused due to other professional activities. The project remains a work in progress and may be resumed in the future.

Current status:

* [x] Basic game engine architecture
* [x] Game session management
* [x] Event management
* [x] Keyboard input abstraction
* [x] Renderer abstraction
* [x] Terminal renderer
* [x] macOS-specific terminal handling
* [ ] Complete Tetris game logic
* [ ] Complete Tetris gameplay
* [ ] Finalize controls
* [ ] Improve cross-platform support
* [ ] Add additional input devices
* [ ] Add additional rendering backends

## Architecture

The project is currently split into two main parts:

```text
Tetris/
├── App/
│   ├── include/
│   ├── Main.cpp
│   └── TetrisGame.cpp
│
├── Core/
│   ├── include/
│   ├── AppLauncher.cpp
│   ├── CtrlKeyboard.cpp
│   ├── EventManager.cpp
│   ├── GameEngine.cpp
│   ├── GameSession.cpp
│   ├── IRenderer.cpp
│   ├── Menu.cpp
│   ├── RenderVisitor.cpp
│   └── TerminalCoreTermios.cpp
│
├── Main/
├── makefile
└── README.md
```

### App

The `App` layer contains the application-specific code.

For this project, this is where the Tetris implementation lives. The intention is to keep game-specific logic separate from the underlying engine.

### Core

The `Core` layer contains the reusable parts of the game engine.

It currently includes components for:

* game engine management;
* game sessions;
* event management;
* keyboard input;
* rendering;
* menus;
* terminal handling;
* application launching.

The separation between `App` and `Core` is intended to make the engine reusable for other games or applications.

## Modular game engine

One of the main goals of the project is to avoid coupling the game engine to a specific input device, renderer or operating system.

The engine is therefore designed around interfaces that allow different implementations to communicate with the core.

### Input

The input layer is designed to allow different devices to be connected to the engine.

Currently:

```text
Game
  │
  ▼
Game Engine
  │
  ▼
Input Interface
  │
  └── Keyboard
```

The same approach could be extended to other input devices, for example:

```text
Input Interface
├── Keyboard
├── Gamepad
└── Other controllers
```

The objective is to allow the game logic to work independently from the physical input device.

### Rendering

The same principle applies to rendering.

The engine communicates with a renderer through an abstraction rather than directly depending on a specific display technology.

The current implementation uses the terminal:

```text
Game
  │
  ▼
Game Engine
  │
  ▼
Renderer Interface
  │
  └── Terminal Renderer
```

This leaves room for other rendering implementations in the future.

For example:

```text
Renderer Interface
├── Terminal
├── Window / GUI
└── Other rendering backends
```

The renderer can therefore evolve independently from the game logic.

## Platform support

The project is intended to be portable across platforms.

The current development environment is primarily:

* macOS
* C++20
* Clang++
* Terminal

Platform-specific functionality is kept isolated where possible so that other implementations can be added later.

The long-term goal is to support at least:

```text
macOS
Windows
```

without requiring changes to the core game logic.

## Technologies

* C++20
* Clang++
* Make
* Termios
* Git

## Building

Clone the repository:

```bash
git clone https://github.com/gketo/Tetris.git
cd Tetris
```

Build the project:

```bash
make
```

Run it:

```bash
make run
```

The project currently relies on macOS-specific terminal functionality, so the development and execution environment is primarily macOS.

## Development goals

The main purpose of this project is not only to implement Tetris, but also to experiment with the design of a small, modular game engine.

The main architectural goals are:

* keep game logic independent from input devices;
* keep game logic independent from rendering;
* isolate platform-specific code;
* use interfaces to decouple engine components;
* make components replaceable;
* allow the same engine to potentially be reused by other games.

Tetris is therefore being used as the first application built on top of this engine.

## Future work

Once development resumes, the main priorities will be:

1. Complete the Tetris implementation.
2. Finalize the interaction between the game and the engine.
3. Improve the current terminal renderer.
4. Add gamepad support.
5. Improve Windows compatibility.
6. Add additional rendering backends.
7. Improve testing and documentation.

## License

No open-source license has currently been specified for this project.
