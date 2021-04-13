#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
void user_input(string player)
{
	int x=0, y=0; // coordenadas terao de ser incializadas dependendo do mapa ( se nao me engano o eixo dos y aponta para baixo e o x para a direita logo qnd vamos pra baixo somamos ao y)
	string inp; //a posição do player vai ser uma string x y separada por um " ", so precisamos fazer algo pra pegar isso.
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
	return ;
}
void play(vector<vector<char>> &maze, vector<string> &robots,string player)
{
	return;
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
		cout << "choose the maze number (01 to 99):";
		cin >> numero;// vai ser preciso dar fill para aceitar 1 digito ou 2 digitos (ex: 1 e 01)
		ficheiro = "MAZE_" + numero + ".TXT";
		mapa.open(ficheiro);
		if (mapa.is_open())
		{
			int maze_height, maze_length;
			int	number_of_robots = 0;
			string player_pos;
			char x;
			mapa >> maze_height >> x >> maze_length;
			vector<vector<char>> maze(maze_height, vector<char>(maze_length));		
			mapa >> noskipws;
			for (int i = 0; i < maze_height; i++) //this puts the maze into the vector
			{
				getline(mapa, mapeamento);
				for (int j = 0; j < maze_length; j++)
				{
					mapa >> maze[i][j];
					if (maze[i][j] == 'R')
					{
						number_of_robots++;
					}
					else if (maze[i][j] == 'H')
					{
						player_pos = to_string(i) + " " + to_string(j);
					}
				}
			}
			mapa.close();
			vector<string> robots(number_of_robots+1);
			int robot_id = 1;
			for (int i = 0; i < maze_height; i++) //this creates an id for each robot and saves its position
			{
				for (int j = 0; j < maze_length; j++)
				{
					if (maze[i][j] == 'R')
					{
						robots[robot_id] = to_string(i) + " " + to_string(j); 
						robot_id++;
					}
				}
			}		
			error = false;
			play(maze,robots,player_pos);
		}
		else
		{
			cout << "not a valid maze number, please try again." << endl;
		}
	}
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