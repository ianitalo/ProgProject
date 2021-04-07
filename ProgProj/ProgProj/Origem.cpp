#include <iostream>
using namespace std;
void play()
{
	int maze_number;
	cout << "chooser the number of the maze: ";
	cin >> maze_number;
	//aqui começam as cenas de criação de file.
}
void menu()
{
	unsigned short answer;
	cout << "choose :" << endl << "1 for Rules" << endl << "2 for Play" << endl << "0 for Exit" << endl;
	cin >> answer;
	if (answer == 1)
	{
		cout << "You will be placed in a maze made up of high-voltage fences." << endl <<
			"There are robots that will try to destroy you." << endl <<
			"The only way you have to destroy them (and win the game) " << endl <<
			"is to make them crash with each other or make them crash" << endl <<
			"with the eletric fences (sorry, you can not punch them)." << endl <<
			"If you are the one hiting the robots or colliding with the fences you die." << endl <<
			"Every time you make a move the robots will also make a move going to your direction by the shortest path" << endl <<
			"(thats how you trick them). The robots have no vision sensors but" << endl <<
			"they have an accurate odour sensor that allows them to follow the player!" << endl << endl << endl <<
			"you can only move to one of the 8 neighbour cells of your current cell." << endl <<
			"these are the letters you can use to move :" << endl <<
			"Q           W            E" << endl << endl <<
			"A          you           D" << endl << endl <<
			"Z           X            C" << endl << endl <<
			"you can also stay in the same place by choosing 'S'" << endl << endl;
		menu();
	} 
	else if (answer == 2)
	{
		play();
	}
	else if (answer == 0)
	{
		return;
	}
}
int main()
{
	menu();
	return 0;
}