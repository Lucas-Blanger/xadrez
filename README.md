# Chess Game in C

This project was developed as part of the Programming Laboratory II course in the Computer Science program at the Federal University of Santa Maria.

## Description

The program implements a simplified chess game that allows players to make moves on the board and check if a move results in check or checkmate. It keeps a record of the moves and the captured pieces during the game.

The board is initialized with the pieces in the standard chess starting positions, and the program provides functionalities for moving pieces and capturing opponent pieces, as well as checking if the king is in check or if a checkmate has occurred.

## Features

- Initialization of the chessboard with white and black pieces;
- Validation of moves for pieces such as pawns, rooks, knights, bishops, queens, and kings;
- Detection of check and checkmate;
- Recording of moves and piece captures;
- Display of the moves made and captured pieces.

## Structure

The code is organized as follows:

- **Piece**: Structure representing a chess piece, containing the type and color of the piece.
- **Move**: Structure that stores a move, containing a description of the move made.
- **Board**: The chessboard is represented by an 8x8 matrix of pointers to pieces.

## How to Play

1. The program displays the board and asks the player to input a move in the format column row column row (e.g., `E2 E4`).
2. The player must enter valid moves according to chess rules.
3. The game checks if the move is valid and updates the board.
4. Captures and moves are recorded, and the program continues until a checkmate occurs.

## Author

Lucas Blanger - Developed as part of the Programming Laboratory II course at the Federal University of Santa Maria (UFSM).
