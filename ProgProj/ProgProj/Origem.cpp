#include <iostream>
using namespace std;
void board() // é possivel que tenhamos de mover esta funcao para outro file 
{
	const int width = 60;
	const int height = 25;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++) // para fazer os mapas mudamos as condicoes em todas as barreiras menos as laterais e superiores
		{
			if (i == 0 || i == (height - 1))// barreiras superiores
				cout << "X";
			else if (i % 6 == 0 && j <= (2 * width / 3)) // faz barreiras lado esquerdo (cobrem 2/3 da largura)
				cout << "X";
			else if ((i + 3) % 6 == 0 && j >= (1 * width / 3)) //  faz barreiras do lado direito 
				cout << "X";
			else if (j == 0 || j == (width - 1)) // barreiras laterais
				cout << "X";
			else
				cout << " ";
		}
		cout << endl;
	}
	return;
}
void play()
{
	int maze_number;
	cout << "chooser the number of the maze: ";
	cin >> maze_number;
	board();
	//aqui começam as cenas de criação de file.
	return;
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