#include <iostream>
#include <list>
#include <string>
#include <iomanip>

#define MAX 1000
using namespace std;

bool premiseContains(string clause, string premise) {
    string allPremises = premise.substr(0, premise.length() - 1);
    string toEqual = clause.substr(0, clause.find("=>"));;
    bool isEqual = false;

    cout << "allPremises in this round is: " << allPremises << endl;
    cout << "toEqual in this round is: " << toEqual << endl;
    isEqual = (allPremises == toEqual) ? true : false;
    cout << "isEqual in this round is: " << isEqual << endl;
    return allPremises == toEqual;
}

int main() {
    list<int> count;
    list<string> inferred;
    list<string> agenda;
    list<string> clause;

    string KB = "P(1, 1) F;B(1, 1) F;B(2, 1) T;B(1, 1) => (P(1, 2) | P(2, 1));B(2, 1) => (P(1, 1) | P(2, 2) | P(3, 1));";
    string q = "P(3, 1) T";
    
    //  split KB
    int j = 0;
    int spiltLength = 0;
    string split[MAX];
    for (int i = 0; i < KB.length(); i++) {
        if (j == 0 && KB[i] == ';') {
            split[spiltLength] = KB.substr(j, i - j);
            spiltLength++;
            j = i + 1;
        }
        else if (KB[i] == ';') {
            split[spiltLength] = KB.substr(j, i - j);
            spiltLength++;
            j = i + 1;
        }
    }

    //  KB and put them into two different list
    cout << "KB is :" << endl;
    for (int i = 0; i < spiltLength; i++) {
        cout << split[i] << endl;

        if (split[i].find("=>") == std::string::npos) {
            agenda.push_back(split[i]);
        } else {
            clause.push_back(split[i]);
            int times = 1;
            for (int j = 0; j < split[i].length(); j++) {
                if (split[i][j] == '&')
                    times++;
            }
            count.push_back(times);
        }
    }

    cout << endl << "agenda is :" << endl;
    for (std::list<string>::iterator it = agenda.begin(); it != agenda.end(); ++it) {
        cout << *it << endl;
    }

    cout << endl << "caluse is :" << endl;
    for (std::list<string>::iterator it = clause.begin(); it != clause.end(); ++it) {
        cout << *it << endl;
    }

    cout << endl << "count is :" << endl;
    for (std::list<int>::iterator it = count.begin(); it != count.end(); ++it) {
        cout << *it << endl;
    }

    while (!agenda.empty()) {
      string p = agenda.front();
      agenda.pop_front();
      if (p.find(q.substr(0, q.length() - 2)) != std::string::npos && p[p.length() - 1] == q[q.length() - 1]) {
          cout << "OK! " << q << endl;
          break;
      }

      cout << endl << "p in this round is: " << p << endl;

      inferred.push_back(p);
      std::list<int>::iterator itS = count.begin();
      for (std::list<string>::iterator it = clause.begin(); it != clause.end(); ++it) {
          cout << "it is this round is: " << *it << endl;
          if (premiseContains(*it, p)) {
              *itS = *itS - 1;

              if (*itS < 0) {
                  string result = (*it).substr((*it).find("=>") + 3, (*it).length() - 1) + p[p.length() - 1];
                  agenda.push_back(result);
              }
              itS++;
          }
      }
    }

    return 0;
}
