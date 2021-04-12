#include <iostream>
#include <fstream>
#include <string>
using namespace std;
void user_input()
{
	int x = 0, y = 0; // coordenadas terao de ser incializadas dependendo do mapa ( se nao me engano o eixo dos y aponta para baixo e o x para a direita logo qnd vamos pra baixo somamos ao y)
	string inp;
	cin >> inp;
	
	
	if (inp == "q" || inp == "Q")
	{
		x -= 1;
		y -= 1;
	}
	else if (inp == "w" || inp == "W")
	{
		y -= 1;
	}
	else if (inp == "e" || inp == "E")
	{
		x += 1;
		y -= 1;
	}
	else if (inp == "a" || inp == "A")
	{
		x -= 1;
	}
	else if (inp == "s" || inp == "S")
	{
		//continue;
	}
	else if (inp == "d" || inp == "D")
	{
		x += 1;
	}
	else if (inp == "z" || inp == "Z")
	{
		x -= 1;
		y += 1;
	}
	else if (inp == "x" || inp == "X")
	{
		y += 1;
	}
	else if (inp == "c" || inp == "C")
	{
		x += 1;
		y += 1;
	}
	else
	{
		cout << "invalid input, try again.";
	}
}


void maze_selection()
{
	string mapeamento;
	string numero;
	bool error = true;
	string ficheiro;
	ifstream mapa;
	while (error)
	{
		cout << "choose the maze number (01, 02 or 03):";
		cin >> numero;// vai ser preciso dar fill para aceitar 1 digito ou 2 digitos (ex: 1 e 01)
		ficheiro = "MAZE_" + numero + ".TXT";
		mapa.open(ficheiro);
		if (mapa.is_open())
		{
			cout << "this is the maze you choose." << endl;
			while (getline(mapa, mapeamento))
			{
				cout << mapeamento << endl;
			}
			error = false;
			//play();
		}
		else
		{
			cout << "not a valid maze number, please try again." << endl;
		}
	}
	mapa.close();
}
void play()
{
	//int maze_number;
	//cout << "chooser the number of the maze: ";
	//cin >> maze_number;
	//aqui come�am as cenas de cria��o de file.
	return;
}
void menu()
{
	unsigned short answer;
	bool error = false;
	do 
	{
		cout <<
			"--------------" << endl <<
			"|choose :    |" << endl <<
			"|1 for Rules |" << endl <<
			"|2 for Play  |" << endl <<
			"|0 for Exit  |" << endl <<
			"--------------" << endl;
		cin >> answer;
		if (!cin.good())
		{
			cout << "this is not a valid choice, please try again." << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			error = true;
		}
		else if (answer == 1)
		{
			cout << "----------------------------------------------------------------------------------------------------------" << endl <<
				"|                                                RULES                                                   |" << endl <<
				"----------------------------------------------------------------------------------------------------------" << endl <<
				"|You will be placed in a maze made up of high-voltage fences.                                            |" << endl <<
				"|There are robots that will try to destroy you.                                                          |" << endl <<
				"|The only way you have to destroy them (and win the game)                                                |" << endl <<
				"|is to make them crash with each other or make them crash                                                |" << endl <<
				"|with the eletric fences (sorry, you can not punch them).                                                |" << endl <<
				"|If you are the one hiting the robots or colliding with the fences you die.                              |" << endl <<
				"|Every time you make a move the robots will also make a move going to your direction by the shortest path|" << endl <<
				"|(thats how you trick them). The robots have no vision sensors but                                       |" << endl <<
				"|they have an accurate odour sensor that allows them to follow the player!                               |" << endl <<
				"|                                                                                                        |" << endl <<
				"|                                                                                                        |" << endl <<
				"|you can only move to one of the 8 neighbour cells of your current cell.                                 |" << endl <<
				"|these are the letters you can use to move :                                                             |" << endl <<
				"|                                     Q           W            E                                         |" << endl <<
				"|                                                                                                        |" << endl <<
				"|                                     A          you           D                                         |" << endl <<
				"|                                                                                                        |" << endl <<
				"|                                     Z           X            C                                         |" << endl <<
				"|                                                                                                        |" << endl <<
				"|you can also stay in the same place by choosing 'S'.                                                    |" << endl <<
				"----------------------------------------------------------------------------------------------------------" << endl;
			menu();
			error = false;
		}
		else if (answer == 2)
		{
			maze_selection();
			error = false;
		}
		else if (answer == 0)
		{
			error = false;
			return;
		}
		else
		{
			cout << "this is not a valid choice, please try again." << endl;
			error = true;
		}
		} while (error);
	}
int main()
{
	//testes();
	menu();
	//maze_selection();
	//user_input();
	return 0;
}