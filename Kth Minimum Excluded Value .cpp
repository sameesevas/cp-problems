#include<bits/stdc++.h>
#define ll int
#define pb push_back
#define fr(a,b) for(int i = a; i < b; i++)
#define rep(i,a,b) for(int i = a; i < b; i++)
#define mod 1000000007
#define inf (1LL<<60)
#define all(x) (x).begin(), (x).end()
#define prDouble(x) cout << fixed << setprecision(10) << x
#define triplet pair<ll,pair<ll,ll>>
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)
using namespace std;
#define MAXN 1000005

struct node
{
    int val;
    node* left, *right;
    node() {}
    node(node* l, node* r, int v)
    {
        left = l;
        right = r;
        val = v;
    }
};

node* version[MAXN];
void build(node* n,int low,int high)
{
    if (low==high)
    {
        n->val = 0;
        return;
    }
    int mid = (low+high) / 2;
    n->left = new node(NULL, NULL, 0);
    n->right = new node(NULL, NULL, 0);
    build(n->left, low, mid);
    build(n->right, mid+1, high);
    n->val = n->left->val + n->right->val;
}
 
void upgrade(node* prev, node* cur, int low, int high,
                                   int idx, int value)
{
    if (idx > high or idx < low or low > high)
        return;
 
    if (low == high)
    {
        cur->val = value;
        return;
    }
    int mid = (low+high) / 2;
    if (idx <= mid)
    {
        cur->right = prev->right;
        cur->left = new node(NULL, NULL, 0);
        upgrade(prev->left,cur->left, low, mid, idx, value);
    }
    else
    {
      
        cur->left = prev->left;
        cur->right = new node(NULL, NULL, 0);
        upgrade(prev->right, cur->right, mid+1, high, idx, value);
    }

    cur->val = cur->left->val + cur->right->val;
}
	int query1(node * cur, int lo, int hi, int i, int j)
	{
		if (hi < i || lo > j)
			return 0;
		if (i <= lo && hi <= j)
		{
			return cur->val;
		}
		int mid = lo + hi >> 1;
		int lf = query1(cur,lo, mid, i, j); 
		     int rt= query1(cur,mid + 1, hi, i, j);
                int val = lf+rt;
                return val;
	}
int query(node* past, node *pres, int l, int r , int k)
{
    if(l==r)
    {
        return l;
    }
    else
    {
       
        int mid=(l+r)/2;
         int mysegC= (mid-l+1)-(pres->left->val-past->left->val);
        if(k<=mysegC)
        {
            return query(past->left,pres->left,l,mid,k);
        }
        else
        {
            return query(past->right,pres->right,mid+1,r,k-mysegC);
        }
    }
}

signed main() {
   fast_io;
   int n,q;
   cin>>n;
   vector<int> a(n),indexTree(n);
    node* root = new node(NULL, NULL, 0);
    build(root, 1, 1e6);
    version[0]=root;
   for(int i=0;i<n;i++)
   {
        cin>>a[i];
        version[i+1]= new node(NULL, NULL, 0);
        upgrade(version[i],version[i+1],1,1e6,a[i],1);
       
   }

    
    cin>>q;
    while(q--)
    {
        int l,r,k;
        cin>>l>>r>>k;
        l--,r--;
        if (l > r) swap(l, r);
        int ans=1000000-(query1(version[r+1],1,1e6,1,1e6)-query1(version[l],1,1e6,1,1e6));
        if(ans<k)
        {
            cout<<1000000+(k-ans)<<endl;
            continue;
        }
        cout<<query(version[l],version[r+1],1,1e6,k)<<endl;
        
    }

   return 0;
}