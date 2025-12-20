
//{{BLOCK(happyface)

//======================================================================
//
//	happyface, 256x256@4, 
//	+ palette 256 entries, not compressed
//	+ 15 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 480 + 2048 = 3040
//
//	Time-stamp: 2025-12-14, 09:59:36
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_HAPPYFACE_H
#define GRIT_HAPPYFACE_H

#define happyfaceTilesLen 480
extern const unsigned int happyfaceTiles[120];

#define happyfaceMapLen 2048
extern const unsigned short happyfaceMap[1024];

#define happyfacePalLen 512
extern const unsigned short happyfacePal[256];

#endif // GRIT_HAPPYFACE_H

//}}BLOCK(happyface)
