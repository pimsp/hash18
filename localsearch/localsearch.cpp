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

const int maxRC = 10000, MAXRIDES = 10000, MAXCARS = 1000;

struct ride_t
{
	// time.x: start time, time.y: end time
	ii fr, to, time;
	int d, idx; // distance, index
	bool used;
};

int R, C, F, N, B, T;
ride_t rides[MAXRIDES];
int invidx[MAXRIDES];
vii carrides[MAXCARS]; // (ride, endtime)

inline static int NYdist(ii a, ii b)
{
	return abs(a.x - b.x) + abs(a.y - b.y);
}

void TryOptimise()
{
	REP(i, N) {
		if (rides[i].used) continue;
		REP(j, F) {
			if (rides[i].used) break;
			int maxk = (int)carrides[j].size();
			REP(k, maxk) {
				// try to replace carrides[j][k] with i (which happens to be not so very helpful (at all))
				int oldtstart, newtstart;
				int score = NYdist(rides[i].fr, rides[i].to) - NYdist(rides[carrides[j][k].x].fr, rides[carrides[j][k].x].to);
				if(k==0){
					newtstart = NYdist(make_pair(0,0), rides[i               ].fr);
					oldtstart = NYdist(make_pair(0,0), rides[carrides[j][k].x].fr);
				} else {
					newtstart = carrides[j][k-1].y + NYdist(rides[carrides[j][k-1].x].to, rides[i               ].fr);
					oldtstart = carrides[j][k-1].y + NYdist(rides[carrides[j][k-1].x].to, rides[carrides[j][k].x].fr);
				}
				if(newtstart <= rides[i               ].time.x) score += B;
				if(oldtstart <= rides[carrides[j][k].x].time.x) score -= B;
				if (score < 0) continue;
				if(newtstart + rides[i].d > rides[i].time.y) continue;
				
				rides[carrides[j][k].x].used = false;
				carrides[j][k].x = i;
				carrides[j][k].y = newtstart + rides[i].d;
				rides[carrides[j][k].x].used = true;
			}
		}
	}
}

void run()
{
	scanf("%d %d %d %d %d %d", &R, &C, &F, &N, &B, &T);
	REP(i, N) {
		scanf("%d %d %d %d %d %d", &rides[i].fr.x, &rides[i].fr.y, &rides[i].to.x, &rides[i].to.y, &rides[i].time.x, &rides[i].time.y);
		rides[i].d = NYdist(rides[i].fr, rides[i].to);
		rides[i].time.y -= rides[i].d;
		rides[i].idx = i;
	}

	sort(rides, rides + N, [] (ride_t a, ride_t b) -> bool {
		return a.time < b.time;
	});
	REP(i, N){
		invidx[rides[i].idx]=i;
	}
	
	REP(i, F) {
		int a, M, time;
		time = 0;
		ii loc = make_pair(0,0);
		scanf("%d", &M);
		REP(j, M){
			scanf("%d", &a);
			time += NYdist(loc, rides[invidx[a]].fr);
			if (time < rides[invidx[a]].time.x) time = rides[invidx[a]].time.x;
			time += rides[invidx[a]].d;
			loc = rides[invidx[a]].to;
			carrides[i].eb(invidx[a], time);
			rides[invidx[a]].used = true;
		}
	}
	
	TryOptimise();
	
	REP(i, F) {
		printf("%d", (int) carrides[i].size());
		for (ii j : carrides[i]) printf(" %d", rides[j.x].idx);
		printf("\n");
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
