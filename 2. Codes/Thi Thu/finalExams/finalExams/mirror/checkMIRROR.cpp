#include <bits/stdc++.h>

using namespace std;
const int maxN = 1e5 + 1;

double res[maxN], hs, best = 0;
int t, n;

double Check(string inp, string out, string ans) {
    // ans --> hoc sinh
    // out --> me
    FILE *fileInput = fopen(inp.c_str(), "r");
    FILE *fileAns = fopen(ans.c_str(), "r");
    FILE *fileOut = fopen(out.c_str(), "r");
    
    int isOk = 1;
    
    fscanf(fileInput, "%d", &n);
    
    for (int i=1; i<=n; i++) {
        fscanf(fileOut, "%lf", &res[i]);
        best = max(best, res[i]);
    }

    fscanf(fileAns, "%d", &t);
    fscanf(fileAns, "%lf", &hs);

    if ((hs + 1e6 < best) || (t < 1) || (t > n)) {isOk = 0;}
    else {
        if (abs(res[t] - hs) > 1e3) {isOk = 0;}
    }
    
    
    fclose(fileInput);
    fclose(fileAns);
    fclose(fileOut);
    return isOk;
}

int main(int argc, const char * argv[]) {
    // Read Input
	string inp;
	string out;
	string ans;

    int themis = 1; //themis C7
    if (themis == 1) {
        string spath = "";
        getline(cin,spath);
        inp = spath + "MIRROR.INP";
        out = spath + "MIRROR.OUT";
        getline(cin,spath);
        ans = spath + "MIRROR.OUT";
    }
    else {
    	string inpCMS(argv[1]); inp = inpCMS;
	    string outCMS(argv[2]); out = outCMS;
	    string ansCMS(argv[3]); ans = ansCMS;
    }

    
    double result = Check(inp, out, ans);
    
    if (result < 0) {
    	if (themis == 0) {
            cout << 0.0 << endl;
        	//cerr << "Phuong an sai" << endl;
        }
        else {
            cout << "SAI";
        }
        
    }

    else {
        if (themis == 0) {
            cout << result << endl;
        }
        else {
        	//cout << "DUNGMOTPHAN"<< endl;
            cout <<result<< endl;
        }

    }

}
