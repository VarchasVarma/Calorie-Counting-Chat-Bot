#include <ostream>
#include <bits/stdc++.h>
#include <fstream>
#include <array>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include <iomanip>

using namespace std;

typedef vector<string> vstring;

vstring split(string in, char delim = ' '){
    stringstream ss(in);
    string temp;
    vstring out;
    while (getline(ss, temp, delim)){
        out.push_back(temp);
    }
    
    return out;
}

string read(string file){
    string tempLine;
    string unparsed = "";
    ifstream data(file);
    while(true){
        getline(data, tempLine);
        unparsed += tempLine;
        if(data.fail()) break;
    }

    return unparsed;
}

vstring parse(string u_p){
    stringstream convert(u_p);
    string tempSeg;
    vstring segmented;

    while(getline(convert, tempSeg, '?')){
        segmented.push_back(tempSeg);
    }

    return segmented;
}

string unite(vstring in){
    string united = "";
    for (int i = 0; i < in.size(); i++) {
        united += in.at(i);
    }

    return united;
}

void print(vstring const &in)
{
        cout << "========================================================================================\n";
        cout << left 
             << "|" << setw(4) << "No."
             << "|" << setw(50) << "Item:" 
             << right 
             << "|" << setw(15) << "Serving (g)" 
             << "|" << setw(15) << "Calories\n";
    for (int i = 0; i < in.size(); i++) {
        string temp = in.at(i);
        int fSeg = temp.find(",");
        int sSeg = temp.find("!");

        cout << left 
             << "|" << setw(4) << to_string(i+1) + "." 
             << "|" << setw(50) << temp.substr(0, fSeg) 
             << right 
             << "|" << setw(15) << temp.substr(fSeg+1, sSeg-fSeg-1) 
             << "|" << setw(15) << temp.substr(sSeg+1, -1) << "\n";
        
    }
        cout << "========================================================================================\n";
}

string lower(string in) {  
    transform(in.begin(), in.end(), in.begin(), [](char c) { 
      return tolower(c); 
    });
    return in;  
}  

vstring foodSearch(vstring in, string search){
    vstring foundFoods;
    
    for(int i = 0; i < in.size(); i++){
        if (lower(in.at(i)).find(lower(search)) != string::npos) {
            foundFoods.push_back(in.at(i));
        }
    }

    return foundFoods;
}

vstring foodAdd(vstring in, vstring &store, int num){
    if (num > in.size()){
        cout << "That item does not exist :astonished:\n";
    }
    else{
        store.push_back(in.at(num-1));
    }

    return store;
}

int vectorCross(vstring v1, vstring v2) {
    for(int i = 0; i < v1.size(); i++){
        for (int n = 0; n < v2.size(); n++){
            if(!v1.at(i).compare(v2.at(n))){
                return stoi(v2.back());
            }
        }
    }
    return 0;
}

vstring addF(string food, string in, vstring db, vstring &aF){
    vstring foundFoods = foodSearch(db, food);
    print(foundFoods);

    cout << "Which item would you like to add?\n";
    cin >> in;
    
    cout << "\n\nYour Foods:\n";
    foodAdd(foundFoods, aF, stoi(in));
    print(aF);
    return aF;
}

vstring removeF(int in, vstring &aF){
    aF.erase(aF.begin()+in-1);
    print(aF);  
    return aF;
}

int interpret (vstring inp, vstring ak, vstring rk, vstring qk){
    int check = 0;

    check += vectorCross(inp, ak);
    check += vectorCross(inp, rk);
    check += vectorCross(inp, qk);

    return check;
}

int main(){
    //declare variables
    string in, decid, food, refer;
    int remo;
    vstring database = parse(read("Food and Calories.txt"));
    vstring addedFoods;
    vstring firstFunc = {"1", "one", "uno", "first", "10"};
    vstring addKeys = {"add", "put", "new", "input", "place", "redo", "+", "3"};
    vstring removeKeys = {"remove", "subtract", "take", "out", "slash", "-", "minus", "undo", "4"};
    vstring quitKeys = {"quit", "back", "escape", "leave", "exit", "5"};
    bool foodL = false;

    start:
    cout << "What function would you like to use?\n1. Food Log\n";
    getline(cin >> ws, in);

    if(vectorCross(split(in, ' '), firstFunc)) foodL = true;
    else if(vectorCross(split(in, ' '), quitKeys)) exit(0);

    while (foodL){
        int check;
        cout << "What would you like to do?\n";
        getline(cin, decid);
        vstring inp = split(decid, ' ');

        check = interpret(inp, addKeys, removeKeys, quitKeys);

        cout << check;
        if(check > 5 || check == 0){
            cout << "I am unsure what you want to do!\n";
            continue;
        }
        else{
            switch(check){
                case 3:
                    cout << "Search:\n";
                    cin.ignore();
                    getline (cin, food);
                    addF(food, refer, database, addedFoods);
                    break;
                case 4:
                    cout << "\nWhich item do you want to remove?\n";
                    cin >> remo;
                    removeF(remo, addedFoods);
                    break;
                case 5:
                    foodL = false;
                    break;
                default:
                    cout << "You have found a bug, please report this!";
                    break;
            }
        }
    }

    goto start;


}       
