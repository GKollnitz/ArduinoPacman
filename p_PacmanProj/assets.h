// This file was generated with the command-line:
//    /usr/local/bin/gd2asset -f assets.gd2 -o assets.h pcmsp.png red.png yellow.png pink.png blue.png whiteGhost.png blueGhost.png powerP.png sadMap.jpg pacman_chomp.wav pacman_death.wav pacman_eatfruit.wav pacman_eatghost.wav

#define PCMSP_HANDLE 0
#define PCMSP_WIDTH 13
#define PCMSP_HEIGHT 117
#define PCMSP_CELLS 1
#define RED_HANDLE 1
#define RED_WIDTH 14
#define RED_HEIGHT 14
#define RED_CELLS 1
#define YELLOW_HANDLE 2
#define YELLOW_WIDTH 14
#define YELLOW_HEIGHT 14
#define YELLOW_CELLS 1
#define PINK_HANDLE 3
#define PINK_WIDTH 14
#define PINK_HEIGHT 14
#define PINK_CELLS 1
#define BLUE_HANDLE 4
#define BLUE_WIDTH 14
#define BLUE_HEIGHT 14
#define BLUE_CELLS 1
#define WHITEGHOST_HANDLE 5
#define WHITEGHOST_WIDTH 14
#define WHITEGHOST_HEIGHT 14
#define WHITEGHOST_CELLS 1
#define BLUEGHOST_HANDLE 6
#define BLUEGHOST_WIDTH 14
#define BLUEGHOST_HEIGHT 14
#define BLUEGHOST_CELLS 1
#define POWERP_HANDLE 7
#define POWERP_WIDTH 14
#define POWERP_HEIGHT 14
#define POWERP_CELLS 1
#define SADMAP_HANDLE 8
#define SADMAP_WIDTH 240
#define SADMAP_HEIGHT 272
#define SADMAP_CELLS 1
#define PACMAN_CHOMP 136352UL
#define PACMAN_CHOMP_LENGTH 2864
#define PACMAN_CHOMP_FREQ 8000
#define PACMAN_DEATH 139216UL
#define PACMAN_DEATH_LENGTH 6136
#define PACMAN_DEATH_FREQ 8000
#define PACMAN_EATFRUIT 145352UL
#define PACMAN_EATFRUIT_LENGTH 1752
#define PACMAN_EATFRUIT_FREQ 8000
#define PACMAN_EATGHOST 147104UL
#define PACMAN_EATGHOST_LENGTH 2288
#define PACMAN_EATGHOST_FREQ 8000
#define ASSETS_END 149392UL
#define LOAD_ASSETS()  (GD.safeload("assets.gd2"))

static const shape_t PCMSP_SHAPE = {0, 13, 117, 0};
static const shape_t RED_SHAPE = {1, 14, 14, 0};
static const shape_t YELLOW_SHAPE = {2, 14, 14, 0};
static const shape_t PINK_SHAPE = {3, 14, 14, 0};
static const shape_t BLUE_SHAPE = {4, 14, 14, 0};
static const shape_t WHITEGHOST_SHAPE = {5, 14, 14, 0};
static const shape_t BLUEGHOST_SHAPE = {6, 14, 14, 0};
static const shape_t POWERP_SHAPE = {7, 14, 14, 0};
static const shape_t SADMAP_SHAPE = {8, 240, 272, 0};
