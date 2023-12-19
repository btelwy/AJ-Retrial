# AJ-Retrial
An expansion and improvement romhack for Apollo Justice: Ace Attorney (DS)

In progress. This repository does not represent any finished product, as it is designed to facilitate working.

-------------------------------------------------------------------------------
Guide to folders:

Added assets: assets not originally in AJ

Documentation: documentation for various aspects of AJ romhacking

Extracted materials: rips of AJ's file structure, all taken by me except for SFX (from Sounds Resource) and the soundfont (from iteachvader on YouTube at https://www.youtube.com/watch?v=_UL8lE-daMM)

Helper programs: tools I've written tailored to making romhacking AJ easier

Modified binaries: modified binary files, the end result of romhacking and what replace the original files in the file structure

Patches: all patches created up to this point

-------------------------------------------------------------------------------
Guide to extracted materials folder:

AJ soundfont: the instruments the game uses in its music

cpac2d.bin: contains the game's 2D assets

cpac3d.bin: contains the game's textures and models

Extracted script: the game's script in the form of decompressed binary files

Extracted script backup: a duplicate folder I made in case I mess up while text editing

Readable script: the game's original script in a readable format, obtained with phoenixtools

opdemo: probably not needed, but images making up the case intros

saigen: probably not needed, but images making up the 3D visualization sections in court

SFX: a rip of the sound effects in the game

arm9.bin: the game's main code in binary format

mes_all.bin: where the game's entire script is stored in compressed format

sound_data.sdat: the binary file containing all the game's music, sound effects, and other files relating to sound

-------------------------------------------------------------------------------
Programs used in this project:

ImHex (hex editor)

Tinke (DS file system viewer)

no$gba, DeSmuME, and melonDS (DS emulators)

deltapatcher (creates and applies .xdelta patches)

Ghidra (disassembly tool)

CUE's DS compression tools (compresses and decompresses common DS compression schemes)
