#ifndef CONFIG_H
#define CONFIG_H

/**
* Nagłówek konfiguracyjny - zawiera define'y
*/

// logika

#define SPEEDSHOT 3

// nazwa gracza

#define NAME_REGEX "^[a-zA-Z0-9_\\.]{1,16}$"

// rozmiar okna

#define WINDOW_WIDTH 1134
#define WINDOW_HEIGHT 670

#define CANVAS_WIDTH 910
#define CANVAS_HEIGHT 650
#define CANVAS_PADDING 10

// ogolnie przyjete ustawienia

#define MAX_HEALTH 100
#define INIT_POWER 10
#define MAX_PLAYERS 8

// czasy w milisekundach

#define CLIENT_REDRAW_INTERVAL 17
#define CLIENT_SEND_INTERVAL 80
#define SERVER_SEND_INTERVAL 200
#define CLIENT_CONNECTION_TIMEOUT 10000

// numery id elementów planszy
// id o numerze 0 nie jest brany pod uwagę!!!

#define EMPTY_BOARD_FIELD_ID 0
#define DIRT_BOARD_FIELD_ID 1
#define SAND_BOARD_FIELD_ID 2
#define GRASS_BOARD_FIELD_ID 3
#define FLOWERGRASS_BOARD_FIELD_ID 4
#define WALL_BOARD_FIELD_ID 5
#define THICK_WALL_BOARD_FIELD_ID 6
#define WATER_BOARD_FIELD_ID 7

#define BOOM_1_BOARD_FIELD_ID 8
#define BOOM_2_BOARD_FIELD_ID 9
#define BOOM_3_BOARD_FIELD_ID 10

#define TANK_BOARD_FIELD_ID 11
#define TANK_BLUE_BOARD_FIELD_ID 12
#define TANK_RED_BOARD_FIELD_ID 13
#define TANK_RED_ME_BOARD_FIELD_ID 14
#define TANK_BLUE_ME_BOARD_FIELD_ID 15

#define BULLET_BOARD_FIELD_ID 16

#define SHIELD_BOARD_FIELD_ID 17

#define BOARD_FIELD_ID(item) item##_BOARD_FIELD_ID

// ustawienia planszy

#define BOARD_COLS 14
#define BOARD_ROWS 10
#define BOARD_FIELD_WIDTH 65
#define BOARD_FIELD_HEIGHT 65
#define BOARD_SUBFIELDS 5
#define BOARD_FIELD_PATH ":/img/sprites/%1.png"
#define BOARD_FIELDS_LENGTH 17

// bledy

#define USER_NAME_IS_NOT_UNIQUE 1
#define SERVER_IS_FULL 2
#define SERVER_IS_EMPTY 3

// ramki

#define PLAYER_FRAME_SIZE 26
#define SHOT_FRAME_SIZE 10

#endif // CONFIG_H
