//********************************************************************
//
// Michael Boling
// Operating Systems
// Programming Project #6: Simulation of Page Replacement Strategies
// April 9, 2023
// Instructor: Dr. Siming Liu
//
//********************************************************************

// I will make each of my .txt files to have the page reference string to be of length 20

//" it is suggested that you have several program data files that you can re-direct standard input
// and thus have your program read." ... hence, :
// 1.) I have "Program Data Files" of Names: testcase1.txt, testcase2.txt, testcase3.txt, testcase4.txt, testcase5.txt
// and testcase6.txt
// 2.) testcase1.txt outputs FIFO and LRU algorithm results. testcase2.txt outputs OPT and RAND results.
// testcase3.txt outputs FIFO and OPT results. testcase4.txt outputs FIFO and RAND results. testcase5.txt
// outputs LRU and RAND results. testcase6.txt outputs LRU and OPT results
// 3.) The program MUST take an input value of the name of the .txt file that were mentioned above
// 4.) As shown from the "Example Input:" the .txt files MUST follow that formatting w/ a reference string of length 20
// 5.) The page reference string may be changed (as long as still of size 20) and the # of frames may be changed
// for any of the .txt files. **please note: the .txt files should only be implemented and specified to the
// names which it was given to on 2.)
//=====================================================================================================================

#include <iostream>
#include <stdio.h>
#include <fstream> //to read from .txt file
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
#include <time.h>

using namespace std;

// Global Variables and Array(s):
char nm_1[5];
char nm_2[5];
char nm_3[5];
char nm_4[5];
int read_ref_value[20] = {0};
int read_ref = 0;
int num_frames = 0;

char test1[] = "testcase1.txt";
char test2[] = "testcase2.txt";
char test3[] = "testcase3.txt";
char test4[] = "testcase4.txt";
char test5[] = "testcase5.txt";
char test6[] = "testcase6.txt";
char cml_string[20];

// functions:

void print_1();
void print_2();
void print_3();
void print_4();
void print_pageref();
void FIFO();
void LRU();
void RAND();
void OPT();

//============
int maxprint_1 = 0;
int maxprint_2 = 0;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int fault_1 = 0;

    // no "user prompts", so will be using .txt files for test cases as shown in the
    //  "Project Specifications"

    string txt_file = argv[1];
    txt_file = txt_file.c_str();

    if (argc != 2)
    {
        cout << "Please enter the .txt file as a command line argument.\n"
             << endl;
    }
    ifstream Read_File;
    Read_File.open(txt_file);

    strcpy(cml_string, argv[1]);

    if ((strcmp(cml_string, test1)) == 0)
    {
        while (read_ref < 20)
        {
            Read_File >> read_ref_value[read_ref++];
        }
        Read_File >> num_frames;
        // 4 because thats the # of letters in FIFO
        for (int i = 0; i < 4; i++)
        {
            Read_File >> nm_1[i];
        }
        // 3 because thats the # of letters in LRU
        for (int i = 0; i < 3; i++)
        {
            Read_File >> nm_2[i];
        }
        maxprint_1 = 4;
        maxprint_2 = 3;
    }
    else if ((strcmp(cml_string, test2)) == 0)
    {
        while (read_ref < 20)
        {
            Read_File >> read_ref_value[read_ref++];
        }
        Read_File >> num_frames;
        // 3 because thats the # of letters in OPT
        for (int i = 0; i < 3; i++)
        {
            Read_File >> nm_1[i];
        }
        // 4 because thats the # of letters in RAND
        for (int i = 0; i < 4; i++)
        {
            Read_File >> nm_2[i];
        }
        maxprint_1 = 3;
        maxprint_2 = 4;
    }
    else if ((strcmp(cml_string, test3)) == 0)
    {
        while (read_ref < 20)
        {
            Read_File >> read_ref_value[read_ref++];
        }
        Read_File >> num_frames;
        // 3 because thats the # of letters in FIFO
        for (int i = 0; i < 4; i++)
        {
            Read_File >> nm_1[i];
        }
        // 4 because thats the # of letters in OPT
        for (int i = 0; i < 3; i++)
        {
            Read_File >> nm_3[i];
        }
        maxprint_1 = 4;
        maxprint_2 = 3;
    }
    else if ((strcmp(cml_string, test4)) == 0)
    {
        while (read_ref < 20)
        {
            Read_File >> read_ref_value[read_ref++];
        }
        Read_File >> num_frames;
        // 3 because thats the # of letters in FIFO
        for (int i = 0; i < 4; i++)
        {
            Read_File >> nm_1[i];
        }
        // 4 because thats the # of letters in RAND
        for (int i = 0; i < 4; i++)
        {
            Read_File >> nm_2[i];
        }
        maxprint_1 = 4;
        maxprint_2 = 4;
    }
    else if ((strcmp(cml_string, test5)) == 0)
    {
        while (read_ref < 20)
        {
            Read_File >> read_ref_value[read_ref++];
        }
        Read_File >> num_frames;
        // 3 because thats the # of letters in LRU
        for (int i = 0; i < 3; i++)
        {
            Read_File >> nm_4[i];
        }
        // 4 because thats the # of letters in RAND
        for (int i = 0; i < 4; i++)
        {
            Read_File >> nm_2[i];
        }
        maxprint_1 = 3;
        maxprint_2 = 4;
    }
    else
    {
        while (read_ref < 20)
        {
            Read_File >> read_ref_value[read_ref++];
        }
        Read_File >> num_frames;
        // 3 because thats the # of letters in LRU
        for (int i = 0; i < 3; i++)
        {
            Read_File >> nm_1[i];
        }
        // 4 because thats the # of letters in OPT
        for (int i = 0; i < 3; i++)
        {
            Read_File >> nm_2[i];
        }
        maxprint_1 = 3;
        maxprint_2 = 3;
    }

    print_pageref();
    cout << "Number of Frames: " << num_frames << endl;

    if ((strcmp(cml_string, test1)) == 0)
    {

        FIFO();
        LRU();
    }
    else if ((strcmp(cml_string, test2)) == 0)
    {

        OPT();
        RAND();
    }
    else if ((strcmp(cml_string, test3)) == 0)
    {

        FIFO();
        OPT();
    }
    else if ((strcmp(cml_string, test4)) == 0)
    {

        FIFO();
        RAND();
    }
    else if ((strcmp(cml_string, test5)) == 0)
    {

        LRU();
        RAND();
    }
    else
    {
        LRU();
        OPT();
    }
    return 0;
}

//********************************************************************
//
// FIFO Function
//
// This function determines the number of page faults using a
// first-in-first-out approach. That is, for a given array of frames..it determines if a
// "page" is in your physical memory...if the page is in your physical memory then it does
// not increment the page fault and if it isnt in your physical memory then it increments # of page faults.
// At the end of the function, it prints out the algorithm name and the # of page faults that incurred.
//
// Return Value
// ------------
// void                         n/a
//
// Value Parameters
// ----------------
// n/a
//
// Reference Parameters
// --------------------
// n/a
//
// Local Variable Data Dictionary:
//
// fault = # of page faults, flag = determine if frame_arr[] and read_ref_value[] have similair/different
// values, frame_arr[] = to compare values against read_ref_value[], counter = to determine which value of
// frame_arr[] to swap out with "page fault victim" , i = read_ref_value iterator.
//*******************************************************************

void FIFO()
{
    int fault = 0;
    bool flag = false;
    int frame_arr[num_frames];
    fill_n(frame_arr, num_frames, -1);
    int counter = 0;
    int i = 0;

    // main loop run # of length of read_ref_value
    for (i = 0; i < 20; i++)
    {
        // setting flag to false indicating frame_arr[j] and read_ref_value[i] are not same
        flag = false;
        for (int j = 0; j < num_frames; j++)
        {
            // if we do indeed find the same value per correct iteration
            if (frame_arr[j] == read_ref_value[i])
            {
                // No need to continue since we dont have page fault
                flag = true;
                break;
            }
        }
        // test if we should increment counter and fault depending if there was a page fault or not
        if (flag == false)
        {
            // swapping out page fault "victim"
            frame_arr[counter] = read_ref_value[i];
            fault = fault + 1;
            counter = counter + 1;
            // reset counter
            if (counter >= num_frames)
            {
                // reset
                counter = 0;
            }
        }
    }

    print_1();
    cout << fault << endl;
}
//********************************************************************
//
// OPT Function
//
// This function replaces the page what will NOT be used (in the future) for the longest period of time.
// At the end of the function, it prints out the algorithm name and the # of page faults that incurred.
//
// Return Value
// ------------
// void                         n/a
//
// Value Parameters
// ----------------
// n/a
//
// Reference Parameters
// --------------------
// n/a
//
// Local Variable Data Dictionary:
//
// Unfortunately, I could not figure out a solution to this algorithm. So, I have just implemented LRU in its
// place so I could have the print statement/formatting in the right ordering.
// But this is not the correct solution unfortunately.
//*******************************************************************
void OPT()
{
    int fault = 0;
    int frame_arr[num_frames];
    fill_n(frame_arr, num_frames, -1);
    int counter[num_frames] = {0};

    int imp = 0;
    for (int i = 0; i < 20; i++)
    {

        int j = 0;
        // setting flag to false indicating frame_arr[j] and read_ref_value[i] are not same
        bool flag = false;
        for (int z = 0; z < num_frames; z++)
        {
            // if we do indeed find the same value per correct iteration
            if (frame_arr[j] == read_ref_value[imp])
            {
                flag = true;
                counter[j] = (imp + 1);
            }
            j++;
        }

        // test if we should increment counter and fault depending if there was a page fault or not
        if (flag == false)
        {
            int least_rec_used = 0;
            int L_2 = 0;
            while ((num_frames - 1) > L_2)
            {
                if (counter[L_2 + 1] < counter[least_rec_used])
                {
                    least_rec_used = (L_2 + 1);
                }
                L_2 = (L_2 + 1);
            }
            // swap out value
            frame_arr[least_rec_used] = read_ref_value[imp];
            counter[least_rec_used] = (imp + 1);
            fault++;
        }
        imp++;
    }
    if ((strcmp(cml_string, test3)) == 0)
    {

        print_3();
        cout << fault << endl;
    }
    else
    {
        print_1();
        cout << fault << endl;
    }
}

//********************************************************************
//
// LRU Function
//
// This function swaps out the value of the frame_arr[] for the appropriate iteration/value
// of the reference string array depending on the "counter" that was the most least recently used.
// At the end of the function, it prints out the algorithm name and the # of page faults that incurred.
//
// Return Value
// ------------
// void                         n/a
//
// Value Parameters
// ----------------
// n/a
//
// Reference Parameters
// --------------------
// n/a
//
// Local Variable Data Dictionary:
// fault = # of faults, frame_arr[] = to compare against reference string array, counter[] = array to
// monitor when last page used, imp = to keep track of iterations among for loops, j = iterator for inner loop
// least_rec_used= to keep track of lowest count value, L_2 = dummy variable to summplement and help find lowest count value
//
//*******************************************************************
void LRU()
{

    int fault = 0;
    int frame_arr[num_frames];
    fill_n(frame_arr, num_frames, -1);
    int counter[num_frames] = {0};

    int imp = 0;
    for (int i = 0; i < 20; i++)
    {

        int j = 0;
        // setting flag to false indicating frame_arr[j] and read_ref_value[i] are not same
        bool flag = false;
        for (int z = 0; z < num_frames; z++)
        {
            // if we do indeed find the same value per correct iteration
            if (frame_arr[j] == read_ref_value[imp])
            {
                flag = true;
                counter[j] = (imp + 1);
            }
            j++;
        }

        // test if we should increment counter and fault depending if there was a page fault or not
        if (flag == false)
        {
            int least_rec_used = 0;
            int L_2 = 0;
            while ((num_frames - 1) > L_2)
            {
                if (counter[L_2 + 1] < counter[least_rec_used])
                {
                    least_rec_used = (L_2 + 1);
                }
                L_2 = (L_2 + 1);
            }
            // swap out value
            frame_arr[least_rec_used] = read_ref_value[imp];
            counter[least_rec_used] = (imp + 1);
            fault++;
        }
        imp++;
    }

    if ((strcmp(cml_string, test5)) == 0)
    {

        print_4();
        cout << fault << endl;
    }
    else
    {
        print_2();
        cout << fault << endl;
    }
}

//********************************************************************
//
// RAND Function
//
// This function makes each page in the main memory to have an equal likelihood of being selected
// for replacement.
// At the end of the function, it prints out the algorithm name and the # of page faults that incurred.
//
// Return Value
// ------------
// void                         n/a
//
// Value Parameters
// ----------------
// n/a
//
// Reference Parameters
// --------------------
// n/a
//
// Local Variable Data Dictionary:
// fault = # of page faults, flag = to check if frame_arr[] and string array are same,
// frame_arr[] = to compare against string arr, counter = keep track of frame_arr[] value to swap out,
// i = iterator for string arr, random num = to generate random # for page replacement
//
//*******************************************************************
void RAND()
{
    int fault = 0;
    bool flag = false;
    int frame_arr[num_frames];
    fill_n(frame_arr, num_frames, -1);
    int counter = 0;
    int i = 0;
    int random_num = 0;

    // main loop run # of length of read_ref_value
    for (i = 0; i < 20; i++)
    {
        // setting flag to false indicating frame_arr[j] and read_ref_value[i] are not same
        flag = false;
        for (int j = 0; j < num_frames; j++)
        {
            // if we do indeed find the same value per correct iteration
            if (frame_arr[j] == read_ref_value[i])
            {
                // No need to continue since we dont have page fault
                flag = true;
                break;
            }
        }
        // testing if we should replace random page in memory
        if (flag == false)
        {
            // generate random num
            random_num = rand() % num_frames;
            // assign it to counter
            counter = random_num;

            // swapping out page fault "victim" based on random page that our counter represents
            frame_arr[counter] = read_ref_value[i];

            fault++;

            // reset counter, just to be sure of no error.. shouldnt matter however since we will generate random num
            if (counter >= num_frames)
            {
                counter = 0;
            }
        }
    }

    print_2();
    cout << fault << endl;
}
//********************************************************************
//
// print_1 Function
//
// This function prints out the name of the replacement algorithm as chosen accordingly from the command line.
// maxprint_1 will take on different values depending on which .txt file was inputted on the command line.
//
// Return Value
// ------------
// void                         n/a
//
// Value Parameters
// ----------------
// n/a
//
// Reference Parameters
// --------------------
// n/a
//
// Local Variable Data Dictionary:
// n/a
//
//*******************************************************************

void print_1()
{
    for (int i = 0; i < maxprint_1; i++)
    {
        cout << nm_1[i];
    }
    cout << ": ";
}

//********************************************************************
//
// print_2 Function
//
// This function prints out the name of the replacement algorithm as chosen accordingly from the command line.
// maxprint_2 will take on different values depending on which .txt file was inputted on the command line.
//
// Return Value
// ------------
// void                         n/a
//
// Value Parameters
// ----------------
// n/a
//
// Reference Parameters
// --------------------
// n/a
//
// Local Variable Data Dictionary:
// n/a
//
//*******************************************************************

void print_2()
{
    for (int i = 0; i < maxprint_2; i++)
    {
        cout << nm_2[i];
    }
    cout << ": ";
}
//********************************************************************
//
// print_3 Function
//
// This function prints out the name of the replacement algorithm as chosen accordingly from the command line.
// maxprint_2 will take on different values depending on which .txt file was inputted on the command line.
//
// Return Value
// ------------
// void                         n/a
//
// Value Parameters
// ----------------
// n/a
//
// Reference Parameters
// --------------------
// n/a
//
// Local Variable Data Dictionary:
// n/a
//
//*******************************************************************
void print_3()
{
    for (int i = 0; i < maxprint_2; i++)
    {
        cout << nm_3[i];
    }
    cout << ": ";
}

//********************************************************************
//
// print_4 Function
//
// This function prints out the name of the replacement algorithm as chosen accordingly from the command line.
// maxprint_2 will take on different values depending on which .txt file was inputted on the command line.
//
// Return Value
// ------------
// void                         n/a
//
// Value Parameters
// ----------------
// n/a
//
// Reference Parameters
// --------------------
// n/a
//
// Local Variable Data Dictionary:
// n/a
//
//*******************************************************************
void print_4()
{
    for (int i = 0; i < maxprint_2; i++)
    {
        cout << nm_4[i];
    }
    cout << ": ";
}

//********************************************************************
//
// print_pageref Function
//
// This function prints out the page reference string as was inputted from the .txt file
// that was inputted on the command line.
//
// Return Value
// ------------
// void                         n/a
//
// Value Parameters
// ----------------
// n/a
//
// Reference Parameters
// --------------------
// n/a
//
// Local Variable Data Dictionary:
// n/a
//
//*******************************************************************
void print_pageref()
{
    cout << "Page Reference String:" << endl;
    for (int i = 0; i < read_ref; i++)
    {
        cout << read_ref_value[i] << " ";
    }
    cout << "\n";
}
