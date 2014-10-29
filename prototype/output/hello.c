#include <stdio.h>
#include <string.h>
#include "mongoose.h"

struct redLED{
char title[30];
int minInclusive;
int value;
};
struct redLED redLED;

struct greenLED{
char title[30];
int minInclusive;
int value;
};
struct greenLED greenLED;


static int ev_handler(struct mg_connection *conn, enum mg_event ev) {
switch (ev) {
case MG_AUTH: return MG_TRUE;
case MG_REQUEST:

char buffer_redLED[50];
sprintf(buffer_redLED, "%s %d\n", redLED.title, redLED.value);
mg_printf_data(conn, buffer_redLED, conn->uri);
char buffer_greenLED[50];
sprintf(buffer_greenLED, "%s %d\n", greenLED.title, greenLED.value);
mg_printf_data(conn, buffer_greenLED, conn->uri);

return MG_TRUE;
default: return MG_FALSE;
}
}
int main(void) {
struct mg_server *server; 


strcpy(redLED.title, "Red LED");
redLED.minInclusive = 0;
redLED.value = 0;

strcpy(greenLED.title, "Green LED");
greenLED.minInclusive = 0;
greenLED.value = 1;


// Create and configure the server
server = mg_create_server(NULL, ev_handler);
mg_set_option(server, "listening_port", "8282");
// Serve request. Hit Ctrl-C to terminate the program
printf("Starting on port %s\n", mg_get_option(server, "listening_port"));
for (;;) {
mg_poll_server(server, 1000);
}
// Cleanup, and free server instance
mg_destroy_server(&server);
return 0;
}
