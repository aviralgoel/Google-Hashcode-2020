#include <bits/stdc++.h>

using namespace std;

/*
struct ppcomp {
  bool operator()(const std::pair<pair<int, int>, int> &a, const std::pair<pair<int, int>, int> &b) {
    if (a->first.first != b->first.first) {
      return a->first.first < b->irst.first;
    }
    return a->first.second > b->first.second;
  }

} ppcomp1;
*/

int B, L, D;
vector<int> scores;
bool b_bool[1000000];

struct library {
    int id;
    int n;
    int t;
    int m;
    int pbooks;
    int pdays;
    //int f;
    vector<int> bids;
    vector<pair<int, int> > vp_score_bid;
    vector<int> selected_bids;
};
vector<library> lib;
vector<library> oplib; //list of selected libraries
vector<pair<int, int> > vp_time;

void read(char* input_file) {
    ifstream fin(input_file);
    fin>>B>>L>>D;
    for(int i = 0; i < B; i++) {
        int x;
        fin>>x;
        scores.push_back(x);
    }
    for(int i = 0; i < L; i++) {
        library temp_lib;
        temp_lib.id = i;
        temp_lib.pbooks = 0;
        temp_lib.pdays = 0;
        fin>>temp_lib.n>>temp_lib.t>>temp_lib.m;
        for(int j = 0; j < temp_lib.n; j++) {
            int x;
            fin>>x;
            temp_lib.bids.push_back(x);
        }

        for(int j = 0; j < temp_lib.n; j++) {
            temp_lib.vp_score_bid.push_back({scores[temp_lib.bids[j]], temp_lib.bids[j]});
        }

        sort(temp_lib.vp_score_bid.begin(), temp_lib.vp_score_bid.end());

        vp_time.push_back({temp_lib.t, temp_lib.id});
        lib.push_back(temp_lib);
    }
}

void solve() {
    sort(vp_time.begin(), vp_time.end());

    int days_remaining = D;
    int books_remaining = B;

    for(int i = 0; i < L; i++) {
        int lib_id = vp_time[i].second;

        //cout<<"Lib: "<<i<<" "<<lib_id<<" "<<endl;
        if(lib[lib_id].t > days_remaining) {
            return;
        }
        days_remaining -= lib[lib_id].t;
        //cout<<"days remaining "<<days_remaining<<endl;
        lib[lib_id].pdays = days_remaining;
        lib[lib_id].pbooks = min(days_remaining * lib[lib_id].m, lib[lib_id].n);

        for(int j = 0; j < lib[lib_id].bids.size(); j++) {
            //cout<<j<<endl;
            int book_id = lib[lib_id].vp_score_bid[j].second;
            //cout<<book_id;
            if(!b_bool[book_id]) {
                b_bool[book_id] = true;
                lib[lib_id].selected_bids.push_back(book_id);
                books_remaining--;
            }
            if(lib[lib_id].selected_bids.size() == lib[lib_id].pbooks) {
                break;
            }
        }
        //cout<<"books remaining "<<books_remaining<<endl;
        if(lib[lib_id].selected_bids.size() == 0) {
            days_remaining += lib[lib_id].t;
        } else {
            //cout<<"Lib: "<<i<<" added"<<endl;
            oplib.push_back(lib[lib_id]);
        }

        if(books_remaining == 0) {
            return;
        }
    }
}

void write(char* output_file) {
    ofstream outfile(output_file);
    outfile<<oplib.size()<<endl;
    for(int i = 0; i < oplib.size(); i++) {
        outfile<<oplib[i].id<<" "<<oplib[i].selected_bids.size()<<endl;
        for(int j = oplib[i].selected_bids.size() - 1; j >= 0; j--) {
            outfile<<oplib[i].selected_bids[j]<<" ";
        }
        outfile<<endl;
    }
}

int main()
{
    char* INPUTS[] = {"a_example.txt", "b_read_on.txt", "c_incunabula.txt", "d_tough_choices.txt", "e_so_many_books.txt", "f_libraries.txt"};
    char* OUTPUTS[] = {"a_example.out", "b_read_on.out", "c_incunabula.out", "d_tough_choices.out", "e_so_many_books.out", "f_libraries.out"};
    for(int x = 0; x < 6; x++) {
        scores.clear();
        lib.clear();
        oplib.clear();
        vp_time.clear();
        memset(b_bool, false, sizeof b_bool);

        read(INPUTS[x]);
        cout<<"read done"<<endl;
        //cout<<B<<" "<<L<<" "<<D<<" "<<lib.size();

        solve();
        cout<<"solve done"<<endl;

        write(OUTPUTS[x]);
        cout<<"write done"<<endl;
    }
    return 0;
}
