#include <vector>
#include <iostream>
#include <algorithm>
#include <memory>
#include <sstream>

using namespace std;

/*---------------------------------------------------------------------------*/

typedef unique_ptr<string> ustring;

template<typename T>
ustring formatVector(vector<T> &v) {
    ustring s = make_unique<string>();
    s->assign("");
    for (const auto &x: v) {
        s->append(s->empty() ? "(" : ", ");
        stringstream ss;
        ss << x;
        s->append(ss.str());
    }
    s->append(")");
    return s;
}

/*---------------------------------------------------------------------------*/

template<typename T> using CVector = vector<vector<T>>;

template<typename T>
void printVectors(const char *title, CVector<T> &v) {
    cout << "\n\n" << title << ": ========================================\n";
    cout << "Printing " << v.size() << " vectors numbered 0.." << (v.size() - 1) << "\n";
    for (int i = 0; i < v.size(); i++) {
        cout << i << ": " << formatVector(v[i])->c_str() << "\n";
    }
    cout << "===================================================\n";
}

template<typename T>
void sortCombinations(CVector<T> &v, int (compareFunc)(T &a, T &b)) {
    std::sort(v.begin(), v.end(), [&compareFunc](auto a, auto b) {
        int rv = 0;
        int c = min(a.size(), b.size());
        for (int i = 0; i < c && rv == 0; i++) {
            rv = compareFunc(a[i], b[i]);
        }
        return rv < 0;
    });
}

template<typename T>
int combinationCount(const CVector<T> &v) {
    int count = 0;
    for (int i = 0; i < v.size(); i++) {
        count = v[i].size() * (i == 0 ? 1 : count);
    }
    return count;
}

template<typename T>
CVector<T> &combinations(const CVector<T> &v, CVector<T> &dest) {
    dest.clear();
    int count = combinationCount(v);
    dest.resize(count);
    for (int i = 0; i < count; i++) {
        dest[i].resize(v.size());
        int quotient = i;
        for (int j = 0; j < v.size(); j++) {
            div_t d = std::div(quotient, v[j].size());
            quotient = d.quot;
            dest[i][j] = std::move(v[j][d.rem]);
        }
    }
    return dest;
}

/*---------------------------------------------------------------------------*/

int main() {
    /*---------------------------------------------------------------------------*/

    CVector<int> integerSource({
                                       {1},
                                       {2, 3, 4},
                                       {5, 6},
                                       {7}
                               });
    printVectors("Integer Source", integerSource);

    CVector<int> integerDestination;
    combinations(integerSource, integerDestination);
    printVectors("Generated Integer Result", integerDestination);

    sortCombinations<int>(integerDestination,
                          [](int &a, int &b) { return a - b; });
    printVectors("Sorted Integer Result", integerDestination);

    /*---------------------------------------------------------------------------*/

    CVector<string> stringSource({
                                         {
                                                 "alpha"
                                         },
                                         {
                                                 "beta",
                                                 "gamma",
                                                 "delta"
                                         },
                                         {
                                                 "zeta",
                                                 "eta",
                                                 "theta",
                                                 "iota",
                                                 "kappa",
                                                 "lambda",
                                                 "mu",
                                                 "nu",
                                                 "xi",
                                                 "omicron",
                                                 "pi",
                                                 "rho",
                                                 "sigma",
                                                 "tau",
                                                 "upsilon"
                                         },
                                         {
                                                 "phi",
                                                 "chi"
                                         },
                                         {
                                                 "psi",
                                                 "omega"
                                         }
                                 }

    );
    printVectors("String Source", stringSource);

    CVector<string> stringDestination;
    combinations(stringSource, stringDestination);

    printVectors("String Result", stringDestination);
    sortCombinations<string>(stringDestination,
                             [](string &a, string &b) { return a.compare(b); });
    printVectors("Sorted String Result", stringDestination);
}


