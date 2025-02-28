#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream source;
    source.open("name_score.txt");
    string textline;

    while(getline(source,textline)){
        char a[100] = "";
        for(unsigned i = 0; i < textline.size(); i++){
            a[i] = textline[i];
        }
        char format[] = "%[^:]: %d %d %d";
        char name[100];
        int score1, score2, score3;
        int sum = 0;

        sscanf(a, format, name, &score1, &score2, &score3);
        sum = score1 + score2 + score3;
        char grade = score2grade(sum);

        string text = "";
        for(int i = 0; name[i] != '\0'; i++){
            text += name[i];
        }
        names.push_back(text);
        scores.push_back(sum);
        grades.push_back(grade);
    }
}

void getCommand(string &command, string &key){
    string text;
    cout << "Please input your command: " << endl;
    getline(cin,text);
    int lo = text.find_first_of(" ");
    command = text.substr(0,lo);
    key = text.substr(lo+1,text.size());


}

void searchName(vector<string> names, vector<int> scores, vector<char> grades, string key){
    cout << "---------------------------------\n";
    for(unsigned int i = 0; i < names.size(); i++){
        if(key == toUpperStr(names[i])){
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            cout << "---------------------------------\n";
            return;
        }
    }
    cout << "Cannot found." << endl;
    cout << "---------------------------------\n";


}

void searchGrade(vector<string> names, vector<int> scores, vector<char> grades, string key){
    cout << "---------------------------------\n";
    bool found = false;
    for(unsigned int i = 0; i < names.size(); i++){
        if(key[0] == grades[i]){
            cout << names[i] << " (" << scores[i] << ")" << endl;
            found = true;
        }
    }
    if(!found) cout << "Cannot found." << endl;
    cout << "---------------------------------\n";

}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
