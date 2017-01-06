#include <iostream>
#include <cstdlib>
#include <list>
#include <map>

using namespace std;

map<string, bool> model;
list<string> symbols;

bool PL_TRUE(map<string, bool> model) {
    if (model["S(2, 1)"] && (model["W(1, 1)"] || model["W(2, 2)"] || model["W(3, 1)"]))
        if((!model["B(2, 1)"]) && (!model["P(1, 1)"]) && (!model["P(2, 2)"]))
            if (model["B(1, 2)"] && (model["P(1, 1)"] || model["P(1, 3)"] || model["P(2, 2)"]))
                if ((!model["S(1, 2)"]) && (!model["W(1, 1)"]) && (!model["W(2, 2)"]))
					return true;
	return false;
}

//  KB is known
bool TT_CHECK_ALL(string query, list<string> symbols, map<string, bool> model) {
	if (!symbols.empty()) {
		if (PL_TRUE(model)) {
			return model[query];
		} else {
			return true;
		}
	} else {
		string p = symbols.front();
        symbols.pop_front();

		map<string, bool> modelTrue(model);
        map<string, bool> modelFalse(model);
		modelTrue[p] = true;
		modelFalse[p] = false;

		return TT_CHECK_ALL(query, symbols, modelTrue) && TT_CHECK_ALL(query, symbols, modelFalse);
	}
	return true;
}

int main() {

	string keywords[] = {"B(1, 2)", "S(1, 2)", "S(2, 1)", "B(2, 1)", "P(1, 3)", "W(3, 1)", "P(2, 2)", "W(2, 2)"};

	for (int i = 0; i < 8; i++) {
		symbols.push_back(keywords[i]);
	}

    cout << "P(1, 3) " << (TT_CHECK_ALL("P(1, 3)", symbols, model) ? "T" : "F") << endl;

    cout << "W(3, 1) " << (TT_CHECK_ALL("W(3, 1)", symbols, model) ? "T" : "F") << endl;

    return 0;
}
