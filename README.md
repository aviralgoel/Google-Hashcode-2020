# Google-Hashcode-2020
 This was the submission of our team of 2 people for the Google Hashcode 2020 hosted online.
 We scored a overal rank of #3897 and #4 in the nation.
 
 # Book Scanning: task description

Google provided a list of L libraries and B books. The task is to plan which books to scan from which library to maximize the total score of all scanned books, taking into account that each library needs to be signed up before it can ship books.

Each book B[k] has a certain score S[k], where S[k] belongs to the range [0, 1’000]. The maximum size of list of books is 100’000, i.e., the index k belongs to the range [0, 99’999].

Each library L[k] has three parameters:

 1. the set of books in the library (a “list” of the indexes of the books).
 2. the time – measured as number of days – that it takes to sign the library up for scanning. The maximum time required to sign up is 100’000 days.
 3. The maximum number of books that can be scanned each day, after the library has signed up

The maximum number of libraries is 100’000, i.e., the index k belongs to the range [0, 99’999].

The maximum time of the simulation is D – 1. All books scanned after this time do not provide any score. All libraries signed up after this time are ignored. The value of the parameter D belongs to the range [1; 100’000].

Implicitly, both books and libraries are identified by a numerical index.
 
 From what we can understand within the given 5 hours time frame of the competition, we had set the following aims.
 Objective:
 1. Store all the information (Books, Libraries and Days available) (Done)
 2. Store all the information about each book and each library (Done)
 3. Optimize in such a way that you can figure out, which books yield more score, which libraries have more books. (Sort of Done)
 4. Further Optimize (or rank) the libraries according to their sign up time. (Partially Done)
 5. Look for further optimizations which can make concurrent sign up of many libraries at once. (Somewhat done but solution is dumb)
 6. Further optimization according to test cases. (NOT DONE)
    
Takeaways:
 1. We should have been a little more prepared for the large sets of the data.
 2. We should have also experimented with randomization of the data, rather than just sorting.
 3. We should have tried a combination of (random+sort) on the data set. 
 4. Obviously, thought of better approaches, perhaps, graph or advance set theory. 
