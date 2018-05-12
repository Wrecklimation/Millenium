#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <iomanip>
#include <fstream>
#include <fcntl.h>

using namespace std;

string filename = ("data.txt");
int length = 100;
char * username = new char[length];
char * password = new char[length];
char * name = new char[length];
char * level = new char[length];
int score = 0;
int turns = 0;
bool jigsaw = false;
bool jigsaw2 = false;
bool sparkler = false;
bool crate = false;
bool rucksack = false;
bool key = false;
bool device = false;
bool pencil = false;
bool sketchbook = false;
bool vestry = false;
bool fuse = false;
bool myClock = false;

void destructor() {
	delete[] username;
	delete[] password;
	delete[] name;
	delete[] level;
}//cleans up after the program

void clearScreen() {
	if (system("clear") == -1) {
		cout << ("Whoopsies!! Looks like something went wrong trying to open the game.\n")
			 << ("Please close the terminal and clear some RAM and try again.\n")
			 << endl;
		destructor();
		exit(EXIT_FAILURE);
	}//if

	return;
}//function to open create and open the game

void gameIntro(bool show) {
	if (show) {
		for (int i = 0; i < 1000; i++) {
			cout << ("        +")
				 << setw(180)
				 << setfill('-')
				 << ("+")
				 << endl;
			for (int i = 0; i < 60; i++){
				if (i == 26) {
					cout << ("\t|                   |                  _    _      _                            _         ___  ____ _ _                  _                                      |                   |\n")
						 << ("\t|                   |                 | |  | |    | |                          | |        | \\/  (_) | |                (_)                                      |                   |\n")
						 << ("\t|                   |                 | |  | | ___| | ___ ___  _ __ ___   ___  | |_ ___   | .  . |_| | | ___ _ __  _ __  _ _   _ _ __ ___                       |                   |\n")
						 << ("\t|                   |                 | |/\\| |/ _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ | __/ _ \\  | |\\/| | | | |/ _ \\ '_ \\| '_ \\| | | | | '_ ` _ \\                      |                   |\n")
						 << ("\t|===================|                 \\  /\\  /  __/ | (_| (_) | | | | | |  __/ | || (_) | | |  | | | | |  __/ | | | | | | | |_| | | | | | |                     |===================|\n")
						 << ("\t|                   |                  \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___|  \\__\\___/  \\_|  |_/_|_|_|\\___|_| |_|_| |_|_|\\__,_|_| |_| |_|                     |                   |\n");
					i += 6;                                                                                             
				}//if
				if (((i % 10) == 0) && (i != 0)) {
					cout << ("\t|===================|")
						 << setw(160)
						 << setfill(' ')
						 << ("\t|===================|")
						 << endl;
				}//if
				cout << ('\t')
					 << ("|                   |")
					 << setw(160)
					 << setfill(' ')
					 << ("|                   |")
					 << endl;
			}//for
			cout << ("        +")
				 << setw(180)
				 << setfill('-')
				 << ("+")
				 << endl;
		}//for
		sleep(2);
		clearScreen();
	}//if
	else {
		cout << ("        +")
			 << setw(180)
			 << setfill('-')
			 << ("+")
			 << endl;
		cout << ("\t|                                                                 ___  ____ _ _                 _                                                                                   |\n")
			 << ("\t|                                                                |   \\/ (_) | |                (_)                                                                                  |\n")
			 << ("\t|                                                                | .  . |_| | | ___ _ __  _ __  _ _   _ _ __ ___                                                                    |\n")
			 << ("\t|                                                                | |\\/| | | | |/ _ \\ '_ \\| '_ \\| | | | | '_ ` _ \\                                                                   |\n")
			 << ("\t|                                                                | |  | | | | |  __/ | | | | | | | |_| | | | | | |                                                                  |\n")
			 << ("\t|                                                                \\_|  |_/_|_|_|\\___|_| |_|_| |_|_|\\__,_|_| |_| |_|                                                                  |")
			 << endl;                                                                                          
		cout << ("        +")
			 << setw(181)
			 << setfill('-')
			 << ("+\n")
			 << endl;
	}//eslse
	
	return;	 
}//function to start up the game

bool accountCheck() {
	string response = ("");
	string yes = ("y");
	string no = ("n");

	ASK:
		gameIntro(false);
		cout << ("Do you need to create a Millennium's account (y or n)? ");
		getline(cin, response);

		if (strcmp(yes.c_str(), response.c_str()) == 0) {
			return true;
		}//if
		else if (strcmp(no.c_str(), response.c_str()) == 0) {
			return false;
		}//if
		else {
			cout << ("Whoopsies!! Thats is an unknown response please try again.\n");
			sleep(2);
			clearScreen();
			goto ASK;
		}//else

		return true;
}//funtion that checks if they need to make an account

void makeAccount() {
	string usernameNew = ("");
	string passwordNew = ("");
	string nameNew = ("");
	string genderNew = ("");
	string raceNew = ("");
	string myClassNew = ("");
	string levelNew = ("0");
	string empty = ("");
	string male = ("Male");
	string female = ("Female");
	bool valid = false;

	ofstream data(filename, ios::out);

	while (!valid) {
		cout << ("Username: ");
		getline(cin, usernameNew);
		if (strcmp(usernameNew.c_str(), empty.c_str()) == 0) {
			cout << ("Your username needs to be filled out.")
				 << endl;
			valid = false;
		}//if
		else {
			data.write(usernameNew.c_str(), usernameNew.size());
			data << ('\n');
			valid = true;
		}//else
	}//while
	
	valid = false;
	while (!valid) {
		cout << ("Password: ");
		getline(cin, passwordNew);
		if ((strcmp(passwordNew.c_str(), usernameNew.c_str()) == 0) || (strcmp(passwordNew.c_str(), empty.c_str()) == 0)) {
			cout << ("Your password needs to be different then your username and filled out.")
				 << endl;
			valid = false;
		}//if
		else {
			data.write(passwordNew.c_str(), passwordNew.size());
			data << ('\n');
			valid = true;
		}//else
	}//while

	cout << ("Character Name: ");
	getline(cin, nameNew);
	data.write(nameNew.c_str(), nameNew.size());
	data << ('\n');

	valid = false;
	while (!valid) {
		cout << ("Gender (Male, Female): ");
		getline(cin, genderNew);
		if (((strcmp(genderNew.c_str(), male.c_str()) != 0) && (strcmp(genderNew.c_str(), female.c_str()) != 0)) || (strcmp(genderNew.c_str(), empty.c_str()) == 0)) {
			cout << ("Your gender needs to be either a male or female try again.")
				 << endl;
			valid = false;
		}//if
		else {
			data.write(genderNew.c_str(), genderNew.size());
			data << ('\n');
			valid = true;
		}//else
	}//while

	data.write(levelNew.c_str(), levelNew.size());
	data << ('\n');
	data.close();

	if (chmod(filename.c_str(), 0444) == -1) {
		cout << ("Whoopsies!! Looks like something went wrong trying to create your account\n")
			 << ("the game.  Please close the terminal and clear some RAM and try again.\n")
			 << endl;
		destructor();
		exit(EXIT_FAILURE);
	}//if

	return;
}//function that initializes users account

void gameLogin() {
	string response = ("");
	string again = ("Again");
	string create = ("Create");
	string usernameTemp = ("");
	string passwordTemp = ("");

	LOGIN:
		clearScreen();
		gameIntro(false);
		ifstream data("data.txt", ios::in | ios::beg);
		data.getline(username, length);
		data.getline(password, length);

		cout << ("\nPlease enter in your account credentials.") << endl;
		cout << ("Username: ");
		getline(cin, usernameTemp);
		cout << ("Password: ");
		getline(cin, passwordTemp);

		if ((strcmp(username, usernameTemp.c_str()) == 0) && (strcmp(password, passwordTemp.c_str()) == 0)) {
			data.getline(name, length);
			data.getline(level, length);
			data.close();
		}//if

		else {
			data.close();
			username = nullptr;
			password = nullptr;

			TRY_AGAIN:
			cout << ("Your username or password was invalid! Would you like to try again or create a new account? (Again, Create)");
			getline(cin, response);

			if (strcmp(again.c_str(), response.c_str()) == 0) {
				goto LOGIN;
			}//if
			else if (strcmp(create.c_str(), response.c_str()) == 0) {
				makeAccount();
			}//else if
			else {
				cout << ("Invalid response.") << endl;
				goto TRY_AGAIN;
			}//else
		}//else
		
		return;
}//function to log the user into the game

void prologue() {
	string response = ("");
	bool beerTent = false;
	bool placedOne = false;
	bool placedTwo = false;

	clearScreen();
	gameIntro(false);

	cout << ("To play this game there are just a few formatted responses you should become familiar with.\n")
		 << ("There are some more commands that are not as general but there use will be described in game.\n\n")
		 << ("\tTo collect any item use the command:                                    get \" THE_ITEM \"\n")
		 << ("\tTo look more closely at something after using get use the command:      examine \" THE_ITEM \"\n")
		 << ("\tTo travel with the game use the command:                                go \" N_E_S_W \"\n")
		 << endl;

	BEGINNING:
	cout << ("+---------------------+\n")
		 << ("|      Prologue:      |\n")
		 << ("|    Century Park     |\n")
		 << ("|        1999         |\n")
		 << ("+---------------------+\n\n")
		 << ("New Year's Eve, 1999, a quarter to midnight (11:45) and where else to be but Century Park! Fireworks cascade across\n")
		 << ("the sky, your stomach rumbles uneasily, music and lasers howl across the parkland... Not exactly your ideal\n") 
		 << ("party (especially as that rather attractive stranger in black has slipped back into the crowds) - but cheer up, you\n")
		 << ("won't live to see the next.\n")
		 << ("At one side of the great Park, on a gravel path which runs west to northeast beside poplar trees. Crowds of\n")
		 << ("celebrants are enjoying themselves to the north, having abandoned the canvas marquee east.\n\n>");

	for (;;) {
		getline(cin, response);
		turns++;
		cout << endl;

		if(strcmp("go west", response.c_str()) == 0) {
			clearScreen();
			gameIntro(false);

			cout << ("+----------------------+\n")
				 << ("|  LaFleur's Monument  |\n")
				 << ("+----------------------+\n")
				 << endl;

			cout << ("A corner of the Park, beside copses of trees and some fencing. Standing about here is the outdoor equivalent to\n")
				 << ("always being in the kitchen at parties.\n\n")
				 << ("The pyramidal Monument, built by the (very eccentric) Hungarian who laid out the park, dominates this\n")
				 << ("corner. It isn't very pleasing to the eye. Although the party's organisers planned to bounce flashy lasers off the\n") 
				 << ("tip, somehow they don't seem to have got round to it.\n\n>");

			for (;;) {
				getline(cin, response);
				turns++;
				cout << endl;

				if (strcmp("go east", response.c_str()) == 0) {
					clearScreen();
					gameIntro(false);
					goto BEGINNING;
				}//if
				else if ((strcmp("go north", response.c_str()) == 0) || (strcmp("go south", response.c_str()) == 0) || (strcmp("go west", response.c_str()) == 0)) {
					cout << ("As you look into the woods and see how dark and scary it has become from when you first arrived at the party you\n")
						 << ("decide that going down that path would not be the best idea.\n\n>");
				}//else if
				else {
					cout << ("Sorry that is an unknown command try going back where you came from or reviewing the layout description for clues\n")
						 << ("that may help you dicover what you need to do.\n\n>");
				}//else
			}//for
		}//if
		else if (strcmp("go north", response.c_str()) == 0) {
			cout << ("But, that way lies the party. The crowd, the miasma of celebration for something you never wanted to celebrate\n")
				 << ("in the first place. You know you'll succumb in the end, but for now you can't bear the idea.\n\n>");
		}//else if
		else if (strcmp("go south", response.c_str()) == 0) {
			cout << ("There are only trees and railings that way.\n\n>");
		}//else if
		else if (strcmp("go east", response.c_str()) == 0) {
			clearScreen();
			gameIntro(false);

			cout << ("+---------------------+\n")
				 << ("|      Beer Tent      |\n")
				 << ("+---------------------+\n")
				 << endl;

			cout << ("Hours ago, this was a popular beer tent; long since, the drink ran out and the party moved on, leaving just\n")
				 << ("canvas walls and bare benches.\n\nSticking out of an unpleasant baked potato is a sparkler, still fizzing away.\n\n")
				 << ("The canvas flutters slightly and you can just make out that figure in black rushing away back to the park. It\n")
				 << ("must be that tantalising stranger again - who else would be wearing black at this party?\n\n>");

			for (;;) {
				getline(cin, response);
				turns++;
				cout << endl;

				if (strcmp("get sparkler", response.c_str()) == 0) {
					if (!sparkler) {
						cout << ("Taken\n\n>");
						sparkler = true;
					}//if
					else {
						cout << ("There is no longer a sparkler in the room. Check your pocket.\n\n>");
					}//else
				}//if
				else if ((strcmp("go north", response.c_str()) == 0) || (strcmp("go south", response.c_str()) == 0) || (strcmp("go east", response.c_str()) == 0)) {
					cout << ("The heavy canvas is in the way and, although there's clearly something bulky stacked up behind the southern\n")
						 << ("side, you can only go back west but maybe if you went south from the park you could get behind the tent.\n\n>");
				}//else if
				else if (strcmp("go west", response.c_str()) == 0) {
					PARK:
					clearScreen();
					gameIntro(false);

					cout << ("+--------------------+\n")
						 << ("|    Century Park    |\n")
						 << ("+--------------------+\n")
						 << endl;

					if (!jigsaw) {
						cout << ("Somebody (and you have a pretty good idea who) seems to have dropped, of all things, a jigsaw piece here.\n\n>");
					}//if
					else {
						cout <<("\n\n>");
					}//else

					for (;;) {
						getline(cin, response);
						turns++;
						cout << endl;

						if (strcmp("go north", response.c_str()) == 0) {
							cout << ("But, that way lies the party. The crowd, the miasma of celebration for something you never wanted to celebrate\n")
								 << ("in the first place. You know you'll succumb in the end, but for now you can't bear the idea.\n\n>");
						}//if
						else if (strcmp("go west", response.c_str()) == 0) {
							clearScreen();
							gameIntro(false);

							cout << ("+----------------------+\n")
								 << ("|  LaFleur's Monument  |\n")
								 << ("+----------------------+\n")
								 << endl;

							cout << ("The pyramidal Monument, built by the (very eccentric) Hungarian who laid out the park, dominates this\n")
								 << ("corner. It isn't very pleasing to the eye. Although the party's organisers planned to bounce flashy lasers off the\n") 
				 				 << ("tip, somehow they don't seem to have got round to it.\n\n>");

				 			for (;;) {
								getline(cin, response);
								turns++;
								cout << endl;

								if (strcmp("go east", response.c_str()) == 0) {
									clearScreen();
									gameIntro(false);
									goto PARK;
								}//if
								else if ((strcmp("go north", response.c_str()) == 0) || (strcmp("go south", response.c_str()) == 0) || (strcmp("go west", response.c_str()) == 0)) {
									cout << ("As you look into the woods and see how dark and scary it has become from when you first arrived at the party you\n")
										 << ("decide that going down that path would not be the best idea.\n\n>");
								}//else if
								else {
									cout << ("Sorry that is an unknown command try going back where you came from or reviewing the layout description for clues\n")
										 << ("that may help you dicover what you need to do.\n\n>");
								}//else
							}//for
						}//else if
						else if (strcmp("go east", response.c_str()) == 0) {
							clearScreen();
							gameIntro(false);
							beerTent = true;

							cout << ("+---------------------+\n")
								 << ("|      Beer Tent      |\n")
								 << ("+---------------------+\n")
								 << endl;

							if (!sparkler) {
								cout << ("Sticking out of an unpleasant baked potato is a sparkler, still fizzing away.\n\n>");
							}//if

							for (;;) {
								getline(cin, response);
								turns++;
								cout << endl;

								if (strcmp("get sparkler", response.c_str()) == 0) {
									if (!sparkler) {
										cout << ("Taken\n\n>");
										sparkler = true;
									}//if
									else {
										cout << ("There is no longer a sparkler in the room. Check your pocket.\n\n>");
									}//else
								}//if
								else if (sparkler) {
									cout << ("It is trademarked \"Eterno\" and waggishly claims it will see the century out.\n\n>");
								}//else if
								else if (strcmp("go west", response.c_str()) == 0) {
									clearScreen();
									gameIntro(false);
									goto PARK;
								}//else if
								else if ((strcmp("go north", response.c_str()) == 0) || (strcmp("go south", response.c_str()) == 0) || (strcmp("go east", response.c_str()) == 0)) {
									cout << ("The heavy canvas is in the way and, although there's clearly something bulky stacked up behind the southern\n")
										 << ("side, you can only go back west.\n\n>");
								}//else if
								else {
									cout << ("Sorry that is an unknown command try going back where you came from or reviewing the layout description for clues\n")
										 << ("that may help you dicover what you need to do.\n\n>");
								}//else
							}//for
						}//else if
						else if (strcmp("go south", response.c_str()) == 0) {
							cout << ("There are many places better not visited tonight, and chief among them is this one, despite a certain fin de\n")
								 << ("siecle decadence. It's a crevice behind the beer tent, between dense trees and the rear wall of the Park. The\n")
								 << ("most politely describable use to which it has been put is as a dump for old plastic crates of beer bottles.\n\n")
								 << ("Mingled amongst the beer crates is a wooden crate, broached at the top.\n\n")
								 << ("Discarded beside the old box is an empty rucksack.\n\n")
								 << ("[Your score has just gone up by one point.]\n\n>");

							score += 1;

							for (;;) {
								getline(cin, response);
								turns++;
								cout << endl;

								if ((strcmp("go east", response.c_str()) == 0) || (strcmp("go south", response.c_str()) == 0) || (strcmp("go west", response.c_str()) == 0)) {
									cout << ("That way's even worse. Fresh air may be found to the north past the party.\n\n>");
								}//if
								else if (strcmp("get crate", response.c_str()) == 0) {
									cout << ("Taken\n\n>");
									crate = true;
								}//else if
								else if ((strcmp("examine crate", response.c_str()) == 0) && (crate)) {
									cout << ("An old tea-chest of a box, open-topped, the variety which once swung ashore on ropes in East India Docks in\n")
										 << ("the great Victorian heyday. Branded on one side is \"A.4\".\n\n>");
								}//else if
								else if (strcmp("get rucksack", response.c_str()) == 0) {
									cout << ("Taken\n\n>");
									rucksack = true;
								}//else if
								else if ((strcmp("examine rucksack", response.c_str()) == 0) && (rucksack)) {
									cout << ("It looks oddly like a rucksack you once took with you to Paris on vacation, but perhaps all rucksacks look that\n")
										 << ("way.  When you open it you see a key and foriegn complex device.\n\n>");
								}//else if
								else if ((strcmp("get key", response.c_str()) == 0) && (rucksack)) {
									cout << ("Taken\n\n>");
									key = true;
								}//else if
								else if ((strcmp("examine key", response.c_str()) == 0) && (key)) {
									cout << ("The label on the tag is in some east European language.\n\n>");
								}//else if
								else if ((strcmp("get device", response.c_str()) == 0) && (rucksack)) {
									cout << ("Taken\n\n[Your score has gone up by one point]\n\n>");
									score += 1;
									device = true;
								}//else
								else if ((strcmp("examine device", response.c_str()) == 0) && (device)) {
									cout << ("A highly curious device, like a wood-mounted gimballed compass, with dials and swinging arrows, inscribed\n")
										 << ("\"tempora mutantur, nos et mutamur in illis\". The main feature is a white button. The easiest arrow to read\n")
										 << ("points to 99.\n\n>");
								}//else if
								else if (strcmp("go north", response.c_str()) == 0) {
									SOUTH:
									clearScreen();
									gameIntro(false);

									cout << ("+--------------------+\n")
										 << ("|    Century Park    |\n")
										 << ("+--------------------+\n")
										 << endl;

									if (!jigsaw) {
										cout << ("Somebody (and you have a pretty good idea who) seems to have dropped, of all things, a jigsaw piece here.\n\n>");
									}//if
									else {
										cout <<("\n\n>");
									}//else

									for (;;) {
										getline(cin, response);
										turns++;
										cout << endl;

										if (strcmp("go north", response.c_str()) == 0) {
											CHURCHYARD:
											clearScreen();
											gameIntro(false);

											cout << ("+---------------------+\n")
												 << ("|     Church Yard     |\n")
												 << ("+---------------------+\n")
												 << endl;

											cout << ("A few remains of fences and a crumbling wall are all that divides the overgrown edge of the Park from this\n")
												 << ("long-neglected churchyard, serene and dappled with blacks and greens. Ivy and brambles curl their slow arms\n")
												 << ("around the stones, and the door of the Victorian red-brick chapel (to the east) has gone altogether.\n\n")
												 << ("A night-jar flutters from perch to perch along an old iron fence.\n\n>");

											for (;;) {
												getline(cin, response);
												turns++;
												cout << endl;

												if ((strcmp("go north", response.c_str()) == 0) || (strcmp("go west", response.c_str()) == 0)) {
													cout << ("You can't go that way!\n\n>");
												}//if
												else if (strcmp("go south", response.c_str()) == 0) {
													goto SOUTH;
												}//else if
												else if (strcmp("go east", response.c_str()) == 0) {
													CHAPEL:
													clearScreen();
													gameIntro(false);

													cout << ("+----------------------+\n")
														 << ("|   Victorian Chapel   |\n")
														 << ("+----------------------+\n")
														 << endl;

													cout << ("An odour compounded of desiccated, pressed flowers, incense and wax makes you feel somehow rested in this\n")
														 << ("modest and now deconsecrated chapel. The old brass fittings and altar have been stripped, and the vestry to\n")
														 << ("the east is heaped with debris.\n\n")
														 << ("In pride of place is a shocking modern-art statue of a man, and it is a kind of collage. He has an air-raid\n")
														 << ("warden's helmet, a sickle in one hand, a soldering iron in the other: an old-fashioned cavalry officer's tunic and\n")
														 << ("a pair of miner's trousers, then Indian sandals.\n\n>");

													for (;;) {
														getline(cin, response);
														turns++;
														cout << endl;

														if ((strcmp("go north", response.c_str()) == 0) || (strcmp("go south", response.c_str()) == 0)) {
															cout << ("There is only the churchyard, to the west. The vestry lies east.\n\n>");
														}//if
														else if (strcmp("get statue", response.c_str()) == 0){
															cout << ("It is far to heavy and fixed in the ground. Try just examining it.\n\n>");
														}//else if
														else if (strcmp("examine statue", response.c_str()) == 0) {
															cout << ("Written around the base, in large Roman letters, is: \"Bonor LaFleur, 1917-95: Inventor, Sculptor,\n")
																 << ("Philanthropist\", and his motto: \"felix qui potuit rerum cognoscere causas\".\n\n>");
														}//else if
														else if (strcmp("go west", response.c_str()) == 0) {
															goto CHURCHYARD;
														}//else if
														else if (strcmp("go east", response.c_str()) == 0) {
															clearScreen();
															gameIntro(false);
															vestry = true;

															cout << ("+----------------------+\n")
																 << ("|        Vestry        |\n")
																 << ("+----------------------+\n")
																 << endl;

															cout << ("The vestry once held surplices. Today, it holds a surplus. Debris, broken furniture, blown-in leaves, panes of\n")
																 << ("dusty glass and mildewed cloth, all unwanted.\n\n")
																 << ("There's even an old Victorian piano stool, but no sign of a piano. Open it to see the contents.\n\n>");

															for (;;) {
																getline(cin, response);
																turns++;
																cout << endl;

																if ((strcmp("go north", response.c_str()) == 0) || (strcmp("go east", response.c_str()) == 0) || (strcmp("go south", response.c_str()) == 0)) {
																	cout << ("It's a dead end.\n\n>");
																}//if
																else if (strcmp("open stool", response.c_str()) == 0) {
																	cout << ("You lift the hinged lid seeing a penicil and a sketch book.\n\n>");
																}//else if
																else if (strcmp("get pencil", response.c_str()) == 0) {
																	if (!pencil) {
																		cout << ("Taken\n\n[Your score has gone up by one point]\n\n>");
																		pencil = true;
																		score += 1;
																	}//if
																	else {
																		cout << ("You already have the pencil silly!\n\n>");
																	}//else
																}//else if
																else if (strcmp("get sketch book", response.c_str()) == 0) {
																	if (!sketchbook) {
																		cout << ("Taken\nMaybe you should draw that night-jar you saw earlier in the churchyard.\n\n[Your score has gone up by one point]\n\n>");
																		sketchbook = true;
																		score += 1;
																	}//if
																	else {
																		cout << ("You already have the sketch book silly!\n\n>");
																	}//else
																}//else if
																else if (strcmp("go west", response.c_str()) == 0) {
																	goto CHAPEL;
																}//else if
																else {
																	cout << ("Sorry that is an unknown command try going back where you came from or reviewing the layout description for clues\n")
																		 << ("that may help you dicover what you need to do.\n\n>");
																}//else
															}//for
														}//else if
														else {
															cout << ("Sorry that is an unknown command try going back where you came from or reviewing the layout description for clues\n")
																 << ("that may help you dicover what you need to do.\n\n>");
														}//else
													}//for
												}//else if
												else if (strcmp("get night jar", response.c_str()) == 0) {
													cout << ("Unfortunately you have nothing suitable to catch the bird with: no wicker-work cage, for instance.\n\n>");
												}//else if
												else if ((strcmp("sketch night jar", response.c_str()) == 0) && (pencil) && (sketchbook)) {
													cout << ("You sketch in a picture of the night-jar, with a curious sense of deja-vu, and the feeling that drawing such\n")
														 << ("pictures is somehow a worthwhile aim.\n\n>");
												}//else if
												else {
													cout << ("Sorry that is an unknown command try going back where you came from or reviewing the layout description for clues\n")
														 << ("that may help you dicover what you need to do.\n\n>");
												}//else
											}//for
										}//if
										else if ((strcmp("go east", response.c_str()) == 0) || (strcmp("go south", response.c_str()) == 0) || ((strcmp("go west", response.c_str()) == 0) && (!vestry))) {
											cout << ("You could do that but as the party gets louder and the people particpating get rowdier you think to yourself maybe\n")
												 << ("I should go north past the party to the church yard for some fresh air.\n\n>");
										}//else if
										else if ((strcmp("go west", response.c_str()) == 0) && (vestry)) {
											clearScreen();
											gameIntro(false);

											cout << ("+----------------------+\n")
												 << ("|  LaFleur's Monument  |\n")
												 << ("+----------------------+\n")
												 << endl;

											cout << ("A corner of the Park, beside copses of trees and some fencing. Standing about here is the outdoor equivalent to\n")
												 << ("always being in the kitchen at parties.\n\n")
												 << ("The pyramidal Monument, built by the (very eccentric) Hungarian who laid out the park, dominates this\n")
												 << ("corner. It isn't very pleasing to the eye. Although the party's organisers planned to bounce flashy lasers off the\n")
												 << ("tip, somehow they don't seem to have got round to it. You think about climbing up there to light it.\n\n>");

											for (;;) {
												getline(cin, response);
												turns++;
												cout << endl;

												if (strcmp("go up", response.c_str()) == 0) {
													clearScreen();
													gameIntro(false);

													cout << ("+----------------------+\n")
														 << ("|   Atop The Pyramid   |\n")
														 << ("+----------------------+\n")
														 << endl;

													cout << ("The anticipated good-view-of-the-party is spoiled somewhat by the perilous nature of the footing - on a sharp\n")
														 << ("triangular wedge of metal. \"exegi monumentum aere perennius,\" says an inscription. Let's hope so.\n\n")
														 << ("Poking out of the top of the monument is a rickety lightning-conductor. You think to light the fuse.\n\n>");

													for (;;) {
														getline(cin, response);
														turns++;
														cout << endl;

														if (strcmp("light fuse", response.c_str()) == 0) {
															if (sparkler){
																cout << ("(with the sparkler)\n")
																	 << ("The fuse wire in the lightning rod begins to burn down. It shrivels away with a disappointing fizzing sound, and\n")
																	 << ("then the whole monument is rocked slightly by a bang from within. A little smoke rises from the base.\n\n")
																	 << ("[Your score has just gone up by one point.]\n\n>");

																score += 1;
																fuse = true;
															}//if
															else {
																cout << ("You have nothing to light the fuse with. You remember something about a sparkler...\n\n>");
															}//else
														}//if
														else if (strcmp("go down", response.c_str()) == 0) {
															clearScreen();
															gameIntro(false);

															cout << ("+----------------------+\n")
																 << ("|  LaFleur's Monument  |\n")
																 << ("+----------------------+\n")
																 << endl;

															cout << ("The Monument dominates this corner, yet only you seem to have noticed the charred and saw-toothed\n")
																 << ("doorway open in one side. You think about entering the pyramid.\n\n>");

															for (;;) {
																getline(cin, response);
																turns++;
																cout << endl;

																if (strcmp("enter pyramid", response.c_str()) == 0) {
																	clearScreen();
																	gameIntro(false);

																	cout << ("+--------------------------+\n")
																		 << ("| Corridor In the Monument |\n")
																		 << ("+--------------------------+\n")
																		 << endl;

																	cout << ("A short metal corridor running along the inside of one wall of the pyramid, and sloping slightly inward. The\n")
																		 << ("scene out through the south entrance is perfectly, even alarmingly still. The far end turns and opens inside to\n")
																		 << ("the east.\n\n")
																		 << ("Mounted on the inner wall is a glass display case.\n\n>");

																	for (;;) {
																		getline(cin, response);
																		turns++;
																		cout << endl;

																		if (strcmp("get case", response.c_str()) == 0) {
																			cout << ("That item is fixed and can not be taken. Try just examining it.\n\n>");
																		}//if
																		else if (strcmp("examine case", response.c_str()) == 0) {
																			cout << ("The display case, which is sealed with an elaborate, carved metal lock, contains a papier-mache model of\n")
																				 << ("parkland.\n\n>");
																		}//else if
																		else if (strcmp("open case", response.c_str()) == 0) {
																			cout << ("It seems to be locked.\n\n>");
																		}//else if
																		else if (strcmp("unlock case", response.c_str()) == 0) {
																			if (key) {
																				cout << ("That key does not fit this old lock.\n\n>");
																			}//if
																			else {
																				cout << ("You have no key to unlock the case.\n\n>");
																			}//else
																		}//else if
																		else if (strcmp("go south", response.c_str()) == 0) {
																			cout << ("Some kind of invisible wall blocks the doorway. Through it you can see absolute stillness, smoke hanging rigid\n")
																				 << ("as if photographed.\n\n>");
																		}//else if
																		else if ((strcmp("go north", response.c_str()) == 0) || (strcmp("go west", response.c_str()) == 0)) {
																			cout << ("The corridor enters from the south, and exits to the east.\n\n>");
																		}//else if
																		else if (strcmp("go east", response.c_str()) == 0) {
																			clearScreen();
																			gameIntro(false);
																			bool look = false;
																			bool clean = false;
																			bool board = false;

																			cout << ("+-------------------------+\n")
																				 << ("|   Inside the Monument   |\n")
																				 << ("+-------------------------+\n")
																				 << endl;

																			cout << ("A sloping crevice of metal, sunken into the ground some way to make a larger-than-expected room.\n")
																				 << ("The air is frigid.\n\n")
																				 << ("At the centre is a heavy old table, as grimy as the rest of this cavity, a thick layer of dust shadowing its beautiful\n")
																				 << ("marquetry. You catch a glimse of some things under the table.\n\n")
																				 << ("On a kind of steel mantelpiece sits a late Victorian ormolu clock, with a curious single hand on the sixty-minute\n")
																				 << ("dial, pointed upwards in the zero position.\n\n>");

																			for (;;) {
																				getline(cin, response);
																				turns++;
																				cout << endl;

																				if ((strcmp("go north", response.c_str()) == 0) || (strcmp("go south", response.c_str()) == 0) || (strcmp("go east", response.c_str()) == 0) || (strcmp("go west", response.c_str()) == 0)) {
																					cout << ("Curiousity has taken over your brain and will not leave without answers!\n\n>");
																				}//if
																				else if (strcmp("examine under table", response.c_str()) == 0) {
																					cout << ("With all jigsaw puzzles, no matter how careful you are a piece always ends up on the floor. Clearly someone has been\n.")
																						 << ("here and knocked this piece off.\n\n>");
																					look = true;
																				}//else if
																				else if ((strcmp("get jigsaw piece", response.c_str()) == 0) && (look)) {
																					if (!jigsaw2) {
																						cout << ("Taken...its engraves southwest of center.\n\n")
																							 << ("[Your score has gone up by one point]\n\n>");
																						score += 1;
																					}//if
																					else {
																						cout << ("You already collected that piece silly.\n\n>");
																					}//else
																				}//else if
																				else if (strcmp("examine table", response.c_str()) == 0) {
																					cout << ("A heavy old table, high and wide and is to dusty to make out (try cleaning), with fine inlaid marquetry decoration.\n")
																						 << ("On one side is a brass plaque, declaring it to be \"by Mr Gm. Nelson, begun at the Holywell Stables, MCMXCIII;\n")
																						 << ("completed at the Waynflete and Summertown, MCMVC\".\n\n>");
																				}//else if
																				else if (strcmp("clean table", response.c_str()) == 0) {
																					cout << ("The table comes up a shine. On top of it seems to be a some kind of frame, or board, which perhaps bears\n")
																						 << ("further examination.\n\n")
																						 << ("[Your score has gone up by one point]\n\n>");
																					score += 1;
																					clean = true;
																				}//else if
																				else if ((strcmp("examine board", response.c_str()) == 0) && (clean)) {
																					cout << ("A four-by-four square grid of mahogany, with gold leaf inscriptions denoting the squares \"a1\" to \"d4\", and\n")
																						 << ("giving the Latin tag \"nec deus intersit nisi dignus vindice nodus inciderit\".\n\n>");
																					board = true;
																				}//else if
																				else if ((strcmp("put piece at a4", response.c_str()) == 0) && (board)) {
																					cout << ("It fits nicely into a4.\n\n>");
																					placedOne = true;
																				}//else if
																				else if ((strcmp("put piece at c2", response.c_str()) == 0) && (board)) {
																					cout << ("It fits nicely into c2.\n\n>");
																					placedTwo = true;
																				}//else if
																				else if (strcmp("get clock", response.c_str()) == 0) {
																					cout << ("Taken\n\n");
																					myClock = true;
																					if (placedOne && placedTwo) {
																						cout << ("The clock has one hand and goes from 0 to 59.  If you have placed both jigsaw pieces we will move the hand\n")
																							 << ("and if you place it in the correct location you will use the time machine you have stumbled upon. You have played \n")
																							 << (turns)
																							 << (" turns.");
																						for (;;) {
																							cout << ("What number do you want to set the hand to: ");
																							getline(cin, response);
																							char * temp = nullptr;
																							sprintf(temp, "%d", turns);
																							turns++;
																							cout << endl;
																							if (strcmp(response.c_str(), temp) == 0) {
																								cout << ("Congratulations!!!!! You have completed the Millennium prologue. Please respond the the creator Zachary\n")
																									 << ("Davis (Connor by GroupMe) with any bugs or ANY issue or odd-spot you have noticed!");
																								return;
																							}//if
																							else {
																								cout << ("Look up at how many turns you have taken up until now and try that.  If greater than 59 try subtracting 60 until it is\n")
																									 << ("less than 59.");
																							}//else
																						}//for
																					}//if
																				}//else if
																				else {
																					cout << ("Sorry that is an unknown command try going back where you came from or reviewing the layout description for clues\n")
																						 << ("that may help you dicover what you need to do.\n\n>");
																				}//else
																			}//for
																		}//else if
																		else {
																			cout << ("Sorry that is an unknown command try going back where you came from or reviewing the layout description for clues\n")
																				 << ("that may help you dicover what you need to do.  If you are placing a puzzle piece it doesn't fit there.\n\n>");
																		}//else
																	}//for
																}//if
																else if ((strcmp("go north", response.c_str()) == 0) || (strcmp("go east", response.c_str()) == 0) || (strcmp("go south", response.c_str()) == 0) || (strcmp("go west", response.c_str()) == 0)) {
																	cout << ("No way you are way to far down the rabbit hole now!\n\n>");
																}//else if
																else {
																	cout << ("Sorry that is an unknown command try going back where you came from or reviewing the layout description for clues\n")
																		 << ("that may help you dicover what you need to do.\n\n>");
																}//else
															}//for
														}//else if
													}//for
												}//if
												else if (strcmp("go east", response.c_str()) == 0) {
													cout << ("You think to yourself, why would you do that now that you are so intrigued!\n\n>");
												}//else if
												else if ((strcmp("go north", response.c_str()) == 0) || (strcmp("go south", response.c_str()) == 0) || (strcmp("go west", response.c_str()) == 0)) {
													cout << ("As you look into the woods and see how dark and scary it has become from when you first arrived at the party you\n")
														 << ("decide that going down that path would not be the best idea.\n\n>");
												}//else if
												else {
													cout << ("Sorry that is an unknown command try going back where you came from or reviewing the layout description for clues\n")
														 << ("that may help you dicover what you need to do.\n\n>");
												}//else
											}//for
										}//else if
										else {
											cout << ("Sorry that is an unknown command try going back where you came from or reviewing the layout description for clues\n")
												 << ("that may help you dicover what you need to do.\n\n>");
										}//else
									}//for
								}//else if
								else {
									cout << ("Sorry that is an unknown command try going back where you came from or reviewing the layout description for clues\n")
										 << ("that may help you dicover what you need to do.\n\n>");
								}//else
							}//for
						}//else if
						else if (strcmp("get jigsaw piece", response.c_str()) == 0) {
							if (!jigsaw) {
								cout << ("Taken\n[You score has increased by one.]\n\n>");
								score += 1;
								jigsaw = true;
							}//if
							else {
								cout << ("You already collected that jigsaw piece silly.\n\n>");
							}//else
						}//else if
						else {
							cout << ("Sorry that is an unknown command try going back where you came from or reviewing the layout description for clues\n")
								 << ("that may help you dicover what you need to do.\n\n>");
						}//else
					}//for
				}//else if
				else {
					cout << ("Sorry that is an unknown command try going back where you came from or reviewing the layout description for clues\n")
						 << ("that may help you dicover what you need to do.\n\n>");
				}//else
			}//for
		}//else if
		else {
			cout << ("Sorry that is an unknown command try going back where you came from or reviewing the layout description for clues\n")
				 << ("that may help you dicover what you need to do.\n\n>");
		}//else
	}//while
}//functiont that sets up the users account for play

int main () {
	string empty = ("");
	cout << ("Click the enter key to begin the game.") << endl;
	getline(cin, empty);

	clearScreen();
	gameIntro(true);
	if (accountCheck()) {
		makeAccount();
	}//if
	gameLogin();
	prologue();
	destructor();

	return EXIT_SUCCESS;	
}//main