/* easteregg
*/


struct dungeon {
char *description;
unsigned char exit;
unsigned char n;
unsigned char s;
unsigned char w;
unsigned char e;
}

#define NORTH	0x01
#define SOUTH	0x02
#define WEST	0x04
#define EAST	0x08


struct dungeon dungeons[]={
0{ "inside the buspirate", NORTH|WEST|SOUTH|EAST, 1, 6, 2, 7 },
1{ "infront of a diode", SOUTH, 0, 0, 0, 0 },
2{ "near a I2C device", NORTH|WEST, 3, 0, 4, 0 },
3{ "near a pullup resistor", SOUTH, 0, 2, 0, 0 },
4{ "poking into the internal of a I2C device", 0, 0, 0, 0, 0 },
5{ "standing besides the 3v3 regulator" 0, 0, 0, 0, 0 },
6{ "back in HiZ mode", 0, 0, 0, 0, 0 },
7{ "besides ICSP", WEST, EAST
8{ "behind C3"
9{ "in front of R23 and C20"
a{ "next to VR3