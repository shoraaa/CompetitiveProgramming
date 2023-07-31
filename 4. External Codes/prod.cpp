#include <bits/stdc++.h>
using namespace std;
int m,n,k;
int A[1002][12][12];
vector<int> maxx(vector<int> s,vector<int> t)
{
    if (s[s.size()-1]==10&&t[t.size()-1]<10) return t;
    if (s[s.size()-1]<10&&t[t.size()-1]==10) return s;
    if (s[s.size()-1]==10&&t[t.size()-1]==10)
    {
        if (s.size()>t.size()) return t;
        if (s.size()<t.size()) return s;
        for (int i=s.size()-2;i>=0;i--)
            if (s[i]!=t[i])
        {
            if (s[i]<t[i]) return s;
            if (s[i]>t[i]) return t;
        }
        return s;
    }
    if (s.size()>t.size()) return s;
    if (s.size()<t.size()) return t;
    for (int i=s.size()-1;i>=0;i--)
       if (s[i]!=t[i])
        {
            if (s[i]>t[i]) return s;
            if (s[i]<t[i]) return t;
        }
    return s;
}
vector<int> minn(vector<int> s,vector<int> t)
{
    if (s[s.size()-1]==10&&t[t.size()-1]<10) return s;
    if (s[s.size()-1]<10&&t[t.size()-1]==10) return t;
    if (s[s.size()-1]==10&&t[t.size()-1]==10)
    {
        if (s.size()>t.size()) return s;
        if (s.size()<t.size()) return t;
        for (int i=s.size()-2;i>=0;i--)
            if (s[i]!=t[i])
        {
            if (s[i]<t[i]) return t;
            if (s[i]>t[i]) return s;
        }
        return s;
    }
    if (s.size()>t.size()) return t;
    if (s.size()<t.size()) return s;
    for (int i=s.size()-1;i>=0;i--)
       if (s[i]!=t[i])
        {
            if (s[i]>t[i]) return t;
            if (s[i]<t[i]) return s;
        }
    return s;
}
vector <int> nen(long long v)
{
    vector <int> ans;
    int kt=0;
    if (v<0)
    {
        v=abs(v);
        kt=1;
    }
    while (v>0)
    {
        ans.push_back(v%10);
        v/=10;
    }
    if (kt==1) ans.push_back(10);
    if (ans.size()==0) ans.push_back(0);
    return ans;
}
vector<int> cong(vector<int> s,vector<int> t)
{
    while (s.size()<t.size()) s.push_back(0);
    while (t.size()<s.size()) t.push_back(0);
    vector <int> ans;
    int nho=0;
    for (int i=0;i<s.size();i++)
    {
        int k=s[i]+t[i]+nho;
        nho=k/10;
        k=k%10;
        ans.push_back(k);
    }
    if (nho>0) ans.push_back(1);
    while (ans.size()>1&&ans[ans.size()-1]==0)
        ans.pop_back();
    return ans;
}
void write(vector <int> A)
{
    for (int i=A.size()-1;i>=0;i--)
        if (A[i]==10) cout<<'-';
        else cout<<A[i];
    //cout<<endl;
}
vector<int> nhan(long long s,long long ss)
{
    vector<int> ans;
    int kt=0;
    if (s<0)
    {
        kt=1-kt;
        s=abs(s);
    }
    if (ss<0)
    {
        kt=1-kt;
        ss=abs(ss);
    }
    int d=0;
    while (ss>0)
    {
        long long t=s*(ss%10);
        vector <int> p=nen(t);
        vector <int> ts;
        for (int i=1;i<=d;i++)
            ts.push_back(0);
        for (int i=0;i<p.size();i++)
            ts.push_back(p[i]);
        ans=cong(ans,ts);
        d++;
        ss/=10;
    }
    if (ans.size()==0) ans.push_back(0);
    if (kt==1) ans.push_back(10);
    return ans;
}

void init()
{
    cin>>k>>m>>n;
    for (int i=1;i<=k;i++)
        for (int x=1;x<=m;x++)
            for (int y=1;y<=n;y++)
                cin>>A[i][x][y];
}

void solve()
{
    init();
    vector <int> res;
    for (int i=1;i<=30;i++)
        res.push_back(0);
    res.push_back(1);
    res.push_back(10);
    for (int x1=1;x1<=m;x1++)
        for (int y1=1;y1<=n;y1++)
            for (int x2=x1+1;x2<=m;x2++)
                for (int y2=y1+1;y2<=n;y2++)
        {
            long long vmax=-1e18;
            long long vmin=1e18;
            long long vmax1=-1e18;
            long long vmin1=1e18;
            for (int i=1;i<=k;i++)
            {
                long long t=A[i][x1][y1];
                t*=A[i][x1][y2];t*=A[i][x2][y1];
                t*=A[i][x2][y2];
                if (t<vmin)
                {
                    vmin1=vmin;
                    vmin=t;
                }
                else vmin1=min(vmin1,t);
                if (t>vmax)
                {
                    vmax1=vmax;
                    vmax=t;
                }
                else vmax1=max(vmax1,t);
            }
            res=maxx(res,nhan(vmax,vmax1));
            res=maxx(res,nhan(vmin,vmin1));
        }
    write(res);
}
int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    freopen("prod.inp","r",stdin);
    freopen("prod.out","w",stdout);
    solve();
}
