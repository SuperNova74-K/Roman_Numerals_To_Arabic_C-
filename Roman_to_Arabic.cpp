/*
* Purpose     : Roman numerals to Arabic Translator
* Author      : Khaled Waleed Salah / ID : 20210127
* Institution : FCAI - CU
* Date        : 3/14/2022
*/

//#include<bits/stdc++.h>
#include<iostream>;
#include<map>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

map<char, int> values_of_char;
map<string, int> values_of_string;

string string_to_upper(string in);
int is_valid_input(string in);
int occurrences_num_char(string str, char target);
string allowed = "MXDLVIC";

vector <int> values_in_sequence = {};

int main(){
    values_of_char = {
            {'M' , 1000},
            {'D' , 500},
            {'C' , 100},
            {'L' , 50},
            {'X' , 10},
            {'V' , 5},
            {'I' , 1},
    };
    values_of_string = {
            {"IV" , 4},
            {"IX" , 9},
            {"XL" , 40},
            {"XC" , 90},
            {"CD" , 400},
            {"CM" , 900},
    };

    string original;
    cout << "Please enter a Valid Roman number: ";
    cin >> original;
    original = string_to_upper(original);
    cin.clear();

    // checking for wrong input
    while(is_valid_input(original)){
        cout << "input is invalid." << endl;
        cout << "Please enter a Valid Roman number: ";
        cin >> original;
        original = string_to_upper(original);
        cin.clear();
        cout << endl;
    }

    long long answer = 0;
    for (auto i: values_in_sequence) {
        answer += i;
    }
    cout << endl;
    cout << "The Arabic Number is : " << answer << endl;
    cout << "Thank you for using my program.";
}




string string_to_upper(string in) {
    string out;
    for (auto i: in) {
        if (i >= 'a' && i <= 'z') {
            out += char(i - 32);
        } else {
            out += i;
        }
    }
    return out;
}

int occurrences_num_char(string str, char target){
    int answer = 0;
    for(auto i : str){
        if(i == target){
            answer += 1;
        }
    }
    return answer;
}


int is_valid_input(string in){
    //checking for allowed characters
    for (int i = 0; i < in.size(); ++i) {
        if(allowed.find(in[i]) == -1){
            return 1;
        }
    }

    //checking for impossible occurences
    int i_coutner = occurrences_num_char(in, 'I');
    int v_coutner = occurrences_num_char(in, 'V');
    int x_coutner = occurrences_num_char(in, 'X');
    int l_coutner = occurrences_num_char(in, 'L');
    int c_coutner = occurrences_num_char(in, 'C');
    int d_coutner = occurrences_num_char(in, 'D');

    if(i_coutner > 3 || v_coutner > 1 || x_coutner > 3|| l_coutner > 1 || c_coutner > 4 || d_coutner > 1){
        return 2;
    }

    // checking for the sequence of numbers
    for (int i = 0; i < in.size(); ++i) {
        // for every number except for the last
        if(i != in.size() - 1){
            string temp = "";
            temp += in[i];
            temp += in[i+1];
            for(auto &it : values_of_string){
                if(it.first == temp){
                    values_in_sequence.push_back(values_of_string[temp]);
                    i++;
                    // basically continue for the inner loop and the outer loop as well (means : skips one iteration)
                    goto cnt;
                }
            }
            //if that didn't happen then the value must be of a single character.
            values_in_sequence.push_back(values_of_char[in[i]]);

        }else{
            // this is done for the last number only (if it isn't already taken in a previous number like IX)
            values_in_sequence.push_back(values_of_char[in[i]]);
        }
        cnt:;
    }

    // here we sort the sequence of numbers and check if the original is sorted 
    vector<int> sorted_sequence = values_in_sequence;
    sort(sorted_sequence.begin(), sorted_sequence.end());
    reverse(sorted_sequence.begin(), sorted_sequence.end());

    if(sorted_sequence == values_in_sequence){
        // if data equals the sorted version of it then that means that the original was sorted !
        // by extension there is no invalid number like IIV, because the first I will be 1 while the second
        // will be 4 , so the sequence is 1 , 4 which is not sorted, so we reject the input (IIV in that case).
        return 0;
    }else{
        // if they are not equal clear the vectors so they don't make the next input fulty, to give the user anther chance
        sorted_sequence.clear();
        values_in_sequence.clear();
        return 3;
    }

}