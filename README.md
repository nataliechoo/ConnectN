# ConnectN
A game like Connect 4 but with any size and any goal. Includes two bots: one smart, and one dumb.

NOTE: for each turn, smart robots will assess the game state and will always choose the best possible move, meaning that that for larger boards, the possible move traversal will take time (will be noticeably slow starting from a 5x5 board) 

GAME SETUP: 
the game will prompt for: 
- the dimensions of your desired board
- the number of connected elements needed to win a game
- whether you would like to play against a dumb robot
- whether you would like to play against a smart bot, or see two smart bots play against each other

HOW TO PLAY:
- after choosing your desired game settings, the game will prompt for your move. type a number (1 to N) representing the column you would like to play a piece in 
- to win, get N consecutive pieces diagonally, vertically, or horizontally
