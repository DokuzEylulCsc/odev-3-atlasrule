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

        int question=-1;
        int i=9;

        while (1) {

          if (line[i] == ',' && line[i+1] == ',') {
            //If no answer
            question += 1;
          }

          if (line[i] == ',' && line[i+1] != ',' ) {
            //If there is an answer
            question +=1;

            if ( line[i+1] == answers[question*2] ) { 
              //If the answer is correct
              notes[student] += 4;
            }

            else {
              //If the answer is wrong
              notes[student] -= 1;
            }
            
          }

          if(line[i+1] == '\0') {
            break;
          }

          if (question > 10) {
            break;
          }

          i += 1;
        }

        student += 1;
      }


      counter += 1;
    }
    myfile.close();
  }

  else cout << "-Dosya okunamadi-\n";

  //Sorting data and saving students' notes into output file

  int notes_sorted[student];
  
  for (int i=0; i<student; i++) {

    // Normalizing the data 
    //(I assume normalizing not meant to be statistically)
    if (notes[i] < 0) {
      notes[i] = 0;
    }

    if (notes[i] > 100) {
      notes[i] = 100;
    }

    notes_sorted[i] = notes[i];
  }

  //Selection-sort used
  int mindex, temp;
  for (int i=0; i<student; i++) {
    mindex = i;
    for (int j=i+1; j<student; j++) {
      if (notes_sorted[j] < notes_sorted[mindex]) {
        mindex = j;
      }

      temp = notes_sorted[mindex];
      notes_sorted[mindex] = notes_sorted[i];
      notes_sorted[i] = temp;
    }
  }

  //Saving sorted notes into output file
  ofstream output_file ("output.txt");
  if (output_file.is_open())
  {

    cout << "\n\n\n";
    for (int i=0; i<student; i++) {
      cout << notes_sorted[i] << endl;

      output_file << notes_sorted[i] << endl; 
    }

    //Saving the additional info into output file

    int min = notes[0];
    int max = notes[0], sum=0;
    for (int i=0; i< student; i++) {

      if (notes[i] < min) {
        min = notes[i];
      }

      if (notes[i] > max) {
        max = notes[i];
      }

      sum += notes[i];
    }

    int mean = sum / (float) student;

    int median = notes_sorted[student / 2];

    int range = max - min;
    
    output_file << " En Küçük: " << min;
    output_file << " En Büyük: " << max;
    output_file << " Ortalama: " << mean;
    output_file << " Medyan: " << median;
    output_file << " Range: " << range << endl;

    


      output_file.close();
  }
  else cout << "-Dosya yazilamadi-";


  return 0;
}
