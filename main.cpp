#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <fstream>

using namespace std;
 
class Word {
    public:
        std::string text;
        int frequency;

        Word(string t, int f) {
            text = t;
            frequency = f;
        }
};

class WordFrequencyCounter {
    public:
        vector<Word> CountWordFrequency(string s) {
           vector<string> words; 
            vector<string> counted_words;
            vector<Word> object_words;

            int frequency = 0;
            
            stringstream ss(s);  
            string word;
            
            int count = 0;
            while (ss >> word) {
                // Extracting words from StringStream, removing non alphabet characters from individual strings, and pushing to vector
                word.erase(remove_if(word.begin(), word.end(), [](char c) { return !isalpha(c); } ), word.end());
                transform(word.begin(), word.end(), word.begin(), ::tolower); 
                words.push_back(word);
                count+=1;
            }

            // Algorithm to count frequency from string vector
            for (int i = 0; i < count; i++) {
                frequency = 0;

                // if the word was already counted, skip this iteration
                if(find(counted_words.begin(), counted_words.end(), words[i]) != counted_words.end()) {
                    continue;
                    
                // else, add word to already counted vector, and count how many instances it is found in the word vector, then push it to word object vector
                } else {
                    counted_words.push_back(words[i]);

                    for (int y = 0; y < words.size(); y++) {
                        if (words[i] == words[y]) {frequency++;}
                    }
                    
                    object_words.push_back(Word(words[i], frequency));

                }
            }

        // sorting from most frequent to least frequent, used lambda function to write the sorting parameter
        sort(object_words.begin(), object_words.end(), [](const Word lhs, const Word rhs) {
            return lhs.frequency > rhs.frequency;
        });

           return object_words;
        }
};

int main() {
    //declaring IO variables
    ifstream input_file("input.txt"); 
    ofstream output_file("output.txt");
    string s = "";
    int count = 0;

    // collecting text from file
    while (input_file) {
        s += input_file.get();
    }

    vector<Word> words;
    WordFrequencyCounter wfc;

    words = wfc.CountWordFrequency(s);
    
    //printing values
    for (int i = 0; i < words.size(); i++ ) {
        cout << words[i].text + " " + to_string(words[i].frequency)  << endl;
        output_file << words[i].text + " " + to_string(words[i].frequency)  << endl;
    }

    cout << endl;
    return 0;
}