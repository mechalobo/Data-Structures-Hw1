//
//  main.cpp
//  ParsingPractice
//
//
//  Created by Eder Aguilar on 9/8/23.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct card {
    string title;
    string author;
    int word_count;
    int line_count;
    vector<string> strings; //to hold the contents of all the lines in a file
    int letterCount = 0; // to calculate letter frequency
    int letters[26] {0}; // will contain the count of all 26 letters in the alphabet
};

void parseFile(fstream&, card&);
fstream& operator>>(fstream&, card&);
void processLetterFrequency(card&);
void writeToFile(fstream&, card&);
void writeToCardCatalog(fstream&, card&);


int main() {
    // insert code here...
    fstream file, oFile;
    string line, fileName, choice;
    const int NUM_INITIAL = 1;
    card cards[NUM_INITIAL];
    vector<string> strings;
    
    
    while(true) {
        do {
            cout << "Enter name of file to be processed: " << endl;
            getline(cin, fileName);
            file.open(fileName, ios::in);
            if(file.fail()) {
                cout << "Error! No such file exists!\n";
            }
            
        }while(file.fail());
        
        file >> cards[0]; //operator overload to fill the contents of the card struct
        processLetterFrequency(cards[0]); // calculate the letter frequency
        file.close(); //close the file
        
        //write to CardCatalog the contents of the first card
        oFile.open("CardCatalog.txt", ios::app | ios::in);
        writeToCardCatalog(oFile, cards[0]);
        oFile.close(); //close the file
        cout << "Successfully wrote the card data to CardCatalog.txt" << endl;
        
        //prompt user if they want to see letter frequency
        do {
            cout << "Would you like to see the letter frequency? Enter yes or no." << endl;
            getline(cin, choice);
            if(choice != "yes" && choice != "no") {
                cout << "Please enter a valid prompt." << endl;
            }

        } while(choice != "yes" && choice != "no");
        
        if(choice == "yes") {
            //write to file the letter frequency
            oFile.open("output.txt", ios::app | ios::out);
            if(oFile) {
                writeToFile(oFile,cards[0]);
            }
            oFile.close();
            cout << "Successfully wrote the letter frequency to output.txt." << endl;
        }
        
        do {
            cout << "Would you like to process another file? Enter yes or no." << endl;
            getline(cin, choice);
            if(choice != "yes" && choice != "no") {
                cout << "Please enter a valid prompt." << endl;
            }

        } while(choice != "yes" && choice != "no");
        
        if(choice == "yes") continue;
        else break;
    }
    cout << "Terminating program..." << endl;
    
    return 0;
}


//overload the >> operator so that it parses out the contents of the input file and store it in a struct
fstream& operator>>(fstream& file, card& card) {
    string line;
    string keyword = "Content";
    int lcount = 0;
    int wcount = 0;
    string temp;
    
    getline(file, card.title);
    getline(file, card.author);
    
    while(getline(file, line)) {
        if(line.empty()) continue; //we want to keep eating empty lines
        
        else break; //we successfully processed the contents line
    }
    while(getline(file, line)) {
        if(line.empty()) {
            //eat empty lines and count them as a line in the lcount counter
            lcount++;
            continue;
        }
        card.strings.push_back(line); //add the line of string to vector in order to process letter frequency
        lcount++;
        stringstream ss(line);
        while(ss >> temp) {
            wcount++;
        }
        
    } //count the number of lines in file
    card.line_count = lcount;
    card.word_count = wcount;
    
    return file;
}

void processLetterFrequency(card& card) {
    int index;
    
    //take a full line from the contents section of the book
    for(string line: card.strings) {
        //for each character in the line that isn't a new line character...
        for(int i=0; line[i] != '\0'; i++) {
            //force lower case to upper case
            if(line[i] >= 'a' && line[i] <= 'z') {
                line[i] -= 32;
                card.letterCount++;
            }
            //since all characters are upper case, ignore everything else
            if(line[i] < 'A' || line[i] > 'Z') continue;
                    
            index = line[i] - 'A';
            card.letters[index]++;
        }

    }
}

void writeToFile(fstream& file, card& card) {
    file << card.title << " letter frequency:" << endl;
    //Print frequency
    file << "\nCharacter   Frequency\n";
    for(int i=0; i < 26; i++){
        if(card.letters[i] != 0){
          file <<"  " << (char)(i + 65) << "         "
              << (double) card.letters[i] / card.letterCount << endl;
        }
    }
    file << endl; //leave spaces in between writings
}

void writeToCardCatalog(fstream& file, card& card) {
    file << "Title: " << card.title << endl;
    file << "Full Author: " << card.author << endl;
    file << "Word count: " << card.word_count << endl;
    file << "Line count: " << card.line_count << endl;
    file << endl; //leave spaces in between cards
}
