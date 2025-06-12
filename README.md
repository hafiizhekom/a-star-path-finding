# A* Snake Path Finding Game

A Snake game with A* (A Star) pathfinding algorithm written in C++. This game allows players to play manually or let the computer automatically solve the path from start to goal using the A* algorithm.

## Features

- Dynamically sized map (width and height can be set).
- Random placement of start (`@`) and goal (`?`).
- Randomly placed obstacles (`O`).
- Manual play mode (with direction commands).
- Automatic solution mode using the A* algorithm.
- Path visualization (`X` for closed path, `#` for open path, `*` for the snake's body).

## How to Run

1. **Compile the code:**

   ```sh
   g++ "A Star Snake New.cpp" -o a_star_snake
   ```

2. **Run the program:**

   ```sh
   ./a_star_snake
   ```

3. **Follow the on-screen instructions:**
   - Enter the width and height of the area.
   - Choose the number of obstacles.
   - Select `play` mode for manual play or `solve` for automatic solution.

## Manual Game Controls

- `atas`         : Move up
- `bawah`        : Move down
- `kiri`         : Move left
- `kanan`        : Move right
- `ataskanan`    : Move diagonally up-right
- `ataskiri`     : Move diagonally up-left
- `bawahkanan`   : Move diagonally down-right
- `bawahkiri`    : Move diagonally down-left

## Map Symbols

- `@` : Start point
- `?` : Goal
- `O` : Obstacle
- `*` : Snake body (in manual play)
- `X` : Path already traversed (closed path)
- `#` : Path under consideration (open path)
- `_` : Empty area

## Notes

- This program uses the `conio.h` library and `system("cls")`, so it only runs on Windows.
- The maximum map size is 70x100.

## License

This project is created for educational purposes.

---