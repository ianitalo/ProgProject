#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <algorithm>
#include <cmath>
using namespace std;

void leader_board(unsigned number, string name, double rounded_time, string leader_string)
{
	vector<string> leaderboard_string;
	string score, time, trash1, trash2, screen_string;
	vector<double> DoubVec;

	// comments are mirrored for both parts of this if statement
	if (number >= 0 && number < 10) //this is to make inputs like 1 and 01 to be accepted
	{
		ofstream check("MAZE_0" + to_string(number) + "_WINNERS.TXT", ios::app); // check if the file exists without altering it, if it doesnt, create one
		check.close();

		ifstream collect("MAZE_0" + to_string(number) + "_WINNERS.TXT");
		if (!collect)
		{
			cout << "cannot open leaderboard."; //in case anything goes wrong, to avoid file corruption.
			return;
		}

		if (collect.is_open())
		{
			getline(collect, trash1);// ignore header
			getline(collect, trash2);//

			while (getline(collect, score))
			{
				leaderboard_string.push_back(score); // fill vector with relevant info from the leaderboard (previous names + scores)
			}
			for (int i = 0; i < leaderboard_string.size(); i++)// allows us to get the actual score value from the leaderboard's strings
			{
				for (int j = 21; j >= 16; j--)
				{
					if (leaderboard_string[i][j] == ' ' || leaderboard_string[i][j] == '-')
					{
						break;
					}
					else
					{
						time = leaderboard_string[i][j] + time;
					}
				}
				DoubVec.push_back(stoi(time));// each score is added to a vector
				time = "";
			}
		}

		if (leaderboard_string.size() == 0)// in case the file exists but is empty
		{
			leaderboard_string.push_back(leader_string);
		}

		bool last_score = false;

		for (int i = 0; i < DoubVec.size(); i++)// check if current time is better than each of the times on the leader board, if it is add it to the 
		{										// vector on that position. This automatically sorts the board.
			if (rounded_time <= DoubVec[i])
			{
				leaderboard_string.insert(leaderboard_string.begin() + i, leader_string);
				break;
			}
			if (i == DoubVec.size() - 1)
			{
				last_score = true;
			}
		}

		if (last_score)
		{
			leaderboard_string.push_back(leader_string); // in case the current time is the worst one it will be added to the bottom of the vector
		}

		ofstream updated("MAZE_0" + to_string(number) + "_WINNERS.TXT");
		updated <<
			"Player         –  Time" << endl <<
			"----------------------" << endl;
		for (int i = 0; i < leaderboard_string.size(); i++)
		{
			updated << leaderboard_string[i] << endl; //write updated file with info from vector
		}
		updated.close();

		ifstream screen("MAZE_0" + to_string(number) + "_WINNERS.TXT");
		while (getline(screen, screen_string))
		{
			cout << screen_string << endl;  //display leaderboard
		}
	}
	else
	{
		ofstream check("MAZE_" + to_string(number) + "_WINNERS.TXT", ios::app);
		check.close();

		ifstream collect("MAZE_" + to_string(number) + "_WINNERS.TXT");
		if (!collect)
		{
			cout << "cannot open leaderboard.";
			return;
		}

		if (collect.is_open())
		{
			getline(collect, trash1);
			getline(collect, trash2);

			while (getline(collect, score))
			{
				leaderboard_string.push_back(score);
			}
			for (int i = 0; i < leaderboard_string.size(); i++)
			{
				for (int j = 21; j >= 16; j--)
				{
					if (leaderboard_string[i][j] == ' ' || leaderboard_string[i][j] == '-')
					{
						break;
					}
					else
					{
						time = leaderboard_string[i][j] + time;
					}
				}
				DoubVec.push_back(stoi(time));
				time = "";
			}
		}

		if (leaderboard_string.size() == 0)
		{
			leaderboard_string.push_back(leader_string);
		}

		bool last_score = false;

		for (int i = 0; i < DoubVec.size(); i++)
		{
			if (rounded_time <= DoubVec[i])
			{
				leaderboard_string.insert(leaderboard_string.begin() + i, leader_string);
				break;
			}
			if (i == DoubVec.size() - 1)
			{
				last_score = true;
			}
		}

		if (last_score)
		{
			leaderboard_string.push_back(leader_string);
		}

		ofstream updated("MAZE_" + to_string(number) + "_WINNERS.TXT");
		updated <<
			"Player         –  Time" << endl <<
			"----------------------" << endl;
		for (int i = 0; i < leaderboard_string.size(); i++)
		{
			updated << leaderboard_string[i] << endl;
		}
		updated.close();

		ifstream screen("MAZE_" + to_string(number) + "_WINNERS.TXT");
		while (getline(screen, screen_string))
		{
			cout << screen_string << endl;
		}
	}
}

void display(const vector<vector<char>>& maze) //displays maze with updated positions
{
	for (size_t i = 0; i < maze.size(); i++)
	{
		for (size_t j = 0; j < maze[i].size(); j++)
		{
			cout << maze[i][j];
		}
		cout << endl;
	}
}
void gameover(string player, const vector<vector<char>>& maze, unsigned number, std::chrono::high_resolution_clock::time_point start)
{
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> time = end - start;
	string name;
	display(maze);
	if (player != "Dead")
	{
		cout << "you win :) " << endl;
		cout << "time elapsed: " << time.count() << " s" << endl;
		cout << "please enter your name here (note that the name must have a size between 1 and 15 chars.): ";
		cin.ignore();
		getline(cin, name);

		while (name.size() > 15 || name.size() < 1)
		{
			cout << "Invalid name size! please try again." << endl;
			getline(cin, name);
		}

		int num_spaces = 15 - name.size(); // 
		string spaces(num_spaces, ' ');    //  fill name with " " untill desired length ( so it fits the leaderboard )
		name = name + spaces;              //

		double rounded_time = round(time.count() * 1000.0) / 1000.0; // rounding time to 3 digits
		string rounded_string = to_string(rounded_time);
		for (int i = rounded_string.size() - 1; i > 0; i--) // even after rounding, a few of the 0s to the right are considered in the .size() function, this for loop is a work-around.
		{
			if (rounded_string[i] == '0')
			{
				rounded_string.pop_back();
			}
			else
			{
				break;
			}
		}
		int time_size = rounded_string.size();

		num_spaces = 0;                                 // 
		num_spaces = 6 - time_size;                     // num of " " to get desired length 
		string time_spaces(num_spaces, ' ');			//

		string leader_string = name + "-" + time_spaces + rounded_string;

		leader_board(number, name, rounded_time, leader_string);

	}
	else
	{
		cout << "time elapsed: " << time.count() << " s" << endl;
		cout << "you lose :( " << endl;
	}
}
bool collision_with_robots(const string player, const vector<string>& robots)
{
	for (size_t i = 1; i < robots.size(); i++)
	{
		if (robots[i] == player)
		{
			return true;
		}
	}
	return false;
}
void kill_backstabed_robots(vector<string>& robots, const int robots_indice1, const int robots_indice2)
{
	for (size_t i = 1; i < robots.size(); i++)
	{
		if (robots[i] == to_string(robots_indice1) + " " + to_string(robots_indice2))
		{
			robots[i] = "Dead";
		}
	}
}
bool any_robots_alive(const vector<string>& robots)
{
	for (size_t i = 1; i < robots.size(); i++)
	{
		if (robots[i] != "Dead")
		{
			return true;
		}
	}
	return false;
}
void move_robots(string& player, vector<vector<char>>& maze, vector<string>& robots, unsigned numero, std::chrono::high_resolution_clock::time_point start)
{
	int player_indice1, player_indice2, robots_indice1, robots_indice2;


	size_t space = player.find(" ");
	if (player != "Dead")
	{
		player_indice1 = stoi(player.substr(0, space));
		player_indice2 = stoi(player.substr(space));


		for (size_t i = 1; i < robots.size(); i++)
		{
			if (robots[i] == "Dead") //the robot does not move if he is dead
			{
				continue;
			}
			else
			{
				space = robots[i].find(" ");
				robots_indice1 = stoi(robots[i].substr(0, space)); //get the position of the robot[i]
				robots_indice2 = stoi(robots[i].substr(space));

				if (player_indice1 < robots_indice1 && player_indice2 < robots_indice2) // robots follow the player blindly
				{
					robots_indice1 -= 1;
					robots_indice2 -= 1;

					if (maze[robots_indice1][robots_indice2] == 'H' || maze[robots_indice1][robots_indice2] == 'h')
					{
						maze[robots_indice1][robots_indice2] = 'h';
						player = "Dead";
					}
					else if (maze[robots_indice1][robots_indice2] != ' ')
					{
						if (maze[robots_indice1][robots_indice2] == 'R')
						{
							kill_backstabed_robots(robots, robots_indice1, robots_indice2);
						}
						robots[i] = "Dead";
						maze[robots_indice1][robots_indice2] = 'r';
					}
					else
					{
						maze[robots_indice1][robots_indice2] = 'R';
						robots[i] = to_string(robots_indice1) + " " + to_string(robots_indice2);
					}
				}
				else if (player_indice1 < robots_indice1 && player_indice2 == robots_indice2)
				{
					robots_indice1 -= 1;

					if (maze[robots_indice1][robots_indice2] == 'H' || maze[robots_indice1][robots_indice2] == 'h')
					{
						maze[robots_indice1][robots_indice2] = 'h';
						player = "Dead";
					}
					else if (maze[robots_indice1][robots_indice2] != ' ')
					{
						if (maze[robots_indice1][robots_indice2] == 'R')
						{
							kill_backstabed_robots(robots, robots_indice1, robots_indice2);
						}
						robots[i] = "Dead";
						maze[robots_indice1][robots_indice2] = 'r';
					}
					else
					{
						maze[robots_indice1][robots_indice2] = 'R';
						robots[i] = to_string(robots_indice1) + " " + to_string(robots_indice2);
					}
				}
				else if (player_indice1 < robots_indice1 && player_indice2 > robots_indice2)
				{
					robots_indice1 -= 1;
					robots_indice2 += 1;

					if (maze[robots_indice1][robots_indice2] == 'H' || maze[robots_indice1][robots_indice2] == 'h')
					{
						maze[robots_indice1][robots_indice2] = 'h';
						player = "Dead";
					}
					else if (maze[robots_indice1][robots_indice2] != ' ')
					{
						if (maze[robots_indice1][robots_indice2] == 'R')
						{
							kill_backstabed_robots(robots, robots_indice1, robots_indice2);
						}
						robots[i] = "Dead";
						maze[robots_indice1][robots_indice2] = 'r';
					}
					else
					{
						maze[robots_indice1][robots_indice2] = 'R';
						robots[i] = to_string(robots_indice1) + " " + to_string(robots_indice2);
					}
				}
				else if (player_indice1 == robots_indice1 && player_indice2 < robots_indice2)
				{
					robots_indice2 -= 1;

					if (maze[robots_indice1][robots_indice2] == 'H' || maze[robots_indice1][robots_indice2] == 'h')
					{
						maze[robots_indice1][robots_indice2] = 'h';
						player = "Dead";
					}
					else if (maze[robots_indice1][robots_indice2] != ' ')
					{
						if (maze[robots_indice1][robots_indice2] == 'R')
						{
							kill_backstabed_robots(robots, robots_indice1, robots_indice2);
						}
						robots[i] = "Dead";
						maze[robots_indice1][robots_indice2] = 'r';
					}
					else
					{
						maze[robots_indice1][robots_indice2] = 'R';
						robots[i] = to_string(robots_indice1) + " " + to_string(robots_indice2);
					}
				}
				else if (player_indice1 == robots_indice1 && player_indice2 > robots_indice2)
				{
					robots_indice2 += 1;

					if (maze[robots_indice1][robots_indice2] == 'H' || maze[robots_indice1][robots_indice2] == 'h')
					{
						maze[robots_indice1][robots_indice2] = 'h';
						player = "Dead";
					}
					else if (maze[robots_indice1][robots_indice2] != ' ')
					{
						if (maze[robots_indice1][robots_indice2] == 'R')
						{
							kill_backstabed_robots(robots, robots_indice1, robots_indice2);
						}
						robots[i] = "Dead";
						maze[robots_indice1][robots_indice2] = 'r';
					}
					else
					{
						maze[robots_indice1][robots_indice2] = 'R';
						robots[i] = to_string(robots_indice1) + " " + to_string(robots_indice2);
					}
				}
				else if (player_indice1 > robots_indice1 && player_indice2 < robots_indice2)
				{
					robots_indice1 += 1;
					robots_indice2 -= 1;

					if (maze[robots_indice1][robots_indice2] == 'H' || maze[robots_indice1][robots_indice2] == 'h')
					{
						maze[robots_indice1][robots_indice2] = 'h';
						player = "Dead";
					}
					else if (maze[robots_indice1][robots_indice2] != ' ')
					{
						if (maze[robots_indice1][robots_indice2] == 'R')
						{
							kill_backstabed_robots(robots, robots_indice1, robots_indice2);
						}
						robots[i] = "Dead";
						maze[robots_indice1][robots_indice2] = 'r';
					}
					else
					{
						maze[robots_indice1][robots_indice2] = 'R';
						robots[i] = to_string(robots_indice1) + " " + to_string(robots_indice2);
					}
				}
				else if (player_indice1 > robots_indice1 && player_indice2 == robots_indice2)
				{
					robots_indice1 += 1;

					if (maze[robots_indice1][robots_indice2] == 'H' || maze[robots_indice1][robots_indice2] == 'h')
					{
						maze[robots_indice1][robots_indice2] = 'h';
						player = "Dead";
					}
					else if (maze[robots_indice1][robots_indice2] != ' ')
					{
						if (maze[robots_indice1][robots_indice2] == 'R')
						{
							kill_backstabed_robots(robots, robots_indice1, robots_indice2);
						}
						robots[i] = "Dead";
						maze[robots_indice1][robots_indice2] = 'r';
					}
					else
					{
						maze[robots_indice1][robots_indice2] = 'R';
						robots[i] = to_string(robots_indice1) + " " + to_string(robots_indice2);
					}
				}
				else if (player_indice1 > robots_indice1 && player_indice2 > robots_indice2)
				{
					robots_indice1 += 1;
					robots_indice2 += 1;

					if (maze[robots_indice1][robots_indice2] == 'H' || maze[robots_indice1][robots_indice2] == 'h')
					{
						maze[robots_indice1][robots_indice2] = 'h';
						player = "Dead";
					}
					else if (maze[robots_indice1][robots_indice2] != ' ')
					{
						if (maze[robots_indice1][robots_indice2] == 'R')
						{
							kill_backstabed_robots(robots, robots_indice1, robots_indice2);
						}
						robots[i] = "Dead";
						maze[robots_indice1][robots_indice2] = 'r';
					}
					else
					{
						maze[robots_indice1][robots_indice2] = 'R';
						robots[i] = to_string(robots_indice1) + " " + to_string(robots_indice2);
					}
				}
			}
		}
	}
	if (player == "Dead" || !any_robots_alive(robots)) //in case robots killed the player or robots died
	{
		gameover(player, maze, numero, start);
		return;
	}
}
void user_input(string& player, vector<vector<char>>& maze, vector<string>& robots)
{
	size_t space = player.find(" ");
	bool error = true;
	int player_indice1, player_indice2, robots_indice1, robots_indice2;
	char inp;
	while (error)
	{
		if (player != "Dead")
		{
			player_indice1 = stoi(player.substr(0, space));// player coords as ints
			player_indice2 = stoi(player.substr(space));   //
		}
		error = false;
		cout << "your move: ";
		cin >> inp;
		if (!cin.good() || (cin.peek() != EOF && cin.peek() != '\n'))
		{
			cout << "invalid input, try again." << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			error = true;
		}
		else if (inp == 'q' || inp == 'Q')
		{
			player_indice1 -= 1;
			player_indice2 -= 1;
		}
		else if (inp == 'w' || inp == 'W')
		{
			player_indice1 -= 1;
		}
		else if (inp == 'e' || inp == 'E')
		{
			player_indice1 -= 1;
			player_indice2 += 1;
		}
		else if (inp == 'a' || inp == 'A')
		{
			player_indice2 -= 1;
		}
		else if (inp == 's' || inp == 'S')
		{
			//dont move
		}
		else if (inp == 'd' || inp == 'D')
		{
			player_indice2 += 1;
		}
		else if (inp == 'z' || inp == 'Z')
		{
			player_indice1 += 1;
			player_indice2 -= 1;
		}
		else if (inp == 'x' || inp == 'X')
		{
			player_indice1 += 1;
		}
		else if (inp == 'c' || inp == 'C')
		{
			player_indice1 += 1;
			player_indice2 += 1;
		}
		else
		{
			cout << "invalid input, try again." << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			error = true;
		}
		if ((maze[player_indice1][player_indice2] == 'r') && !error) //player cant move to cells occupied by dead robots
		{
			cout << "you can not move this way, try again." << endl;
			error = true;
		}
		else if (!error)
		{
			player = to_string(player_indice1) + " " + to_string(player_indice2); //valid move updates player to check collision

			if (maze[player_indice1][player_indice2] != ' ' || collision_with_robots(player, robots)) //player suicide
			{
				for (size_t i = 1; i < robots.size(); i++) //redraw robots in the maze in case player suicides
				{
					if (robots[i] != "Dead")
					{
						robots_indice1 = stoi(robots[i].substr(0, space)); //get the position of the robot[i]
						robots_indice2 = stoi(robots[i].substr(space));
						maze[robots_indice1][robots_indice2] = 'R';
					}
				}
				maze[player_indice1][player_indice2] = 'h';
				player = "Dead"; //in this case	gameover() should not be called because move_robots() will also call it		
			}
			else
			{
				maze[player_indice1][player_indice2] = 'H';
				player = to_string(player_indice1) + " " + to_string(player_indice2);
			}
		}
	}

}
void maze_clear(vector<vector<char>>& maze) // clears the maze of all entities excepts walls, so that they can be written in the new position
{

	for (size_t i = 0; i < maze.size(); i++)
	{
		for (size_t j = 0; j < maze[i].size(); j++)
		{
			if (maze[i][j] == 'R' || maze[i][j] == 'H')
			{
				maze[i][j] = ' ';
			}
		}
	}
	return;
}
void play(vector<vector<char>>& maze, vector<string>& robots, string player, unsigned number, std::chrono::high_resolution_clock::time_point start)
{
	while (player != "Dead" && any_robots_alive(robots)) //game ends if the player dies or if there are no robots left alive
	{
		display(maze);
		maze_clear(maze);
		user_input(player, maze, robots);
		move_robots(player, maze, robots, number, start);

	}
}
void maze_selection()
{
	string mapping, file;
	unsigned number;
	bool error = true;
	ifstream map;
	while (error)
	{
		cout << "choose the maze number (01 to 99):";
		do
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cin >> number;
			if (!cin.good())
			{
				cout << "not a valid maze number, please try again." << endl;
			}
		} while (!cin.good());
		if (number >= 0 && number < 10) //this is to make inputs like 1 and 01 to be accepted
		{
			file = "MAZE_0" + to_string(number) + ".TXT";
		}
		else
		{
			file = "MAZE_" + to_string(number) + ".TXT";
		}
		map.open(file);
		if (map.is_open())
		{
			int maze_height, maze_length, number_of_robots = 0;
			string player_pos;
			char x;
			map >> maze_height >> x >> maze_length;
			vector<vector<char>> maze(maze_height, vector<char>(maze_length));
			map >> noskipws;
			for (int i = 0; i < maze_height; i++) //this puts the maze into the vector
			{
				getline(map, mapping);
				for (int j = 0; j < maze_length; j++)
				{
					map >> maze[i][j];
					if (maze[i][j] == 'R') // finds robots
					{
						number_of_robots++;
					}
					else if (maze[i][j] == 'H') // finds the hero and saves its position
					{
						player_pos = to_string(i) + " " + to_string(j);
					}
				}
			}
			map.close();
			vector<string> robots(number_of_robots + 1);
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
			auto start = std::chrono::high_resolution_clock::now();
			play(maze, robots, player_pos, number, start);
		}
		else
		{
			cout << "not a existing maze number, please try again." << endl;
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
			cin.ignore(INT_MAX, '\n');
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
	menu();
	return 0;
}