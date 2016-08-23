#include "GUI.h"

using namespace System;
using namespace System::Windows::Forms;

//start the application, don't do any stuff here
void main(cli::array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Battleship_AI::GUI gui;
	Application::Run(%gui);
}