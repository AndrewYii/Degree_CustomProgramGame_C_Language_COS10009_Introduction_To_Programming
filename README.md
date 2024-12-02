# Custom Program
- This is a custom platform game created with C, using the Raylib and JSON-C libraries.

## Prerequisites

### Before running the program, make sure you have the following installed: 
- GCC (GNU Compiler Collection)
- Raylib library
- JSON-C library

## Installation

### MingW64 (64-bit) (Recommended)
- `pacman -S mingw-w64-x86_64-raylib`
- `pacman -S mingw-w64-x86_64-json-c`

### MingW32 (32-bit)
- `pacman -S mingw-w64-i686-raylib`
- `pacman -S mingw-w64-i686-json-c`

## Usage
- Ensure that you have added the appropriate path for the selected bin directory (MingW64 or MingW32) in your environment variables.
- Restart your system to apply changes to the environment variables.

### Recommended Way (Command)
- Write in the terminal:
    ```bash
    gcc main.c -o game.exe -I -L -lraylib -ljson-c -lopengl32 -lgdi32 -lwinmm # Compile the program (General: both MingW64 & MingW32)
    ```

- After compiling the program, run it with the following command in the terminal:
    ```bash
    ./game.exe # to run the game (custom program)
    ```

### Alternate Way 1 (F5 to run & debug)
- You can also use **F5** to debug through Visual Studio Code.
- If you have MingW32 setup in your environment variables, adjust the properties in the .vscode folder (tasks.json, launch.json, c_cpp_properties.json) to match your setup.
- Keep the project folder shallow (avoid deeply nested directories) to ensure smooth debugging with **F5**
- It is recommended to place the project folder on the **Desktop** for easy access and fewer path-related issues.

### Alternate Way 2 (Command)
- Requirement:
    - Download make extension for your compiler
    #### Msys
    - `pacman -S make`
    - Connect the pathway for the make.exe in environmental elements
- Write in the terminal:
    ```bash
    make  # Compile the program 
    ```
- After compiling the program, run it with the following command in the terminal:
    ```bash
    ./game.exe # to run the game (custom program)
    ```
- once you would like to clean the game.exe:
    ```bash
    .make clean # clear the game (custom program)
    ```

## Demo Video Link  

### Installation Link 
- https://youtu.be/wWIj9HaRGWY

### Game (Custom Program) Trailer Link 
- https://youtu.be/jmQMNYP65ZQ

## Facing Problems
- If you are unable to run the program using MingW32, try using the MingW64 setup. This program was developed using the MingW64 environment, and the setup instructions are much clearer when following the MingW64 pathway.
- That's all! Have fun, and enjoy your journey with my game (custom program). If you encounter any issues or need further information, feel free to contact me.
