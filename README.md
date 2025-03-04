# Classy Clash

A 2D top-down action game built with C++ and raylib, featuring a knight battling goblins in a nature-themed environment.

## Prerequisites

- [raylib](https://www.raylib.com/) (v3.0.0)
- C++ compiler with C++14 support
- For Windows:
  - [w64devkit](https://github.com/skeeto/w64devkit) installed in `C:/raylib/w64devkit`
  - raylib installed in `C:/raylib/raylib`

## Project Structure

```
classy-clash/
├── .vscode/            # VSCode configuration
│   ├── tasks.json     # Build tasks
│   └── .gitkeep
├── nature_tileset/    # Map and tileset files
│   ├── game-map.tmx
│   ├── game-map_v2.tmx
│   ├── game-map_v2.png
│   ├── map.tiled-project
│   ├── map.tiled-session
│   ├── RPG Nature Tileset.tsx
│   └── RPG Nature Tileset.png
├── characters/        # Character sprite sheets
│   ├── knight_idle_spritesheet.png
│   ├── knight_run_spritesheet.png
│   ├── goblin_idle_spritesheet.png
│   └── goblin_run_spritesheet.png
├── Character.h        # Character base class
├── Enemy.h           # Enemy class
├── Prop.h            # Environmental props
├── Config.h          # Game configuration
├── main.cpp          # Main game loop
├── Makefile          # Build configuration
└── README.md         # Project documentation
```

## Building and Running

### Using VSCode (Recommended)

1. Open the project in VSCode
2. Choose a build configuration:
   - Press `Ctrl+Shift+B` for debug build
   - Use Command Palette (`Ctrl+Shift+P`) and select "Tasks: Run Task" -> "build release" for release build

### Using Make Directly

Debug build:
```bash
make PLATFORM=PLATFORM_DESKTOP BUILD_MODE=DEBUG OBJS=*.cpp
```

Release build:
```bash
make PLATFORM=PLATFORM_DESKTOP BUILD_MODE=RELEASE OBJS=*.cpp
```

## Controls

- WASD - Move the knight
- Mouse - Aim
- Left Click - Attack

## Features

- Smooth character movement and animation
- Combat system
- Environmental obstacles
- Enemy AI
- Top-down perspective gameplay

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Credits

- Game engine: [raylib](https://www.raylib.com/)
- Character and environment assets: [Add source here]
