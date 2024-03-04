#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;

int iteratie=1;

vector<uint16_t> v;

void bubbleSort(vector<uint16_t>* array) {

    // loop to access each array element
    for (int step = 1; step < array->size(); ++step) {

        // loop to compare array elements
        for (int i = 0; i < array->size() - step; ++i) {

            // compare two adjacent elements
            // change > to < to sort in descending order
            if (array->at(i) > array->at(i+1)) {

                // swapping elements if elements
                // are not in the intended order
                int temp = array->at(i);
                array->at(i) = array->at(i+1);
                array->at(i+1) = temp;
            }
        }
    }

}

// Merge two subarrays L and M into arr
void merge(vector<uint16_t> arr, int p, int q, int r) {

    // Create L ← A[p..q] and M ← A[q+1..r]
    int n1 = q - p + 1;
    int n2 = r - q;

    int L[1001], M[1001];

    for (int i = 0; i < n1; i++)
        L[i] = arr[p + i];
    for (int j = 0; j < n2; j++)
        M[j] = arr[q + 1 + j];

    // Maintain current index of sub-arrays and main array
    int i, j, k;
    i = 0;
    j = 0;
    k = p;

    // Until we reach either end of either L or M, pick larger among
    // elements L and M and place them in the correct position at A[p..r]
    while (i < n1 && j < n2) {
        if (L[i] <= M[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = M[j];
            j++;
        }
        k++;
    }

    // When we run out of elements in either L or M,
    // pick up the remaining elements and put in A[p..r]
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = M[j];
        j++;
        k++;
    }
}

// Divide the array into two subarrays, sort them and merge them
void mergeSort(vector<uint16_t> arr, int l, int r) {
    if (l < r) {
        // m is the point where the array is divided into two subarrays
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        // Merge the sorted subarrays
        merge(arr, l, m, r);
    }
}

uint16_t pixel_calculat(uint32_t n, uint32_t i, uint32_t j, vector<vector<uint8_t>>* img, string& alg) {

   v.clear();

    int inaltime = img->size();//corespunzatoare lui I
    int latime = img->at(0).size();//corespunzatoare lui J

//    cout<<"inaltime e: "<<inaltime<<"si latime e: "<<latime<<endl;
//    cout<<"i : "<<i<<" j : "<<j<<endl;
//    cout<<"window e intre: ii "<<(int) (i - n / 2)<<" si "<<(int) (i + n / 2)<<
//    "\n jj "<<(int) (j - n / 2)<<" si "<<(int) (j + n / 2)<<endl;


    if (i+1 <= n / 2 || inaltime - i<= n / 2 || j +1 <= n / 2 ||
        latime - j <= n / 2) {//fereastra iese din dimensiunile imaginii
        //cout<<"a intrat in if "<<endl;

        for (int ii = (int) (i - n / 2); ii <= (int) (i + n / 2); ii++)
            for (int jj = (int) (j - n / 2); jj <= (int) (j + n / 2); jj++) {

                if (ii >= 0 && ii < inaltime && jj >= 0 && jj < latime)//cazul ideal
                {
                    v.push_back(img->at(ii).at(jj));
                    //cout<<"caz ideal\n";
                }
                else if (ii < 0 && jj < 0)//iese si sus si la stanga
                {
                    v.push_back(img->at(0).at(0));
                    //cout<<"sus si stanga\n";
                }
                else if (ii < 0 && jj >= 0 && jj < latime)//iese doar sus
                {
                    v.push_back(img->at(0).at(jj));
                    //cout<<"doar sus\n";
                }
                else if (ii < 0 && jj >= latime)//iese si sus si la dreapta
                {
                    v.push_back(img->at(0).at(latime-1));
                    //cout<<"sus si dreapta\n";
                }
                else if (ii >= 0 && ii < inaltime && (jj >= latime))//iese doar la dreapta
                {
                    v.push_back(img->at(ii).at(latime-1));
                    //cout<<"jj este "<<jj<<" iar latime este "<<latime<<" deci rezulta "<<"jj>=latime are val "<<(jj>=latime);
                    //cout<<" doar dreapta\n";
                }
                else if (ii >= inaltime && jj >= latime)//iese si la dreapta si jos
                {
                    v.push_back(img->at(inaltime-1).at(latime-1));
                    //cout<<"dreapta si jos\n";
                }
                else if (ii >= inaltime && jj >= 0 && jj < latime)//iese doar jos
                {
                    v.push_back(img->at(inaltime-1).at(jj));
                    // cout<<"doar jos\n";
                }
                else if (ii >= inaltime && jj < 0)//iese si jos si la stanga
                {
                    v.push_back(img->at(inaltime-1).at(0));
                    //  cout<<"jos si stanga\n";
                }
                else if (ii >= 0 && ii < inaltime && jj < 0)//iese doar la stanga
                {
                    v.push_back(img->at(ii).at(0));
                    //  cout<<"doar stanga\n";
                }

                // se putea face si cu un fel de normalizare: daca ii<0 da 0
                //daca ii>=inaltime da inaltime-1 etc...

                //cout<<"ii : "<<ii<<", jj : "<<jj<<" si s-a adaugat "<<v[v.size()-1]<<" la vectorul v \n";
            }
    } else {//fereastra e in intregime in imagine
        // cout<<"a intrat in else "<<endl;
        for (uint32_t ii = i - n / 2; ii <= i + n / 2; ii++)
            for (uint32_t jj = j - n / 2; jj <= j + n / 2; jj++) {
                v.push_back(img->at(ii).at(jj));
                //cout << "s-a adaugat " << v[v.size() - 1] << " la vectorul v \n";
            }
    }


//mergeSort(v, 0, v.size());

    if (alg == "merge")
        sort(v.begin(),v.end());
    else if (alg == "bubble")
        bubbleSort(&v);

//    for(int l=0;l<v.size();l++)
//        cout<<v[l]<<' ';
//    cout<<'\n';

    if (v.size() == n * n) {
        cout << "What a wonderful world! Iteration: " << iteratie <<'\n';

        iteratie++;
    }
    else
        cout<<"not working"<<endl;

    // cout<<(uint16_t) v.at(v.size()/2+1)<<endl;
    return (uint16_t) v.at(v.size()/2);
}

int main() {

    string sorting_algorithm, in_file, out_file, tip_fisier;
    uint16_t max_gri;
    uint16_t x;
    uint32_t latime, inaltime, window_size;

    char buffer;

    cin >> sorting_algorithm >> window_size >> in_file >> out_file;
    cout<<sorting_algorithm<<window_size<<in_file<<out_file;

    //in_file = "lena_noise.pgm";//pentru testele de pe computer
    //out_file="lena_out.pgm";

    //cout<<sorting_algorithm<<window_size<<in_file<<out_file;

    ifstream scan(in_file);
    ofstream print(out_file);

    getline(scan, tip_fisier);
    print << tip_fisier << '\n';//pregatirea fisierului sa poata fi cititd

//    scan >> buffer;
//
//    while (buffer == '#') {
//        scan.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//        scan >> buffer;
//    }

    scan >> latime >> inaltime;
    print<<latime<<' '<<inaltime<<'\n';

    scan >> max_gri;
    print<<max_gri<<'\n';

    vector<vector<uint8_t>> imagine;
    vector<uint8_t> rand;

    for (uint32_t i = 1; i <= inaltime; i++) {
        for (uint32_t j = 1; j <= latime; j++) {
            scan >> x;
            rand.push_back(x);
        }
        imagine.push_back(rand);
        rand.clear();
    }

    for (uint32_t i = 0; i < inaltime; i++) {
        for (uint32_t j = 0; j < latime; j++)
            print << pixel_calculat(window_size,i,j,&imagine,sorting_algorithm)<< ' ';
        print<<'\n';
    }


    return 0;
}
