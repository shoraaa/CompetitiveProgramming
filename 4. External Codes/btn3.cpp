#include <bits/stdc++.h>
using namespace std;
int n,k,d[3],code[300];
long long F[202][10];
string G[202][10002];
const char c[6]={'(',')','[',']','{','}'};
char A[12];
string s;
map <string,int> mp;
string cong(string s,string t)
{
    while (s.length()<t.length()) s='0'+s;
    while (t.length()<s.length()) t='0'+t;
    string ans="";int nho=0;
    for (int i=s.length()-1;i>=0;i--)
    {
        int k=s[i]+t[i]-96+nho;
        nho=k/10;k%=10;
        ans=char(k+'0')+ans;
    }
    if (nho==1) ans="1"+ans;
    return ans;
}
string tinh(int i,string s)
{
    if (mp[s]==0) {mp[s]=mp.size();for (int i=1;i<=n+1;i++) G[i][mp[s]]="";}
    if (G[i][mp[s]]!="") return G[i][mp[s]];
    if (i>=n)
    {
        if (s.size()==0) G[i][mp[s]]="1";
        else G[i][mp[s]]="0";
        return G[i][mp[s]];
    }
    string ans="0";
    for (int j=0;j<6;j++)
    {
        if (code[c[j]]<3&&s.size()<k)
        {
            ans=cong(ans,tinh(i+1,s+c[j]));
            continue;
        }
        if (s.size()==0) continue;
        if (code[c[j]]+code[s[s.size()-1]]==5)
        {
            string p="";
            for (int l=0;l<s.size()-1;l++)
                p+=s[l];
            ans=cong(ans,tinh(i+1,p));
        }
    }
    G[i][mp[s]]=ans;
   // cout<<i<<' '<<s<<' '<<ans<<endl;
    return ans;
}
void solve()
{
    cin>>n>>k;
    code['(']=0;code['[']=1;code['{']=2;
    code['}']=3;code[']']=4;code[')']=5;

    cin>>s;
    string res="0";
    stack <char> st;
    int dem=0;
    for (int i=0;i<s.length();i++)
    {
        for (int j=0;j<6;j++)
        {
            if (c[j]==s[i]) break;
            string ss;
            while (!st.empty())
            {
                ss=st.top()+ss;
                st.pop();
            }
            for (int i=0;i<ss.size();i++)
                st.push(ss[i]);

            if (code[c[j]]<3)
            {
                if (st.size()==k)
                    continue;
                ss+=c[j];
            }
            else
            {
                if (st.empty()||code[st.top()]+code[c[j]]!=5)
                    continue;
                ss.erase(ss.size()-1,1);
            }
            res=cong(res,tinh(i+1,ss));
        }
        if (st.empty()||code[s[i]]+code[st.top()]!=5)
            st.push(s[i]);
        else st.pop();
    }
    cout<<cong(res,"1");
}
int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    freopen("btn3.inp","r",stdin);
    freopen("btn3.out","w",stdout);
    solve();
}
