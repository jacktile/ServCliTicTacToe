/** SIMPLE SERVER 
 * Jackie - July 9, 2020
 *
 * SPECIFICATIONS:
 * Must accept clients/create player descriptors containing:
 * 	- Player's IP address 
 * 	- Player's player number (either 1 or 2)
 * 	- Players current score (initialized to 0)
 *
 * Must update each players screen with the new board 
 * Must only allow one player to submit their response at once 
 * 	- Send a greyed out board to the inactivate player
 * 	- Player currently submitting their score can only click on the boxes that have not yet been sent
 *
 * Tic-Tac toe algorithm
 * 	- Check if there are 3 vertically adjacent selections for each player 
 * 	- Check if there are 3 horizontally adjacent selections for each player
 * 	- Check diagonal selections for each player, for 3 selections 
 * 	- IF someone wins, depict their player number on the screen and end the process.
 */
#include <iostream>

typedef struct Player
{
	/**
	 * Stores information related to each individual player
	 */
	int player_num;
	int score;
	// need some way to reasonably store ip address

} Player;

int def_tic_tac_toe(int *tic_arr)
{
	/*
	 * Returns 0 if neither player wins
	 * If a player wins, their player ID number will be returned 
	 *
	 * tic_arr is array with 0, 1, 2 .. [] and other error info if needed
	 * - the size of this array is expected to be 9, no error checking
	 *
	 * Not an optimized algorithm, just implemented the first thing 
	 * come to mind
	 */

	// vertical check
	for (int j = 0; j < 3; j++)
	{
		if (tic_arr[j] == tic_arr[j+3] && tic_arr[j+3] == tic_arr[j+6] && tic_arr[j] != 0)
			return tic_arr[j];
	}

	// horizontal check
	for (int i = 0; i < 9; i = i+3)
	{
		if (tic_arr[i] == tic_arr[i+1] && tic_arr[i+1] == tic_arr[i+2] && tic_arr[i] != 0)
			return tic_arr[i];
	}
	
	// diagonal check
	if (tic_arr[0] == tic_arr[4] && tic_arr[4] == tic_arr[8] && tic_arr[0] != 0)
		return tic_arr[0];

	if (tic_arr[2] == tic_arr[4] && tic_arr[4] == tic_arr[6] && tic_arr[2] != 0) 
		return tic_arr[2];

	return -1;
}

int main()
{
	// temporary test array
	int test_arr[] = {0, 0, 1, 0, 0, 1, 0, 2, 1};
	std::cout << def_tic_tac_toe(test_arr) << "\n";
	return 0;
}
