/* 
 * Course: CS216-002
 * Project: Project2
 * Purpose: repeatedly ask the user to type prefix to match 
 *          then display the matched terms in two orders: 
 *          lexicographic order by query;
 *          descending order by weight.
 *          
 *          repeatedly ask the user to type the prefix to match
 *          and generate all the prefix-matched terms
 *          then display the prefix-matched terms in descending order by weight
 * Author: Rylee Hobbs
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include "term.h"
#include "SortingList.h"
#include "autocomplete.h"

using namespace std;

int main(int argc, char** argv) {

    const int ARGUMENTS = 3;
           
    // check the command line argument, an input file name is needed
    if (argc != ARGUMENTS)
    {
        cout << "Warning: need exactly two command line arguments." << endl;
        cout << "Usage: " << argv[0] << " <filename>" << " number" << endl;
        return 1;
    }
    
    //convert char value from argv to int
    char* toConvert = argv[2];
    int cmdnumber = atoi(toConvert);
    
    if (cmdnumber <= 0)
    {
        cout << "Warning: the number of matching terms needs to be a positive number!" << endl;
        return 1;
    }
    
    // check if the input file can be opened successfully
    ifstream infile;
    infile.open(argv[1]);
    if (!infile.good())
    {
        cout << "Cannot open the file named " << argv[1] << endl;
        return 2;
    }  
    
    // read in the terms from the input file
    // line by line and store into Autocomplete object
    Autocomplete autocomplete;
    long weight;
    string query;
    
    //Autocomplete object
    
    while (!infile.eof())
    {
        infile >> weight >> ws;
        getline(infile, query);
        if (query != "")
        {    
            Term newterm(query, weight);
            autocomplete.insert(newterm);
        }  
    } 
    autocomplete.sort();
   
    // close the file stream
    infile.close();
    

    string prefix;
    cout << "Please input the search query (type \"exit\" to quit): " << endl;
    getline(cin, prefix);
    
    while (prefix != "exit")
    {
        // create a Term object from given prefix, weight is 0
        Term toMatch(prefix, 0);

        // create a SortingList object named matchedTerms to store the prefix-match terms
        SortingList<Term> matchedTerms = autocomplete.allMatches(prefix);
        
               
        if (matchedTerms.size() == 0)
            cout << "No matched query!" << endl;
        else //found matched terms
        {
           for (int i = 0; i < cmdnumber && i < matchedTerms.size(); i++)
            {
                cout << matchedTerms[i] << endl;
            }
        }
        cout << "Please input the search query (type \"exit\" to quit): " << endl;
        getline(cin, prefix);
    }    

    return 0;
}

