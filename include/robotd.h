#pragma once

#include <stdint.h>

#define TMP_BUF_SIZE 1024  // MUST be a multiple of 4
#define RECV_BUF_SIZE 1024
#define REQ_DATA_MAX_LENGTH 128
#define MAX_NUM_CLIENTS 4

#define WS_OPCODE_CONTINUATION 0x00
#define WS_OPCODE_TEXT 0x01
#define WS_OPCODE_BIN 0x02
#define WS_OPCODE_CLOSE 0x08
#define WS_OPCODE_PING 0x09
#define WS_OPCODE_PONG 0x0A

struct robotd_client_;
typedef struct robotd_client_ robotd_client;

void robotd_init(uint32_t port);
void robotd_init_ap(char *ssid);
void robotd_set_websocket_receive_cb(void (*cb)(robotd_client *pclient,
    uint8_t opcode, char *data, size_t length));
void robotd_websocket_send(robotd_client *pclient, uint8_t opcode, char *data,
    size_t length);
void robotd_websocket_send_all(uint8_t opcode, char *data, size_t length);

