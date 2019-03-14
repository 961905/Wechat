#include <string.h>
#include "users.h"
#include "server.h"

Server_t *NewServer(ServerConfig_t ServerConfig) {
    Server_t *server =(Server_t *)malloc(sizeof(Server_t ));
    memset(server,0, sizeof(Server_t ));
    server->ioEngine = NewIoEngine();
    server->users = NewUsers();
    server->groups = NewGroups();

    return server;
}

int ServerStart(Server_t *server) {

}



int main(){
    ServerConfig_t config;
    Server_t*server = NewServer(config);
    ServerStart(server);
}