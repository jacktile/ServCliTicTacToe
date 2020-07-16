/**
 * player_page.hpp
 *
 * Definition of the page that will be sent to each user. There
 */

#ifndef player_page_hpp

typdef char* page;
class Player_Page
{
	private:
		int current_score;	// keeping track of the player's score 
		bool x_or_o;		// 0 for x, 1 for o
	public:
		player_page();
		page get_new_page();
		int update_score();
		int get_score();
};


#endif 
