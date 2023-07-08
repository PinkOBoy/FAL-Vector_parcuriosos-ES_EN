/*
* Solucion aportada por el profesor de la FdI (UCM):
* Solution given by FdI's (UCM) professor:
*   ANTONIO ALEJANDRO SANCHEZ RUIZ-GRANADOS
*/
#include <iostream>
#include <vector>

using namespace std;

/*
 * Calculates if v[a..b] is parcurioso
 * - numEven: number of even numbers in v[a..b] (output)
 * - numOdd: number of odd numbers in v[a..b] (output)
 * - sumEven: sum of even numbers in v[a..b] (output)
 * - sumOdd: sum of odd numbers in v[a..b] (output)
 */
bool parcurious(const vector<int>& v, int a, int b,
    int& numEven, int& numOdd, int& sumEven, int& sumOdd) {
    int r;
    if (a == b) {
        // only one element: even or odd
        if (v[a] % 2 == 0) {
            numEven = 1;
            sumEven = v[a];
            numOdd = sumOdd = 0;
        }
        else {
            numOdd = 1;
            sumOdd = v[a];
            numEven = sumEven = 0;
        }
        r = true;
    }
    else {
        // more than one element
        // recursive call on each half
        int m = (a + b) / 2;
        int numEven1, numOdd1, sumEven1, sumOdd1;
        bool r1 = parcurious(v, a, m, numEven1, numOdd1, sumEven1, sumOdd1);
        int numEven2, numOdd2, sumEven2, sumOdd2;
        bool r2 = parcurious(v, m + 1, b, numEven2, numOdd2, sumEven2, sumOdd2);

        // output parameters
        r = numEven1 <= numOdd2 && sumEven1 <= sumOdd2 && (r1 || r2);
        numEven = numEven1 + numEven2;
        numOdd = numOdd1 + numOdd2;
        sumEven = sumEven1 + sumEven2;
        sumOdd = sumOdd1 + sumOdd2;
    }
    return r;
}

/* Recurrence equations:
 * T(n) = c0 if n == 1
 * T(n) = 2*T(n/2) + c if n > 1
 * a = 2, b = 2, k = 0 so a > b^k and the cost is O(n^{log_b{a}) = O(n)
 */

void solve() {
    int n;
    cin >> n;
    vector<int> v(100000);
    for (int i = 0; i < n; ++i)
        cin >> v[i];

    int numEven, numOdd, sumEven, sumOdd;
    cout << (parcurious(v, 0, n - 1, numEven, numOdd, sumEven, sumOdd) ? "SI" : "NO") << endl;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
        solve();
    return 0;
}