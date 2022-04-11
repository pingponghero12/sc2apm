#include <iostream>
#include <string>
#include <random>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <conio.h>
//Yes, I'm using namespace std. Yes I'm noob at programing.
using namespace std;


//Definiton of variables
float time_pass;
int apm;
int points = 0;
string input = "";
string expected = "";
string tempStr;
string list = "!@#$%^&*(";
char a;
char tempRan;
bool score = 0;
clock_t time_req;


//Function that generates the character to type
string generator()
{
  //Generation of random number
  int i = rand()%44;

  //Checking which character, writing it and retutning
  if(i<26)
  {
    tempRan = 'a' + i;
    tempStr = tempRan;
    cout<<"\t"<<tempStr<<endl;
    return tempStr;
  }
  else if(i<35)
  {
    tempRan = list[i-26];
    tempStr = tempRan;
    cout<<"\t"<<i-25<<" + Shift"<<endl;
    return tempStr;
  }
  else
  {
    tempStr = to_string(i-34);
    cout<<"\t"<<tempStr<<endl;
    return tempStr;
  }

}


//Main function
int main()
{
  //Cleaning the console before opening the program
  system("cls");

  //Displaying information about program and waiting to start it
  cout<<"SC2traing v. 1.0"<<endl<<"To stop enter ?"<<endl;
  system("pause");
  cout<<endl;

  //Starting counting time after player started playing
  time_req = clock();

//Main loop
  while(input!="?") //Checking if player ended game
  {
    //Displaying information about progrma after cleaning console
    cout<<"SC2traing v. 1.0"<<endl<<"To stop enter ?"<<endl<<endl;

    //Checking up score of last game
    if(score == 1)
    {
      cout<<"Good job";
    }
    else
    {
      cout<<"You missed";
    }

    //Displaying player's points
    cout<<" | Your score: "<<points<<endl<<endl;

    //Genertion of character and overwriting expected with it
    expected = generator();
    //Reading character form console
    a = getch();
    input = a;

    //Cheching if readed character equals expected character
    if(input==expected)
    {
      points++;
      //Setting score of this round to true
      score = 1;
    }
    else
    {
      //Setting score of this round to false
      score = 0;
    }

    //Cleaning the console
    system("cls");
  }

  //Calculating time and apm
  time_req = clock()- time_req;
	time_pass =  (float)time_req/CLOCKS_PER_SEC;
  apm = points/(time_pass/60);

  //Displaying all the information
  cout<<"SC2traing v. 1.0"<<endl<<"To stop enter ?"<<endl<<endl;
  cout<<"You're done. Your score is equal "<<points<<endl;
  cout<<"Your time is equal "<<time_pass<<endl;
  cout<<"Your apm is equal "<<apm<<endl;

  //End of program
  system("pause");
  return 0;
}
