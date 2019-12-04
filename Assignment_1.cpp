/**********************************************************
 * Course: CS213 - Programming II  - 2019                 *
 * Title:  Assignment I                                   *
 * Group:  G1 (Old)                                       *
 * Team members:                                          *
 *   Abdelrahman Nasr Abdelsalam         -   20170343     *
 *   Bahaa El-din Osama Sayed            -   20170078     *
 *   Karim Nour El-din Saleh             -   20170200     *
 *   Omar Mohamed Atta                   -   20170184     *
 **********************************************************/

#include <iostream>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;


/// Global Variables
string user = "USER", spacing = "     ";
string myChoice;

int capacity = 0;
string *queAndAns = new string[capacity];  /// Dynamic array to carry questions and answers.

int success = 2;

int QuesTakenPerQuiz;
int correct_Answer = 0;
int wrong_Answer = 0;

double avg = 0;
double sum = 0;
int capacity_2 = 0;
int *stat = new int[capacity_2]; /// Dynamic array to carry number of correct answers per quiz


/// Functions Declarations
string choice();
void mainMenu();

/// administrator functions
void admin();

void viewQue();
void deleteQue(int t_queId);
void AddQue();
void expandFive(); /// related to AddQue()
void loadQue();


/// The rest of Main menu options functions
void updateName(string &u);

void newQuiz();
void generate_random_questions(int NumOFQuestion);
void randomize(int arr[], int n);

void trackQuizResult();
void scoreStat();
void allScores();

void goBack(); /// General function for go back or exit choice


int main() {

    mainMenu();

    return 0;
}


string choice() {
    string x;
    cout << endl << "My choice: ";
    cin >> x;
    cout << "\n------------------------------------------------------------------\n" << endl;

    return x;
}


/// Abdelrahman Part
void mainMenu() {
    string menuItems[6] = {
            "Go to administration menu",
            "Update your name",
            "Start a new quiz",
            "Display your scores statistics",
            "Display all your scores",
            "Exit"};

    cout << "Welcome " << user << ", please choose from the following options:" << endl;

    for (int i = 0; i < sizeof(menuItems) / sizeof(menuItems[0]); i++) {
        cout << spacing << "[" << i + 1 << "] " << menuItems[i] << endl;
    }

    myChoice = choice();

    if      (myChoice == "1") admin();
    else if (myChoice == "2") updateName(user);
    else if (myChoice == "3") newQuiz();
    else if (myChoice == "4") scoreStat();
    else if (myChoice == "5") allScores();
    else if (myChoice == "6") exit(0);
    else {

        cout << "==============================\n";
        cout << "= Error! Incorrect choice :( =\n";
        cout << "==============================\n\n";

        mainMenu();
    }
}


void admin() {
    string adminOptions[4] = {
            "View all questions",
            "Add new question",
            "Load questions from file",
            "Go back to main menu"};

    cout << "Welcome to the administration menu, please choose from the following options:" << endl;

    for (int i = 0; i < sizeof(adminOptions) / sizeof(adminOptions[0]); i++) {
        cout << spacing << "[" << i + 1 << "] " << adminOptions[i] << endl;
    }

    myChoice = choice();

    if      (myChoice == "1") viewQue();
    else if (myChoice == "2") AddQue();
    else if (myChoice == "3") loadQue();
    else if (myChoice == "4") mainMenu();
    else {

        cout << "==============================\n";
        cout << "= Error! Incorrect choice :( =\n";
        cout << "==============================\n\n";

        admin();
    }

}


void expandFive() {
    string *temp = queAndAns;           ///ASk.
    queAndAns = new string[capacity + 5];

    if (capacity > 0) {
        for (int i = 0; i < capacity; ++i) {
            queAndAns[i] = temp[i];
        }
    }

    capacity += 5; /// to keep track of size

    delete[] temp;
}


void viewQue() {
    int queId;
    string tempChoice;

    cout << "Number of questions available: " << capacity / 5 << "\n\n";

    if (capacity > 0) {
        string tempChoice;
        int counter;

        cout << "Questions list:" << endl;
        cout << "---------------" << endl;

        for (int i = 0; i < capacity; i++) {
            tempChoice = "";

            if (i % 5 == 0) {
                cout << endl << endl;
                cout << "[" << (i / 5) + 1 << "] " << queAndAns[i] << endl;
                counter = 0; /// reset alphabet counter
            } else {
                tempChoice += "[";
                tempChoice += (char) ('a' + counter);
                tempChoice += "] ";
                tempChoice += queAndAns[i];

                cout << spacing;
                cout << left << setfill(' ') << setw(20);   /// TO arrangement choices.
                cout << tempChoice;

                counter++;
            }

        }
    } else {
        cout << "\n=======================================\n";
        cout << "= There are no questions to be viewed =\n";
        cout << "=   Please, add/load some questions   =\n";
        cout << "=======================================\n\n";

        admin();
    }

    cout << "\n------------------------------------------------------------------\n" << endl;

    /// Alert messages for deletion process
    if (success == 1) {
        cout << "\n========================================\n";
        cout << "= The question is deleted successfully =\n";
        cout << "========================================\n\n";

        success = 2; /// reset tracker value
    } else if (success == 0) {
        cout << "\n=============================================\n";
        cout << "= Sorry, The question ID is out of range :( =\n";
        cout << "=============================================\n\n";

        success = 2; /// reset tracker value
    }

    /// Delete a question
    cout << "Press [d] and the question ID if you want to delete a question (Example: d 2)" << endl;
    cout << "Press [b] if you want to go back to the main menu" << endl;

    myChoice = choice();

    if (myChoice == "d") {
        cin >> queId;
        deleteQue(queId);
    } else if (myChoice == "b") mainMenu();
    else {

        cout << "==============================\n";
        cout << "= Error! Incorrect choice :( =\n";
        cout << "==============================\n\n";

        cin.clear();
        fflush(stdin);

        admin(); /// temp
    }

}


void deleteQue(int t_queId) {
    /// question index
    int quePos = (t_queId - 1) * 5;

    /// To make sure that the question number is available and not only one question
    if (quePos >= 0 && capacity > quePos && capacity > 5) {

        string *temp = queAndAns;
        queAndAns = new string[capacity - 5];

        int n = 0;

        for (int i = 0; i < capacity; ++i) {
            if (i == quePos - 1 || (i == quePos && quePos == 0)) {
                i += 5; /// To make a gap that ignore the deleted question
                n = 5; /// To reduce the gap between iterators
            }
            queAndAns[i - n] = temp[i];
        }

        capacity -= 5; /// To keep track of size

        delete[] temp;

        success = 1; /// To alert success

    } else if (quePos == 0 && capacity == 5) { /// when there is only one question
        queAndAns = new string[capacity - 5];
        capacity -= 5;
    } else {
        success = 0; /// To alert failure
    }

    viewQue();
}


void AddQue() {
    string data;
    string info[5] = {
            "Your question: ",
            "choice 1 (the correct choice): ",
            "choice 2: ",
            "choice 3: ",
            "choice 4: "};

    expandFive();   /// expand the array

    /// take the data and store it into the array of questions
    cin.ignore();
    for (int i = 0; i < 5; i++) {
        cout << info[i];
        getline(cin, data);

        if (i == 1) data = "*" + data; /// To know the right answer
        queAndAns[(capacity - 5) + i] = data; /// (capacity-5) to return to the start point
    }

    cout << "\n=======================================\n";
    cout << "= YOUR QUESTION IS ADDED SUCCESSFULLY =\n";
    cout << "=======================================\n\n";

    admin();

}


void loadQue() {
    string filename, temp;
    fstream datafile;
    string c;
    int counter = 0;

    cout << "File name: ";
    cin.ignore();
    getline(cin, filename);

    int nameLen = filename.length();

    /// place extension if it doesn't exist
    if (nameLen <= 4 || filename.substr(nameLen - 4) != ".txt") filename += ".txt";

    datafile.open(filename.c_str(), ios::in);


    if (datafile.fail()) {
        cout << "\n=============================\n";
        cerr << "= Error! File not found! :( =\n";
        cout << "=============================\n\n";
        cout << filename;
        admin();
    }

    while (!datafile.eof()) {
        temp = "*";
        getline(datafile, c);

        if (counter % 5 == 0) { /// to receive a new question
            expandFive();
            counter = 0; /// re-initialization of counter
        } else if ((counter - 1) % 5 == 0) { /// to identify the correct answer with "*"
            temp += c;
            c = temp;
        }

        queAndAns[(capacity - 5) + counter] = c; /// to be placed based on arrangement of questions

        counter++;
    }

    cout << "\n==========================================\n";
    cout << "= THE FILE HAS BEEN LOADED SUCCESSFULLY! =\n";
    cout << "==========================================\n\n";

    datafile.close();

    admin();
}


void updateName(string &u) {
    cout << "Current Name: " << u << endl;
    cout << "New Name: ";
    cin >> u;
    cout << "------------------------------------------------------------------" << endl;
    mainMenu();
}



/// Bahaa Part
void newQuiz() {

    int correct_Ans;
    QuesTakenPerQuiz = 5; /// Assume equal 5 questions.

    if (QuesTakenPerQuiz > capacity / 5) /// capacity / 5 = number of questions.
    {

        cout << "\n=====================================================\n";
        cerr << "= The questions are not enough to create a new quiz =\n";
        cerr << "=        Please, add at least " << QuesTakenPerQuiz - capacity / 5 << " new questions.      =\n";
        cout << "=====================================================\n\n";

        mainMenu();

    } else {
        generate_random_questions(QuesTakenPerQuiz);
    }
}




void generate_random_questions(int NumOFQuestion)
{

    int *arr = new int[capacity];   /// This is pool .
    int store[NumOFQuestion];       /// Some questions choices from pool of questions and store in new array.
    string correct_choice;

    /// This is for question.
    for (int i = 0; i < capacity; ++i) {
        arr[i] = i;
    }

    randomize(arr, capacity);  /// capacity mean pool of questions.

    int j = 0;
    int cnt = 0; /// This is to bound the number of questions.

    for (int i = 0; i < capacity; ++i)  /// pool.
    {
        if (arr[i] % 5 == 0)
        {
            store[j] = arr[i];    /// store of j .. [j = index] ... not values
            ///  array of Questions and answer.

            ++j;     /// i do my j=0  to start save values from index 0  to cnt  because i may above 0 .
            ++cnt;  /// to bound number of question must saved depend on number of question.
        }

        if (cnt == NumOFQuestion) /// limitation.
        {
            break;
        }
    }

    string tempChoice;

    correct_Answer = 0; /// Reset values
    wrong_Answer = 0;
    sum = 0;

    for (int i = 0; i < NumOFQuestion; i++)  /// i actual just need to loop Numbers of questions not more than that.
    {
        /// because  i store them in array.


        cout << "\n";
        cout << "[" << i + 1 << "] " << queAndAns[store[i]] << "\n\n";

        /// for generating random choices.
        int arr2[4] = {4, 2, 3, 1};/// just initial , but must be from 1 to 4 .
        randomize(arr2,4);
        cout << "\n";
        for (int k = 0; k < 4; k++) /// To loop for choices of each question(just 4 choices for every question).
        {
            tempChoice = "";  /// It must be empty for each iteration.
            tempChoice += "[";
            tempChoice += (char) ('a' + k);   /// When counter = 0  alphabet = a   and  counter =1  alphabet = b ... and so one .
            tempChoice += "]";
            tempChoice += queAndAns[store[i] + arr2[k]]; /// [ 5 + 1 ] /// next choice.


            /// To delete the star from screen.
            if (tempChoice[3] == '*')  /// The star exist in postion 4 = index[3].
            {

                correct_choice = tempChoice[1];   /// Store correct choice .
                tempChoice.erase(tempChoice.begin() + 3);
            }

            cout << spacing;
            cout << left << setfill(' ') << setw(25);   /// To arrange choices and spaces.
            cout << tempChoice;
        }

        cout << "\n\n";
        if (choice() == correct_choice) {
            ++correct_Answer;
        }
    }

    trackQuizResult(); /// To capture stats and calculate average

    wrong_Answer = NumOFQuestion - correct_Answer;

    cout << "\t\t" << "******************************" << "\n";
    cout << "\t\t" << "*   Your score      : " << fixed << setprecision(2) << avg << "   *\n";
    cout << "\t\t" << "*   Correct Answers : " << correct_Answer << "      *\n";
    cout << "\t\t" << "*   Wrong Answers   : " << wrong_Answer << "      *\n";
    cout << "\t\t" << "******************************" << "\n\n";

    delete[] arr;


    mainMenu();
}



/// The idea, it take range of values say 30 and starting change position of them
/// with bound of i which change in each iteration.
/// and store my range to array without duplicate any values.
void randomize(int arr[], int n) {

    /// Example: if i wanna  range from 0 to 9 , i will write my code rand()%10  ,it will print values from 0 to 9.
    srand(time(0));  /// To change the values for each run.
    int j = 0;
    for (int i = n - 1; i > 0; i--) /// is must to start from big values to smallest.
    {
        j = rand() % (i);   /// i generation values from 0 to n-1 in each loop.

        swap(arr[i],arr[j]);/// i swap original values from array with values of j (in range of array)
    }
}




/// Karim Part
void trackQuizResult() {

    /// A temporary array that holds stat value so we can expand stat array
    int *temp = stat;
    stat = new int[capacity_2 + 1]; /// Expand by one

    /// Give the values back to stat array
    for (int i = 0; i < capacity_2; ++i) {
        stat[i] = temp[i];
    }
    capacity_2++; /// To keep track of the number of quizzes taken

    delete[] temp;



    /// If number of quizzes taken = 1 then store in index 0 the number of correct answer for quiz 1
    stat[capacity_2 - 1] = correct_Answer;

    /// Get average score
    for (int h = 0; h < capacity_2; h++) {
        sum += stat[h];
    }

    avg = sum / capacity_2;
}


void scoreStat() {
    if (capacity_2 == 0) {

        cout << "\n=================================================\n";
        cout << "= Sorry, You should at least solve 1 quiz first =\n";
        cout << "=================================================\n\n";


    } else {
        int high = stat[0]; /// Assuming high score is at the first quiz
        int low = stat[0]; /// Assuming low score is at the first quiz

        /// Making a boundary so it compares when there are two values or more
        if (capacity_2 > 1) {

            /// Get highest score
            for (int j = 1; j < capacity_2; ++j) {
                if (high < stat[j])

                    high = stat[j];

            }

            /// Get lowest score
            for (int k = 1; k < capacity_2; ++k) {
                if (low > stat[k])

                    low = stat[k];

            }
        }

        cout << "Your score statistics: " << endl;
        cout << spacing << "- Number of Quizzes taken: " << capacity_2 << endl;
        cout << spacing << "- Highest score:           " << high << endl;
        cout << spacing << "- Lowest score:            " << low << endl;
        cout << spacing << "- Average score:           " << fixed << setprecision(2) << avg << "\n\n";
    }

    goBack();
}

/// Omar Part
void allScores() {

    if (capacity_2 == 0) {

        cout << "\n=================================================\n";
        cout << "= Sorry, You should at least solve 1 quiz first =\n";
        cout << "=================================================\n\n";


    } else {
        cout << "Total number of quizzes: " << capacity_2 << "\n\n\n";
        for (int i = 0; i < capacity_2; i++) {
            cout << "Quiz " << i+1 << ": " << endl;
            cout << "-------" << endl;
            cout << "Score:           " << stat[i] << "/" << QuesTakenPerQuiz << endl;
            cout << "Correct answers: " << stat[i] << endl;
            cout << "Wrong answers:   " << 5 - stat[i] << endl;
            cout << "\n------------------------------------------------------------------\n" << endl;
        }
    }

    goBack();
}


void goBack() {

    cout << "Press [b] if you want to go back to the main menu or [e] to exit" << endl;
    myChoice = choice();

    if      (myChoice == "b") mainMenu();
    else if (myChoice == "e") exit(0);
    else    goBack();

}
