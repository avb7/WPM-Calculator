//wpm calculator by Aditya Bhatnagar

//Header files
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <time.h>

using namespace std;

//The class to store the fastest player's details
class fastest_player{
      string name;
      int wpm;

      public: 
              fastest_player(){wpm=0;}
              
              void getdata(int speed){
                   cout<<"You're the fastest user"<<endl;
                   cout<<"Enter your name: ";
                   getline(cin, name);
                   wpm = speed;
                   }
      
              void showdata(){
                   cout<<"\nFastest typer: "<<name<<endl;
                   cout<<"Typing speed: "<<wpm<<endl;
                   }
                   
              int fastest_wpm(){return wpm;}
              
      };
//member functions of the class


//prototyping the functions
void start_calculation();
int count_words();
string read_txtfile();
int calculate_wpm(double time);
void display_fastest();
void write_data(int wpm);


int main(){
    string line;
    
    //displaying the menu 
    cout<<"WPM (Words per minute) Calculator: "<<endl<<endl;
    cout<<"Options: "<<endl;
    cout<<"1. Start!"<<endl;
    cout<<"2. Fastest typer yet"<<endl<<endl;
    
    int ans;
enter_option:
    cout<<"Enter option number: ";
    cin>>ans;
    switch(ans){
                case 1: start_calculation(); break;
                case 2:  display_fastest(); system("pause"); break;
                default: goto enter_option;
             }

    
}
//function to start the 'Typing task'
void start_calculation(){
     string line, read_text;
     float time;
     
    
     cout<<read_txtfile()<<endl;
     cout<<"no of words: ";
     cout<<count_words();
     
     system("cls");
    
     
start:
     cout<<"Instructions: "<<endl<<endl;
     cout<<"A sentence will be displayed. You'll be asked to type it in."<<endl;
     cout<<"The time you take to enter the sentence will be calculated in 'wpm.'"<<endl<<endl;
     cout<<"NOTE- As soon you continue, the timer will start."<<endl<<endl;     
     system("pause");
     
     system("cls");
     
     // Starting the Time counter
     clock_t begin = clock();
     
     cout<<"Enter the following sentence: "<<endl<<read_txtfile()<<endl<<endl;
     
     cout<<"Type here: "<<endl;
     cin.ignore();
     getline(cin, line);
    
     
     //Ending the Time counter
      clock_t end = clock();
      double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
      //elapsed_secs is the difference between 'end time' and 'begin time' which is basically the time taken to type
      
      //creating the class object, fstream variables for the binary file
      fastest_player obj;
      ifstream bin("fastest_player.dat", ios::binary);
      ofstream bout("fastest_player.dat", ios::binary);
      
      //check if entered text matches the line string
      read_text = read_txtfile();      
      if (read_text == line){
                    //add to list of users
                    cout<<endl<<"Your typing speed is "<<calculate_wpm(elapsed_secs)<<" words per minute"<<endl<<endl;
                    write_data(calculate_wpm(elapsed_secs));
                                   
                    }
      else {
           system("cls");
           cout<<"You entered the line of text incorrectly. "<<endl<<endl;
           
           }
    
    system("pause");
          
     }
     
//function to call the number of words (5 chars= 1 word) <standard wpm word>
int count_words(){
    ifstream fin;
    char text_temp;
    int text_count=0;
    fin.open("line.txt");
     
     //counting the number of words
     while(!fin.eof()){
                       fin.get(text_temp);
                       text_count++;
                       }
     text_count = text_count / 5;
     return text_count;
    }

//function to read the line from the text file
string read_txtfile(){
     ifstream fin;
     string text_line;
     
     fin.open("line.txt");
     //reading the text file
     getline(fin, text_line);
    
    return text_line;
    }
    
//function to calculate words per minute
int calculate_wpm(double time){
     
     int wpm = (count_words()*60)/time;
     return wpm;
    
    }
//writing the 'fastest_player.dat'
void write_data(int speed){
      fastest_player obj;
      ifstream bin("fastest_player.dat", ios::binary);
      
      bin.read((char*)&obj, sizeof(obj));
      bin.close();
          
      //if (speed > obj.fastest_wpm()){
                fstream bout;
                bout.open("fastest_player.dat", ios::binary|ios::out);
                 obj.getdata(speed);
                 bout.write((char*)&obj, sizeof(obj));
                 bout.close();
                
                // rename("fastest_player1.dat", "fastest_player.dat");
                
                 
                 
                // }
      
     
     
     }
//displaying the fastest player
void display_fastest(){
     fastest_player obj;
     ifstream fin;
     
     fin.open("fastest_player.dat", ios::binary|ios::in);
     while(fin.read((char*)&obj, sizeof(obj)))
     {
     obj.showdata();                   
     }
     fin.close();
      
     }
