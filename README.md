# Just Another Chess Engine

## Introduction
  This is a chess engine which supports [UCI](http://wbec-ridderkerk.nl/html/UCIProtocol.html) protocol. It was tested with [Arena](http://www.playwitharena.de/) as well as command line.
  My primary goals were to ~~beat AlphaZero~~:
  * Learn newer C++ features and their performance trade offs.
  * Attempt various code / performance optimizations. E.g. assembler routies, multicore, AVX.
  while having some fun. I choose this project because I could keep pushing it to other areas that I am interested in, namely hardware (GPU/FPGA) and AI, if I get that far. Also it doesn't conflict with my professional business domain.
  
## Usage  
  The compiled engine can be loaded to Arena and can be used to play a game or solve mate in N moves puzzles.
  Alternatively the engine can be started from command line and UCI commands can be used to communicate with it. In addition a file containing UCI commands can be passed as the first parameter. Once the commands in the file are processed, __jace__ will not exit, but wait for subsequent commands via the command line.
  An example UCI script is:
```uci
isready
ucinewgame
isready
position fen 8/4Q3/3pbp2/4k3/4B3/4K3/8/8 w - - 0 1
go depth 5
```
  Note that the engine detects a checkmate when the king is captured or the opponent doesnt' have a valid move while the king is under check. The implementation is simpler that way. For example, to solve a *2 move mate*, we need to set the depth to 5. Depth is in half-moves. When playing, Arena will detect the checkmate and stop the game.

## Current Status
As of now:
 * The engine 'knows' how to play legal chess.
 * MinMax algorigthm to navigate down the tree of possible moves.
 * Leaf node position evaluation with a simple heuristic.

There is no plan to continue development, at least in the short term.

