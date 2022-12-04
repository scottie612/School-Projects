#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <iomanip>

using namespace std;



void Printmap(unordered_map<string, int> const &m) {
    vector<pair<string,int>> vect;
    for(auto & x : m){
        vect.push_back(x);
    }
    std::sort(vect.begin(), vect.end(),
            [](const pair<string,int>& a, const pair<string,int>& b) {              //got this sort fuction from https://www.techiedelight.com/sort-map-values-cpp/
                  if (a.second != b.second)
                      return a.second > b.second;

                  return a.first > b.first;
              });


    int i=0;
    for (auto &t : vect) {
        cout<<setw(4)<<"No. "<<i<<": ";
        cout<<setw(20)<<left<< t.first <<right<<t.second << endl;
        i++;
	if(i==10)
		break;
    }
}

int main() {
    unordered_map<string, int> nums;
    unordered_map<string, int> words;
    unordered_map<string, int> chars;
    string input;
    string number, alpha, special;

    while(getline(cin, input)){;
    for (int i = 0; i < input.length(); i++) {
        if (input[i] == '\n') {
            special = "'/n'";
        } else if (input[i] == '\t') {
            special = "'/t'";
        } else if (input[i] == ' ') {
            special = "Space";
        } else {
            special = input[i];
        }

        if (chars.count(special) > 0) {
            chars[special] = chars.at(special) + 1;
            special = "";
        } else {
            chars[special] = 1;
            special = "";
        }
        if (isdigit(input[i])) {
            number.push_back(input[i]);
            if (!isdigit(input[i + 1])) {
                if (nums.count(number) > 0) {
                    nums[number] = nums.at(number) + 1;
                    number = "";
                } else {
                    nums[number] = 1;
                    number = "";
                }
            }
        } else if ((input[i] >= 'A' && input[i] <= 'Z') || (input[i] >= 'a' && input[i] <= 'z')) {

            alpha.push_back(tolower(input[i]));
            if (!((input[i + 1] >= 'A' && input[+1] <= 'Z') || (input[i + 1] >= 'a' && input[i + 1] <= 'z'))) {
                if (words.count(alpha) > 0) {
                    words[alpha] = words.at(alpha) + 1;
                    alpha = "";
                } else {
                    words[alpha] = 1;
                    alpha = "";
                }
            }
        }
    }
}
    cout<<"Total "<<chars.size()<<" different characters, 10 most used characters:"<<endl;
    Printmap(chars);
    cout<<"Total "<<words.size()<<" different words, 10 most used words:"<<endl;
    Printmap(words);
    cout<<"Total "<<nums.size()<<" different numbers, 10 most used numbers:"<<endl;
    Printmap(nums);



    return 0;
}
