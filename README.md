# 🐍 Snake Game (Console Version)

A classic console-based Snake Game written in C, where the snake grows by eating dots!

Built as a simple fun project to practice basic game logic, console graphics, and keyboard input handling in C.

---

## 🎮 How to Play

- **Use Arrow Keys** to move the snake.
- **Eat the dot ( . )** to grow longer.
- **Avoid hitting the walls or yourself** — or it's game over!
- **Press Enter** any time to end the game.

---

## 📦 Features

- Console-based graphical boundaries.
- Dynamic snake movement and growth.
- Live score display.
- Simple game-over detection.
- Random dot placement.

---

## 🚀 How to Run

1. Clone the repository or download the `.c` file.
2. Compile the code using any C compiler. Example:

   ```bash
   gcc snake_game.c -o snake_game
   ```

3. Run the compiled file:

   ```bash
   ./snake_game
   ```

**Note:**  
This game uses Windows-specific libraries like `conio.h` and `windows.h`, so it runs smoothly on **Windows CMD** or **Visual Studio Command Prompt**.  
For other environments, you might need to adjust input and display functions.

---

## 📑 Dependencies

- `stdio.h`
- `stdlib.h`
- `time.h`
- `windows.h`
- `conio.h`

---

## 📌 Future Improvements

- Cross-platform compatibility (Linux / macOS)
- Multiple difficulty levels
- Sound effects
- Colorful console output

