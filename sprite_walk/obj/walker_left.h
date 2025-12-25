
//{{BLOCK(walker_left)

//======================================================================
//
//	walker_left, 256x256@4, 
//	+ palette 256 entries, not compressed
//	+ 2 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 64 + 2048 = 2624
//
//	Time-stamp: 2025-12-24, 23:46:59
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_WALKER_LEFT_H
#define GRIT_WALKER_LEFT_H

#define walker_leftTilesLen 64
extern const unsigned int walker_leftTiles[16];

#define walker_leftMapLen 2048
extern const unsigned short walker_leftMap[1024];

#define walker_leftPalLen 512
extern const unsigned short walker_leftPal[256];

#endif // GRIT_WALKER_LEFT_H

//}}BLOCK(walker_left)
