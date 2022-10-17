# 🗑️Trash Can
Code too small or too bad to have separate repository. But maybe, sometimes...

Main rules for this repository are Four U Rule:
 - Untested
 - Uncommented
 - Unsupported
 - Maybe even unworking

 Table of contents
   * [Game theory](#Game-theory)
   * [UnWatermark TG](#UnWatermark-TG)
   * [Tipa CFS](#Tipa-CFS)
   * [Weiler_cut](#Weiler-cut)
   * [Tipa_linpack](#Tipa-Linpack)
   * [Tipa_Caesar](#Tipa-Caesar)

# Game theory
 
[link](/game_theory)

 Simple realization of iterative method of solving antagonistic games. 
 
 Usage: 
 
 `./gt <filename> [number of iterations] [first strategy of player A]`

 
# UnWatermark TG
 
[link](/UnWatermarkTG)

 Simple script in javascript for deleting parts of JSON with provided name. 
 
 Usage: 
 
 To actually use it for unwatermarking Telegram stickers, convert files of stickers to JSON, find name of watermark layers (if they are named), then use this script and convert back from JSON to sticker.


 # Tipa CFS
 
[link](/tipa_CFS)

 Attempt to model Linux CFS (Completely Fair Scheduler). Not stable, working on old version of QT and probably isn't correct. 


 # Weiler Cut

[link](/Weiler_cut)

 <img src="images/weiler_image.png" alt="" width="600"/>

 Simple app to test Weiler Atherton polygon clipping algorithm. It was meant to be included in [crystalls](https://github.com/SmirnuX/crystalls), but in current version it's too buggy.
 
 Usage:
 
 You can move shapes by pressing arrow keys. On the right side of two shapes you will see two colums of shapes - inner and outer lists.
 
 
 # Tipa Linpack

[link](/tipa_linpack)

 Attempt to recreate linpack with multithreading. Cause base algorithmm of solving linear equations can't be done in parallel well, it just launches one linear equation per thread. 
 
  Usage: 
 
 `./linpack [size of matrix = 1000] [number of threads = 1] [number of tests = 1]`

 # Tipa Caesar

[link](/tipa_caesar)

 <img src="images/caesar_image.png" alt="" width="600"/>

Tool to encrypt or decipher text in russian language using Caesar cipher with keyword.
caesar_image.png