# Data Server
We will now be implementing the first mechanisms to store user data. 

The tic tac toe selections will be stored in a boolean array with 9 indices. During each user's turn, the user will click a button related to their respective selection. If the selection is not available (i.e., another user selected it in a previous turn), then the user will be prompted to click a different button.

Each time the server receives a response from the players, the server will send an updated view of the browser. If an error occured destined to only one player, then the server will handle that.

====================================================

For future extraneous cases (which we will not yet consider):
What if more than one player tries to enter the server at once?
	Fork a new process
What if a player stops playing? 
	Timeout or have a "QUIT" button 

# Timeline 
[] Implement HTTP headers so that the HTML is properly formatted 
[] Organize CPP files for Tic-Tac-Toe game 
