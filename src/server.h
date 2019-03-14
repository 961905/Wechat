#include "user.h"
#include "users.h"
#include "groups.h"
#include "io_engine.h"

typedef struct ServerConfig {
    int bindPort;
} ServerConfig_t;


typedef struct Server {
    Users_t *users;
    Groups_t *groups;
    IoEngine_t *ioEngine;
} Server_t;


Server_t *NewServer(ServerConfig_t ServerConfig);


int ServerStart(Server_t *server);