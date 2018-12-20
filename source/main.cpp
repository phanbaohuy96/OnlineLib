#include "ServerSocket.h"
#include "ClientSocket.h"
#include "conio.h"

//global 
ServerSocket::SocketType type = ServerSocket::SocketType::CLIENT;
const char *ip = "";
int port = -1;

// --Type Client --RemoteIP 127.0.0.1 --Port 54000
void ParseArgv(int argc, char *argv[])
{
	cout << "#######################################" << endl;
	cout << "# There were " << argc << " parameters\n";
	if (argc < 3)
		cerr << "Argv is invalid..." << endl;
	for (int i = 1; i<argc; i = i + 2)
	{
		string arg = argv[i];
		if (arg == "--Port")
		{
			string argC = argv[i + 1];
			port = atoi(argC.c_str());
			cout << "# Port is: " << port << endl;
		}
		else if (arg == "--RemoteIP")
		{
			ip = argv[i + 1];
			cout << "# Remote ip is: " << ip << endl;
		}
		else if (arg == "--Type")
		{
			string argC = argv[i + 1];
			if (argC == "Server")
			{
				type = ServerSocket::SocketType::SERVER;
				cout << "# Server type." << endl;
			}
			else
			{
				cout << "# Client type." << endl;
			}
		}
	}
	cout << "#######################################" << endl;
}

int main(int argc, char *argv[])
{		
	ParseArgv(argc, argv);
	if (type == ServerSocket::SocketType::CLIENT)
	{
		ClientSocket *client = new ClientSocket(ip, port);

		client->MessageListening();

		client->Sendmessage();

		client->Shutdown();
	}
	else 
	{
		ServerSocket *server = new ServerSocket(port);

		server->Listening();

		server->SocketLoop();

		server->Shutdown();
	}

	cout << "\nPress any key to exit...";
	_getch();
	return 0;
}