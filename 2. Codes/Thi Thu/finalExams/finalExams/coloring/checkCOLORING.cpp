#include <bits/stdc++.h>

using namespace std;
const int maxN = 1024;

int nTest, n;
int r[maxN][2], c[maxN][2], x[1000001], y[1000001];
char s[1000001];

double Check(string inp, string out, string ans) {
    // ans --> hoc sinh
    // out --> me
    FILE *fileInput = fopen(inp.c_str(), "r");
    FILE *fileAns = fopen(ans.c_str(), "r");
    
    int isOk = 1;
    
    fscanf(fileInput, "%d", &nTest);

    while (nTest > 0) {
        nTest--;

        fscanf(fileInput, "%d", &n);
        memset(r, 0, sizeof(r));
        memset(c, 0, sizeof(c));

        for (int i=1; i<=n; i++) {
            fscanf(fileInput, "%d%d", &x[i], &y[i]);
        }

        fscanf(fileAns, "%s", s);
        if (strlen(s) != n) { isOk = 0; break;}

        for (int i=1; i<=n; i++) {
            int cm = (s[i - 1] == 'B');
            r[x[i]][cm]++;
            c[y[i]][cm]++;
        }
        for(int i = 0; i < 1024; i++) {
            if (abs(r[i][0] - r[i][1]) > 1) { isOk = 0; break;}
            if (abs(c[i][0] - c[i][1]) > 1) { isOk = 0; break;}
        }
        if (isOk == 0) break;
    }

    fclose(fileInput);
    fclose(fileAns);
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
        inp = spath + "COLORING.INP";
        out = spath + "COLORING.OUT";
        getline(cin,spath);
        ans = spath + "COLORING.OUT";
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
