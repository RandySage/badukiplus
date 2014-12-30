/***************************************************************************
                          game.h  -  game class header file
                             -------------------
    begin                : Sun Oct 13 2002
    copyright            : (C) 2002 by Andrew D. Balsa
    email                : andrebalsa@mailingaddress.org
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef GAME_H
#define GAME_H

/*--------------  Defines  ------------------*/

#define PLAY_MOVE (0)   /* code for normal play */
#define RESIGN (-2)     /* code for resigning */
#define PASS (-1)       /* pass */
#define BOTHPASS (-3)   /* code for both sides passed, game is over*/

/* codes for players; and a code for something (e.g. a point on the board) */
/* which belongs to neither*/
enum bVal {BLACK, WHITE, EMPTY};
typedef enum bVal sType;


/*--------------  Globals  ------------------*/

// Class game

class game {

public:

   int RANDOM_SEED;        /* seed for rand() Random Number Generator */
   int kox, koy;           /* coords of current ko, or negative for none */

   enum bVal pla;          /* code for next player to play */
   int tur;                /* the number of this move */

   int ex;                 /* x coordinate of last move generated by engine */
   int ey;                 /* y coordinate of last move generated by engine */

   string emove;           /* vertex in letternumber format of last move by engine */
   
   float komi;             /* komi value for this game */
   
   int blackHandicap;      /* number of handicap stones for Black */

   enum bVal BadukiColor;   /* color Baduki is playing */

   int qpa;                /* flag for the last move was a pass, so that if this */
                           /* move is a pass, the game is finished */

   int boardSize;          /* Size of board which we are using */
                           /* (an optional command line parameter) */
                           /* default = 9 */

   int capturedBlack;      /* Number of black stones that White has captured */

   int capturedWhite;      /* Number of white stones that Black has captured */

   int territoryBlack;     /* Estimated Black territory */

   int territoryWhite;     /* Estimated White territory */
};

#define TRUE 1
#define FALSE 0

#define MAXGROUPS 160

#define PLACED 0
#define REMOVED 1

const int numPoints = 19;
const int maxPoint = 18;

#define maxSIZE 19

/*-- definitions used when counting up --*/

#define CNT_UNDECIDED	0
#define CNT_BLACK_TERR	1
#define CNT_WHITE_TERR	2
#define CNT_NOONE	3

/*-- macro functions --*/

/*Return TRUE if (x,y) corresponds to a point on the board.*/
#define onboard(x) (0<=(x)&&(x)<thegame.boardSize)
#define LegalPoint(x,y) (onboard(x)&&onboard(y))
#define ForeachPoint(a,b)	for(a=0;a<thegame.boardSize;a++) for (b=0;b<thegame.boardSize;b++)

struct String {
  enum bVal color;		/* The color of the string */
  short code,			/* The code used to mark stones in the string */
    count,			/* The number of stones in the string */
    internal,			/* The number of internal liberties */
    external,			/* The number of external liberties */
    liberties,			/* The total number of liberties */
    eyes,			/* The number of eyes */
    alive,			/* A judgement of how alive this string is */
    territory;			/* The territory this string controls */
};

struct bRec {
  enum bVal Val;		/* What is at this intersection */
  short xOfs, yOfs;
  short mNum;
  short StringNum;		/* What string the stone belongs to */
  short marked;			/* TRUE or FALSE */
};

#define iNil 32767		/* a distinguished value like nil */
#define  maxString 512
#define  maxSPoint 16
#define Default_tryLimit 50
#define MAX_STRING_PER_GROUP	20
#define MAX_GROUP	100

/*Return a letter corresponding to column x; 'i' is omitted from letter */
/* sequence by tradition.*/
#define lettercol(x) (                                                  \
		      (0<=(x)&&(x)<=7) ? 'a'+(x) : (7<(x)&&(x)< thegame.boardSize) ? 'a'+(x)+1 :  \
		    		'@')
//				This character replaces the call
//		                panic("illegal lettercol()") )
//				to avoid compilation errors with g++

/*Convert any uppercase letter to lowercase.*/
#define lowercase(c) ('A'<=(c)&&(c)<='Z'?(c)-'A'+'a':(c))

typedef int intBoard[19][19];	/* these were -2 to maxPoint + 2 */

typedef int boolBoard[19][19];

typedef struct {
  int px, py;
} point;

typedef struct {
  int px, py;
  enum bVal color;
} pointc;

typedef struct {
  point p[401];
  int indx;
} pointList;

typedef struct {
  point p[maxSPoint + 1];
  int indx;
} sPointList;

typedef struct {
  int indx, v[401];
} intList;

typedef struct {
  int w, s, sm;
} sgRec;

typedef struct {
  int mark, score, eyes, min_x, max_x, min_y, max_y, lx, ly;
} vsgRec;

typedef struct {
  int stringMark, atLevel, gid,
  	isLive, isDead, isSafe, libC, numEyes, exts, size,
  	lx, ly, kx, ky, sx, sy, kc, sc;
} stringRec;

typedef struct {
  int Mark, strength, tr1, tr2, score, eyes, exts,
  	stones, strings, string[MAX_STRING_PER_GROUP];
} groupRec;

typedef enum {
  rem, add, chLib, reMap
} playType;

typedef struct {
  int who, xl, yl, nextSID, sNumber, lx, ly, pae;
} pAddRec;
typedef struct {
  int who, xl, yl, nextSID, sNumber;
} pRemRec;
typedef struct {
  int oldLC, oldLevel;
} chLibRec;
typedef struct {
  int oldSID;
} reMapRec;
typedef struct {
  int SID;
  playType kind;
  union {
    pRemRec rem;
    pAddRec add;
    chLibRec chLib;
    reMapRec reMap;
  } uval;
} playRec;

struct altmovestype {
  int px;
  int py;
  float value;
  int value2;
  int target;
  int why;
};

#endif // GAME_H
