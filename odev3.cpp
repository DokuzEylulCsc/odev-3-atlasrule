#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

int main () {
  string line;
  ifstream myfile ("input.txt");

int counter=0, n_questions, notes[100]={0} , student=0;

string answers;

  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      cout << line << '\n';

      if (counter == 0) {
        //n_questions = std::stoi(line);
        n_questions = atoi(line.c_str());
      }

      if (counter == 1) {
        answers = line;
      }

      else {

        int question=1;
        int i=9;

        while (1) {

          if(line[i]=='\0') {
            break;
          }

          if (line[i] == ',' && line[i+1] == ',') {
            //If no answer
            question += 1;
          }

          if (line[i] == ',' && line[i+1] != ',' ) {
            //If there is an answer

            question +=1;

            if ( answers[question*2] == line[i+1] ) { 
              //If the answer is correct
              notes[student] += 4;
            }

            else {
              //If the answer is wrong
              notes[student] -= 1;
            }
            
          }


          i += 1;

          if (question > 19) {
            break;
          }

        }

        student += 1;

      }


      counter += 1;

    }
    myfile.close();
  }

  else cout << "-Dosya okunamadi-\n"; 


  for (int i=0; i<student; i++) {
    cout << notes[i] << "\n" ;
  }


  return 0;
}
