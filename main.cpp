/* Google Hashcode 2020
    Submitted Solution by Aviral Goel and Urvashi Kishnani
    National Ranking #4
    Overall Ranking #3897

    Objective:
    1. Store all the information (Books, Libraries and Days available) [Done]
    2. Store all the information about each book and each library [Done]
    3. Optimize in such a way that you can figure out, which books yield more score, which libraries have more books. [Done]
    4. Further Optimize (or rank) the libraries according to their sign up time. [Partially Done]
    5. Look for further optimizations which can make concurrent sign up of many libraries at once.[Somewhat done but solution is dumb]
    6. Further optimization according to test cases. [NOT DONE]

    Code written: Feb 20th, 2020.
    Time Taken: 5 Hours
    Authors: Aviral Goel and Urvashi Kishnani

    NOTE TO SELF: ALWAYS COMMENT WHILE WRITING
*/


#include <bits/stdc++.h>
using namespace std;




// Global variables for total no. of books, no. of libraries and no. of days available.
int B, L, D;
// vector array to store the score of each book.
vector<int> scores;
bool b_bool[1000000];

//Library Struct for storing the input information of every library and additional calculated info
struct library {
    int id;
    int n;
    int t;
    int m;
    int pbooks;
    int pdays;
    //int f;
    vector<int> bids; // IDs of all the books which are in that library
    vector<pair<int, int> > vp_score_bid; // a vector pair of books and their scores which are available in that library
    vector<int> selected_bids; // list of selected books from that library which are sent for sign up
};

vector<library> lib; //list of input libraries
vector<library> oplib; //list of selected libraries
vector<pair<int, int> > vp_time; //library pair with its sign up time


// Data Input function
void read(char* input_file) {

    ifstream fin(input_file);
    //Take in no. of books, libraries, and days available.
    fin>>B>>L>>D;

    //Store score of each book available in the question universe
    for(int i = 0; i < B; i++) {
        int x;
        fin>>x;
        scores.push_back(x);
    }


    //Store details for each library
    for(int i = 0; i < L; i++)
    {
        //Initialize a library struct object
        library temp_lib;
        temp_lib.id = i; //Library ID
        temp_lib.pbooks = 0; // initial Books since signed up
        temp_lib.pdays = 0; // initial Days since signed up

        // Input number of books, time to sign up, no. of books that can be signed up per day
        fin>>temp_lib.n>>temp_lib.t>>temp_lib.m; //scanf

        //For every book available in the library
        for(int j = 0; j < temp_lib.n; j++) {
            int x;
            // record it's book ID
            fin>>x;
            temp_lib.bids.push_back(x);
        }

        // For every book in the library, create a vector pair of the book score and book ID
        for(int j = 0; j < temp_lib.n; j++) {
            // Get the ID of the jth book and get the score of the book with THAT specific book ID
            temp_lib.vp_score_bid.push_back({scores[temp_lib.bids[j]], temp_lib.bids[j]});
        }

        // sort the vector pair with respect to decreasing order of scores
        sort(temp_lib.vp_score_bid.begin(), temp_lib.vp_score_bid.end());

        //Global vector pair to store sign up time for each library
        vp_time.push_back({temp_lib.t, temp_lib.id});

        //vector of library struct objects
        lib.push_back(temp_lib);
    }
}

void solve() {

    //sort to rank the libraries with least sign up time first. Quicker sign ups implies they can send more in the long run.
    sort(vp_time.begin(), vp_time.end());

    //Count how many days are left for the whole process, and how many books are left overall.
    int days_remaining = D;
    int books_remaining = B;

    // For every library there is.
    for(int i = 0; i < L; i++)
    {
        //Is there enough time left to sign up this library, if not, return

        int lib_id = vp_time[i].second;
        //cout<<"Lib: "<<i<<" "<<lib_id<<" "<<endl;
        if(lib[lib_id].t > days_remaining) {
            return;
        }

        //If there is time left, then sign this up and calculate how much score will be yield from this library until the end
        days_remaining -= lib[lib_id].t;
        //cout<<"days remaining "<<days_remaining<<endl;


        lib[lib_id].pdays = days_remaining; // No. of days for this library to send books

        // no. of books it can send, either depending on days remaining or all of it's books, if books are less
        lib[lib_id].pbooks = min(days_remaining * lib[lib_id].m, lib[lib_id].n);

        //For all the books in this particular library
        for(int j = 0; j < lib[lib_id].bids.size(); j++) {
            //cout<<j<<endl;
            int book_id = lib[lib_id].vp_score_bid[j].second;
            //cout<<book_id;
            //if the library has that certain book, add it to the book which will be sent
            if(!b_bool[book_id]) {
                b_bool[book_id] = true;
                lib[lib_id].selected_bids.push_back(book_id);
                books_remaining--;
            }
            //Stop if all books are over
            if(lib[lib_id].selected_bids.size() == lib[lib_id].pbooks) {
                break;
            }
        }
        //cout<<"books remaining "<<books_remaining<<endl;

        //When no books are left
        if(lib[lib_id].selected_bids.size() == 0)
        {
            days_remaining += lib[lib_id].t;
        }
        else
        {
            //cout<<"Lib: "<<i<<" added"<<endl;
            oplib.push_back(lib[lib_id]);
        }

        if(books_remaining == 0)
        {
            return;
        }
    }
}

// Function to display output
void write(char* output_file) {
    ofstream outfile(output_file);
    outfile<<oplib.size()<<endl;
    //For each selected library
    for(int i = 0; i < oplib.size(); i++) {
        //Display the no. of books which that library sent
        outfile<<oplib[i].id<<" "<<oplib[i].selected_bids.size()<<endl;

        // Display individual book IDs that were sent to sign up
        for(int j = oplib[i].selected_bids.size() - 1; j >= 0; j--) {
            outfile<<oplib[i].selected_bids[j]<<" ";
        }
        outfile<<endl;
    }
}

int main()
{
    //Set of input and output file names
    char* INPUTS[] = {"a_example.txt", "b_read_on.txt", "c_incunabula.txt", "d_tough_choices.txt", "e_so_many_books.txt", "f_libraries.txt"};
    char* OUTPUTS[] = {"a_example.out", "b_read_on.out", "c_incunabula.out", "d_tough_choices.out", "e_so_many_books.out", "f_libraries.out"};

    //For all input files
    for(int x = 0; x < 6; x++)
    {
        //Clear buffer for each input test case file
        scores.clear();
        lib.clear();
        oplib.clear();
        vp_time.clear();
        memset(b_bool, false, sizeof b_bool);

        // Read, Solve and Diplay
        //files are in different folder, please make sure files are in source folder!!!!
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



