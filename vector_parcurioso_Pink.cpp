/*
 * USUARIO DEL JUEZ: G04
 * NOMBRE Y APELLIDOS: JAIME BENEDI GALDEANO
 */
#include <iostream>
#include <vector>
using namespace std;

//--ENGLISH--------------------------------------------------------------------------
/**RECURRENCE EQUATIONS
* For every call, the size of the problem gets halved,
* that is, in each call does some calculations (O(1)) on a number
* of one digit lesser than the previous call.
*
* Defining:
*
*   n::= number of elements of the vector v.
*
* We know, thanks to the Generalitation techniques for recursive
* algorithms, that, in case the problem gets reduced in a specific
* amount of data (a constant is subtracted from thesize of the problem
* in each call), its recurrence equations will be:
* 
*        | c0                       0 <= n <= n0
*   T(n)=|
*        | a * T(n / b) + c1 * n^k  n >= n0
*
* Where:
*
*   a::= number of recursive calls inside of the algorithm.
*   b::= subtrahend
*   k::= a number so n^k represents the complexity of the non-recursive code
*        of our algorithm.
*
* Therefore, we can affirm that the recurrence equations of our algorithm are:
* 
*          | c0                         n = 1
*    T(n)= |
*          | 2 * T(n / 2) + c1 * n^0    n > 1
*/
/** COMPLEXITY OF THE ALGORITHM
 * Thanks to the previosly defined information and to the Generalitation
 * techniques for recursive algorithms, we know that, when the recurrence
 * equations look like:
 * 
 *        | c0                       0 <= n <= n0
 *   T(n)=|
 *        | a * T(n / b) + c1 * n^k  n >= n0
 *
 * The following assumptions are correct:
 * 
 *  a < b^k -> T(n) belongs to O(n ^ k)
 *  a = b^k -> T(n) belongs to O(n^k * ln(n))
 *  a > b^k -> T(n) belongs to O(n ^ logb(a))
 * 
 * Applying it to our recurrence equations:
 * 
 *  2 > 2^0
 * 
 * Therefore, T(n) belongs to O(n ^ log2(2)) = O(n).
*/

//--SPANISH--------------------------------------------------------------
/*ECUACION DE RECURRENCIA:
* Por cada llamada recursiva, dividimos el vector actual en dos mitades,
* lo que significa que reducimos el tama�o del problema a la mitad por
* cada llamada realizada.
* 
* Sabemos por la generalizacion de las ecuaciones de recurrencia y el
* estudio de su coste de eficiencia que las ecuaciones de recurrencia
* de algoritmos recursivos que dividen el tama�o del problema por cada
* llamada realizada, son:
* 
*       | c0                        0 <= n <= n0
*   T(n)|
*       | a * T(n / b) + c1 * n^k   n >= n0
* 
* Donde:
* 
*   a::= numero de llamadas recursivas dentro del algoritmo.
*   b::= particion del problema por llamada.
*   k::= numero tal que n^k equivale al coste de eficiencia del resto del
*        codigo no recursivo del algortimo.
* 
* Con esto en mente, definimos:
* 
*   n::= numero de elementos que tiene el segmento en la llamada actual.
* 
* Y podemos declarar que la ecuacion recursiva de nuestro algoritmo ser�:
* 
*       | c0                        n = 1
*   T(n)|
*       | 2 * T(n / 2) + c1 * n^0   n > 1
* 
*/
/* COMPLEJIDAD DEL ALGORITMO:
* Dado los datos anteriores y teniendo en cuenta la generalizacion de las
* ecuaciones de recurrencia de un algoritmo y el estudio de su coste de 
* eficiencia, sabemos que se cumplira lo siguiente:
* 
*   a < b^k -> T(n) pertenece a O(n ^ k)
*   a = b^k -> T(n) pertenece a O(n^k * ln(n))
*   a > b^k -> T(n) pertenece a O(n ^ logb(a))
* 
* En nuestro caso particular se cumple que:
* 
*   2 > 2^0
* 
* Por lo tanto:
* 
*   T(n) pertenece a O(n ^ log2(2)) = O(n ^ 1) = O(n)
*/
bool parcurioso(
    const vector<int>& v,
    int head,
    int tail,
    int& contPares,
    int& contImpar,
    int& sumPares,
    int& sumImpar
) {
    //CASO BASE: el segmento es de longitud 1 y siempre es parcurioso
    if (head == tail) {
        if (v[head] % 2 == 0) {
            ++contPares;
            sumPares = v[head];
        } else {
            ++contImpar;
            sumImpar = v[head];
        }
        return true;
    }/*CASO RECURSIVO: el segmento es de longitud > 1 y evaluamos la
     * caracteristica de parcurioso, que consiste en:
     * 
     *  #pares del segmento izq <= #impares del segmento der
     * ^
     *  SUMA pares del segmento izq <= SUMA impares del segmento der
     * ^
     *  parcurioso(segmento izq) v parcurioso(segmento der) == true
     */
    else {
        int mediatriz = (head + tail) / 2,
            sumIzqPares = 0, sumDerPares = 0,
            sumIzqImpar = 0, sumDerImpar = 0,
            contIzqPares = 0, contDerPares = 0,
            contIzqImpar = 0, contDerImpar = 0;
        
        bool parCurIzq = parcurioso(
                v, head, mediatriz,
                contIzqPares, contIzqImpar,
                sumIzqPares, sumIzqImpar
            ),

             parCurDer = parcurioso(
                 v, mediatriz + 1, tail,
                 contDerPares, contDerImpar,
                 sumDerPares, sumDerImpar
             );

        contPares = contIzqPares + contDerPares;
        contImpar = contIzqImpar + contDerImpar;
        sumPares = sumIzqPares + sumDerPares;
        sumImpar = sumIzqImpar + sumDerImpar;

        return (contIzqPares <= contDerImpar) &&
               (sumIzqPares <= sumDerImpar) &&
               (parCurIzq || parCurDer);
    }
}

void solve() {
    // read case
    int n;
    cin >> n;

    vector<int> v(n);
    for (int i = 0; i < n; ++i)
        cin >> v[i];

    int contPares = 0,
        contImpar = 0,
        sumImpar = 0,
        sumPares = 0;

    if (parcurioso(v, 0, n - 1, contPares, contImpar, sumPares, sumImpar))
        cout << "SI" << endl;
    else cout << "NO" << endl;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
        solve();

    return 0;
}