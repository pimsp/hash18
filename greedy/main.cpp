#include<bits/stdc++.h>

using namespace std;

#define x first
#define y second
#define pb push_back
#define eb emplace_back
#define all(v) (v).begin(), (v).end()
#define rep(i,a,b) for (auto i = (a); i != (b); ++i)
#define REP(i,n) rep(i,0,n)

typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;

ostream& operator<<(ostream &out, const ii &pr) { return out << '(' << pr.x << ',' << pr.y << ')'; }

const int maxRC = 10000, MAXRIDES = 10000;

struct ride_t
{
	// time.x: start time, time.y: end time
	ii fr, to, time;
	int d; // distance
};

int R, C, F, N, B, T;
ride_t rides[MAXRIDES];


void run()
{
	cin >> R >> C >> F >> N >> B >> T;
	REP(i, N) {
		cin >> rides[i].fr.x >> rides[i].fr.y;
		cin >> rides[i].to.x >> rides[i].to.y;
		cin >> rides[i].time.x >> rides[i].time.y;
		rides[i].d = abs(rides[i].fr.x - rides[i].to.x) + abs(rides[i].fr.y - rides[i].to.y);
		rides[i].time.y -= rides[i].d;
	}
	
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	run();

	return 0;
}
