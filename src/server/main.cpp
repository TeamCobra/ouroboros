#include "ouroboros_server.h"
#include <iostream>
#include <unistd.h>

using namespace std;
using namespace ouroboros;

int main()
{
	ouroboros_server s;
	cout << s.get("server")->getJSON() << endl;
	s.start();
	sleep(10);
	s.stop();
	return 0;
}
