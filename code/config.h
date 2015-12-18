#ifndef CONFIG_H
#define CONFIG_H

// rozmiar okna

#define WINDOW_WIDTH 1134
#define WINDOW_HEIGHT 670

#define CANVAS_WIDTH 910
#define CANVAS_HEIGHT 650
#define CANVAS_PADDING 10

// ogolnie przyjete ustawienia

#define MAX_HEALTH 100
#define INIT_POWER 30

// czasy

#define CLIENT_SEND_INTERVAL 80
#define SERVER_SEND_INTERVAL 200

// numery id elementów planszy
// id o numerze 0 nie jest brany pod uwagę!!!

#define EMPTY_BOARD_FIELD_ID 0
#define DIRT_BOARD_FIELD_ID 1
#define SAND_BOARD_FIELD_ID 2
#define GRASS_BOARD_FIELD_ID 3
#define FLOWERGRASS_BOARD_FIELD_ID 4
#define WALL_BOARD_FIELD_ID 5
#define WATER_BOARD_FIELD_ID 6
#define TANK_BOARD_FIELD_ID 7
#define SHIELD_BOARD_FIELD_ID 8
#define BULLET_BOARD_FIELD_ID 9
#define BOOM_1_BOARD_FIELD_ID 10
#define BOOM_2_BOARD_FIELD_ID 11
#define BOOM_3_BOARD_FIELD_ID 12

#define BOARD_FIELD_ID(item) item##_BOARD_FIELD_ID

// ustawienia planszy

#define BOARD_COLS 14
#define BOARD_ROWS 10
#define BOARD_FIELD_WIDTH 65
#define BOARD_FIELD_HEIGHT 65
#define BOARD_FIELD_PATH "../img/sprites/%1.png"
#define BOARD_FIELDS_LENGTH 12

#endif // CONFIG_H
