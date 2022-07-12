//============================================================================
// Name        : .cpp
// Author      : Fasih Abdullah
// Roll no     : 20I-0432
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Ludo
//============================================================================

#ifndef CENTIPEDE_CPP_
#define CENTIPEDE_CPP_
//#include "Board.h"			//include all required liberaries
#include "util.h"
#include <iostream>
#include<string>
#include<unistd.h>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include<cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;

void game_loop_start();
void string_convert();				//functions prototyping 
void highscore_calculate();
void turn1_steps(unsigned char);
void turn2_steps(unsigned char);
void turn3_steps(unsigned char);
void turn4_steps(unsigned char);
int game_start();
void dice_looped();
void highscore_add(int);

int red_x_y[4][2]={{156,156},{276,156},{156,276},{276,276}}, blue_x_y[4][2]={{156,804},{276,804},{156,924},{276,924}};
int yellow_x_y[4][2]={{804,804},{924,804},{804,924},{924,924}}, green_x_y[4][2]={{804,156},{924,156},{804,276},{924,276}};
int start_pos[4][4][2];
int kill_count[4]={0,0,0,0};
int number_players=5;
int pl_c[4];
int dice[4], dice_val, dice_score;					// variables declaration
int turn=0;
int looped=0;
int rearrange=0;
int saved_scores[10];
int redoriginal[4][2];
int lowest_highscore_index;
int scores[4]={0,0,0,0};
string names[4];
string saved_names[10];
string score_disp[4];
bool win[4]={0,0,0,0};
int wins=0;
//int repeat=5;

// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void highscore_add(){		// function called only when all pieces are on home triangle // adds new highscore to highscore.txt // needed to seperate the final steps of program 
	if(wins==1){	//wins check
		int score_high=0;

		for(int i=0; i<number_players; i++){		// calculate high score to be replaced 
			
			if(scores[i]>saved_scores[i]){
				score_high=scores[i];
				
				ofstream out;			//open file for writing 
				
				out.open("highscores.txt", ios::trunc);

				if(!out.is_open()) cout<<"Error opening highscore file!"<<endl;

				saved_scores[9]=score_high;

				for(int i=0; i<10; i++){								//write to file 
					out<<saved_names[i]<<" "<<saved_scores[i]<<endl;
				}
				
				out.close();			//close file 

				cout<<"New highscore!"<<endl;
				cout<<"The new leaderboard is: \n"<<endl;


				for(int i=0; i<10; i++){								// show new highscores 
					cout<<saved_names[i]<<" "<<saved_scores[i]<<endl;
				}
			}
		}
	}

	if(wins==number_players-1){		// exit game condition 
		cout<<"Game ended!"<<endl;
		exit(1);
	}
}

void dice_looped(){		// calculates random dice value after looped section has been initiated 

	cout << "space pressed 2" << endl;

		dice_val=rand()%6+1;			// random generator was seeded in main function 
		

		//dice2=rand()%6+1;

		cout<<"Dice value is: "<<dice_val<<endl;

		/*if(dice_val_fake==6){	// 1st 6
			repeat=1;
		}else dice_val=dice_val_fake;*/
		
		

}

void turn1_steps(unsigned char key){	// function used to seperate steps for turn 1 



			if(rearrange==0){		// one time run check
					for(int i=0; i<4; i++){
						for(int j=0; j<2; j++){
							redoriginal[i][j]=red_x_y[i][j];	// stores original positions for red gotis 
						}
					}
					rearrange++;	//prevent rearrange in same turn
			}

				

			if (key == 49) //turn 1 press 1
					{
					int current_score=scores[0];
					int turn_score=0;	

						if(red_x_y[0][0]==156 && red_x_y[0][1]==156 && dice_val==6){		//starting point and check for 6 goti 1
							red_x_y[0][1]=108;
							red_x_y[0][0]=468;
						}
						else if(red_x_y[0][0]==156 && red_x_y[0][1]==156 && dice_val!=6 && ((red_x_y[1][0]!=276 || red_x_y[1][1]!=156 || red_x_y[2][0]!=156 || red_x_y[2][1]!=276 || red_x_y[3][0]!=276 || red_x_y[3][1]!=276))){
							return;
						}

						else if(!(red_x_y[0][0]==156 && red_x_y[0][1]==156)) {			//out of base
							for(int i=0; i<dice_val; i++){//multiple 6 rule add after
								if(red_x_y[0][0]==468 && red_x_y[0][1]==396){
									red_x_y[0][0]=396;
									red_x_y[0][1]=468;
									turn_score++;//
									//i++;
									continue;
									/*for(int j=0; j<dice_val-i; j++){
										red_x_y[0][0] -= 72;
									}
									break;*/
									}//continue this pattern
								else if(red_x_y[0][0]==396 && red_x_y[0][1]==612){ 		// corner shifts and jumps
									red_x_y[0][0]=468;
									red_x_y[0][1]=684;
									turn_score++;//
									continue;
									}
								else if(red_x_y[0][0]==612 && red_x_y[0][1]==684){
									red_x_y[0][0]=684;
									red_x_y[0][1]=612;//
									turn_score++;
									continue;
									}
								else if(red_x_y[0][0]==684 && red_x_y[0][1]==468){
									red_x_y[0][0]=612;
									red_x_y[0][1]=396;//
									turn_score++;
									continue;
									}
								else if(red_x_y[0][0]==36 && red_x_y[0][1]==468){
									red_x_y[0][0]=36;
									red_x_y[0][1]=540;// 1st blue		// columns (changed direction)
									turn_score++;
									continue;
									}
								else if(red_x_y[0][0]==36 && red_x_y[0][1]==612){
									red_x_y[0][0]=108;
									red_x_y[0][1]=612;// 2nd blue
									turn_score++;
									continue;
									}
								else if(red_x_y[0][0]==468 && red_x_y[0][1]==1044){
									red_x_y[0][0]=540;
									red_x_y[0][1]=1044;// 1st yellow
									turn_score++;
									continue;
									}
								else if(red_x_y[0][0]==612 && red_x_y[0][1]==1044){
									red_x_y[0][0]=612;
									red_x_y[0][1]=972;// 2nd yellow
									turn_score++;
									continue;
									}
								else if(red_x_y[0][0]==1044 && red_x_y[0][1]==612){
									red_x_y[0][0]=1044;
									red_x_y[0][1]=540;// 1st green
									turn_score++;
									continue;
									}
								else if(red_x_y[0][0]==1044 && red_x_y[0][1]==468){
									red_x_y[0][0]=972;
									red_x_y[0][1]=468;// 2nd green
									turn_score++;
									continue;
									}
								else if(red_x_y[0][0]==612 && red_x_y[0][1]==36){
									red_x_y[0][0]=540;
									red_x_y[0][1]=36;// 1st red
									turn_score++;
									continue;
									}
								else if(red_x_y[0][0]==540 && red_x_y[0][1]==36){
									red_x_y[0][0]=540;
									red_x_y[0][1]=108;// red home column
									turn_score +=15;
									continue;
									}
								
								if((red_x_y[0][0]>432 && red_x_y[0][0]<576 && red_x_y[0][1]>0 && red_x_y[0][1]<432) || (red_x_y[0][0]>432 && red_x_y[0][0]<504 && red_x_y[0][1]>648 && red_x_y[0][1]<1080)){// use x axis method instead
									if(red_x_y[0][0]==540){
										if(((540-red_x_y[0][1])/72)<=dice_val){	//home entry check
											turn=2;
											return;
										}
									}
									red_x_y[0][1] +=72;//inc y axis //red home col//
									turn_score++;
								}
								else if((red_x_y[0][0]>0 && red_x_y[0][0]<432 && red_x_y[0][1]==468)||(red_x_y[0][0]>648 && red_x_y[0][0]<1080 && red_x_y[0][1]==468)){
									red_x_y[0][0] -=72;//dec x axis//
									turn_score++;
								}
								else if((red_x_y[0][0]>648 && red_x_y[0][0]<1080 && red_x_y[0][1]==612)||(red_x_y[0][0]>0 && red_x_y[0][0]<432 && red_x_y[0][1]==612)){
									red_x_y[0][0] +=72;//inc x axis//
									turn_score++;
								}
								else if((red_x_y[0][1]>0 && red_x_y[0][1]<432 && red_x_y[0][0]==612)||(red_x_y[0][0]==612 && red_x_y[0][1]<1080 && red_x_y[0][1]>648)){
									red_x_y[0][1] -=72;//dec y axis
									turn_score++;
									}
								else if((red_x_y[0][1]>432 && red_x_y[0][1]<648 && red_x_y[0][0]==36)){
									red_x_y[0][1] +=72;//inc y axis
									turn_score++;
								}
								else if((red_x_y[0][0]>432 && red_x_y[0][0]<648 && red_x_y[0][1]==1044)){
									red_x_y[0][0] +=72;//inc x axis
									turn_score++;
								}
								else if((red_x_y[0][1]>432 && red_x_y[0][1]<648 && red_x_y[0][0]==1044)){
									red_x_y[0][1] -=72;//dec y axis
									turn_score++;
								}
								else if((red_x_y[0][0]>432 && red_x_y[0][0]<648 && red_x_y[0][1]==36)){
									red_x_y[0][0] -=72;//dec x axis
									turn_score++;
								}
									//works nice!
							}
						}
						
							

						if(dice_val==6 && rearrange<3){		// dice values check and decide turns 
							dice_val=-9999;
							turn=1;
							rearrange++;
						}else if(dice_val==6 && rearrange==3){
								for(int k=0; k<4; k++){
									for(int o=0; o<2; o++){
										red_x_y[k][o]=redoriginal[k][o];
									}
								}
								scores[0]=current_score;
								turn_score=0;
								dice_val=-999999;
								turn=2;
								rearrange=0;
						}else if(dice_val>=1 && dice_val<=6){
							dice_val=-999999;
							turn=2;
							rearrange=0;
						}
						

							for(int i=0; i<4; i++){// 0		// kill blue when red 1 turn
								
								for(int j=0; j<1; j++){//0
									if(red_x_y[0][j]==blue_x_y[i][j] && red_x_y[0][j+1]==blue_x_y[i][j+1]){// 00 00 01 01
										blue_x_y[i][j]=start_pos[1][i][j];  //00 100
										blue_x_y[i][j+1]=start_pos[1][i][j+1];// 01 101
										turn_score +=10;
									}
								}
							}

							for(int i=0; i<4; i++){// 0 	//kill yellow when red 1
								
								for(int j=0; j<1; j++){//0
									if(red_x_y[0][j]==yellow_x_y[i][j] && red_x_y[0][j+1]==yellow_x_y[i][j+1]){// 00 00 01 01
										yellow_x_y[i][j]=start_pos[2][i][j];  //00 100
										yellow_x_y[i][j+1]=start_pos[2][i][j+1];// 01 101
										turn_score +=10;
									}
								}
							}

							for(int i=0; i<4; i++){// 0 	//kill green when red 1
								
								for(int j=0; j<1; j++){//0
									if(red_x_y[0][j]==green_x_y[i][j] && red_x_y[0][j+1]==green_x_y[i][j+1]){// 00 00 01 01
										green_x_y[i][j]=start_pos[3][i][j];  //00 100
										green_x_y[i][j+1]=start_pos[3][i][j+1];// 01 101
										turn_score +=10;
									}
								}
							}
							cout<<turn_score;
							scores[0] = scores[0] + turn_score;
					}	
			

					if (key == 50) //turn 1 press 2
					{
						
						int current_score=scores[0];
						int turn_score=0;	

						if(red_x_y[1][0]==276 && red_x_y[1][1]==156 && dice_val==6){		//starting point and check for 6 goti 2
							red_x_y[1][1]=108;
							red_x_y[1][0]=468;
						}
						else if(red_x_y[1][0]==276 && red_x_y[1][1]==156 && dice_val!=6 && ((red_x_y[0][0]!=156 || red_x_y[0][1]!=156|| red_x_y[2][0]!=156 || red_x_y[2][1]!=276 || red_x_y[3][0]!=276 || red_x_y[3][1]!=276))){
							return;
						}

						else if(!(red_x_y[1][0]==276 && red_x_y[1][1]==156)) {			//out of base
							for(int i=0; i<dice_val; i++){//multiple 6 rule add after
								if(red_x_y[1][0]==468 && red_x_y[1][1]==396){
									red_x_y[1][0]=396;
									red_x_y[1][1]=468;//
									turn_score++;
									//i++;
									continue;
									/*for(int j=0; j<dice_val-i; j++){
										red_x_y[1][0] -= 72;
									}
									break;*/
									}//continue this pattern
								else if(red_x_y[1][0]==396 && red_x_y[1][1]==612){
									red_x_y[1][0]=468;									//corner and jumps
									red_x_y[1][1]=684;//
									turn_score++;
									continue;
									}
								else if(red_x_y[1][0]==612 && red_x_y[1][1]==684){
									red_x_y[1][0]=684;
									red_x_y[1][1]=612;//
									turn_score++;
									continue;
									}
								else if(red_x_y[1][0]==684 && red_x_y[1][1]==468){
									red_x_y[1][0]=612;
									red_x_y[1][1]=396;//
									turn_score++;
									continue;
									}
								else if(red_x_y[1][0]==36 && red_x_y[1][1]==468){
									red_x_y[1][0]=36;
									red_x_y[1][1]=540;// 1st blue
									turn_score++;
									continue;
									}
								else if(red_x_y[1][0]==36 && red_x_y[1][1]==612){
									red_x_y[1][0]=108;
									red_x_y[1][1]=612;// 2nd blue
									turn_score++;
									continue;
									}
								else if(red_x_y[1][0]==468 && red_x_y[1][1]==1044){
									red_x_y[1][0]=540;
									red_x_y[1][1]=1044;// 1st yellow
									turn_score++;
									continue;
									}
								else if(red_x_y[1][0]==612 && red_x_y[1][1]==1044){
									red_x_y[1][0]=612;
									red_x_y[1][1]=972;// 2nd yellow
									turn_score++;
									continue;
									}
								else if(red_x_y[1][0]==1044 && red_x_y[1][1]==612){
									red_x_y[1][0]=1044;
									red_x_y[1][1]=540;// 1st green
									turn_score++;
									continue;
									}
								else if(red_x_y[1][0]==1044 && red_x_y[1][1]==468){
									red_x_y[1][0]=972;
									red_x_y[1][1]=468;// 2nd green
									turn_score++;
									continue;
									}
								else if(red_x_y[1][0]==612 && red_x_y[1][1]==36){
									red_x_y[1][0]=540;
									red_x_y[1][1]=36;// 1st red
									turn_score++;
									continue;
									}
								else if(red_x_y[1][0]==540 && red_x_y[1][1]==36){
									red_x_y[1][0]=540;
									red_x_y[1][1]=108;// red home column
									turn_score +=15;
									continue;
									}
								
								if((red_x_y[1][0]>432 && red_x_y[1][0]<576 && red_x_y[1][1]>0 && red_x_y[1][1]<432) || (red_x_y[1][0]>432 && red_x_y[1][0]<504 && red_x_y[1][1]>648 && red_x_y[1][1]<1080)){// use x axis method instead
									if(red_x_y[1][0]==540){
										if(((468+72-red_x_y[1][1])/72)<=dice_val){	
											turn=2;		//home entry check
											return;
										}
									}
									red_x_y[0][1] +=72;//inc y axis //red home col//
									turn_score++;
								}
								else if((red_x_y[1][0]>0 && red_x_y[1][0]<432 && red_x_y[1][1]==468)||(red_x_y[1][0]>648 && red_x_y[1][0]<1080 && red_x_y[1][1]==468)){
									red_x_y[1][0] -=72;//dec x axis//
									turn_score ++;
								}
								else if((red_x_y[1][0]>648 && red_x_y[1][0]<1080 && red_x_y[1][1]==612)||(red_x_y[1][0]>0 && red_x_y[1][0]<432 && red_x_y[1][1]==612)){
									red_x_y[1][0] +=72;//inc x axis//
									turn_score ++;
								}
								else if((red_x_y[1][1]>0 && red_x_y[1][1]<432 && red_x_y[1][0]==612)||(red_x_y[1][0]==612 && red_x_y[1][1]<1080 && red_x_y[1][1]>648)){
									red_x_y[1][1] -=72;//dec y axis
									turn_score ++;
								}
								else if((red_x_y[1][1]>432 && red_x_y[1][1]<648 && red_x_y[1][0]==36)){
									red_x_y[1][1] +=72;//inc y axis
									turn_score ++;
								}
								else if((red_x_y[1][0]>432 && red_x_y[1][0]<648 && red_x_y[1][1]==1044)){
									red_x_y[1][0] +=72;//inc x axis
									turn_score ++;
								}
								else if((red_x_y[1][1]>432 && red_x_y[1][1]<648 && red_x_y[1][0]==1044)){
									red_x_y[1][1] -=72;//dec y axis
									turn_score ++;
								}
								else if((red_x_y[1][0]>432 && red_x_y[1][0]<648 && red_x_y[1][1]==36)){
									red_x_y[1][0] -=72;//dec x axis
									turn_score ++;
								}
									//works nice! 
							}
						}
					
							if(dice_val==6 && rearrange<3){		//goti 2 // dice turn decision 
							dice_val=-9999;
							turn=1;
							rearrange++;
						}else if(dice_val==6 && rearrange==3){
								for(int k=0; k<4; k++){
									for(int o=0; o<2; o++){
										red_x_y[k][o]=redoriginal[k][o];
									}
								}
								scores[0]=current_score;
								turn_score=0;
								dice_val=-999999;
								turn=2;
								rearrange=0;
						}else if(dice_val>=1 && dice_val<=6){
							dice_val=-999999;
							turn=2;
							rearrange=0;
						}

							for(int i=0; i<4; i++){// 0					// kill system piece 2 
								
								for(int j=0; j<1; j++){//0
									if(red_x_y[1][j]==blue_x_y[i][j] && red_x_y[1][j+1]==blue_x_y[i][j+1]){// 00 00 01 01
										blue_x_y[i][j]=start_pos[1][i][j];  //00 100
										blue_x_y[i][j+1]=start_pos[1][i][j+1];// 01 101
										turn_score += 10;
									}
								}
							}

							for(int i=0; i<4; i++){// 0 	//kill yellow when red 2
								
								for(int j=0; j<1; j++){//0
									if(red_x_y[1][j]==yellow_x_y[i][j] && red_x_y[1][j+1]==yellow_x_y[i][j+1]){// 00 00 01 01
										yellow_x_y[i][j]=start_pos[2][i][j];  //00 100
										yellow_x_y[i][j+1]=start_pos[2][i][j+1];// 01 101
										turn_score += 10;
									}
								}
							}

							for(int i=0; i<4; i++){// 0 	//kill green when red 2
								
								for(int j=0; j<1; j++){//0
									if(red_x_y[1][j]==green_x_y[i][j] && red_x_y[1][j+1]==green_x_y[i][j+1]){// 00 00 01 01
										green_x_y[i][j]=start_pos[3][i][j];  //00 100
										green_x_y[i][j+1]=start_pos[3][i][j+1];// 01 101
										turn_score += 10;
									}
								}
							}
							scores[0] = scores[0] + turn_score;			// save score 
					}
								// add more keys 3
				if (key == 51) //turn 1 press 3
				{
					int turn_score=0;
					int current_score=scores[0];

					if(red_x_y[2][0]==156 && red_x_y[2][1]==276 && dice_val==6){		//starting point and check for 6 goti 3
						red_x_y[2][1]=108;
						red_x_y[2][0]=468;
					}
					else if(red_x_y[2][0]==156 && red_x_y[2][1]==276 && dice_val!=6 && ((red_x_y[0][0]!=156 || red_x_y[0][1]!=156|| red_x_y[1][0]!=276 || red_x_y[1][1]!=156 || red_x_y[3][0]!=276 || red_x_y[3][1]!=276))){
							return;
						}

					else if(!(red_x_y[2][0]==156 && red_x_y[2][1]==276)) {
						for(int i=0; i<dice_val; i++){//multiple 6 rule add after		// jumps and corner shifts 
							if(red_x_y[2][0]==468 && red_x_y[2][1]==396){
								red_x_y[2][0]=396;
								red_x_y[2][1]=468;//
								turn_score++;
								//i++;
								continue;
								/*for(int j=0; j<dice_val-i; j++){
									red_x_y[2][0] -= 72;
								}
								break;*/
								}//continue this pattern
							else if(red_x_y[2][0]==396 && red_x_y[2][1]==612){
								red_x_y[2][0]=468;
								red_x_y[2][1]=684;//
								turn_score++;
								continue;
								}
							else if(red_x_y[2][0]==612 && red_x_y[2][1]==684){
								red_x_y[2][0]=684;
								red_x_y[2][1]=612;//
								turn_score++;
								continue;
								}
							else if(red_x_y[2][0]==684 && red_x_y[2][1]==468){
								red_x_y[2][0]=612;
								red_x_y[2][1]=396;//
								turn_score++;
								continue;
								}
							else if(red_x_y[2][0]==36 && red_x_y[2][1]==468){
								red_x_y[2][0]=36;
								red_x_y[2][1]=540;// 1st blue
								turn_score++;
								continue;
								}
							else if(red_x_y[2][0]==36 && red_x_y[2][1]==612){
								red_x_y[2][0]=108;
								red_x_y[2][1]=612;// 2nd blue
								turn_score++;
								continue;
								}
							else if(red_x_y[2][0]==468 && red_x_y[2][1]==1044){
								red_x_y[2][0]=540;
								red_x_y[2][1]=1044;// 1st yellow
								turn_score++;
								continue;
								}
							else if(red_x_y[2][0]==612 && red_x_y[2][1]==1044){
								red_x_y[2][0]=612;
								red_x_y[2][1]=972;// 2nd yellow
								turn_score++;
								continue;
								}
							else if(red_x_y[2][0]==1044 && red_x_y[2][1]==612){
								red_x_y[2][0]=1044;
								red_x_y[2][1]=540;// 1st green
								turn_score++;
								continue;
								}
							else if(red_x_y[2][0]==1044 && red_x_y[2][1]==468){
								red_x_y[2][0]=972;
								red_x_y[2][1]=468;// 2nd green
								turn_score++;
								continue;
								}
							else if(red_x_y[2][0]==612 && red_x_y[2][1]==36){
								red_x_y[2][0]=540;
								red_x_y[2][1]=36;// 1st red
								turn_score++;
								continue;
								}
							else if(red_x_y[2][0]==540 && red_x_y[2][1]==36){
								red_x_y[2][0]=540;
								red_x_y[2][1]=108;// red home column
								turn_score +=15;
								continue;
								}
							
							if((red_x_y[2][0]>432 && red_x_y[2][0]<576 && red_x_y[2][1]>0 && red_x_y[2][1]<432) || (red_x_y[2][0]>432 && red_x_y[2][0]<504 && red_x_y[2][1]>648 && red_x_y[2][1]<1080)){// use x axis method instead
								if(red_x_y[2][0]==540){
										if(((468+72-red_x_y[2][1])/72)<=dice_val){	
											turn=2;		//home entry check
											return;
										}
								}
									red_x_y[0][1] +=72;//inc y axis //red home col//
									turn_score++;
							}
							else if((red_x_y[2][0]>0 && red_x_y[2][0]<432 && red_x_y[2][1]==468)||(red_x_y[2][0]>648 && red_x_y[2][0]<1080 && red_x_y[2][1]==468)){
								red_x_y[2][0] -=72;//dec x axis//
								turn_score ++;
							}
							else if((red_x_y[2][0]>648 && red_x_y[2][0]<1080 && red_x_y[2][1]==612)||(red_x_y[2][0]>0 && red_x_y[2][0]<432 && red_x_y[2][1]==612)){
								red_x_y[2][0] +=72;//inc x axis//
								turn_score ++;
							}
							else if((red_x_y[2][1]>0 && red_x_y[2][1]<432 && red_x_y[2][0]==612)||(red_x_y[2][0]==612 && red_x_y[2][1]<1080 && red_x_y[2][1]>648)){
								red_x_y[2][1] -=72;//dec y axis
								turn_score ++;
							}
							else if((red_x_y[2][1]>432 && red_x_y[2][1]<648 && red_x_y[2][0]==36)){
								red_x_y[2][1] +=72;//inc y axis
								turn_score ++;
							}
							else if((red_x_y[2][0]>432 && red_x_y[2][0]<648 && red_x_y[2][1]==1044)){
								red_x_y[2][0] +=72;//inc x axis
								turn_score ++;
							}
							else if((red_x_y[2][1]>432 && red_x_y[2][1]<648 && red_x_y[2][0]==1044)){
								red_x_y[2][1] -=72;//dec y axis
								turn_score ++;
							}
							else if((red_x_y[2][0]>432 && red_x_y[2][0]<648 && red_x_y[2][1]==36)){
								red_x_y[2][0] -=72;//dec x axis
								turn_score ++;
							}
								//works nice!
						}
					}

						if(dice_val==6 && rearrange<3){ 	//goti 3	// dice turn decision system 
							dice_val=-9999;
							turn=1;
							rearrange++;
						}else if(dice_val==6 && rearrange==3){
								for(int k=0; k<4; k++){
									for(int o=0; o<2; o++){
										red_x_y[k][o]=redoriginal[k][o];
									}
								}
								scores[0]=current_score;
								turn_score=0;
								dice_val=-999999;
								turn=2;
								rearrange=0;
						}else if(dice_val>=1 && dice_val<=6){
							dice_val=-999999;
							turn=2;
							rearrange=0;
						}
				
				
								for(int i=0; i<4; i++){// 0		 kill system 
								
								for(int j=0; j<1; j++){//0
									if(red_x_y[2][j]==blue_x_y[i][j] && red_x_y[2][j+1]==blue_x_y[i][j+1]){// 00 00 01 01
										blue_x_y[i][j]=start_pos[1][i][j];  //00 100
										blue_x_y[i][j+1]=start_pos[1][i][j+1];// 01 101
										turn_score +=10;
									}
								}
							}

							for(int i=0; i<4; i++){// 0 	//kill yellow when red 2
								
								for(int j=0; j<1; j++){//0
									if(red_x_y[2][j]==yellow_x_y[i][j] && red_x_y[2][j+1]==yellow_x_y[i][j+1]){// 00 00 01 01
										yellow_x_y[i][j]=start_pos[2][i][j];  //00 100
										yellow_x_y[i][j+1]=start_pos[2][i][j+1];// 01 101
										turn_score +=10;
									}
								}
							}

							for(int i=0; i<4; i++){// 0 	//kill green when red 2
								
								for(int j=0; j<1; j++){//0
									if(red_x_y[2][j]==green_x_y[i][j] && red_x_y[2][j+1]==green_x_y[i][j+1]){// 00 00 01 01
										green_x_y[i][j]=start_pos[3][i][j];  //00 100
										green_x_y[i][j+1]=start_pos[3][i][j+1];// 01 101
										turn_score +=10;
									}
								}
							}
							scores[0]= scores[0]+turn_score;
				}
					// add more keys 4

				if (key == 52) //turn 1 press 4
				{
					int turn_score=0;
					int current_score=scores[0];
					

					if(red_x_y[3][0]==276 && red_x_y[3][1]==276 && dice_val==6){		//starting point and check for 6 goti 4
						red_x_y[3][1]=108;
						red_x_y[3][0]=468;
					}
					else if(red_x_y[3][0]==276 && red_x_y[3][1]==276 && dice_val!=6 && ((red_x_y[0][0]!=156 || red_x_y[0][1]!=156|| red_x_y[1][0]!=276 || red_x_y[1][1]!=156 || red_x_y[2][0]!=156 || red_x_y[2][1]!=276))){
							return;
						}



					else if(!(red_x_y[3][0]==276 && red_x_y[3][1]==276)) {					// corners and jumps 
						for(int i=0; i<dice_val; i++){//multiple 6 rule add after
							if(red_x_y[3][0]==468 && red_x_y[3][1]==396){
								red_x_y[3][0]=396;
								red_x_y[3][1]=468;//
								turn_score++;
								//i++;
								continue;
								/*for(int j=0; j<dice_val-i; j++){
									red_x_y[3][0] -= 72;
								}
								break;*/
								}//continue this pattern
							else if(red_x_y[3][0]==396 && red_x_y[3][1]==612){
								red_x_y[3][0]=468;
								red_x_y[3][1]=684;//
								turn_score++;
								continue;
								}
							else if(red_x_y[3][0]==612 && red_x_y[3][1]==684){
								red_x_y[3][0]=684;
								red_x_y[3][1]=612;//
								turn_score++;
								continue;
								}
							else if(red_x_y[3][0]==684 && red_x_y[3][1]==468){
								red_x_y[3][0]=612;
								red_x_y[3][1]=396;//
								turn_score++;
								continue;
								}
							else if(red_x_y[3][0]==36 && red_x_y[3][1]==468){
								red_x_y[3][0]=36;
								red_x_y[3][1]=540;// 1st blue
								turn_score++;
								continue;
								}
							else if(red_x_y[3][0]==36 && red_x_y[3][1]==612){
								red_x_y[3][0]=108;
								red_x_y[3][1]=612;// 2nd blue
								turn_score++;
								continue;
								}
							else if(red_x_y[3][0]==468 && red_x_y[3][1]==1044){
								red_x_y[3][0]=540;
								red_x_y[3][1]=1044;// 1st yellow
								turn_score++;
								continue;
								}
							else if(red_x_y[3][0]==612 && red_x_y[3][1]==1044){
								red_x_y[3][0]=612;
								red_x_y[3][1]=972;// 2nd yellow
								turn_score++;
								continue;
								}
							else if(red_x_y[3][0]==1044 && red_x_y[3][1]==612){
								red_x_y[3][0]=1044;
								red_x_y[3][1]=540;// 1st green
								turn_score++;
								continue;
								}
							else if(red_x_y[3][0]==1044 && red_x_y[3][1]==468){
								red_x_y[3][0]=972;
								red_x_y[3][1]=468;// 2nd green
								turn_score++;
								continue;
								}
							else if(red_x_y[3][0]==612 && red_x_y[3][1]==36){
								red_x_y[3][0]=540;
								red_x_y[3][1]=36;// 1st red
								turn_score++;
								continue;
								}
							else if(red_x_y[3][0]==540 && red_x_y[3][1]==36){
								red_x_y[3][0]=540;
								red_x_y[3][1]=108;// red home column
								turn_score +=15;
								continue;
								}
							
							if((red_x_y[3][0]>432 && red_x_y[3][0]<576 && red_x_y[3][1]>0 && red_x_y[3][1]<432) || (red_x_y[3][0]>432 && red_x_y[3][0]<504 && red_x_y[3][1]>648 && red_x_y[3][1]<1080)){// use x axis method instead
								if(red_x_y[0][0]==540){
										if(((468+72-red_x_y[3][1])/72)<=dice_val){
											turn=2;			//home entry check
											return;
										}
								}
									red_x_y[3][1] +=72;//inc y axis //red home col//
									turn_score++;
							
							}
							else if((red_x_y[3][0]>0 && red_x_y[3][0]<432 && red_x_y[3][1]==468)||(red_x_y[3][0]>648 && red_x_y[3][0]<1080 && red_x_y[3][1]==468)){
								red_x_y[3][0] -=72;//dec x axis//
								turn_score +=1;
							}
							else if((red_x_y[3][0]>648 && red_x_y[3][0]<1080 && red_x_y[3][1]==612)||(red_x_y[3][0]>0 && red_x_y[3][0]<432 && red_x_y[3][1]==612)){
								red_x_y[3][0] +=72;//inc x axis//
								turn_score +=1;
							}
							else if((red_x_y[3][1]>0 && red_x_y[3][1]<432 && red_x_y[3][0]==612)||(red_x_y[3][0]==612 && red_x_y[3][1]<1080 && red_x_y[3][1]>648)){
								red_x_y[3][1] -=72;//dec y axis
								turn_score +=1;
							}
							else if((red_x_y[3][1]>432 && red_x_y[3][1]<648 && red_x_y[3][0]==36)){
								red_x_y[3][1] +=72;//inc y axis
								turn_score +=1;
							}
							else if((red_x_y[3][0]>432 && red_x_y[3][0]<648 && red_x_y[3][1]==1044)){
								red_x_y[3][0] +=72;//inc x axis
								turn_score +=1;
							}
							else if((red_x_y[3][1]>432 && red_x_y[3][1]<648 && red_x_y[3][0]==1044)){
								red_x_y[3][1] -=72;//dec y axis
								turn_score +=1;
							}
							else if((red_x_y[3][0]>432 && red_x_y[3][0]<648 && red_x_y[3][1]==36)){
								red_x_y[3][0] -=72;//dec x axis
								turn_score +=1;
							}
								//works nice!
						}
					}

							if(dice_val==6 && rearrange<3){	//goti 4		// dice turn decision system 
							dice_val=-9999;
							turn=1;
							rearrange++;
						}else if(dice_val==6 && rearrange==3){
								for(int k=0; k<4; k++){
									for(int o=0; o<2; o++){
										red_x_y[k][o]=redoriginal[k][o];
									}
								}
								scores[0]=current_score;
								turn_score=0;
								dice_val=-999999;
								turn=2;
								rearrange=0;
						}else if(dice_val>=1 && dice_val<=6){
							dice_val=-999999;
							turn=2;
							rearrange=0;
						}


								for(int i=0; i<4; i++){// 0		// goti kill system
								
								for(int j=0; j<1; j++){//0
									if(red_x_y[3][j]==blue_x_y[i][j] && red_x_y[3][j+1]==blue_x_y[i][j+1]){// 00 00 01 01
										blue_x_y[i][j]=start_pos[1][i][j];  //00 100
										blue_x_y[i][j+1]=start_pos[1][i][j+1];// 01 101
										turn_score +=10;
									}
								}
							}

							for(int i=0; i<4; i++){// 0 	//kill yellow when red 2
								
								for(int j=0; j<1; j++){//0
									if(red_x_y[3][j]==yellow_x_y[i][j] && red_x_y[3][j+1]==yellow_x_y[i][j+1]){// 00 00 01 01
										yellow_x_y[i][j]=start_pos[2][i][j];  //00 100
										yellow_x_y[i][j+1]=start_pos[2][i][j+1];// 01 101
										turn_score +=10;
									}
								}
							}

							for(int i=0; i<4; i++){// 0 	//kill green when red 2
								
								for(int j=0; j<1; j++){//0
									if(red_x_y[3][j]==green_x_y[i][j] && red_x_y[3][j+1]==green_x_y[i][j+1]){// 00 00 01 01
										green_x_y[i][j]=start_pos[3][i][j];  //00 100
										green_x_y[i][j+1]=start_pos[3][i][j+1];// 01 101
										turn_score +=10;
									}
								}
							}
							scores[0]=scores[0]+turn_score;			// save score 
							cout<<scores[0];
				}	
					
				// win system
				if(red_x_y[0][0]==red_x_y[1][0] && red_x_y[0][0]==red_x_y[2][0] && red_x_y[0][0]==red_x_y[3][0] && red_x_y[0][1]==red_x_y[1][1] && red_x_y[0][1]==red_x_y[2][1] && red_x_y[0][1]==red_x_y[3][1]){
					win[0]=1;
					for(int i=0; i<number_players; i++){
						if (pl_c[i]==0) cout<<"\n"<<saved_names[i]<<"Wins!\n"<<endl;
					}
					highscore_add();
				}

}


void turn2_steps(unsigned char key){ // function used to seperate steps for turn 2
	
	if(rearrange==0){		// one time run check	// remember to save memory redoriginal array was reused  
					for(int i=0; i<4; i++){
						for(int j=0; j<2; j++){
							redoriginal[i][j]=blue_x_y[i][j];	// stores original positions for blue gotis 
						}
					}
					rearrange++;	//prevent rearrange in same turn
	}
	if (key == 49) //turn 2 press 1
					{
			int turn_score=0;
						int current_score=scores[1];


						if(blue_x_y[0][0]==156 && blue_x_y[0][1]==804 && dice_val==6){		//starting point and check for 6 goti 1
							blue_x_y[0][1]=612;// changed this //base exited
							blue_x_y[0][0]=108;
						}
						else if(blue_x_y[0][0]==156 && blue_x_y[0][1]==804 && dice_val!=6 && ((blue_x_y[1][0]!=276 || blue_x_y[1][1]!=804 || blue_x_y[2][0]!=156 || blue_x_y[2][1]!=924 || blue_x_y[3][0]!=276 || blue_x_y[3][1]!=924))){
								return;
								} 		//press 1
						else if(!(blue_x_y[0][0]==156 && blue_x_y[0][1]==804)) {//changed			//out of base
							for(int i=0; i<dice_val; i++){//multiple 6 rule add after
								if(blue_x_y[0][0]==468 && blue_x_y[0][1]==396){				// corners and shifts
									blue_x_y[0][0]=396;
									blue_x_y[0][1]=468;//
									turn_score++;
									//i++;
									continue;
									/*for(int j=0; j<dice_val-i; j++){
										blue_x_y[0][0] -= 72;
									}
									break;*/
									}//continue this pattern
								else if(blue_x_y[0][0]==396 && blue_x_y[0][1]==612){
									blue_x_y[0][0]=468;
									blue_x_y[0][1]=684;//
									turn_score++;
									continue;
									}
								else if(blue_x_y[0][0]==612 && blue_x_y[0][1]==684){
									blue_x_y[0][0]=684;
									blue_x_y[0][1]=612;//
									turn_score++;
									continue;
									}
								else if(blue_x_y[0][0]==684 && blue_x_y[0][1]==468){
									blue_x_y[0][0]=612;
									blue_x_y[0][1]=396;//
									turn_score++;
									continue;
									}
								else if(blue_x_y[0][0]==36 && blue_x_y[0][1]==468){
									blue_x_y[0][0]=36;
									blue_x_y[0][1]=540;// 1st blue
									turn_score++;
									continue;
									}
								else if(blue_x_y[0][0]==36 && blue_x_y[0][1]==612){
									blue_x_y[0][0]=108;
									blue_x_y[0][1]=612;// 2nd blue
									turn_score++;
									continue;
									}
								else if(blue_x_y[0][0]==468 && blue_x_y[0][1]==1044){
									blue_x_y[0][0]=540;
									blue_x_y[0][1]=1044;// 1st yellow
									turn_score++;
									continue;
									}
								else if(blue_x_y[0][0]==612 && blue_x_y[0][1]==1044){
									blue_x_y[0][0]=612;
									blue_x_y[0][1]=972;// 2nd yellow
									turn_score++;
									continue;
									}
								else if(blue_x_y[0][0]==1044 && blue_x_y[0][1]==612){
									blue_x_y[0][0]=1044;
									blue_x_y[0][1]=540;// 1st green
									turn_score++;
									continue;
									}
								else if(blue_x_y[0][0]==1044 && blue_x_y[0][1]==468){
									blue_x_y[0][0]=972;
									blue_x_y[0][1]=468;// 2nd green
									turn_score++;
									continue;
									}
								else if(blue_x_y[0][0]==612 && blue_x_y[0][1]==36){
									blue_x_y[0][0]=540;
									blue_x_y[0][1]=36;// 1st red
									turn_score++;
									continue;
									}
								else if(blue_x_y[0][0]==36 && blue_x_y[0][1]==540){
									blue_x_y[0][0]=108;
									blue_x_y[0][1]=540;// blue home column
									turn_score+=15;
									continue;
									}
								
								if((blue_x_y[0][0]>432 && blue_x_y[0][0]<504 && blue_x_y[0][1]>0 && blue_x_y[0][1]<432) || (blue_x_y[0][0]>432 && blue_x_y[0][0]<504 && blue_x_y[0][1]>648 && blue_x_y[0][1]<1080)){// use x axis method instead// no 
									blue_x_y[0][1] +=72;//inc y axis //red home col removed//
									turn_score+=1;
								}
								else if((blue_x_y[0][0]>0 && blue_x_y[0][0]<432 && blue_x_y[0][1]==468)||(blue_x_y[0][0]>648 && blue_x_y[0][0]<1080 && blue_x_y[0][1]==468)){
									blue_x_y[0][0] -=72;//dec x axis//
									turn_score+=1;
								}
								else if((blue_x_y[0][0]>648 && blue_x_y[0][0]<1080 && blue_x_y[0][1]==612)||(blue_x_y[0][0]>0 && blue_x_y[0][0]<432 && (blue_x_y[0][1]==612||blue_x_y[0][1]==540))){//changed this
									if(blue_x_y[0][1]==540){						// blue base added 
										if(((540-blue_x_y[0][0])/72)<=dice_val){
											if(number_players>2) turn=3;
											else turn=1;
											return;
										}
									}

									blue_x_y[0][0] +=72;//inc x axis//
									turn_score+=1;
								}
								else if((blue_x_y[0][1]>0 && blue_x_y[0][1]<432 && blue_x_y[0][0]==612)||(blue_x_y[0][0]==612 && blue_x_y[0][1]<1080 && blue_x_y[0][1]>648)){
									blue_x_y[0][1] -=72;//dec y axis
									turn_score+=1;
								}
								else if((blue_x_y[0][1]>432 && blue_x_y[0][1]<648 && blue_x_y[0][0]==36)){
									blue_x_y[0][1] +=72;//inc y axis
									turn_score+=1;
								}
								else if((blue_x_y[0][0]>432 && blue_x_y[0][0]<648 && blue_x_y[0][1]==1044)){
									blue_x_y[0][0] +=72;//inc x axis
									turn_score+=1;
								}
								else if((blue_x_y[0][1]>432 && blue_x_y[0][1]<648 && blue_x_y[0][0]==1044)){
									blue_x_y[0][1] -=72;//dec y axis
									turn_score+=1;
								}
								else if((blue_x_y[0][0]>432 && blue_x_y[0][0]<648 && blue_x_y[0][1]==36)){
									blue_x_y[0][0] -=72;//dec x axis
									turn_score+=1;
								}
									//works nice!
							}
						}
					
							if(dice_val==6 && rearrange<3){	//goti 1 // dice turn decision 		
							dice_val=-9999;
							turn=2;
							rearrange++;
						}else if(dice_val==6 && rearrange==3){
								for(int k=0; k<4; k++){
									for(int o=0; o<2; o++){
										blue_x_y[k][o]=redoriginal[k][o];
									}
								}
								turn_score=0;
								scores[1]=current_score;
								dice_val=-999999;
								if(number_players>2){
								turn=3;
							}else turn=1;
								rearrange=0;
						}else if(dice_val>=1 && dice_val<=6){
							dice_val=-999999;
							rearrange=0;
							if(number_players>2){
								turn=3;
							}else turn=1;
						}
					
							for(int i=0; i<4; i++){// 0		// kill blue when red 1 turn
								
								for(int j=0; j<1; j++){//0
									if(blue_x_y[0][j]==red_x_y[i][j] && blue_x_y[0][j+1]==red_x_y[i][j+1]){// 00 00 01 01
										red_x_y[i][j]=start_pos[0][i][j];  //00 100
										red_x_y[i][j+1]=start_pos[0][i][j+1];// 01 101
										turn_score+=10;
									}
								}
							}

							for(int i=0; i<4; i++){// 0 	//kill yellow when red 1
								
								for(int j=0; j<1; j++){//0
									if(blue_x_y[0][j]==yellow_x_y[i][j] && blue_x_y[0][j+1]==yellow_x_y[i][j+1]){// 00 00 01 01
										yellow_x_y[i][j]=start_pos[2][i][j];  //00 100
										yellow_x_y[i][j+1]=start_pos[2][i][j+1];// 01 101
										turn_score+=10;
									}
								}
							}

							for(int i=0; i<4; i++){// 0 	//kill green when red 1
								
								for(int j=0; j<1; j++){//0
									if(blue_x_y[0][j]==green_x_y[i][j] && blue_x_y[0][j+1]==green_x_y[i][j+1]){// 00 00 01 01
										green_x_y[i][j]=start_pos[3][i][j];  //00 100
										green_x_y[i][j+1]=start_pos[3][i][j+1];// 01 101
										turn_score+=10;
									}
								}
							}
							scores[1]=scores[1]+turn_score;
					}	//done 28 dec 11:07 pm
			
				
					//add more keys 2
					if (key == 50) //turn 2 press 2
					{
						int turn_score=0;
						int current_score=scores[1];

						if(blue_x_y[1][0]==276 && blue_x_y[1][1]==804 && dice_val==6){		//starting point and check for 6 goti 2
							blue_x_y[1][1]=612;
							blue_x_y[1][0]=108; //adjusted
						}
						else if(blue_x_y[1][0]==276 && blue_x_y[1][1]==804 && dice_val!=6 && ((blue_x_y[0][0]!=156 || blue_x_y[0][1]!=804|| blue_x_y[2][0]!=156 || blue_x_y[2][1]!=924 || blue_x_y[3][0]!=276 || blue_x_y[3][1]!=924))){
								return;
								}								



						else if(!(blue_x_y[1][0]==276 && blue_x_y[1][1]==804)) {			//out of base
							for(int i=0; i<dice_val; i++){//multiple 6 rule add after
								if(blue_x_y[1][0]==468 && blue_x_y[1][1]==396){		// corners and shifts 
									blue_x_y[1][0]=396;
									blue_x_y[1][1]=468;//
									turn_score++;
									//i++;
									continue;
									/*for(int j=0; j<dice_val-i; j++){
										blue_x_y[1][0] -= 72;
									}
									break;*/
									}//continue this pattern
								else if(blue_x_y[1][0]==396 && blue_x_y[1][1]==612){
									blue_x_y[1][0]=468;
									blue_x_y[1][1]=684;//
									turn_score++;
									continue;
									}
								else if(blue_x_y[1][0]==612 && blue_x_y[1][1]==684){
									blue_x_y[1][0]=684;
									blue_x_y[1][1]=612;//
									turn_score++;
									continue;
									}
								else if(blue_x_y[1][0]==684 && blue_x_y[1][1]==468){
									blue_x_y[1][0]=612;
									blue_x_y[1][1]=396;//
									turn_score++;
									continue;
									}
								else if(blue_x_y[1][0]==36 && blue_x_y[1][1]==468){
									blue_x_y[1][0]=36;
									blue_x_y[1][1]=540;// 1st blue
									turn_score++;
									continue;
									}
								else if(blue_x_y[1][0]==36 && blue_x_y[1][1]==612){
									blue_x_y[1][0]=108;
									blue_x_y[1][1]=612;// 2nd blue
									turn_score++;
									continue;
									}
								else if(blue_x_y[1][0]==468 && blue_x_y[1][1]==1044){
									blue_x_y[1][0]=540;
									blue_x_y[1][1]=1044;// 1st yellow
									turn_score++;
									continue;
									}
								else if(blue_x_y[1][0]==612 && blue_x_y[1][1]==1044){
									blue_x_y[1][0]=612;
									blue_x_y[1][1]=972;// 2nd yellow
									turn_score++;
									continue;
									}
								else if(blue_x_y[1][0]==1044 && blue_x_y[1][1]==612){
									blue_x_y[1][0]=1044;
									blue_x_y[1][1]=540;// 1st green
									turn_score++;
									continue;
									}
								else if(blue_x_y[1][0]==1044 && blue_x_y[1][1]==468){
									blue_x_y[1][0]=972;
									blue_x_y[1][1]=468;// 2nd green
									turn_score++;
									continue;
									}
								else if(blue_x_y[1][0]==612 && blue_x_y[1][1]==36){
									blue_x_y[1][0]=540;
									blue_x_y[1][1]=36;// 1st red
									turn_score++;
									continue;
									}
								else if(blue_x_y[1][0]==36 && blue_x_y[1][1]==540){
									blue_x_y[1][0]=108;
									blue_x_y[1][1]=540;// red home column removed
									turn_score+=15;
									continue;
									}
								
								if((blue_x_y[1][0]>432 && blue_x_y[1][0]<504 && blue_x_y[1][1]>0 && blue_x_y[1][1]<432) || (blue_x_y[1][0]>432 && blue_x_y[1][0]<504 && blue_x_y[1][1]>648 && blue_x_y[1][1]<1080)){// use x axis method instead
									blue_x_y[1][1] +=72;//inc y axis //red home col//removed
									turn_score+=1;
								}
								else if((blue_x_y[1][0]>0 && blue_x_y[1][0]<432 && blue_x_y[1][1]==468)||(blue_x_y[1][0]>648 && blue_x_y[1][0]<1080 && blue_x_y[1][1]==468)){
									blue_x_y[1][0] -=72;//dec x axis//
									turn_score+=1;
								}
								else if((blue_x_y[1][0]>648 && blue_x_y[1][0]<1080 && blue_x_y[1][1]==612)||(blue_x_y[1][0]>0 && blue_x_y[1][0]<432 && (blue_x_y[1][1]==612||blue_x_y[1][1]==540))){//changed
									if(blue_x_y[1][1]==540){
										if(((468+72-blue_x_y[1][0])/72)<=dice_val){
											if(number_players>2) turn=3;
											else turn=1;
											return;
										}
									}

									blue_x_y[1][0] +=72;//inc x axis//
									turn_score+=1;
								}
								else if((blue_x_y[1][1]>0 && blue_x_y[1][1]<432 && blue_x_y[1][0]==612)||(blue_x_y[1][0]==612 && blue_x_y[1][1]<1080 && blue_x_y[1][1]>648)){
									blue_x_y[1][1] -=72;//dec y axis
									turn_score+=1;
								}
								else if((blue_x_y[1][1]>432 && blue_x_y[1][1]<648 && blue_x_y[1][0]==36)){
									blue_x_y[1][1] +=72;//inc y axis
									turn_score+=1;
								}
								else if((blue_x_y[1][0]>432 && blue_x_y[1][0]<648 && blue_x_y[1][1]==1044)){
									blue_x_y[1][0] +=72;//inc x axis
									turn_score+=1;
								}
								else if((blue_x_y[1][1]>432 && blue_x_y[1][1]<648 && blue_x_y[1][0]==1044)){
									blue_x_y[1][1] -=72;//dec y axis
									turn_score+=1;
								}
								else if((blue_x_y[1][0]>432 && blue_x_y[1][0]<648 && blue_x_y[1][1]==36)){
									blue_x_y[1][0] -=72;//dec x axis
									turn_score+=1;
								}
									//works nice!
							}		//checked dec 28 11:15 pm 
						}
					
									if(dice_val==6 && rearrange<3){	//goti 2 // dice turn decision 
							dice_val=-9999;
							turn=2;
							rearrange++;
						}else if(dice_val==6 && rearrange==3){
								for(int k=0; k<4; k++){
									for(int o=0; o<2; o++){
										blue_x_y[k][o]=redoriginal[k][o];
									}
								}
								turn_score=0;
								scores[1]=current_score;
								dice_val=-999999;
								if(number_players>2){
								turn=3;
							}else turn=1;
								rearrange=0;
						}else if(dice_val>=1 && dice_val<=6){
							dice_val=-999999;
							rearrange=0;
							if(number_players>2){
								turn=3;
							}else turn=1;
						}
					
								for(int i=0; i<4; i++){// 0 // kill blue when red 1 turn
									for(int j=0; j<1; j++){//0
										if(blue_x_y[1][j]==red_x_y[i][j] && blue_x_y[1][j+1]==red_x_y[i][j+1]){// 00 00 01 01
											red_x_y[i][j]=start_pos[0][i][j]; //00 100
											red_x_y[i][j+1]=start_pos[0][i][j+1];// 01 101
											turn_score+=10;
										}
									}
								}

								for(int i=0; i<4; i++){// 0 //kill yellow when red 1
									for(int j=0; j<1; j++){//0
										if(blue_x_y[1][j]==yellow_x_y[i][j] && blue_x_y[1][j+1]==yellow_x_y[i][j+1]){// 00 00 01 01
											yellow_x_y[i][j]=start_pos[2][i][j]; //00 100
											yellow_x_y[i][j+1]=start_pos[2][i][j+1];// 01 101
											turn_score+=10;
										}
									}
								}

								for(int i=0; i<4; i++){// 0 //kill green when red 1
									for(int j=0; j<1; j++){//0
										if(blue_x_y[1][j]==green_x_y[i][j] && blue_x_y[1][j+1]==green_x_y[i][j+1]){// 00 00 01 01
											green_x_y[i][j]=start_pos[3][i][j]; //00 100
											green_x_y[i][j+1]=start_pos[3][i][j+1];// 01 101
											turn_score+=10;
										}
									}
								}

								scores[1]=scores[1]+turn_score;
					}
								// add more keys 3
				if (key == 51) //turn 2 press 3
				{
					int turn_score=0;
					int current_score=scores[1];


					if(blue_x_y[2][0]==156 && blue_x_y[2][1]==924 && dice_val==6){		//starting point and check for 6 goti 3
						blue_x_y[2][1]=612;
						blue_x_y[2][0]=108;//changed
					}
					else if(blue_x_y[2][0]==156 && blue_x_y[2][1]==924 && dice_val!=6 && ((blue_x_y[0][0]!=156 || blue_x_y[0][1]!=804|| blue_x_y[1][0]!=276 || blue_x_y[1][1]!=804 || blue_x_y[3][0]!=276 || blue_x_y[3][1]!=924))){
								return;
								}


					else if(!(blue_x_y[2][0]==156 && blue_x_y[2][1]==924)) {
						for(int i=0; i<dice_val; i++){//multiple 6 rule add after
							if(blue_x_y[2][0]==468 && blue_x_y[2][1]==396){
								blue_x_y[2][0]=396;
								blue_x_y[2][1]=468;//
								turn_score++;
								//i++;
								continue;
								/*for(int j=0; j<dice_val-i; j++){
									blue_x_y[2][0] -= 72;
								}
								break;*/
								}//continue this pattern
							else if(blue_x_y[2][0]==396 && blue_x_y[2][1]==612){
								blue_x_y[2][0]=468;
								blue_x_y[2][1]=684;//
								turn_score++;
								continue;
								}
							else if(blue_x_y[2][0]==612 && blue_x_y[2][1]==684){
								blue_x_y[2][0]=684;
								blue_x_y[2][1]=612;//
								turn_score++;
								continue;
								}
							else if(blue_x_y[2][0]==684 && blue_x_y[2][1]==468){
								blue_x_y[2][0]=612;
								blue_x_y[2][1]=396;//
								turn_score++;
								continue;
								}
							else if(blue_x_y[2][0]==36 && blue_x_y[2][1]==468){
								blue_x_y[2][0]=36;
								blue_x_y[2][1]=540;// 1st blue
								turn_score++;
								continue;
								}
							else if(blue_x_y[2][0]==36 && blue_x_y[2][1]==612){
								blue_x_y[2][0]=108;
								blue_x_y[2][1]=612;// 2nd blue
								turn_score++;
								continue;
								}
							else if(blue_x_y[2][0]==468 && blue_x_y[2][1]==1044){
								blue_x_y[2][0]=540;
								blue_x_y[2][1]=1044;// 1st yellow
								turn_score++;
								continue;
								}
							else if(blue_x_y[2][0]==612 && blue_x_y[2][1]==1044){
								blue_x_y[2][0]=612;
								blue_x_y[2][1]=972;// 2nd yellow
								turn_score++;
								continue;
								}
							else if(blue_x_y[2][0]==1044 && blue_x_y[2][1]==612){
								blue_x_y[2][0]=1044;
								blue_x_y[2][1]=540;// 1st green
								turn_score++;
								continue;
								}
							else if(blue_x_y[2][0]==1044 && blue_x_y[2][1]==468){
								blue_x_y[2][0]=972;
								blue_x_y[2][1]=468;// 2nd green
								turn_score++;
								continue;
								}
							else if(blue_x_y[2][0]==612 && blue_x_y[2][1]==36){
								blue_x_y[2][0]=540;
								blue_x_y[2][1]=36;// 1st red
								turn_score++;
								continue;
								}
							else if(blue_x_y[2][0]==36 && blue_x_y[2][1]==540){
								blue_x_y[2][0]=108;
								blue_x_y[2][1]=540;// red home column// removed 
								turn_score+=15;
								continue;
								}
							
							if((blue_x_y[2][0]>432 && blue_x_y[2][0]<504 && blue_x_y[2][1]>0 && blue_x_y[2][1]<432) || (blue_x_y[2][0]>432 && blue_x_y[2][0]<504 && blue_x_y[2][1]>648 && blue_x_y[2][1]<1080)){// use x axis method instead
								blue_x_y[2][1] +=72;//inc y axis //red home col// removed
								turn_score+=1;
							}
							else if((blue_x_y[2][0]>0 && blue_x_y[2][0]<432 && blue_x_y[2][1]==468)||(blue_x_y[2][0]>648 && blue_x_y[2][0]<1080 && blue_x_y[2][1]==468)){
								blue_x_y[2][0] -=72;//dec x axis//
								turn_score+=1;
							}
							else if((blue_x_y[2][0]>648 && blue_x_y[2][0]<1080 && blue_x_y[2][1]==612)||(blue_x_y[2][0]>0 && blue_x_y[2][0]<432 && (blue_x_y[2][1]==612||blue_x_y[2][1]==540))){//adjusted
								if(blue_x_y[2][1]==540){	//blue base added 
										if(((468+72-blue_x_y[2][0])/72)<=dice_val){
											if(number_players>2) turn=3;
											else turn=1;
											return;
										}
									}

									blue_x_y[2][0] +=72;//inc x axis//
									turn_score+=1;
								}
							else if((blue_x_y[2][1]>0 && blue_x_y[2][1]<432 && blue_x_y[2][0]==612)||(blue_x_y[2][0]==612 && blue_x_y[2][1]<1080 && blue_x_y[2][1]>648)){
								blue_x_y[2][1] -=72;//dec y axis
								turn_score+=1;
							}
							else if((blue_x_y[2][1]>432 && blue_x_y[2][1]<648 && blue_x_y[2][0]==36)){
								blue_x_y[2][1] +=72;//inc y axis
								turn_score+=1;
							}
							else if((blue_x_y[2][0]>432 && blue_x_y[2][0]<648 && blue_x_y[2][1]==1044)){
								blue_x_y[2][0] +=72;//inc x axis
								turn_score+=1;
							}
							else if((blue_x_y[2][1]>432 && blue_x_y[2][1]<648 && blue_x_y[2][0]==1044)){
								blue_x_y[2][1] -=72;//dec y axis
								turn_score+=1;
							}
							else if((blue_x_y[2][0]>432 && blue_x_y[2][0]<648 && blue_x_y[2][1]==36)){
								blue_x_y[2][0] -=72;//dec x axis
								turn_score+=1;
							}
								//works nice!
						}
					}		//checked dec 28 11:28pm


						if(dice_val==6 && rearrange<3){	//goti 3// dice turn decide 
							dice_val=-9999;
							turn=2;
							rearrange++;
						}else if(dice_val==6 && rearrange==3){
								for(int k=0; k<4; k++){
									for(int o=0; o<2; o++){
										blue_x_y[k][o]=redoriginal[k][o];
									}
								}
								turn_score=0;
								scores[1]=current_score;
								dice_val=-999999;
								if(number_players>2){
								turn=3;
							}else turn=1;
								rearrange=0;
						}else if(dice_val>=1 && dice_val<=6){
							dice_val=-999999;
							rearrange=0;
							if(number_players>2){
								turn=3;
							}else turn=1;
						}

							for(int i=0; i<4; i++){// 0 // kill blue when red 1 turn
								for(int j=0; j<1; j++){//0
								if(blue_x_y[2][j]==red_x_y[i][j] && blue_x_y[2][j+1]==red_x_y[i][j+1]){// 00 00 01 01
								red_x_y[i][j]=start_pos[0][i][j]; //00 100
								red_x_y[i][j+1]=start_pos[0][i][j+1];// 01 101
								turn_score+=10;
								}
								}
								}

								for(int i=0; i<4; i++){// 0 //kill yellow when red 1
								for(int j=0; j<1; j++){//0
								if(blue_x_y[2][j]==yellow_x_y[i][j] && blue_x_y[2][j+1]==yellow_x_y[i][j+1]){// 00 00 01 01
								yellow_x_y[i][j]=start_pos[2][i][j]; //00 100
								yellow_x_y[i][j+1]=start_pos[2][i][j+1];// 01 101
								turn_score+=10;
								}
								}
								}

								for(int i=0; i<4; i++){// 0 //kill green when red 1
								for(int j=0; j<1; j++){//0
								if(blue_x_y[2][j]==green_x_y[i][j] && blue_x_y[2][j+1]==green_x_y[i][j+1]){// 00 00 01 01
								green_x_y[i][j]=start_pos[3][i][j]; //00 100
								green_x_y[i][j+1]=start_pos[3][i][j+1];// 01 101
								turn_score+=10;
								}
								}
								}
								scores[1]+=turn_score;
				}
		
					// add more keys 4
				if (key == 52) //turn 1 press 4
				{
					int turn_score=0;
					int current_score=scores[1];

					
					if(blue_x_y[3][0]==276 && blue_x_y[3][1]==924 && dice_val==6){		//starting point and check for 6 goti 
						blue_x_y[3][1]=612;
						blue_x_y[3][0]=108;//adjusted 
					}
					else if(blue_x_y[3][0]==276 && blue_x_y[3][1]==924 && dice_val!=6 && ((blue_x_y[0][0]!=156 || blue_x_y[0][1]!=804|| blue_x_y[1][0]!=276 || blue_x_y[1][1]!=804 || blue_x_y[2][0]!=156 || blue_x_y[2][1]!=924))){
							return;
							}


					else if(!(blue_x_y[3][0]==276 && blue_x_y[3][1]==924)) {
						for(int i=0; i<dice_val; i++){//multiple 6 rule add after
							if(blue_x_y[3][0]==468 && blue_x_y[3][1]==396){			// jumps and corners 
								blue_x_y[3][0]=396;
								blue_x_y[3][1]=468;//
								turn_score++;
								//i++;
								continue;
								/*for(int j=0; j<dice_val-i; j++){
									blue_x_y[3][0] -= 72;
								}
								break;*/
								}//continue this pattern
							else if(blue_x_y[3][0]==396 && blue_x_y[3][1]==612){
								blue_x_y[3][0]=468;
								blue_x_y[3][1]=684;//
								turn_score++;
								continue;
								}
							else if(blue_x_y[3][0]==612 && blue_x_y[3][1]==684){
								blue_x_y[3][0]=684;
								blue_x_y[3][1]=612;//
								turn_score++;
								continue;
								}
							else if(blue_x_y[3][0]==684 && blue_x_y[3][1]==468){
								blue_x_y[3][0]=612;
								blue_x_y[3][1]=396;//
								turn_score++;
								continue;
								}
							else if(blue_x_y[3][0]==36 && blue_x_y[3][1]==468){
								blue_x_y[3][0]=36;
								blue_x_y[3][1]=540;// 1st blue
								turn_score++;
								continue;
								}
							else if(blue_x_y[3][0]==36 && blue_x_y[3][1]==612){
								blue_x_y[3][0]=108;
								blue_x_y[3][1]=612;// 2nd blue
								turn_score++;
								continue;
								}
							else if(blue_x_y[3][0]==468 && blue_x_y[3][1]==1044){
								blue_x_y[3][0]=540;
								blue_x_y[3][1]=1044;// 1st yellow
								turn_score++;
								continue;
								}
							else if(blue_x_y[3][0]==612 && blue_x_y[3][1]==1044){
								blue_x_y[3][0]=612;
								blue_x_y[3][1]=972;// 2nd yellow
								turn_score++;
								continue;
								}
							else if(blue_x_y[3][0]==1044 && blue_x_y[3][1]==612){
								blue_x_y[3][0]=1044;
								blue_x_y[3][1]=540;// 1st green
								turn_score++;
								continue;
								}
							else if(blue_x_y[3][0]==1044 && blue_x_y[3][1]==468){
								blue_x_y[3][0]=972;
								blue_x_y[3][1]=468;// 2nd green
								turn_score++;
								continue;
								}
							else if(blue_x_y[3][0]==612 && blue_x_y[3][1]==36){
								blue_x_y[3][0]=540;
								blue_x_y[3][1]=36;// 1st red
								turn_score++;
								continue;
								}
							else if(blue_x_y[3][0]==36 && blue_x_y[3][1]==540){
								blue_x_y[3][0]=108;
								blue_x_y[3][1]=540;// red home column// removed
								turn_score+=15;
								continue;
								}
							
							if((blue_x_y[3][0]>432 && blue_x_y[3][0]<504 && blue_x_y[3][1]>0 && blue_x_y[3][1]<432) || (blue_x_y[3][0]>432 && blue_x_y[3][0]<504 && blue_x_y[3][1]>648 && blue_x_y[3][1]<1080)){// use x axis method instead
								blue_x_y[3][1] +=72;//inc y axis //red home col//removed
								turn_score+=1;
							}
							else if((blue_x_y[3][0]>0 && blue_x_y[3][0]<432 && blue_x_y[3][1]==468)||(blue_x_y[3][0]>648 && blue_x_y[3][0]<1080 && blue_x_y[3][1]==468)){
								blue_x_y[3][0] -=72;//dec x axis//
								turn_score+=1;
							}
							else if((blue_x_y[3][0]>648 && blue_x_y[3][0]<1080 && blue_x_y[3][1]==612)||(blue_x_y[3][0]>0 && blue_x_y[3][0]<432 && (blue_x_y[3][1]==612||blue_x_y[3][1]==540))){//adjusted
								if(blue_x_y[3][1]==540){								//blue base added 
										if(((468+72-blue_x_y[3][0])/72)<=dice_val){
											if(number_players>2) turn=3;
											else turn=1;
											return;
										}
									}

									blue_x_y[3][0] +=72;//inc x axis//
									turn_score+=1;
								}
							else if((blue_x_y[3][1]>0 && blue_x_y[3][1]<432 && blue_x_y[3][0]==612)||(blue_x_y[3][0]==612 && blue_x_y[3][1]<1080 && blue_x_y[3][1]>648)){
								blue_x_y[3][1] -=72;//dec y axis
								turn_score+=1;
							}
							else if((blue_x_y[3][1]>432 && blue_x_y[3][1]<648 && blue_x_y[3][0]==36)){
								blue_x_y[3][1] +=72;//inc y axis
								turn_score+=1;
							}
							else if((blue_x_y[3][0]>432 && blue_x_y[3][0]<648 && blue_x_y[3][1]==1044)){
								blue_x_y[3][0] +=72;//inc x axis
								turn_score+=1;
							}
							else if((blue_x_y[3][1]>432 && blue_x_y[3][1]<648 && blue_x_y[3][0]==1044)){
								blue_x_y[3][1] -=72;//dec y axis
								turn_score+=1;
							}
							else if((blue_x_y[3][0]>432 && blue_x_y[3][0]<648 && blue_x_y[3][1]==36)){
								blue_x_y[3][0] -=72;//dec x axis
								turn_score+=1;
							}
								//works nice!
						}		//checked dec 28 11:28pm
					}
				
					if(dice_val==6 && rearrange<3){	//goti 4 // dice turn decision 
							dice_val=-9999;
							turn=2;
							rearrange++;
						}else if(dice_val==6 && rearrange==3){
								for(int k=0; k<4; k++){
									for(int o=0; o<2; o++){
										blue_x_y[k][o]=redoriginal[k][o];
									}
								}
								turn_score=0;
								scores[1]=current_score;
								dice_val=-999999;
								if(number_players>2){
								turn=3;
							}else turn=1;
								rearrange=0;
						}else if(dice_val>=1 && dice_val<=6){
							dice_val=-999999;
							rearrange=0;
							if(number_players>2){
								turn=3;
							}else turn=1;
						}
				
							for(int i=0; i<4; i++){// 0 // kill blue when red 1 turn
								for(int j=0; j<1; j++){//0
								if(blue_x_y[3][j]==red_x_y[i][j] && blue_x_y[3][j+1]==red_x_y[i][j+1]){// 00 00 01 01
								red_x_y[i][j]=start_pos[0][i][j]; //00 100
								red_x_y[i][j+1]=start_pos[0][i][j+1];// 01 101
								turn_score+=10;
								}
								}
								}

								for(int i=0; i<4; i++){// 0 //kill yellow when red 1
								for(int j=0; j<1; j++){//0
								if(blue_x_y[3][j]==yellow_x_y[i][j] && blue_x_y[3][j+1]==yellow_x_y[i][j+1]){// 00 00 01 01
								yellow_x_y[i][j]=start_pos[2][i][j]; //00 100
								yellow_x_y[i][j+1]=start_pos[2][i][j+1];// 01 101
								turn_score+=10;
								}
								}
								}

								for(int i=0; i<4; i++){// 0 //kill green when red 1
								for(int j=0; j<1; j++){//0
								if(blue_x_y[3][j]==green_x_y[i][j] && blue_x_y[3][j+1]==green_x_y[i][j+1]){// 00 00 01 01
								green_x_y[i][j]=start_pos[3][i][j]; //00 100
								green_x_y[i][j+1]=start_pos[3][i][j+1];// 01 101
								turn_score+=10;
								}
								}
								}
						scores[1]+=turn_score;
				}
					// in turn 2


					/*for(int i=0; i<4; i++){
						kill_count[1]=0;
						for(int j=0; j<2; j++){
							if(blue_x_y[i][j]==red_x_y[i][j]){
								kill_count[1]++;
								if(kill_count[1]==1 || kill_count[1]==2){
								red_x_y[i][j]=start_pos[0][i][j];
								}
							}
							else if(blue_x_y[i][j]==yellow_x_y[i][j]){
								kill_count[1]++;
								if(kill_count[1]==1 || kill_count[1]==2)yellow_x_y[i][j]=start_pos[2][i][j];
							}
							else if(blue_x_y[i][j]==green_x_y[i][j]){
								kill_count[1]++;
								if(kill_count[1]==1 || kill_count[1]==2) green_x_y[i][j]=start_pos[3][i][j];
							}
						}
					}*/
			// win system 
				if(blue_x_y[0][0]==blue_x_y[1][0] && blue_x_y[0][0]==blue_x_y[2][0] && blue_x_y[0][0]==blue_x_y[3][0] && blue_x_y[0][1]==blue_x_y[1][1] && blue_x_y[0][1]==blue_x_y[2][1] && blue_x_y[0][1]==blue_x_y[3][1]){
						win[1]=1;
					for(int i=0; i<number_players; i++){
						if (pl_c[i]==1) cout<<"\n"<<saved_names[i]<<"Wins!\n"<<endl;
							}
						highscore_add();
					}

}

void turn3_steps(unsigned char key){	// function used to seperate steps for turn 3 

		//turn 3 yellow


				if(rearrange==0){		// one time run check
					for(int i=0; i<4; i++){
						for(int j=0; j<2; j++){
							redoriginal[i][j]=yellow_x_y[i][j];	// stores original positions for red gotis 
						}
					}
					rearrange++;	//prevent rearrange in same turn
			}


			if (key == 49) //turn 3 press 1
					{
						int turn_score=0;
						int current_score=scores[2];



						if(yellow_x_y[0][0]==804 && yellow_x_y[0][1]==804 && dice_val==6){		//starting point and check for 6 goti 1
							yellow_x_y[0][1]=972;
							yellow_x_y[0][0]=612;	//adjusted
						}
						else if(yellow_x_y[0][0]==804 && yellow_x_y[0][1]==804 && dice_val!=6 && ((yellow_x_y[1][0]!=924 || yellow_x_y[1][1]!=804 || yellow_x_y[2][0]!=804 || yellow_x_y[2][1]!=924 || yellow_x_y[3][0]!=924 || yellow_x_y[3][1]!=924))){
							return;
							} 


						else if(!(yellow_x_y[0][0]==804 && yellow_x_y[0][1]==804)) {			//out of base
							for(int i=0; i<dice_val; i++){//multiple 6 rule add after
								if(yellow_x_y[0][0]==468 && yellow_x_y[0][1]==396){
									yellow_x_y[0][0]=396;									// corners and jummps 
									yellow_x_y[0][1]=468;//
									turn_score++;
									//i++;
									continue;
									/*for(int j=0; j<dice_val-i; j++){
										yellow_x_y[0][0] -= 72;
									}
									break;*/
									}//continue this pattern
								else if(yellow_x_y[0][0]==396 && yellow_x_y[0][1]==612){
									yellow_x_y[0][0]=468;
									yellow_x_y[0][1]=684;//
									turn_score++;
									continue;
									}
								else if(yellow_x_y[0][0]==612 && yellow_x_y[0][1]==684){
									yellow_x_y[0][0]=684;
									yellow_x_y[0][1]=612;//
									turn_score++;
									continue;
									}
								else if(yellow_x_y[0][0]==684 && yellow_x_y[0][1]==468){
									yellow_x_y[0][0]=612;
									yellow_x_y[0][1]=396;//
									turn_score++;
									continue;
									}
								else if(yellow_x_y[0][0]==36 && yellow_x_y[0][1]==468){
									yellow_x_y[0][0]=36;
									yellow_x_y[0][1]=540;// 1st blue
									turn_score++;
									continue;
									}
								else if(yellow_x_y[0][0]==36 && yellow_x_y[0][1]==612){
									yellow_x_y[0][0]=108;
									yellow_x_y[0][1]=612;// 2nd blue
									turn_score++;
									continue;
									}
								else if(yellow_x_y[0][0]==468 && yellow_x_y[0][1]==1044){
									yellow_x_y[0][0]=540;
									yellow_x_y[0][1]=1044;// 1st yellow
									turn_score++;
									continue;
									}
								else if(yellow_x_y[0][0]==612 && yellow_x_y[0][1]==1044){
									yellow_x_y[0][0]=612;
									yellow_x_y[0][1]=972;// 2nd yellow
									turn_score++;
									continue;
									}
								else if(yellow_x_y[0][0]==1044 && yellow_x_y[0][1]==612){
									yellow_x_y[0][0]=1044;
									yellow_x_y[0][1]=540;// 1st green
									turn_score++;
									continue;
									}
								else if(yellow_x_y[0][0]==1044 && yellow_x_y[0][1]==468){
									yellow_x_y[0][0]=972;
									yellow_x_y[0][1]=468;// 2nd green
									turn_score++;
									continue;
									}
								else if(yellow_x_y[0][0]==612 && yellow_x_y[0][1]==36){
									yellow_x_y[0][0]=540;
									yellow_x_y[0][1]=36;// 1st red
									turn_score++;
									continue;
									}
								else if(yellow_x_y[0][0]==540 && yellow_x_y[0][1]==1044){
									yellow_x_y[0][0]=540;
									yellow_x_y[0][1]=972;// red home column// yellowed
									turn_score+=15;
									continue;
									}
								
								if((yellow_x_y[0][0]>432 && yellow_x_y[0][0]<504 && yellow_x_y[0][1]>0 && yellow_x_y[0][1]<432) || (yellow_x_y[0][0]>432 && yellow_x_y[0][0]<504 && yellow_x_y[0][1]>648 && yellow_x_y[0][1]<1080)){// use x axis method instead
									yellow_x_y[0][1] +=72;//inc y axis //red home col// removed
									turn_score+=1;
								}
								else if((yellow_x_y[0][0]>0 && yellow_x_y[0][0]<432 && yellow_x_y[0][1]==468)||(yellow_x_y[0][0]>648 && yellow_x_y[0][0]<1080 && yellow_x_y[0][1]==468)){
									yellow_x_y[0][0] -=72;//dec x axis//
									turn_score+=1;
								}
								else if((yellow_x_y[0][0]>648 && yellow_x_y[0][0]<1080 && yellow_x_y[0][1]==612)||(yellow_x_y[0][0]>0 && yellow_x_y[0][0]<432 && yellow_x_y[0][1]==612)){
									yellow_x_y[0][0] +=72;//inc x axis//
									turn_score+=1;
								}
								else if((yellow_x_y[0][1]>0 && yellow_x_y[0][1]<432 && yellow_x_y[0][0]==612)||((yellow_x_y[0][0]==612||yellow_x_y[0][0]==540) && yellow_x_y[0][1]<1080 && yellow_x_y[0][1]>648)){
									if(yellow_x_y[0][0]==540){							// yellow base added 
										if(((yellow_x_y[0][1]-612-72)/72)<=dice_val){
											if(number_players>3) turn=4;
											else turn=1;
											return;
										}
									}
									
									yellow_x_y[0][1] -=72;//dec y axis// yellow added
									turn_score+=1;
								}
								else if((yellow_x_y[0][1]>432 && yellow_x_y[0][1]<648 && yellow_x_y[0][0]==36)){
									yellow_x_y[0][1] +=72;//inc y axis
									turn_score+=1;
								}
								else if((yellow_x_y[0][0]>432 && yellow_x_y[0][0]<648 && yellow_x_y[0][1]==1044)){
									yellow_x_y[0][0] +=72;//inc x axis
									turn_score+=1;
								}
								else if((yellow_x_y[0][1]>432 && yellow_x_y[0][1]<648 && yellow_x_y[0][0]==1044)){
									yellow_x_y[0][1] -=72;//dec y axis
									turn_score+=1;
								}
								else if((yellow_x_y[0][0]>432 && yellow_x_y[0][0]<648 && yellow_x_y[0][1]==36)){
									yellow_x_y[0][0] -=72;//dec x axis
									turn_score+=1;
								}
									//works nice!
							}
						}


					if(dice_val==6 && rearrange<3){	//goti 1 // turn dice decide 
							dice_val=-9999;
							turn=3;
							rearrange++;
						}else if(dice_val==6 && rearrange==3){
								for(int k=0; k<4; k++){
									for(int o=0; o<2; o++){
										yellow_x_y[k][o]=redoriginal[k][o];
									}
								}
								turn_score=0;
								scores[2]=current_score;
								dice_val=-999999;
								if(number_players>3){
								turn=4;
							}else turn=1;
								rearrange=0;
						}else if(dice_val>=1 && dice_val<=6){
							dice_val=-999999;
							rearrange=0;
							if(number_players>3){
								turn=4;
							}else turn=1;
						}

							for(int i=0; i<4; i++){// 0		// kill blue when red 1 turn
								
								for(int j=0; j<1; j++){//0
									if(yellow_x_y[0][j]==red_x_y[i][j] && yellow_x_y[0][j+1]==red_x_y[i][j+1]){// 00 00 01 01
										red_x_y[i][j]=start_pos[0][i][j];  //00 100
										red_x_y[i][j+1]=start_pos[0][i][j+1];// 01 101
										turn_score+=10;
									}
								}
							}

							for(int i=0; i<4; i++){// 0 	//kill yellow when red 1
								
								for(int j=0; j<1; j++){//0
									if(yellow_x_y[0][j]==blue_x_y[i][j] && yellow_x_y[0][j+1]==blue_x_y[i][j+1]){// 00 00 01 01
										blue_x_y[i][j]=start_pos[1][i][j];  //00 100
										blue_x_y[i][j+1]=start_pos[1][i][j+1];// 01 101
										turn_score+=10;
									}
								}
							}

							for(int i=0; i<4; i++){// 0 	//kill green when red 1
								
								for(int j=0; j<1; j++){//0
									if(yellow_x_y[0][j]==green_x_y[i][j] && yellow_x_y[0][j+1]==green_x_y[i][j+1]){// 00 00 01 01
										green_x_y[i][j]=start_pos[3][i][j];  //00 100
										green_x_y[i][j+1]=start_pos[3][i][j+1];// 01 101
										turn_score+=10;
									}
								}
							}
						scores[2]+=turn_score;
					}	
			
				
					//add more keys 2
					if (key == 50) //turn 3 press 2
					{
						int turn_score=0;
						int current_score=scores[2];
						
						if(yellow_x_y[1][0]==924 && yellow_x_y[1][1]==804 && dice_val==6){		//starting point and check for 6 goti 2
							yellow_x_y[1][1]=972;
							yellow_x_y[1][0]=612; //adjusted
						}

						else if(yellow_x_y[1][0]==924 && yellow_x_y[1][1]==804 && dice_val!=6 && ((yellow_x_y[0][0]!=804 || yellow_x_y[0][1]!=804|| yellow_x_y[2][0]!=804 || yellow_x_y[2][1]!=924 || yellow_x_y[3][0]!=924 || yellow_x_y[3][1]!=924))){
								return;
								} 

						else if(!(yellow_x_y[1][0]==924 && yellow_x_y[1][1]==804)) {			//out of base
							for(int i=0; i<dice_val; i++){//multiple 6 rule add after
								if(yellow_x_y[1][0]==468 && yellow_x_y[1][1]==396){					// shifts and corners
									yellow_x_y[1][0]=396;
									yellow_x_y[1][1]=468;//
									turn_score++;
									//i++;
									continue;
									/*for(int j=0; j<dice_val-i; j++){
										yellow_x_y[1][0] -= 72;
									}
									break;*/
									}//continue this pattern
								else if(yellow_x_y[1][0]==396 && yellow_x_y[1][1]==612){
									yellow_x_y[1][0]=468;
									yellow_x_y[1][1]=684;//
									turn_score++;
									continue;
									}
								else if(yellow_x_y[1][0]==612 && yellow_x_y[1][1]==684){
									yellow_x_y[1][0]=684;
									yellow_x_y[1][1]=612;//
									turn_score++;
									continue;
									}
								else if(yellow_x_y[1][0]==684 && yellow_x_y[1][1]==468){
									yellow_x_y[1][0]=612;
									yellow_x_y[1][1]=396;//
									turn_score++;
									continue;
									}
								else if(yellow_x_y[1][0]==36 && yellow_x_y[1][1]==468){
									yellow_x_y[1][0]=36;
									yellow_x_y[1][1]=540;// 1st blue
									turn_score++;
									continue;
									}
								else if(yellow_x_y[1][0]==36 && yellow_x_y[1][1]==612){
									yellow_x_y[1][0]=108;
									yellow_x_y[1][1]=612;// 2nd blue
									turn_score++;
									continue;
									}
								else if(yellow_x_y[1][0]==468 && yellow_x_y[1][1]==1044){
									yellow_x_y[1][0]=540;
									yellow_x_y[1][1]=1044;// 1st yellow
									turn_score++;
									continue;
									}
								else if(yellow_x_y[1][0]==612 && yellow_x_y[1][1]==1044){
									yellow_x_y[1][0]=612;
									yellow_x_y[1][1]=972;// 2nd yellow
									turn_score++;
									continue;
									}
								else if(yellow_x_y[1][0]==1044 && yellow_x_y[1][1]==612){
									yellow_x_y[1][0]=1044;
									yellow_x_y[1][1]=540;// 1st green
									turn_score++;
									continue;
									}
								else if(yellow_x_y[1][0]==1044 && yellow_x_y[1][1]==468){
									yellow_x_y[1][0]=972;
									yellow_x_y[1][1]=468;// 2nd green
									turn_score++;
									continue;
									}
								else if(yellow_x_y[1][0]==612 && yellow_x_y[1][1]==36){
									yellow_x_y[1][0]=540;
									yellow_x_y[1][1]=36;// 1st red
									turn_score++;
									continue;
									}
								else if(yellow_x_y[1][0]==540 && yellow_x_y[1][1]==1044){
									yellow_x_y[1][0]=540;
									yellow_x_y[1][1]=972;// red home column // yellow 
									turn_score+=15;
									continue;
									}
								
								if((yellow_x_y[1][0]>432 && yellow_x_y[1][0]<504 && yellow_x_y[1][1]>0 && yellow_x_y[1][1]<432) || (yellow_x_y[1][0]>432 && yellow_x_y[1][0]<504 && yellow_x_y[1][1]>648 && yellow_x_y[1][1]<1080)){// use x axis method instead
									yellow_x_y[1][1] +=72;//inc y axis //red home col// removed
									turn_score+=1;
								}
								else if((yellow_x_y[1][0]>0 && yellow_x_y[1][0]<432 && yellow_x_y[1][1]==468)||(yellow_x_y[1][0]>648 && yellow_x_y[1][0]<1080 && yellow_x_y[1][1]==468)){
									yellow_x_y[1][0] -=72;//dec x axis//
									turn_score+=1;
								}
								else if((yellow_x_y[1][0]>648 && yellow_x_y[1][0]<1080 && yellow_x_y[1][1]==612)||(yellow_x_y[1][0]>0 && yellow_x_y[1][0]<432 && yellow_x_y[1][1]==612)){
									yellow_x_y[1][0] +=72;//inc x axis//
									turn_score+=1;
								}
								else if((yellow_x_y[1][1]>0 && yellow_x_y[1][1]<432 && yellow_x_y[1][0]==612)||((yellow_x_y[1][0]==612||yellow_x_y[1][0]==540) && yellow_x_y[1][1]<1080 && yellow_x_y[1][1]>648)){
									if(yellow_x_y[1][0]==540){
										if(((yellow_x_y[1][1]-612-72)/72)<=dice_val){
											if(number_players>3) turn=4;
											else turn=1;
											return;
										}
									}
									
									yellow_x_y[1][1] -=72;//dec y axis// yellow added
									turn_score+=1;
								}
								else if((yellow_x_y[1][1]>432 && yellow_x_y[1][1]<648 && yellow_x_y[1][0]==36)){
									yellow_x_y[1][1] +=72;//inc y axis
									turn_score+=1;
								}
								else if((yellow_x_y[1][0]>432 && yellow_x_y[1][0]<648 && yellow_x_y[1][1]==1044)){
									yellow_x_y[1][0] +=72;//inc x axis
									turn_score+=1;
								}
								else if((yellow_x_y[1][1]>432 && yellow_x_y[1][1]<648 && yellow_x_y[1][0]==1044)){
									yellow_x_y[1][1] -=72;//dec y axis
									turn_score+=1;
								}
								else if((yellow_x_y[1][0]>432 && yellow_x_y[1][0]<648 && yellow_x_y[1][1]==36)){
									yellow_x_y[1][0] -=72;//dec x axis
									turn_score+=1;
								}
									//works nice!
							}
						}
					

					if(dice_val==6 && rearrange<3){	//goti 2
							dice_val=-9999;
							turn=3;
							rearrange++;
						}else if(dice_val==6 && rearrange==3){
								for(int k=0; k<4; k++){
									for(int o=0; o<2; o++){
										yellow_x_y[k][o]=redoriginal[k][o];
									}
								}
								turn_score=0;
								scores[2]=current_score;
								dice_val=-999999;
								if(number_players>3){
								turn=4;
							}else turn=1;
								rearrange=0;
						}else if(dice_val>=1 && dice_val<=6){
							dice_val=-999999;
							rearrange=0;
							if(number_players>3){
								turn=4;
							}else {
								turn=1;
								}
						}
					
					
					
									for(int i=0; i<4; i++){// 0 // kill blue when red 1 turn
										for(int j=0; j<1; j++){//0
										if(yellow_x_y[1][j]==red_x_y[i][j] && yellow_x_y[1][j+1]==red_x_y[i][j+1]){// 00 00 01 01
										red_x_y[i][j]=start_pos[0][i][j]; //00 100
										red_x_y[i][j+1]=start_pos[0][i][j+1];// 01 101
										turn_score+=10;
										}
										}
										}

										for(int i=0; i<4; i++){// 0 //kill yellow when red 1
										for(int j=0; j<1; j++){//0
										if(yellow_x_y[1][j]==blue_x_y[i][j] && yellow_x_y[1][j+1]==blue_x_y[i][j+1]){// 00 00 01 01
										blue_x_y[i][j]=start_pos[1][i][j]; //00 100
										blue_x_y[i][j+1]=start_pos[1][i][j+1];// 01 101
										turn_score+=10;
										}
										}
										}

										for(int i=0; i<4; i++){// 0 //kill green when red 1
										for(int j=0; j<1; j++){//0
										if(yellow_x_y[1][j]==green_x_y[i][j] && yellow_x_y[1][j+1]==green_x_y[i][j+1]){// 00 00 01 01
										green_x_y[i][j]=start_pos[3][i][j]; //00 100
										green_x_y[i][j+1]=start_pos[3][i][j+1];// 01 101
										turn_score+=10;
										}
										}
										}

						scores[2]+=turn_score;
					}
								// add more keys 3
				if (key == 51) //turn 3 press 3
				{
					int turn_score=0;
					int current_score=scores[2];

					
					if(yellow_x_y[2][0]==804 && yellow_x_y[2][1]==924 && dice_val==6){		//starting point and check for 6 goti 3
						yellow_x_y[2][1]=972;
						yellow_x_y[2][0]=612; // adjusted
					}


						else if(yellow_x_y[2][0]==804 && yellow_x_y[2][1]==924 && dice_val!=6 && ((yellow_x_y[0][0]!=804 || yellow_x_y[0][1]!=804|| yellow_x_y[1][0]!=924 || yellow_x_y[1][1]!=804 || yellow_x_y[3][0]!=924 || yellow_x_y[3][1]!=924))){
								return;
								}


					else if(!(yellow_x_y[2][0]==804 && yellow_x_y[2][1]==924)) {
						for(int i=0; i<dice_val; i++){//multiple 6 rule add after
							if(yellow_x_y[2][0]==468 && yellow_x_y[2][1]==396){
								yellow_x_y[2][0]=396;								// shifts and corners 
								yellow_x_y[2][1]=468;//
								turn_score++;
								//i++;
								continue;
								/*for(int j=0; j<dice_val-i; j++){
									yellow_x_y[2][0] -= 72;
								}
								break;*/
								}//continue this pattern
							else if(yellow_x_y[2][0]==396 && yellow_x_y[2][1]==612){
								yellow_x_y[2][0]=468;
								yellow_x_y[2][1]=684;//
								turn_score++;
								continue;
								}
							else if(yellow_x_y[2][0]==612 && yellow_x_y[2][1]==684){
								yellow_x_y[2][0]=684;
								yellow_x_y[2][1]=612;//
								turn_score++;
								continue;
								}
							else if(yellow_x_y[2][0]==684 && yellow_x_y[2][1]==468){
								yellow_x_y[2][0]=612;
								yellow_x_y[2][1]=396;//
								turn_score++;
								continue;
								}
							else if(yellow_x_y[2][0]==36 && yellow_x_y[2][1]==468){
								yellow_x_y[2][0]=36;
								yellow_x_y[2][1]=540;// 1st blue
								turn_score++;
								continue;
								}
							else if(yellow_x_y[2][0]==36 && yellow_x_y[2][1]==612){
								yellow_x_y[2][0]=108;
								yellow_x_y[2][1]=612;// 2nd blue
								turn_score++;
								continue;
								}
							else if(yellow_x_y[2][0]==468 && yellow_x_y[2][1]==1044){
								yellow_x_y[2][0]=540;
								yellow_x_y[2][1]=1044;// 1st yellow
								turn_score++;
								continue;
								}
							else if(yellow_x_y[2][0]==612 && yellow_x_y[2][1]==1044){
								yellow_x_y[2][0]=612;
								yellow_x_y[2][1]=972;// 2nd yellow
								turn_score++;
								continue;
								}
							else if(yellow_x_y[2][0]==1044 && yellow_x_y[2][1]==612){
								yellow_x_y[2][0]=1044;
								yellow_x_y[2][1]=540;// 1st green
								turn_score++;
								continue;
								}
							else if(yellow_x_y[2][0]==1044 && yellow_x_y[2][1]==468){
								yellow_x_y[2][0]=972;
								yellow_x_y[2][1]=468;// 2nd green
								turn_score++;
								continue;
								}
							else if(yellow_x_y[2][0]==612 && yellow_x_y[2][1]==36){
								yellow_x_y[2][0]=540;
								yellow_x_y[2][1]=36;// 1st red
								turn_score++;
								continue;
								}
							else if(yellow_x_y[2][0]==540 && yellow_x_y[2][1]==1044){
								yellow_x_y[2][0]=540;
								yellow_x_y[2][1]=972;// red home column // yellowed
								turn_score+=15;
								continue;
								}
							
							if((yellow_x_y[2][0]>432 && yellow_x_y[2][0]<504 && yellow_x_y[2][1]>0 && yellow_x_y[2][1]<432) || (yellow_x_y[2][0]>432 && yellow_x_y[2][0]<504 && yellow_x_y[2][1]>648 && yellow_x_y[2][1]<1080)){// use x axis method instead
								yellow_x_y[2][1] +=72;//inc y axis //red home col// removed
								turn_score+=1;
							}
							else if((yellow_x_y[2][0]>0 && yellow_x_y[2][0]<432 && yellow_x_y[2][1]==468)||(yellow_x_y[2][0]>648 && yellow_x_y[2][0]<1080 && yellow_x_y[2][1]==468)){
								yellow_x_y[2][0] -=72;//dec x axis//
								turn_score+=1;
							}
							else if((yellow_x_y[2][0]>648 && yellow_x_y[2][0]<1080 && yellow_x_y[2][1]==612)||(yellow_x_y[2][0]>0 && yellow_x_y[2][0]<432 && yellow_x_y[2][1]==612)){
								yellow_x_y[2][0] +=72;//inc x axis//
								turn_score+=1;
							}
							else if((yellow_x_y[2][1]>0 && yellow_x_y[2][1]<432 && yellow_x_y[2][0]==612)||((yellow_x_y[2][0]==612||yellow_x_y[1][0]==540) && yellow_x_y[2][1]<1080 && yellow_x_y[2][1]>648)){
								if(yellow_x_y[2][0]==540){								// yellow base aded 
										if(((yellow_x_y[2][1]-612-72)/72)<=dice_val){
											if(number_players>3) turn=4;
											else turn=1;
											return;
										}
									}
									
									yellow_x_y[2][1] -=72;//dec y axis// yellow added
									turn_score+=1;
								}
							else if((yellow_x_y[2][1]>432 && yellow_x_y[2][1]<648 && yellow_x_y[2][0]==36)){
								yellow_x_y[2][1] +=72;//inc y axis
								turn_score+=1;
							}
							else if((yellow_x_y[2][0]>432 && yellow_x_y[2][0]<648 && yellow_x_y[2][1]==1044)){
								yellow_x_y[2][0] +=72;//inc x axis
								turn_score+=1;
							}
							else if((yellow_x_y[2][1]>432 && yellow_x_y[2][1]<648 && yellow_x_y[2][0]==1044)){
								yellow_x_y[2][1] -=72;//dec y axis
								turn_score+=1;
							}
							else if((yellow_x_y[2][0]>432 && yellow_x_y[2][0]<648 && yellow_x_y[2][1]==36)){
								yellow_x_y[2][0] -=72;//dec x axis
								turn_score+=1;
							}
								//works nice!
						}
					}

				

					if(dice_val==6 && rearrange<3){	//goti 3
							dice_val=-9999;
							turn=3;
							rearrange++;
						}else if(dice_val==6 && rearrange==3){
								for(int k=0; k<4; k++){
									for(int o=0; o<2; o++){
										yellow_x_y[k][o]=redoriginal[k][o];
									}
								}
								turn_score=0;
								scores[2]=current_score;
								dice_val=-999999;
								if(number_players>3){
								turn=4;
							}else turn=1;
								rearrange=0;
						}else if(dice_val>=1 && dice_val<=6){
							dice_val=-999999;
							rearrange=0;
							if(number_players>3){
								turn=4;
							}else {
								turn=1;
								
							}
						}
				
				
							for(int i=0; i<4; i++){// 0 // kill blue when red 1 turn
									for(int j=0; j<1; j++){//0
									if(yellow_x_y[2][j]==red_x_y[i][j] && yellow_x_y[2][j+1]==red_x_y[i][j+1]){// 00 00 01 01
									red_x_y[i][j]=start_pos[0][i][j]; //00 100
									red_x_y[i][j+1]=start_pos[0][i][j+1];// 01 101
									turn_score+=10;
									}
									}
									}

									for(int i=0; i<4; i++){// 0 //kill yellow when red 1
									for(int j=0; j<1; j++){//0
									if(yellow_x_y[2][j]==blue_x_y[i][j] && yellow_x_y[2][j+1]==blue_x_y[i][j+1]){// 00 00 01 01
									blue_x_y[i][j]=start_pos[1][i][j]; //00 100
									blue_x_y[i][j+1]=start_pos[1][i][j+1];// 01 101
									turn_score+=10;
									}
									}
									}

									for(int i=0; i<4; i++){// 0 //kill green when red 1
									for(int j=0; j<1; j++){//0
									if(yellow_x_y[2][j]==green_x_y[i][j] && yellow_x_y[2][j+1]==green_x_y[i][j+1]){// 00 00 01 01
									green_x_y[i][j]=start_pos[3][i][j]; //00 100
									green_x_y[i][j+1]=start_pos[3][i][j+1];// 01 101
									turn_score+=10;
									}
									}
									}
						scores[2]+=turn_score;

				}
					// add more keys 4

				if (key == 52) //turn 1 press 4
				{
					int turn_score=0;
					int current_score=scores[2];

					if(yellow_x_y[3][0]==924 && yellow_x_y[3][1]==924 && dice_val==6){		//starting point and check for 6 goti 4
						yellow_x_y[3][1]=972;
						yellow_x_y[3][0]=612; // adjusted
					}

						else if(yellow_x_y[3][0]==924 && yellow_x_y[3][1]==924 && dice_val!=6 && ((yellow_x_y[0][0]!=804 || yellow_x_y[0][1]!=804|| yellow_x_y[1][0]!=924 || yellow_x_y[1][1]!=804 || yellow_x_y[2][0]!=804 || yellow_x_y[2][1]!=924))){
								return;
								}



					else if(!(yellow_x_y[3][0]==276 && yellow_x_y[3][1]==276)) {
						for(int i=0; i<dice_val; i++){//multiple 6 rule add after
							if(yellow_x_y[3][0]==468 && yellow_x_y[3][1]==396){
								yellow_x_y[3][0]=396;
								yellow_x_y[3][1]=468;//
								turn_score++;
								//i++;
								continue;
								/*for(int j=0; j<dice_val-i; j++){
									yellow_x_y[3][0] -= 72;
								}
								break;*/
								}//continue this pattern
							else if(yellow_x_y[3][0]==396 && yellow_x_y[3][1]==612){
								yellow_x_y[3][0]=468;
								yellow_x_y[3][1]=684;//
								turn_score++;
								continue;
								}
							else if(yellow_x_y[3][0]==612 && yellow_x_y[3][1]==684){
								yellow_x_y[3][0]=684;
								yellow_x_y[3][1]=612;//
								turn_score++;
								continue;
								}
							else if(yellow_x_y[3][0]==684 && yellow_x_y[3][1]==468){
								yellow_x_y[3][0]=612;
								yellow_x_y[3][1]=396;//
								turn_score++;
								continue;
								}
							else if(yellow_x_y[3][0]==36 && yellow_x_y[3][1]==468){
								yellow_x_y[3][0]=36;
								yellow_x_y[3][1]=540;// 1st blue
								turn_score++;
								continue;
								}
							else if(yellow_x_y[3][0]==36 && yellow_x_y[3][1]==612){
								yellow_x_y[3][0]=108;
								yellow_x_y[3][1]=612;// 2nd blue
								turn_score++;
								continue;
								}
							else if(yellow_x_y[3][0]==468 && yellow_x_y[3][1]==1044){
								yellow_x_y[3][0]=540;
								yellow_x_y[3][1]=1044;// 1st yellow
								turn_score++;
								continue;
								}
							else if(yellow_x_y[3][0]==612 && yellow_x_y[3][1]==1044){
								yellow_x_y[3][0]=612;
								yellow_x_y[3][1]=972;// 2nd yellow
								turn_score++;
								continue;
								}
							else if(yellow_x_y[3][0]==1044 && yellow_x_y[3][1]==612){
								yellow_x_y[3][0]=1044;
								yellow_x_y[3][1]=540;// 1st green
								turn_score++;
								continue;
								}
							else if(yellow_x_y[3][0]==1044 && yellow_x_y[3][1]==468){
								yellow_x_y[3][0]=972;
								yellow_x_y[3][1]=468;// 2nd green
								turn_score++;
								continue;
								}
							else if(yellow_x_y[3][0]==612 && yellow_x_y[3][1]==36){
								yellow_x_y[3][0]=540;
								yellow_x_y[3][1]=36;// 1st red
								turn_score++;
								continue;
								}
							else if(yellow_x_y[3][0]==540 && yellow_x_y[3][1]==1044){
								yellow_x_y[3][0]=540;
								yellow_x_y[3][1]=972;// red home column // yellowed //
								turn_score+=15;
								continue;
								}
							
							if((yellow_x_y[3][0]>432 && yellow_x_y[3][0]<504 && yellow_x_y[3][1]>0 && yellow_x_y[3][1]<432) || (yellow_x_y[3][0]>432 && yellow_x_y[3][0]<504 && yellow_x_y[3][1]>648 && yellow_x_y[3][1]<1080)){// use x axis method instead
								yellow_x_y[3][1] +=72;//inc y axis //red home col// removed
								turn_score+=1;
							}
							else if((yellow_x_y[3][0]>0 && yellow_x_y[3][0]<432 && yellow_x_y[3][1]==468)||(yellow_x_y[3][0]>648 && yellow_x_y[3][0]<1080 && yellow_x_y[3][1]==468)){
								yellow_x_y[3][0] -=72;//dec x axis//
								turn_score+=1;
							}
							else if((yellow_x_y[3][0]>648 && yellow_x_y[3][0]<1080 && yellow_x_y[3][1]==612)||(yellow_x_y[3][0]>0 && yellow_x_y[3][0]<432 && yellow_x_y[3][1]==612)){
								yellow_x_y[3][0] +=72;//inc x axis//
								turn_score+=1;
							}
							else if((yellow_x_y[3][1]>0 && yellow_x_y[3][1]<432 && yellow_x_y[3][0]==612)||((yellow_x_y[3][0]==612||yellow_x_y[3][0]==540) && yellow_x_y[3][1]<1080 && yellow_x_y[3][1]>648)){
								if(yellow_x_y[3][0]==540){
										if(((yellow_x_y[3][1]-612-72)/72)<=dice_val){
											if(number_players>3) turn=4;
											else turn=1;
											return;
										}
									}
									
									yellow_x_y[3][1] -=72;//dec y axis// yellow added
									turn_score+=1;
								}
							else if((yellow_x_y[3][1]>432 && yellow_x_y[3][1]<648 && yellow_x_y[3][0]==36)){
								yellow_x_y[3][1] +=72;//inc y axis
								turn_score+=1;
							}
							else if((yellow_x_y[3][0]>432 && yellow_x_y[3][0]<648 && yellow_x_y[3][1]==1044)){
								yellow_x_y[3][0] +=72;//inc x axis
								turn_score+=1;
							}
							else if((yellow_x_y[3][1]>432 && yellow_x_y[3][1]<648 && yellow_x_y[3][0]==1044)){
								yellow_x_y[3][1] -=72;//dec y axis
								turn_score+=1;
							}
							else if((yellow_x_y[3][0]>432 && yellow_x_y[3][0]<648 && yellow_x_y[3][1]==36)){
								yellow_x_y[3][0] -=72;//dec x axis
								turn_score+=1;
							}
								//works nice!
								// all yellow checked dec 29 1:29 am
						}
					}


					if(dice_val==6 && rearrange<3){	//goti 4
							dice_val=-9999;
							turn=3;
							rearrange++;
						}else if(dice_val==6 && rearrange==3){
								for(int k=0; k<4; k++){
									for(int o=0; o<2; o++){
										yellow_x_y[k][o]=redoriginal[k][o];
									}
								}
								turn_score=0;
								scores[2]=current_score;
								dice_val=-999999;
								if(number_players>3){
								turn=4;
							}else turn=1;
								rearrange=0;
						}else if(dice_val>=1 && dice_val<=6){
							dice_val=-999999;
							rearrange=0;
							if(number_players>3){
								turn=4;
							}else {
								turn=1;
								
							}
						}
				
				
							for(int i=0; i<4; i++){// 0 // kill blue when red 1 turn
										for(int j=0; j<1; j++){//0
										if(yellow_x_y[3][j]==red_x_y[i][j] && yellow_x_y[3][j+1]==red_x_y[i][j+1]){// 00 00 01 01
										red_x_y[i][j]=start_pos[0][i][j]; //00 100
										red_x_y[i][j+1]=start_pos[0][i][j+1];// 01 101
										turn_score+=10;
										}
										}
										}

										for(int i=0; i<4; i++){// 0 //kill yellow when red 1
										for(int j=0; j<1; j++){//0
										if(yellow_x_y[3][j]==blue_x_y[i][j] && yellow_x_y[3][j+1]==blue_x_y[i][j+1]){// 00 00 01 01
										blue_x_y[i][j]=start_pos[1][i][j]; //00 100
										blue_x_y[i][j+1]=start_pos[1][i][j+1];// 01 101
										turn_score+=10;
										}
										}
										}

										for(int i=0; i<4; i++){// 0 //kill green when red 1
										for(int j=0; j<1; j++){//0
										if(yellow_x_y[3][j]==green_x_y[i][j] && yellow_x_y[3][j+1]==green_x_y[i][j+1]){// 00 00 01 01
										green_x_y[i][j]=start_pos[3][i][j]; //00 100
										green_x_y[i][j+1]=start_pos[3][i][j+1];// 01 101
										turn_score+=10;
										}
										}
										}

					scores[2]+=turn_score;
				}
		
							/*for(int i=0; i<4; i++){
								kill_count[2]=0;
						for(int j=0; j<2; j++){
							if(yellow_x_y[i][j]==red_x_y[i][j]){
								kill_count[2]++;
								if(kill_count[2]==1|| kill_count[2]==2)red_x_y[i][j]=start_pos[0][i][j];
							}
							else if(yellow_x_y[i][j]==blue_x_y[i][j]){
								kill_count[2]++;
								if(kill_count[2]==1|| kill_count[2]==2)blue_x_y[i][j]=start_pos[2][i][j];
							}
							else if(yellow_x_y[i][j]==green_x_y[i][j]){
								kill_count[2]++;
								if(kill_count[2]==1|| kill_count[2]==2)green_x_y[i][j]=start_pos[3][i][j];
							}
						}
					}*/
		
		//win system 
			if(yellow_x_y[0][0]==yellow_x_y[1][0] && yellow_x_y[0][0]==yellow_x_y[2][0] && yellow_x_y[0][0]==yellow_x_y[3][0] && yellow_x_y[0][1]==yellow_x_y[1][1] && yellow_x_y[0][1]==yellow_x_y[2][1] && yellow_x_y[0][1]==yellow_x_y[3][1]){
					win[2]=1;
						for(int i=0; i<number_players; i++){
							if (pl_c[i]==2) cout<<"\n"<<saved_names[i]<<"Wins!\n"<<endl;
								}
						highscore_add();
						}
}

void turn4_steps(unsigned char key){ // function to seperate turn 4 steps 


					//turn 4

						if(rearrange==0){		// one time run check
					for(int i=0; i<4; i++){
						for(int j=0; j<2; j++){
							redoriginal[i][j]=green_x_y[i][j];	// stores original positions for red gotis 
						}
					}
					rearrange++;	//prevent rearrange in same turn
			}

			if (key == 49) //turn 4 press 1
					{
						int turn_score=0;
						int current_score=scores[3];


						if(green_x_y[0][0]==804 && green_x_y[0][1]==156 && dice_val==6){		//starting point and check for 6 goti 1
							green_x_y[0][1]=468;
							green_x_y[0][0]=972; // adjusted
						}

						else if(green_x_y[0][0]==804 && green_x_y[0][1]==156 && dice_val!=6 && ((green_x_y[1][0]!=924 || green_x_y[1][1]!=156 || green_x_y[2][0]!=804 || green_x_y[2][1]!=276 || green_x_y[3][0]!=924 || green_x_y[3][1]!=276))){
								return;
								} 



						else if(!(green_x_y[0][0]==804 && green_x_y[0][1]==156)) {			//out of base
							for(int i=0; i<dice_val; i++){//multiple 6 rule add after
								if(green_x_y[0][0]==468 && green_x_y[0][1]==396){
									green_x_y[0][0]=396;
									green_x_y[0][1]=468;//
									turn_score++;
									//i++;
									continue;
									/*for(int j=0; j<dice_val-i; j++){
										green_x_y[0][0] -= 72;
									}
									break;*/
									}//continue this pattern
								else if(green_x_y[0][0]==396 && green_x_y[0][1]==612){
									green_x_y[0][0]=468;
									green_x_y[0][1]=684;//
									turn_score++;
									continue;
									}
								else if(green_x_y[0][0]==612 && green_x_y[0][1]==684){
									green_x_y[0][0]=684;
									green_x_y[0][1]=612;//
									turn_score++;
									continue;
									}
								else if(green_x_y[0][0]==684 && green_x_y[0][1]==468){
									green_x_y[0][0]=612;
									green_x_y[0][1]=396;//
									turn_score++;
									continue;
									}
								else if(green_x_y[0][0]==36 && green_x_y[0][1]==468){
									green_x_y[0][0]=36;
									green_x_y[0][1]=540;// 1st blue
									turn_score++;
									continue;
									}
								else if(green_x_y[0][0]==36 && green_x_y[0][1]==612){
									green_x_y[0][0]=108;
									green_x_y[0][1]=612;// 2nd blue
									turn_score++;
									continue;
									}
								else if(green_x_y[0][0]==468 && green_x_y[0][1]==1044){
									green_x_y[0][0]=540;
									green_x_y[0][1]=1044;// 1st yellow
									turn_score++;
									continue;
									}
								else if(green_x_y[0][0]==612 && green_x_y[0][1]==1044){
									green_x_y[0][0]=612;
									green_x_y[0][1]=972;// 2nd yellow
									turn_score++;
									continue;
									}
								else if(green_x_y[0][0]==1044 && green_x_y[0][1]==612){
									green_x_y[0][0]=1044;
									green_x_y[0][1]=540;// 1st green
									turn_score++;
									continue;
									}
								else if(green_x_y[0][0]==1044 && green_x_y[0][1]==468){
									green_x_y[0][0]=972;
									green_x_y[0][1]=468;// 2nd green
									turn_score++;
									continue;
									}
								else if(green_x_y[0][0]==612 && green_x_y[0][1]==36){
									green_x_y[0][0]=540;
									green_x_y[0][1]=36;// 1st red
									turn_score++;
									continue;
									}
								else if(green_x_y[0][0]==1044 && green_x_y[0][1]==540){
									green_x_y[0][0]=972;
									green_x_y[0][1]=540;// red home column// greened
									turn_score+=15;
									continue;
									}
								
								if((green_x_y[0][0]>432 && green_x_y[0][0]<504 && green_x_y[0][1]>0 && green_x_y[0][1]<432) || (green_x_y[0][0]>432 && green_x_y[0][0]<504 && green_x_y[0][1]>648 && green_x_y[0][1]<1080)){// use x axis method instead
									green_x_y[0][1] +=72;//inc y axis //red home col// removed
									turn_score+=1;
								}
								else if((green_x_y[0][0]>0 && green_x_y[0][0]<432 && green_x_y[0][1]==468)||(green_x_y[0][0]>648 && green_x_y[0][0]<1080 && (green_x_y[0][1]==468||green_x_y[0][1]==540))){
									if(green_x_y[0][1]==540){
										if(((green_x_y[0][0]-612-72)/72)<=dice_val){
											turn=1;
											return;
										}
									}
									
									green_x_y[0][0] -=72;//dec x axis// green added
									turn_score+=1;
								}
								else if((green_x_y[0][0]>648 && green_x_y[0][0]<1080 && green_x_y[0][1]==612)||(green_x_y[0][0]>0 && green_x_y[0][0]<432 && green_x_y[0][1]==612)){
									green_x_y[0][0] +=72;//inc x axis//
									turn_score+=1;
								}
								else if((green_x_y[0][1]>0 && green_x_y[0][1]<432 && green_x_y[0][0]==612)||(green_x_y[0][0]==612 && green_x_y[0][1]<1080 && green_x_y[0][1]>648)){
									green_x_y[0][1] -=72;//dec y axis
									turn_score+=1;
								}
								else if((green_x_y[0][1]>432 && green_x_y[0][1]<648 && green_x_y[0][0]==36)){
									green_x_y[0][1] +=72;//inc y axis
									turn_score+=1;
								}
								else if((green_x_y[0][0]>432 && green_x_y[0][0]<648 && green_x_y[0][1]==1044)){
									green_x_y[0][0] +=72;//inc x axis
									turn_score+=1;
								}
								else if((green_x_y[0][1]>432 && green_x_y[0][1]<648 && green_x_y[0][0]==1044)){
									green_x_y[0][1] -=72;//dec y axis
									turn_score+=1;
								}
								else if((green_x_y[0][0]>432 && green_x_y[0][0]<648 && green_x_y[0][1]==36)){
									green_x_y[0][0] -=72;//dec x axis
									turn_score+=1;
								}
									//works nice!
							}
						}
					
							if(dice_val==6 && rearrange<3){	//goti 1
							dice_val=-9999;
							turn=4;
							rearrange++;
						}else if(dice_val==6 && rearrange==3){
								for(int k=0; k<4; k++){
									for(int o=0; o<2; o++){
										green_x_y[k][o]=redoriginal[k][o];
									}
								}
								turn_score=0;
								scores[3]=current_score;
								dice_val=-999999;
								turn=1;
								rearrange=0;
						}else if(dice_val>=1 && dice_val<=6){
							dice_val=-999999;
							turn=1;
							rearrange=0;
						}
					
					
					
						for(int i=0; i<4; i++){// 0		// kill blue when red 1 turn
								
								for(int j=0; j<1; j++){//0
									if(green_x_y[0][j]==red_x_y[i][j] && green_x_y[0][j+1]==red_x_y[i][j+1]){// 00 00 01 01
										red_x_y[i][j]=start_pos[0][i][j];  //00 100
										red_x_y[i][j+1]=start_pos[0][i][j+1];// 01 101
										turn_score+=10;
									}
								}
							}

							for(int i=0; i<4; i++){// 0 	//kill yellow when red 1
								
								for(int j=0; j<1; j++){//0
									if(green_x_y[0][j]==blue_x_y[i][j] && green_x_y[0][j+1]==blue_x_y[i][j+1]){// 00 00 01 01
										blue_x_y[i][j]=start_pos[1][i][j];  //00 100
										blue_x_y[i][j+1]=start_pos[1][i][j+1];// 01 101
										turn_score+=10;
									}
								}
							}

							for(int i=0; i<4; i++){// 0 	//kill green when red 1
								
								for(int j=0; j<1; j++){//0
									if(green_x_y[0][j]==yellow_x_y[i][j] && green_x_y[0][j+1]==yellow_x_y[i][j+1]){// 00 00 01 01
										yellow_x_y[i][j]=start_pos[2][i][j];  //00 100
										yellow_x_y[i][j+1]=start_pos[2][i][j+1];// 01 101
										turn_score+=10;
									}
								}
							}
						scores[3]+=turn_score;
					}	
			
				
					//add more keys 2
					if (key == 50) //turn 4 press 2
					{
						int turn_score=0;
						int current_score=scores[3];
						
						if(green_x_y[1][0]==924 && green_x_y[1][1]==156 && dice_val==6){		//starting point and check for 6 goti 2
							green_x_y[1][1]=468;
							green_x_y[1][0]=972; // adjusted
						}

						else if(green_x_y[1][0]==924 && green_x_y[1][1]==156 && dice_val!=6 && ((green_x_y[0][0]!=804 || green_x_y[0][1]!=156|| green_x_y[2][0]!=804 || green_x_y[2][1]!=276 || green_x_y[3][0]!=924 || green_x_y[3][1]!=276))){
									return;
									} 



						else if(!(green_x_y[1][0]==924 && green_x_y[1][1]==156)) {			//out of base
							for(int i=0; i<dice_val; i++){//multiple 6 rule add after
								if(green_x_y[1][0]==468 && green_x_y[1][1]==396){
									green_x_y[1][0]=396;
									green_x_y[1][1]=468;//
									turn_score++;
									//i++;
									continue;
									/*for(int j=0; j<dice_val-i; j++){
										green_x_y[1][0] -= 72;
									}
									break;*/
									}//continue this pattern
								else if(green_x_y[1][0]==396 && green_x_y[1][1]==612){
									green_x_y[1][0]=468;
									green_x_y[1][1]=684;//
									turn_score++;
									continue;
									}
								else if(green_x_y[1][0]==612 && green_x_y[1][1]==684){
									green_x_y[1][0]=684;
									green_x_y[1][1]=612;//
									turn_score++;
									continue;
									}
								else if(green_x_y[1][0]==684 && green_x_y[1][1]==468){
									green_x_y[1][0]=612;
									green_x_y[1][1]=396;//
									turn_score++;
									continue;
									}
								else if(green_x_y[1][0]==36 && green_x_y[1][1]==468){
									green_x_y[1][0]=36;
									green_x_y[1][1]=540;// 1st blue
									turn_score++;
									continue;
									}
								else if(green_x_y[1][0]==36 && green_x_y[1][1]==612){
									green_x_y[1][0]=108;
									green_x_y[1][1]=612;// 2nd blue
									turn_score++;
									continue;
									}
								else if(green_x_y[1][0]==468 && green_x_y[1][1]==1044){
									green_x_y[1][0]=540;
									green_x_y[1][1]=1044;// 1st yellow
									turn_score++;
									continue;
									}
								else if(green_x_y[1][0]==612 && green_x_y[1][1]==1044){
									green_x_y[1][0]=612;
									green_x_y[1][1]=972;// 2nd yellow
									turn_score++;
									continue;
									}
								else if(green_x_y[1][0]==1044 && green_x_y[1][1]==612){
									green_x_y[1][0]=1044;
									green_x_y[1][1]=540;// 1st green
									turn_score++;
									continue;
									}
								else if(green_x_y[1][0]==1044 && green_x_y[1][1]==468){
									green_x_y[1][0]=972;
									green_x_y[1][1]=468;// 2nd green
									turn_score++;
									continue;
									}
								else if(green_x_y[1][0]==612 && green_x_y[1][1]==36){
									green_x_y[1][0]=540;
									green_x_y[1][1]=36;// 1st red
									turn_score++;
									continue;
									}
								else if(green_x_y[1][0]==1044 && green_x_y[1][1]==540){
									green_x_y[1][0]=972;
									green_x_y[1][1]=540;// red home column// greened
									turn_score+=15;
									continue;
									}
								
								if((green_x_y[1][0]>432 && green_x_y[1][0]<504 && green_x_y[1][1]>0 && green_x_y[1][1]<432) || (green_x_y[1][0]>432 && green_x_y[1][0]<504 && green_x_y[1][1]>648 && green_x_y[1][1]<1080)){// use x axis method instead
									green_x_y[1][1] +=72;//inc y axis //red home col// removed
									turn_score+=1;
								}
								else if((green_x_y[1][0]>0 && green_x_y[1][0]<432 && green_x_y[1][1]==468)||(green_x_y[1][0]>648 && green_x_y[1][0]<1080 && (green_x_y[1][1]==468||green_x_y[1][1]==540))){
									if(green_x_y[1][1]==540){
										if(((green_x_y[1][0]-612-72)/72)<=dice_val){
											turn=1;
											return;
										}
									}
									
									green_x_y[1][0] -=72;//dec x axis// green added
									turn_score+=1;
								}
								else if((green_x_y[1][0]>648 && green_x_y[1][0]<1080 && green_x_y[1][1]==612)||(green_x_y[1][0]>0 && green_x_y[1][0]<432 && green_x_y[1][1]==612)){
									green_x_y[1][0] +=72;//inc x axis//
									turn_score+=1;
								}
								else if((green_x_y[1][1]>0 && green_x_y[1][1]<432 && green_x_y[1][0]==612)||(green_x_y[1][0]==612 && green_x_y[1][1]<1080 && green_x_y[1][1]>648)){
									green_x_y[1][1] -=72;//dec y axis
									turn_score+=1;
								}
								else if((green_x_y[1][1]>432 && green_x_y[1][1]<648 && green_x_y[1][0]==36)){
									green_x_y[1][1] +=72;//inc y axis
									turn_score+=1;
								}
								else if((green_x_y[1][0]>432 && green_x_y[1][0]<648 && green_x_y[1][1]==1044)){
									green_x_y[1][0] +=72;//inc x axis
									turn_score+=1;
								}
								else if((green_x_y[1][1]>432 && green_x_y[1][1]<648 && green_x_y[1][0]==1044)){
									green_x_y[1][1] -=72;//dec y axis
									turn_score+=1;
								}
								else if((green_x_y[1][0]>432 && green_x_y[1][0]<648 && green_x_y[1][1]==36)){
									green_x_y[1][0] -=72;//dec x axis
									turn_score+=1;
								}
									//works nice! remember to check turn logic
							}
						}
					
							if(dice_val==6 && rearrange<3){	//goti 2
							dice_val=-9999;
							turn=4;
							rearrange++;
						}else if(dice_val==6 && rearrange==3){
								for(int k=0; k<4; k++){
									for(int o=0; o<2; o++){
										green_x_y[k][o]=redoriginal[k][o];
									}
								}
								turn_score=0;
								scores[3]=current_score;
								dice_val=-999999;
								turn=1;
								rearrange=0;
						}else if(dice_val>=1 && dice_val<=6){
							dice_val=-999999;
							turn=1;
							rearrange=0;
						}
					
					
								for(int i=0; i<4; i++){// 0 // kill blue when red 1 turn
									for(int j=0; j<1; j++){//0
									if(green_x_y[1][j]==red_x_y[i][j] && green_x_y[1][j+1]==red_x_y[i][j+1]){// 00 00 01 01
									red_x_y[i][j]=start_pos[0][i][j]; //00 100
									red_x_y[i][j+1]=start_pos[0][i][j+1];// 01 101
									turn_score+=10;
									}
									}
									}

									for(int i=0; i<4; i++){// 0 //kill yellow when red 1
									for(int j=0; j<1; j++){//0
									if(green_x_y[1][j]==blue_x_y[i][j] && green_x_y[1][j+1]==blue_x_y[i][j+1]){// 00 00 01 01
									blue_x_y[i][j]=start_pos[1][i][j]; //00 100
									blue_x_y[i][j+1]=start_pos[1][i][j+1];// 01 101
									turn_score+=10;
									}
									}
									}

									for(int i=0; i<4; i++){// 0 //kill green when red 1
									for(int j=0; j<1; j++){//0
									if(green_x_y[1][j]==yellow_x_y[i][j] && green_x_y[1][j+1]==yellow_x_y[i][j+1]){// 00 00 01 01
									yellow_x_y[i][j]=start_pos[2][i][j]; //00 100
									yellow_x_y[i][j+1]=start_pos[2][i][j+1];// 01 101
									turn_score+=10;
									}
									}
									}

						scores[3]+=turn_score;
					}
								// add more keys 3
				if (key == 51) //turn 4 press 3
				{
					int turn_score=0;
					int current_score=scores[3];


					if(green_x_y[2][0]==804 && green_x_y[2][1]==276 && dice_val==6){		//starting point and check for 6 goti 3
						green_x_y[2][1]=468;
						green_x_y[2][0]=972; // adjusted
					}

					else if(green_x_y[2][0]==804 && green_x_y[2][1]==276 && dice_val!=6 && ((green_x_y[0][0]!=804 || green_x_y[0][1]!=156|| green_x_y[1][0]!=924 || green_x_y[1][1]!=156 || green_x_y[3][0]!=924 || green_x_y[3][1]!=276))){
							return;
							}




					else if(!(green_x_y[2][0]==804 && green_x_y[2][1]==276)) {
						for(int i=0; i<dice_val; i++){//multiple 6 rule add after
							if(green_x_y[2][0]==468 && green_x_y[2][1]==396){
								green_x_y[2][0]=396;
								green_x_y[2][1]=468;//
								turn_score++;
								//i++;
								continue;
								/*for(int j=0; j<dice_val-i; j++){
									green_x_y[2][0] -= 72;
								}
								break;*/
								}//continue this pattern
							else if(green_x_y[2][0]==396 && green_x_y[2][1]==612){
								green_x_y[2][0]=468;
								green_x_y[2][1]=684;//
								turn_score++;
								continue;
								}
							else if(green_x_y[2][0]==612 && green_x_y[2][1]==684){
								green_x_y[2][0]=684;
								green_x_y[2][1]=612;//
								turn_score++;
								continue;
								}
							else if(green_x_y[2][0]==684 && green_x_y[2][1]==468){
								green_x_y[2][0]=612;
								green_x_y[2][1]=396;//
								turn_score++;
								continue;
								}
							else if(green_x_y[2][0]==36 && green_x_y[2][1]==468){
								green_x_y[2][0]=36;
								green_x_y[2][1]=540;// 1st blue
								turn_score++;
								continue;
								}
							else if(green_x_y[2][0]==36 && green_x_y[2][1]==612){
								green_x_y[2][0]=108;
								green_x_y[2][1]=612;// 2nd blue
								turn_score++;
								continue;
								}
							else if(green_x_y[2][0]==468 && green_x_y[2][1]==1044){
								green_x_y[2][0]=540;
								green_x_y[2][1]=1044;// 1st yellow
								turn_score++;
								continue;
								}
							else if(green_x_y[2][0]==612 && green_x_y[2][1]==1044){
								green_x_y[2][0]=612;
								green_x_y[2][1]=972;// 2nd yellow
								turn_score++;
								continue;
								}
							else if(green_x_y[2][0]==1044 && green_x_y[2][1]==612){
								green_x_y[2][0]=1044;
								green_x_y[2][1]=540;// 1st green
								turn_score++;
								continue;
								}
							else if(green_x_y[2][0]==1044 && green_x_y[2][1]==468){
								green_x_y[2][0]=972;
								green_x_y[2][1]=468;// 2nd green
								turn_score++;
								continue;
								}
							else if(green_x_y[2][0]==612 && green_x_y[2][1]==36){
								green_x_y[2][0]=540;
								green_x_y[2][1]=36;// 1st red
								turn_score++;
								continue;
								}
							else if(green_x_y[2][0]==1044 && green_x_y[2][1]==540){
								green_x_y[2][0]=972;
								green_x_y[2][1]=540;// red home column // greened
								turn_score+=15;
								continue;
								}
							
							if((green_x_y[2][0]>432 && green_x_y[2][0]<504 && green_x_y[2][1]>0 && green_x_y[2][1]<432) || (green_x_y[2][0]>432 && green_x_y[2][0]<504 && green_x_y[2][1]>648 && green_x_y[2][1]<1080)){// use x axis method instead
								green_x_y[2][1] +=72;//inc y axis //red home col// removed
								turn_score+=1;
							}
							else if((green_x_y[2][0]>0 && green_x_y[2][0]<432 && green_x_y[2][1]==468)||(green_x_y[2][0]>648 && green_x_y[2][0]<1080 && (green_x_y[2][1]==468||green_x_y[2][1]==540))){
								if(green_x_y[2][1]==540){
										if(((green_x_y[2][0]-612-72)/72)<=dice_val){
											turn=1;
											return;
										}
									}
									
									green_x_y[2][0] -=72;//dec x axis// green added
									turn_score+=1;
								}
							else if((green_x_y[2][0]>648 && green_x_y[2][0]<1080 && green_x_y[2][1]==612)||(green_x_y[2][0]>0 && green_x_y[2][0]<432 && green_x_y[2][1]==612)){
								green_x_y[2][0] +=72;//inc x axis// green added 
								turn_score+=1;
							}
							else if((green_x_y[2][1]>0 && green_x_y[2][1]<432 && green_x_y[2][0]==612)||(green_x_y[2][0]==612 && green_x_y[2][1]<1080 && green_x_y[2][1]>648)){
								green_x_y[2][1] -=72;//dec y axis
								turn_score+=1;
							}
							else if((green_x_y[2][1]>432 && green_x_y[2][1]<648 && green_x_y[2][0]==36)){
								green_x_y[2][1] +=72;//inc y axis
								turn_score+=1;
							}
							else if((green_x_y[2][0]>432 && green_x_y[2][0]<648 && green_x_y[2][1]==1044)){
								green_x_y[2][0] +=72;//inc x axis
								turn_score+=1;
							}
							else if((green_x_y[2][1]>432 && green_x_y[2][1]<648 && green_x_y[2][0]==1044)){
								green_x_y[2][1] -=72;//dec y axis
								turn_score+=1;
							}
							else if((green_x_y[2][0]>432 && green_x_y[2][0]<648 && green_x_y[2][1]==36)){
								green_x_y[2][0] -=72;//dec x axis
								turn_score+=1;
							}
								//works nice!
						}
					}

						if(dice_val==6 && rearrange<3){	//goti 4
							dice_val=-9999;
							turn=4;
							rearrange++;
						}else if(dice_val==6 && rearrange==3){
								for(int k=0; k<4; k++){
									for(int o=0; o<2; o++){
										green_x_y[k][o]=redoriginal[k][o];
									}
								}
								turn_score=0;
								scores[3]=current_score;
								dice_val=-999999;
								turn=1;
								rearrange=0;
						}else if(dice_val>=1 && dice_val<=6){
							dice_val=-999999;
							turn=1;
							rearrange=0;
						}
				
				
							for(int i=0; i<4; i++){// 0 // kill blue when red 1 turn
								for(int j=0; j<1; j++){//0
								if(green_x_y[2][j]==red_x_y[i][j] && green_x_y[2][j+1]==red_x_y[i][j+1]){// 00 00 01 01
								red_x_y[i][j]=start_pos[0][i][j]; //00 100
								red_x_y[i][j+1]=start_pos[0][i][j+1];// 01 101
								turn_score+=10;
								}
								}
								}

								for(int i=0; i<4; i++){// 0 //kill yellow when red 1
								for(int j=0; j<1; j++){//0
								if(green_x_y[2][j]==blue_x_y[i][j] && green_x_y[2][j+1]==blue_x_y[i][j+1]){// 00 00 01 01
								blue_x_y[i][j]=start_pos[1][i][j]; //00 100
								blue_x_y[i][j+1]=start_pos[1][i][j+1];// 01 101
								turn_score+=10;
								}
								}
								}

								for(int i=0; i<4; i++){// 0 //kill green when red 1
								for(int j=0; j<1; j++){//0
								if(green_x_y[2][j]==yellow_x_y[i][j] && green_x_y[2][j+1]==yellow_x_y[i][j+1]){// 00 00 01 01
								yellow_x_y[i][j]=start_pos[2][i][j]; //00 100
								yellow_x_y[i][j+1]=start_pos[2][i][j+1];// 01 101
								turn_score+=10;
								}
								}
								}
					scores[3]+=turn_score;
				
				}
					// add more keys 4

				if (key == 52) //turn 4 press 4
				{
					int turn_score=0;
					int current_score=scores[3];


					if(green_x_y[3][0]==924 && green_x_y[3][1]==276 && dice_val==6){		//starting point and check for 6 goti 4
						green_x_y[3][1]=468;
						green_x_y[3][0]=972; // adjusted
					}

					else if(green_x_y[3][0]==924 && green_x_y[3][1]==276 && dice_val!=6 && ((green_x_y[0][0]!=804 || green_x_y[0][1]!=156|| green_x_y[1][0]!=924 || green_x_y[1][1]!=156 || green_x_y[2][0]!=804 || green_x_y[2][1]!=276))){
							return;
							}


					else if(!(green_x_y[3][0]==924 && green_x_y[3][1]==276)) {
						for(int i=0; i<dice_val; i++){//multiple 6 rule add after
							if(green_x_y[3][0]==468 && green_x_y[3][1]==396){
								green_x_y[3][0]=396;
								green_x_y[3][1]=468;//
								turn_score++;
								//i++;
								continue;
								/*for(int j=0; j<dice_val-i; j++){
									green_x_y[3][0] -= 72;
								}
								break;*/
								}//continue this pattern
							else if(green_x_y[3][0]==396 && green_x_y[3][1]==612){
								green_x_y[3][0]=468;
								green_x_y[3][1]=684;//
								turn_score++;
								continue;
								}
							else if(green_x_y[3][0]==612 && green_x_y[3][1]==684){
								green_x_y[3][0]=684;
								green_x_y[3][1]=612;//
								turn_score++;
								continue;
								}
							else if(green_x_y[3][0]==684 && green_x_y[3][1]==468){
								green_x_y[3][0]=612;
								green_x_y[3][1]=396;//
								turn_score++;
								continue;
								}
							else if(green_x_y[3][0]==36 && green_x_y[3][1]==468){
								green_x_y[3][0]=36;
								green_x_y[3][1]=540;// 1st blue
								turn_score++;
								continue;
								}
							else if(green_x_y[3][0]==36 && green_x_y[3][1]==612){
								green_x_y[3][0]=108;
								green_x_y[3][1]=612;// 2nd blue
								turn_score++;
								continue;
								}
							else if(green_x_y[3][0]==468 && green_x_y[3][1]==1044){
								green_x_y[3][0]=540;
								green_x_y[3][1]=1044;// 1st yellow
								turn_score++;
								continue;
								}
							else if(green_x_y[3][0]==612 && green_x_y[3][1]==1044){
								green_x_y[3][0]=612;
								green_x_y[3][1]=972;// 2nd yellow
								turn_score++;
								continue;
								}
							else if(green_x_y[3][0]==1044 && green_x_y[3][1]==612){
								green_x_y[3][0]=1044;
								green_x_y[3][1]=540;// 1st green
								turn_score++;
								continue;
								}
							else if(green_x_y[3][0]==1044 && green_x_y[3][1]==468){
								green_x_y[3][0]=972;
								green_x_y[3][1]=468;// 2nd green
								turn_score++;
								continue;
								}
							else if(green_x_y[3][0]==612 && green_x_y[3][1]==36){
								green_x_y[3][0]=540;
								green_x_y[3][1]=36;// 1st red
								turn_score++;
								continue;
								}
							else if(green_x_y[3][0]==1044 && green_x_y[3][1]==540){
								green_x_y[3][0]=972;
								green_x_y[3][1]=540;// red home column // greened
								turn_score+=15;
								continue;
								}
							
							if((green_x_y[3][0]>432 && green_x_y[3][0]<504 && green_x_y[3][1]>0 && green_x_y[3][1]<432) || (green_x_y[3][0]>432 && green_x_y[3][0]<504 && green_x_y[3][1]>648 && green_x_y[3][1]<1080)){// use x axis method instead
								green_x_y[3][1] +=72;//inc y axis //red home col// removed
								turn_score+=1;
							}
							else if((green_x_y[3][0]>0 && green_x_y[3][0]<432 && green_x_y[3][1]==468)||(green_x_y[3][0]>648 && green_x_y[3][0]<1080 && (green_x_y[3][1]==468||green_x_y[3][1]==540))){
								if(green_x_y[3][1]==540){
										if(((green_x_y[3][0]-612-72)/72)<=dice_val){
											turn=1;
											return;
										}
									}
									
									green_x_y[3][0] -=72;//dec x axis// green added
									turn_score+=1;
								}
							else if((green_x_y[3][0]>648 && green_x_y[3][0]<1080 && green_x_y[3][1]==612)||(green_x_y[3][0]>0 && green_x_y[3][0]<432 && green_x_y[3][1]==612)){
								green_x_y[3][0] +=72;//inc x axis//
								turn_score+=1;
							}
							else if((green_x_y[3][1]>0 && green_x_y[3][1]<432 && green_x_y[3][0]==612)||(green_x_y[3][0]==612 && green_x_y[3][1]<1080 && green_x_y[3][1]>648)){
								green_x_y[3][1] -=72;//dec y axis
								turn_score+=1;
							}
							else if((green_x_y[3][1]>432 && green_x_y[3][1]<648 && green_x_y[3][0]==36)){
								green_x_y[3][1] +=72;//inc y axis
								turn_score+=1;
							}
							else if((green_x_y[3][0]>432 && green_x_y[3][0]<648 && green_x_y[3][1]==1044)){
								green_x_y[3][0] +=72;//inc x axis
								turn_score+=1;
							}
							else if((green_x_y[3][1]>432 && green_x_y[3][1]<648 && green_x_y[3][0]==1044)){
								green_x_y[3][1] -=72;//dec y axis
								turn_score+=1;
							}
							else if((green_x_y[3][0]>432 && green_x_y[3][0]<648 && green_x_y[3][1]==36)){
								green_x_y[3][0] -=72;//dec x axis
								turn_score+=1;
							}
								//works nice!
						}
					}

						if(dice_val==6 && rearrange<3){	//goti 4
							dice_val=-9999;
							turn=4;
							rearrange++;
						}else if(dice_val==6 && rearrange==3){
								for(int k=0; k<4; k++){
									for(int o=0; o<2; o++){
										green_x_y[k][o]=redoriginal[k][o];
									}
								}
								turn_score=0;
								scores[3]=current_score;
								dice_val=-999999;
								turn=1;
								rearrange=0;
						}else if(dice_val>=1 && dice_val<=6){
							dice_val=-999999;
							turn=1;
							rearrange=0;
						}
				
				
						for(int i=0; i<4; i++){// 0 // kill blue when red 1 turn
							for(int j=0; j<1; j++){//0
							if(green_x_y[3][j]==red_x_y[i][j] && green_x_y[3][j+1]==red_x_y[i][j+1]){// 00 00 01 01
							red_x_y[i][j]=start_pos[0][i][j]; //00 100
							red_x_y[i][j+1]=start_pos[0][i][j+1];// 01 101
							turn_score+=10;
									}
								}
							}

							for(int i=0; i<4; i++){// 0 //kill yellow when red 1
							for(int j=0; j<1; j++){//0
							if(green_x_y[3][j]==blue_x_y[i][j] && green_x_y[3][j+1]==blue_x_y[i][j+1]){// 00 00 01 01
							blue_x_y[i][j]=start_pos[1][i][j]; //00 100
							blue_x_y[i][j+1]=start_pos[1][i][j+1];// 01 101
							turn_score+=10;
							}
							}
							}

							for(int i=0; i<4; i++){// 0 //kill green when red 1
							for(int j=0; j<1; j++){//0
							if(green_x_y[3][j]==yellow_x_y[i][j] && green_x_y[3][j+1]==yellow_x_y[i][j+1]){// 00 00 01 01
							yellow_x_y[i][j]=start_pos[2][i][j]; //00 100
							yellow_x_y[i][j+1]=start_pos[2][i][j+1];// 01 101
							turn_score+=10;
							}
							}
							}
					scores[3]+=turn_score;
				
				}
		
					/*for(int i=0; i<4; i++){
						kill_count[3]=0;
						for(int j=0; j<2; j++){
							if(green_x_y[i][j]==red_x_y[i][j]){
								kill_count[3]++;
								if(kill_count[3]==1|| kill_count[3]==2)red_x_y[i][j]=start_pos[0][i][j];
							}
							else if(green_x_y[i][j]==yellow_x_y[i][j]){
								kill_count[3]++;
								if(kill_count[3]==1|| kill_count[3]==2)yellow_x_y[i][j]=start_pos[2][i][j];
							}
							else if(green_x_y[i][j]==blue_x_y[i][j]){
								kill_count[3]++;
								if(kill_count[3]==1|| kill_count[3]==2)blue_x_y[i][j]=start_pos[3][i][j];
							}
						}
					}*/
		
			// win system 
			if(green_x_y[0][0]==green_x_y[1][0] && green_x_y[0][0]==green_x_y[2][0] && green_x_y[0][0]==green_x_y[3][0] && green_x_y[0][1]==green_x_y[1][1] && green_x_y[0][1]==green_x_y[2][1] && green_x_y[0][1]==green_x_y[3][1]){
				win[3]=1;
					for(int i=0; i<number_players; i++){
						if (pl_c[i]==4) cout<<"\n"<<saved_names[i]<<"Wins!\n"<<endl;
							}
					highscore_add();
				}
}

void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}

void string_convert(){					// function used to convert integer valus of score to string to be used by void display function 
	string str=to_string(scores[0]);
	string str2=to_string(scores[1]);
	string str3=to_string(scores[2]);
	string str4=to_string(scores[3]);
	
	score_disp[0]=str;
	score_disp[1]=str2;
	score_disp[2]=str3;
	score_disp[3]=str4;
return;
}

void highscore_calculate(){			// function used to read file highscores.txt and display its contents if required 
	char highscore_prompt='o';

	ifstream file;					// input object


	cout<<"Game started!"<<endl;
	
	do{
		cout<<"\nDo you want to view leaderboard? (Y/N): ";					// ask user if to display highscore 
		cin>>highscore_prompt;
		cout<<endl;
	} while(highscore_prompt!= 'Y' && highscore_prompt!= 'y' && highscore_prompt!= 'N' && highscore_prompt!= 'n');

	
		file.open("highscores.txt");						// open file 

		if(file.is_open()) cout<<"File opened!"<<endl;			// check file open?
		else cout<<"Error opening file!"<<endl;
		
		int counter_read=0;
		
		while(!file.eof()){														// read file and save info
			file >>saved_names[counter_read]>>saved_scores[counter_read];
			counter_read++;
		}

		if(highscore_prompt=='Y'||highscore_prompt=='y'){					// display highscores in console if asked 
			cout<<"\nDisplaying highscores!\n"<<endl;
			for(int i=0; i<10; i++){
				cout<<saved_names[i]<<" "<<saved_scores[i]<<endl;
			}
			cout<<endl;
		}

		file.close();		// close file 

		int lowest=999999;

		for(int j=0; j<10; j++){				// can be used to replace the lowest highscore from the list 
			if(saved_scores[j]<lowest){
				lowest=saved_scores[j];
				lowest_highscore_index=j;
			}
		}

	return;
}

int game_start(){
	int color;
	
	highscore_calculate();

	do{

	cout<<"\nEnter Number of Players: ";
	cin>>number_players;
	if(!cin.good()) cin.ignore(256);
	cout<<endl;
	if(number_players>4||number_players<1) cout<<"Invalid Entry must be between 2 and 4!"<<endl;

	} while (number_players>4||number_players<2);

	for(int i=0; i<number_players; i++){
		cout<<"\nEnter name: ";
		cin>>names[i];
		cout<<endl;
		cout<<"Player "<<i+1<<" is: "<<names[i]<<endl;
	}

	cout<<"\nAssigning Random Colors!\n"<<endl;
	cout.flush();
	sleep(1);


	srand(time(0));
	//cout<<"end s rand"<<endl;//

	for(int i=0; i<number_players; i++){
	color=rand()%number_players+1;
	//cout<<"end s rand"<<i<<endl;//
	if(i>0 && color==pl_c[i-1]){
		i--;
		continue;
	}
	if(i>1 && color==pl_c[i-2]){
		i--;
		continue;
	}
	if(i>2 && color==pl_c[i-3]){
		i--;
		continue;
	}
	pl_c[i]=color;
	}
	cout<<"rand complete"<<endl;
	for(int i=0; i<4; i++){
		cout<<pl_c[i]<<endl;
	}

	return 1;
}

/*
 * Main Canvas drawing function.
 * */
//Board *b;
void GameDisplay()/**/{
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
	//Fire Gun
	DrawSquare( 432 , 432 , 216, colors[WHITE]); 			// center box
																	// home triangles
	DrawTriangle( 432, 432 , 648 , 432 , 540 , 540, colors[RED]);
	DrawTriangle( 504, 432 , 576 , 432 , 540 , 504, colors[WHITE]);
	
	
	DrawTriangle( 432, 432 , 432 , 648 , 540 , 540, colors[BLUE]);
	DrawTriangle( 432, 504 , 432 , 576 , 504 , 540, colors[WHITE]);
	
	DrawTriangle( 432, 648 , 648 , 648 , 540 , 540, colors[ORANGE]);
	DrawTriangle( 504, 648 , 576 , 648 , 540 , 576, colors[WHITE]);
	
	
	DrawTriangle( 648, 648 , 648 , 432 , 540 , 540, colors[GREEN]);	
	DrawTriangle( 648, 576 , 648 , 504 , 576 , 540, colors[WHITE]);

	DrawLine( 432 , 432 , 648  , 648 , 2 , colors[BLACK] );
	DrawLine( 432 , 648 ,  648 , 432 , 2 , colors[BLACK] );
//																	// corner boxes large 
	DrawSquare( 0, 0 , 432, colors[RED]);

	DrawSquare( 0 , 648 , 432, colors[BLUE]);

	DrawSquare( 648 , 0 , 432, colors[GREEN]);

	DrawSquare( 648 , 648 , 432, colors[ORANGE]);
//														// inside box
	DrawSquare( 72 , 72 , 288, colors[WHITE]);

	DrawSquare( 72 , 720 , 288, colors[WHITE]);

	DrawSquare( 720 , 720 , 288, colors[WHITE]);

	DrawSquare( 720 , 72 , 288, colors[WHITE]);
//														// smaller inside box red
	DrawSquare( 120 , 120 , 72, colors[RED]);//
	DrawSquare( 124 , 124 , 64, colors[WHITE]);


	DrawSquare( 240 , 120 , 72, colors[RED]);//
	DrawSquare( 244 , 124 , 64, colors[WHITE]);

	DrawSquare( 120 , 240 , 72, colors[RED]);//
	DrawSquare( 124 , 244 , 64, colors[WHITE]);

	DrawSquare( 240 , 240 , 72, colors[RED]);//
	DrawSquare( 244 , 244 , 64, colors[WHITE]);
//														// smaller inside boxes blue
	DrawSquare( 120 , 768 , 72, colors[BLUE]);//
	DrawSquare( 124 , 772 , 64, colors[WHITE]);

	DrawSquare( 240 , 768 , 72, colors[BLUE]);//
	DrawSquare( 244 , 772 , 64, colors[WHITE]);

	DrawSquare( 120 , 888 , 72, colors[BLUE]);//
	DrawSquare( 124 , 892 , 64, colors[WHITE]);

	DrawSquare( 240 , 888 , 72, colors[BLUE]);//
	DrawSquare( 244 , 892 , 64, colors[WHITE]);
//													// yellow
	DrawSquare( 768 , 768 , 72, colors[ORANGE]);//
	DrawSquare( 772 , 772 , 64, colors[WHITE]);

	DrawSquare( 888 , 768 , 72, colors[ORANGE]);//
	DrawSquare( 892 , 772 , 64, colors[WHITE]);

	DrawSquare( 768 , 888 , 72, colors[ORANGE]);//
	DrawSquare( 772 , 892 , 64, colors[WHITE]);

	DrawSquare( 888 , 888 , 72, colors[ORANGE]);//
	DrawSquare( 892 , 892 , 64, colors[WHITE]);
//													// green
	DrawSquare( 768 , 120 , 72, colors[GREEN]);
	DrawSquare( 772 , 124 , 64, colors[WHITE]);

	DrawSquare( 888 , 120 , 72, colors[GREEN]);
	DrawSquare( 892 , 124 , 64, colors[WHITE]);

	DrawSquare( 768 , 240 , 72, colors[GREEN]);
	DrawSquare( 772 , 244 , 64, colors[WHITE]);

	DrawSquare( 888 , 240 , 72, colors[GREEN]);
	DrawSquare( 892 , 244 , 64, colors[WHITE]);
//															//columns printing 
		int colrx=432,colry=0;
	for(int i=0; i<6; i++){									
		if(i==1){
			DrawSquare( colrx , colry , 72, colors[RED]);
			DrawCircle(colrx+36,colry+36, 26,colors[WHITE]);
			colry += 72;
			continue;	
		}
		DrawSquare( colrx , colry , 72, colors[WHITE]);
		colry +=72;
	}

	DrawLine( 432 , 0 ,  432 , 432 , 2 , colors[BLACK] );

		int linerx1=432, linery=0, linerx2=504;
	for(int i=0; i<6; i++){
		DrawLine( linerx1 , linery ,  linerx2 , linery , 2 , colors[BLACK] );
		linery += 72;
	}

		colrx=504,colry=0;
	for(int i=0; i<6; i++){
		if(i==0){
			DrawSquare( colrx , colry , 72, colors[WHITE]);
			colry += 72;
			continue;	
		}
		DrawSquare( colrx , colry , 72, colors[RED]);
		DrawTriangle( colrx, colry , colrx+72, colry , colrx+36 , colry+72 , colors[BLACK] );
		DrawTriangle( colrx+2, colry , colrx+70, colry , colrx+36 , colry+70 , colors[WHITE] );
		colry +=72;
	}

	  linerx1=504; linery=0; linerx2=576;
	for(int i=0; i<6; i++){
		DrawLine( linerx1 , linery ,  linerx2 , linery , 2 , colors[BLACK] );
		linery += 72;
	}
		colrx=576; colry=0;
	for(int i=0; i<6; i++){
		if(i==2){
			DrawSquare( colrx , colry , 72, colors[GRAY]);
			DrawTriangle( colrx, colry+36 , colrx+72, colry+36 , colrx+36 , colry+72 , colors[WHITE] );
			DrawTriangle( colrx, colry+36 , colrx+72, colry+36 , colrx+36 , colry , colors[WHITE]);
			colry += 72;
			continue;	
		}
		DrawSquare( colrx , colry , 72, colors[WHITE]);
		colry +=72;
	}

	linerx1=576; linery=0; linerx2=648;
	for(int i=0; i<6; i++){
		DrawLine( linerx1 , linery ,  linerx2 , linery , 2 , colors[BLACK] );
		linery += 72;
	}

	DrawLine( 648 , 0 ,  648 , 432 , 2 , colors[BLACK] );
	DrawLine( 576 , 0 ,  576 ,432 , 2 , colors[BLACK] );
	DrawLine( 504 , 0 ,  504 , 432 , 2 , colors[BLACK] );
//

		 colrx=432,colry=648;
	for(int i=0; i<6; i++){
		if(i==3){
			DrawSquare( colrx , colry , 72, colors[GRAY]);
			DrawTriangle( colrx, colry+36 , colrx+72, colry+36 , colrx+36 , colry+72 , colors[WHITE] );
			DrawTriangle( colrx, colry+36 , colrx+72, colry+36 , colrx+36 , colry , colors[WHITE]);
			
			colry += 72;
			continue;	
		}
		DrawSquare( colrx , colry , 72, colors[WHITE]);
		colry +=72;
	}

	DrawLine( 432 , 648 ,  432 , 1080 , 2 , colors[BLACK] );// RE

		 linerx1=432, linery=648, linerx2=504;
	for(int i=0; i<6; i++){
		DrawLine( linerx1 , linery ,  linerx2 , linery , 2 , colors[BLACK] );
		linery += 72;
	}

		colrx=504,colry=648;
	for(int i=0; i<6; i++){
		if(i==5){
			DrawSquare( colrx , colry , 72, colors[WHITE]);
			colry += 72;
			continue;	
		}
		DrawSquare( colrx , colry , 72, colors[ORANGE]);
		DrawTriangle( colrx, colry+72 , colrx+72, colry+72 , colrx+36 , colry , colors[BLACK] );
		DrawTriangle( colrx+2, colry+72 , colrx+70, colry+72 , colrx+36 , colry+2 , colors[WHITE] );
		
		colry +=72;
	}

	  linerx1=504; linery=648; linerx2=576;
	for(int i=0; i<6; i++){
		DrawLine( linerx1 , linery ,  linerx2 , linery , 2 , colors[BLACK] );
		linery += 72;
	}
		colrx=576; colry=648;
	for(int i=0; i<6; i++){
		if(i==4){
			DrawSquare( colrx , colry , 72, colors[ORANGE]);
			DrawCircle(colrx+36,colry+36, 26,colors[WHITE]);
			colry += 72;
			continue;	
		}
		DrawSquare( colrx , colry , 72, colors[WHITE]);
		colry +=72;
	}

	linerx1=576; linery=648; linerx2=648;
	for(int i=0; i<6; i++){
		DrawLine( linerx1 , linery ,  linerx2 , linery , 2 , colors[BLACK] );
		linery += 72;
	}

	DrawLine( 648 , 648 ,  648 , 1080 , 2 , colors[BLACK] );
	DrawLine( 576 , 648 ,  576 , 1080 , 2 , colors[BLACK] );
	DrawLine( 504 , 648 ,  504 , 1080 , 2 , colors[BLACK] );
//

		 colrx=0,colry=432;
	for(int i=0; i<6; i++){
		if(i==2){
			DrawSquare( colrx , colry , 72, colors[GRAY]);
			DrawTriangle( colrx, colry+36 , colrx+72, colry+36 , colrx+36 , colry+72 , colors[WHITE] );
			DrawTriangle( colrx, colry+36 , colrx+72, colry+36 , colrx+36 , colry , colors[WHITE]);
			
			colrx += 72;
			continue;	
		}
		DrawSquare( colrx , colry , 72, colors[WHITE]);
		colrx +=72;
	}

	DrawLine( 0 , 432 ,  432 , 432 , 2 , colors[BLACK] );// RE

		int linerx=0, linery1=432, linery2=648;
	for(int i=0; i<6; i++){
		DrawLine( linerx , linery1 ,  linerx , linery2 , 2 , colors[BLACK] );
		linerx += 72;
	}

		colrx=0,colry=504;
	for(int i=0; i<6; i++){
		if(i==0){
			DrawSquare( colrx , colry , 72, colors[WHITE]);
			colrx += 72;
			continue;	
		}
		DrawSquare( colrx , colry , 72, colors[BLUE]);
		DrawTriangle( colrx, colry , colrx, colry+72 , colrx+72 , colry+36 , colors[BLACK] );
		DrawTriangle( colrx, colry+2 , colrx, colry+70 , colrx+70 , colry+36 , colors[WHITE] );
		
		colrx +=72;
	}

	  linerx=0; linery1=504; linery2=576;
	for(int i=0; i<6; i++){
		DrawLine( linerx , linery1 ,  linerx , linery2 , 2 , colors[BLACK] );
		linerx += 72;
	}

		colrx=0; colry=576;
	for(int i=0; i<6; i++){
		if(i==1){
			DrawSquare( colrx , colry , 72, colors[BLUE]);
			DrawCircle(colrx+36,colry+36, 26,colors[WHITE]);
			colrx += 72;
			continue;	
		}
		DrawSquare( colrx , colry , 72, colors[WHITE]);
		colrx +=72;
	}

	linerx=0; linery=576; linery2=648;
	for(int i=0; i<6; i++){
		DrawLine( linerx , linery1 ,  linerx , linery2 , 2 , colors[BLACK] );
		linerx += 72;
	}

	DrawLine( 0 , 648 ,  432 , 648 , 2 , colors[BLACK] );
	DrawLine( 0 , 576 ,  432 , 576 , 2 , colors[BLACK] );
	DrawLine( 0 , 504 ,  432 , 504 , 2 , colors[BLACK] ); 

//

	 colrx=648,colry=432;
	for(int i=0; i<6; i++){
		if(i==4){
			DrawSquare( colrx , colry , 72, colors[GREEN]);
			DrawCircle(colrx+36,colry+36, 26,colors[WHITE]);
			colrx += 72;
			continue;	
		}
		DrawSquare( colrx , colry , 72, colors[WHITE]);
		colrx +=72;
	}

	DrawLine( 648 , 432 ,  1080 , 432 , 2 , colors[BLACK] );// RE

		 linerx=648, linery1=432, linery2=648;
	for(int i=0; i<6; i++){
		DrawLine( linerx , linery1 ,  linerx , linery2 , 2 , colors[BLACK] );
		linerx += 72;
	}

		colrx=648,colry=504;
	for(int i=0; i<6; i++){
		if(i==5){
			DrawSquare( colrx , colry , 72, colors[WHITE]);
			colrx += 72;
			continue;	
		}
		DrawSquare( colrx , colry , 72, colors[GREEN]);
		DrawTriangle( colrx+72, colry , colrx+72, colry+72 , colrx , colry+36 , colors[BLACK] );
		DrawTriangle( colrx+72, colry+2 , colrx+72, colry+70 , colrx+2 , colry+36 , colors[WHITE] );
		//F
		colrx +=72;
	}

	  linerx=648; linery1=504; linery2=576;
	for(int i=0; i<6; i++){
		DrawLine( linerx , linery1 ,  linerx , linery2 , 2 , colors[BLACK] );
		linerx += 72;
	}

		colrx=648; colry=576;
	for(int i=0; i<6; i++){
		if(i==3){
			DrawSquare( colrx , colry , 72, colors[GRAY]);
			DrawTriangle( colrx, colry+36 , colrx+72, colry+36 , colrx+36 , colry+72 , colors[WHITE] );
			DrawTriangle( colrx, colry+36 , colrx+72, colry+36 , colrx+36 , colry , colors[WHITE]);
			
			colrx += 72;
			continue;	
		}
		DrawSquare( colrx , colry , 72, colors[WHITE]);
		colrx +=72;
	}

	linerx=648; linery=576; linery2=648;
	for(int i=0; i<6; i++){
		DrawLine( linerx , linery1 ,  linerx , linery2 , 2 , colors[BLACK] );
		linerx += 72;
	}

	DrawLine( 648 , 648 ,  1080 , 648 , 2 , colors[BLACK] );
	DrawLine( 648 , 576 ,  1080 , 576 , 2 , colors[BLACK] );
	DrawLine( 648 , 504 ,  1080 , 504 , 2 , colors[BLACK] ); 

	//red gotis numbers


	for(int i=0; i<4; i++){
			DrawCircle(red_x_y[i][0],red_x_y[i][1], 16,colors[RED]);
			DrawLine( red_x_y[i][0] , red_x_y[i][1]+8 ,  red_x_y[i][0] , red_x_y[i][1]-8 , 2 , colors[BLACK] );

			DrawLine( red_x_y[1][0]+4 , red_x_y[1][1]+8 ,  red_x_y[1][0]+4 , red_x_y[1][1]-8 , 2 , colors[BLACK] );

			DrawLine( red_x_y[2][0]+4 , red_x_y[2][1]+8 ,  red_x_y[2][0]+4 , red_x_y[2][1]-8 , 2 , colors[BLACK] );
			DrawLine( red_x_y[2][0]+8 , red_x_y[2][1]+8 ,  red_x_y[2][0]+8 , red_x_y[2][1]-8 , 2 , colors[BLACK] );

			DrawLine( red_x_y[3][0]+4 , red_x_y[3][1]+8 ,  red_x_y[3][0]+4 , red_x_y[3][1]-8 , 2 , colors[BLACK] );
			DrawLine( red_x_y[3][0]+8 , red_x_y[3][1]+8 ,  red_x_y[3][0]+8 , red_x_y[3][1]-8 , 2 , colors[BLACK] );
			DrawLine( red_x_y[3][0]-4 , red_x_y[3][1]+8 ,  red_x_y[3][0]-4 , red_x_y[3][1]-8 , 2 , colors[BLACK] );
	}

	//blue numbers

	for(int i=0; i<4; i++){
			DrawCircle(blue_x_y[i][0],blue_x_y[i][1], 15,colors[BLUE]);

			DrawLine( blue_x_y[i][0] , blue_x_y[i][1]+8 ,  blue_x_y[i][0] , blue_x_y[i][1]-8 , 2 , colors[WHITE] );

			DrawLine( blue_x_y[1][0]+4 , blue_x_y[1][1]+8 ,  blue_x_y[1][0]+4 , blue_x_y[1][1]-8 , 2 , colors[WHITE] );

			DrawLine( blue_x_y[2][0]+4 , blue_x_y[2][1]+8 ,  blue_x_y[2][0]+4 , blue_x_y[2][1]-8 , 2 , colors[WHITE] );
			DrawLine( blue_x_y[2][0]+8 , blue_x_y[2][1]+8 ,  blue_x_y[2][0]+8 , blue_x_y[2][1]-8 , 2 , colors[WHITE] );

			DrawLine( blue_x_y[3][0]+4 , blue_x_y[3][1]+8 ,  blue_x_y[3][0]+4 , blue_x_y[3][1]-8 , 2 , colors[WHITE] );
			DrawLine( blue_x_y[3][0]+8 , blue_x_y[3][1]+8 ,  blue_x_y[3][0]+8 , blue_x_y[3][1]-8 , 2 , colors[WHITE] );
			DrawLine( blue_x_y[3][0]-4 , blue_x_y[3][1]+8 ,  blue_x_y[3][0]-4 , blue_x_y[3][1]-8 , 2 , colors[WHITE] );
	}

	// green numbers

	for(int i=0; i<4; i++){
			DrawCircle(green_x_y[i][0],green_x_y[i][1], 15,colors[GREEN]);

			DrawLine( green_x_y[i][0] , green_x_y[i][1]+8 ,  green_x_y[i][0] , green_x_y[i][1]-8 , 2 , colors[WHITE] );

			DrawLine( green_x_y[1][0]+4 , green_x_y[1][1]+8 ,  green_x_y[1][0]+4 , green_x_y[1][1]-8 , 2 , colors[WHITE] );

			DrawLine( green_x_y[2][0]+4 , green_x_y[2][1]+8 ,  green_x_y[2][0]+4 , green_x_y[2][1]-8 , 2 , colors[WHITE] );
			DrawLine( green_x_y[2][0]+8 , green_x_y[2][1]+8 ,  green_x_y[2][0]+8 , green_x_y[2][1]-8 , 2 , colors[WHITE] );

			DrawLine( green_x_y[3][0]+4 , green_x_y[3][1]+8 ,  green_x_y[3][0]+4 , green_x_y[3][1]-8 , 2 , colors[WHITE] );
			DrawLine( green_x_y[3][0]+8 , green_x_y[3][1]+8 ,  green_x_y[3][0]+8 , green_x_y[3][1]-8 , 2 , colors[WHITE] );
			DrawLine( green_x_y[3][0]-4 , green_x_y[3][1]+8 ,  green_x_y[3][0]-4 , green_x_y[3][1]-8 , 2 , colors[WHITE] );
	}

	// yellow numbers

	for(int i=0; i<4; i++){
			DrawCircle(yellow_x_y[i][0],yellow_x_y[i][1], 15,colors[ORANGE]);

			DrawLine( yellow_x_y[i][0] , yellow_x_y[i][1]+8 ,  yellow_x_y[i][0] , yellow_x_y[i][1]-8 , 2 , colors[BLACK] );

			DrawLine( yellow_x_y[1][0]+4 , yellow_x_y[1][1]+8 ,  yellow_x_y[1][0]+4 , yellow_x_y[1][1]-8 , 2 , colors[BLACK] );

			DrawLine( yellow_x_y[2][0]+4 , yellow_x_y[2][1]+8 ,  yellow_x_y[2][0]+4 , yellow_x_y[2][1]-8 , 2 , colors[BLACK] );
			DrawLine( yellow_x_y[2][0]+8 , yellow_x_y[2][1]+8 ,  yellow_x_y[2][0]+8 , yellow_x_y[2][1]-8 , 2 , colors[BLACK] );

			DrawLine( yellow_x_y[3][0]+4 , yellow_x_y[3][1]+8 ,  yellow_x_y[3][0]+4 , yellow_x_y[3][1]-8 , 2 , colors[BLACK] );
			DrawLine( yellow_x_y[3][0]+8 , yellow_x_y[3][1]+8 ,  yellow_x_y[3][0]+8 , yellow_x_y[3][1]-8 , 2 , colors[BLACK] );
			DrawLine( yellow_x_y[3][0]-4 , yellow_x_y[3][1]+8 ,  yellow_x_y[3][0]-4 , yellow_x_y[3][1]-8 , 2 , colors[BLACK] );
	}


	if(1){
		 DrawString( 1100, 970, "Colors randomly assigned", colors[WHITE]);
		 DrawString( 1100, 600, "Type number of players to start!", colors[WHITE]);
	}

	
	
	if(pl_c[0]==1) {		//player 1 position
		DrawString( 1100, 1050, names[0], colors[RED]);
		//DrawString( 1100, 1000, score_disp[0] , colors[WHITE]);
	}
	else if(pl_c[0]==2) {
		DrawString( 1100, 1050, names[0], colors[BLUE]);
		//DrawString( 1100, 1000, score_disp[1] , colors[WHITE]);
	}
	else if(pl_c[0]==3) {
		DrawString( 1100, 1050, names[0], colors[ORANGE]);
		//DrawString( 1100, 1000, score_disp[2] , colors[WHITE]);
	}
	else if(pl_c[0]==4) {
		DrawString( 1100, 1050, names[0], colors[GREEN]);
		//DrawString( 1100, 1000, score_disp[3] , colors[WHITE]);
	}

	if(pl_c[1]==1) {			//player 2 position
		DrawString( 1200, 1050, names[1], colors[RED]);
		//DrawString( 1200, 1000, score_disp[0], colors[WHITE]);
	}
	else if(pl_c[1]==2) {
		DrawString( 1200, 1050, names[1], colors[BLUE]);
		//DrawString( 1200, 1000, score_disp[1], colors[WHITE]);
	}
	else if(pl_c[1]==3) {
		DrawString( 1200, 1050, names[1], colors[ORANGE]);
		//DrawString( 1200, 1000, score_disp[2], colors[WHITE]);
	}
	else if(pl_c[1]==4) {
		DrawString( 1200, 1050, names[1], colors[GREEN]);
		//DrawString( 1200, 1000, score_disp[3], colors[WHITE]);
	}
	
	if(number_players>2){

	if(pl_c[2]==1) {		//player 3 position
		DrawString( 1300, 1050, names[2], colors[RED]);
		//DrawString( 1300, 1030, score_disp[0], colors[WHITE]);
		}
	else if(pl_c[2]==2){
		DrawString( 1300, 1050, names[2], colors[BLUE]);
		//DrawString( 1300, 1030, score_disp[1], colors[WHITE]);
	}
	else if(pl_c[2]==3) {
		DrawString( 1300, 1050, names[2], colors[ORANGE]);
		//DrawString( 1300, 1030, score_disp[2], colors[WHITE]);
	}
	else if(pl_c[2]==4) {
		DrawString( 1300, 1050, names[2], colors[GREEN]);
		//DrawString( 1300, 1030, score_disp[3], colors[WHITE]);
	}
	}

	if(number_players>3){
	if(pl_c[3]==1) {		//player 4 position
		DrawString( 1400, 1050, names[3], colors[RED]);
		//DrawString( 1400, 1030, score_disp[0], colors[WHITE]);
	}
	else if(pl_c[3]==2) {
		DrawString( 1400, 1050, names[3], colors[BLUE]);
		//DrawString( 1400, 1030, score_disp[1], colors[WHITE]);
	}
	else if(pl_c[3]==3) {
		DrawString( 1400, 1050, names[3], colors[ORANGE]);
		//DrawString( 1400, 1030, score_disp[2], colors[WHITE]);
	}
	else if(pl_c[3]==4) {
		DrawString( 1400, 1050, names[3], colors[GREEN]);
		//DrawString( 1400, 1030, score_disp[3], colors[WHITE]);
		}
	}

	if(looped==0){
	DrawString( 1100, 100, "Press Space to continue", colors[WHITE]);
	}

	string_convert();

	if(pl_c[0]==1) {		//player 1 position
		//DrawString( 1100, 1050, names[0], colors[RED]);
		DrawString( 1100, 800, score_disp[0] , colors[WHITE]);
	}
	else if(pl_c[0]==2) {
		//DrawString( 1100, 1050, names[0], colors[BLUE]);
		DrawString( 1100, 800, score_disp[1] , colors[WHITE]);
	}
	else if(pl_c[0]==3) {
		//DrawString( 1100, 1050, names[0], colors[ORANGE]);
		DrawString( 1100, 800, score_disp[2] , colors[WHITE]);
	}
	else if(pl_c[0]==4) {
		//DrawString( 1100, 1050, names[0], colors[GREEN]);
		DrawString( 1100, 800, score_disp[3] , colors[WHITE]);
	}

	if(pl_c[1]==1) {			//player 2 position
	//	DrawString( 1200, 1050, names[1], colors[RED]);
		DrawString( 1200, 800, score_disp[0], colors[WHITE]);
	}
	else if(pl_c[1]==2) {
		//DrawString( 1200, 1050, names[1], colors[BLUE]);
		DrawString( 1200, 800, score_disp[1], colors[WHITE]);
	}
	else if(pl_c[1]==3) {
	//	DrawString( 1200, 1050, names[1], colors[ORANGE]);
		DrawString( 1200, 800, score_disp[2], colors[WHITE]);
	}
	else if(pl_c[1]==4) {
		//DrawString( 1200, 1050, names[1], colors[GREEN]);
		DrawString( 1200, 800, score_disp[3], colors[WHITE]);
	}
	
	if(number_players>2){
	if(pl_c[2]==1) {		//player 3 position
	//	DrawString( 1300, 1050, names[2], colors[RED]);
		DrawString( 1300, 800, score_disp[0], colors[WHITE]);
		}
	else if(pl_c[2]==2){
		//DrawString( 1300, 1050, names[2], colors[BLUE]);
		DrawString( 1300, 800, score_disp[1], colors[WHITE]);
	}
	else if(pl_c[2]==3) {
	//	DrawString( 1300, 1050, names[2], colors[ORANGE]);
		DrawString( 1300, 800, score_disp[2], colors[WHITE]);
	}
	else if(pl_c[2]==4) {
		//DrawString( 1300, 1050, names[2], colors[GREEN]);
		DrawString( 1300, 800, score_disp[3], colors[WHITE]);
	}
	}

	if(number_players>3){
	if(pl_c[3]==1) {		//player 4 position
		//DrawString( 1400, 1050, names[3], colors[RED]);
		DrawString( 1400, 800, score_disp[0], colors[WHITE]);
	}
	else if(pl_c[3]==2) {
	//	DrawString( 1400, 1050, names[3], colors[BLUE]);
		DrawString( 1400, 800, score_disp[1], colors[WHITE]);
	}
	else if(pl_c[3]==3) {
	//	DrawString( 1400, 1050, names[3], colors[ORANGE]);
		DrawString( 1400, 800, score_disp[2], colors[WHITE]);
	}
	else if(pl_c[3]==4) {
		//DrawString( 1400, 1050, names[3], colors[GREEN]);
		DrawString( 1400, 800, score_disp[3], colors[WHITE]);
		}
	}

	DrawSquare( 1205 , 215 , 72, colors[WHITE]);				// dice animator 
	
	if(dice_val==1){
			DrawString(1236, 236, "1", colors[BLACK]);
	} 
	else if (dice_val==2){
			DrawString(1236, 236, "2", colors[BLACK]);
	}
	else if (dice_val==3){
			DrawString(1236, 236, "3", colors[BLACK]);
	}
	else if (dice_val==4){
			DrawString(1236, 236, "4", colors[BLACK]);
	}
	else if (dice_val==5){
			DrawString(1236, 236, "5", colors[BLACK]);
	}
	else if (dice_val==6){
			DrawString(1236, 236, "6", colors[BLACK]);
	}

	if(turn==1) DrawString(1400, 236, "Turn", colors[RED]);				// turn selector 
	else if(turn==2) DrawString(1400, 236, "Turn", colors[BLUE]);
	else if(turn==3) DrawString(1400, 236, "Turn", colors[ORANGE]);
	else if(turn==4) DrawString(1400, 236, "Turn", colors[GREEN]);




	//Mushroom
	//DrawSquare( 250 , 250 ,20,colors[GREEN]); 
	//Display Score
	//DrawString( 50, 800, "Score=0", colors[MISTY_ROSE]);
	//Spider
	//DrawTriangle( 300, 450 , 340, 450 , 320 , 490, colors[MISTY_ROSE] ); 
	// Trianlge Vertices v1(300,50) , v2(500,50) , v3(400,250)


	//DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
	//DrawLine( 550 , 50 ,  550 , 480 , 10 , colors[MISTY_ROSE] );	
	
	//DrawCircle(50,670,10,colors[RED]);
	//DrawCircle(70,670,10,colors[RED]);
	//DrawCircle(90,670,10,colors[RED]);

	glutSwapBuffers(); // do not modify this line..

}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {
	if (key
			== GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		// what to do when left key is pressed...
			
	} else if (key
			== GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {
				
	} else if (key
			== GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {

	}

	else if (key
			== GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {

	}

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/

	glutPostRedisplay();

}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
	int static counter=0;
	int dice_new=0;

	if (key == 27/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}


	if (key == 32 && counter<=number_players) //Key for placing the bomb		// initial turn decider dice 
			{
		//do something if b is pressed
		cout << "space pressed" << endl;
		
		dice_new=rand()%6+1;
		dice_val=dice_new;
		dice[counter-1]=dice_val;

		cout<<dice_new<<endl;

		counter++;
		if(counter==number_players+1) looped=1;//check this logic pre 3
	}

//int dice_val_fake;
//int dice1=1,dice2=1,dice3=1;

	if (key == 32 && counter>number_players) 
			{
				dice_looped();
	}

	/*if(key==32 && repeat==1 && counter>number_players){
		dice_val_fake=rand()%6+1;
		
		if(dice_val_fake==6){		// 2nd 6
		repeat=2;
		}else dice_val=dice_val_fake;
	}

	if(key==32 && repeat==2 && counter>number_players){
		dice_val_fake=rand()%6+1;
		
		if(dice_val_fake==6){	//3rd 6
			repeat=0;
		}else dice_val=dice_val_fake;
	}*/


	if (key == 49 && counter==0) // input number of players in glut
			{
		
		number_players=1;
		counter++;
	}
	if (key == 50 && counter==0) 
			{
	
		number_players=2;
		counter++;
	}
	if (key == 51 && counter==0) 
			{
	
		number_players=3;
		counter++;
	}
	if (key == 52 && counter==0) 
			{
	
		number_players=4;
		counter++;
	}

	

	if(counter>0){			//one time run check 
		
		for(int i=0; i<number_players; i++){ 		//wins counter;
			if(win[i]==1){
				wins++;
			}
		}

	if(wins<3){		//decide turns 

		if(turn==1){//turn 1
		if(win[0]==1){
			turn=2;
		}else{
			turn1_steps(key);
		}
		}

		//blue turn starts

		if(turn==2){
			if(win[1]==1){
				turn=3;
			}else{
				turn2_steps(key);
				}
			}

			

			// turn 3 yellow

				if(turn==3){
			if(win[2]==1){
				turn=4;
			}else{
				turn3_steps(key);
				}
			}

		//start turn 4 green

			if(turn==4){
			if(win[3]==1){
				turn=1;
			}else{
				turn4_steps(key);
				}
			}
	}

	} else exit(1); 		// end program 
	
	glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m) {

	//implement here

	game_loop_start();
	glutPostRedisplay();

	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(1000.0, Timer, 0);
}

/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */

void game_loop_start(){
	
	int static counter=0;
	int highest=-999, highest_pl=0;
	
	if(looped==1){				// loope check
		if(counter==0){
		for (int i=0; i<number_players; i++){		// turn decider on dice values highest chosen 
			if(dice[i]>highest){
				highest=dice[i];
				highest_pl=i+1;
			}
			
		}
		turn=highest_pl;
		counter++;
		looped=0;
		}		
	}
	//cout<<"dice 0 is: "<<dice[0]<<endl;
}

void MousePressedAndMoved(int x, int y) {
	//cout << x << " " << y << endl;
	glutPostRedisplay();
}
void MouseMoved(int x, int y) {

	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
			{
		//cout << GLUT_DOWN << " " << GLUT_UP << endl;

	} else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
			{

	}
	glutPostRedisplay();
}
/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {
	 
	//b = new Board(60, 60); // create a new board object to use in the Display Function ...
	game_start();

	

	for(int i=0; i<4; i++){						// save starting positions of the pieces
		for(int j=0; j<2; j++){
			start_pos[0][i][j]=red_x_y[i][j];
			start_pos[1][i][j]=blue_x_y[i][j];
			start_pos[2][i][j]=yellow_x_y[i][j];
			start_pos[3][i][j]=green_x_y[i][j];
		}
	}

	int width = 1600, height = 1080; // i have set my window size to be 800 x 600
	//b->InitalizeBoard(width, height);
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("PF Project Fasih Abdullah 20I-0432"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.

	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();

	return 1;
}
#endif /* AsteroidS_CPP_ */
