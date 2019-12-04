#include "echo_client.h"

void str_to_uint16(char* str, uint16_t* ret) {
    char *end;
    intmax_t val = strtoimax(str, &end, 10);
    *ret = (uint16_t) val;
    return;
}

void print_IP(uint8_t* ip) {
  printf("%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
  return;
}

void parse_IP(char* ip, uint8_t* out) {
  out[0] = (uint8_t)atoi(strtok(ip, "."));
  for(int i = 1; i < 4; i++) {
    out[i] = (uint8_t)atoi(strtok(NULL, "."));
  }
  return;
}
