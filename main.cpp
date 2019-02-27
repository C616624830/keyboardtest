//
//  main.cpp
//  Keyboard_Algo2
//
//  Created by LeOOON on 2/16/19.
//  Copyright © 2019 LeOOON. All rights reserved.
//
//Those  "latin:moreKeys="!text/morekeys_w"" in xml files may disrupt the output of the keyboard layout, so just delete them all.
//To open a new blank file, have to use the "g++ -o cpp.exe main.cpp" first.
//Make sure your path is correct
/*APK installation error: may occur
 after you move the current path of your
 project. Can be resolved by  Build---> Clean and Build--> Build APK*/
//if the replacement displayed improperly, make sure your input layout is correct
#include <iostream>
#include "keyboard.h"
#include <string>
#include <vector>
using namespace std;
void kbd_combination(int num, int rowsize, string& temp_string, int counter[], string array[], string& order, class keyboard layout, class keyboard final_layout);
void kbd_combination2(int num, int rowsize, string& temp_string, int counter[], string array[],vector<string>& order_vector,int k, class keyboard layout, class keyboard final_layout);
void set_content(int row, int num, string& temp_array,string array[]);
bool is_there(char cha,string row_string);

int main(int argc, const char * argv[]) {
    class keyboard layout;
    cout << "Enter the first row: ";
    string row1;
    cin>>row1;
    cout << "Enter second row: ";
    string row2_1=" ";
    string row2_2;
    cin>>row2_2;
    string row2=row2_1+row2_2;
    cout << "Enter third row: ";
    string row3_1="  ";
    string row3_2;
    string row3_3=" ";
    cin>>row3_2;
    string row3=row3_1+row3_2+row3_3;
    //Input testing from line 57 - line 89
    if (row1.length()!=10){
        cout << "Row1 Wrong Length!" <<endl;
        return 0;
    }
    if (row2.length()!=10){
        cout << "Row2 Wrong Length!" <<endl;
        return 0;
    }
    if(row3.length()!=10){
        cout << "Row3 Wrong Length!" <<endl;
        return 0;
    }

    char array[26];
    for (int i=0;i<10;i++){
        array[i]=row1[i];
    }
    for (int i=1;i<10;i++){
        array[i+9]=row2[i];
    }
    for (int i=2;i<9;i++){
        array[i+17]=row3[i];
    }

    for (int i=0;i<26;i++){
        for (int j=25;j>i;j--){
            if (array[i]==array[j]){
                cout << "Key Repitition, Wrong Input!" <<endl;
                return 0;
            }
        }
    }
    
    class keyboard final_layout("qwdrtuylkp"," zasehniom","  xfcvgbj ");//row1, row2, row3
    cout << "Enter max number of keys swapped in one replacement: ";
    int num;
    cin>>num;
    cout << "\nOption menu:\n1. Normal transition.\n2. Most frequent keys prioritization.\n3. Vowel + most frequent consonants prioritization.\n4. Combination order.\nEnter your option of order replacement: ";
    int option;
    cin>>option;
    cout << "\n\n\nOriginal Keyboard layout: ";
    layout.print_layout();
    cout << "\nReplacement start: \n\n";
    string order="abcdefghijklmnopqrstuvwxyz";
    layout.transition_layouts(final_layout, 3, 4, order);//num - 3, 4 - option
    
//    //start to get the optimized order from here
//    class keyboard layout;
//    class keyboard final_layout("qwdrtuylkp"," zasehniom","  xfcvgbj ");
//    string order;
//    int num=26;
//    string arrayofString[27];
//    for(int i=0;i<num+1;i++){
//        for(int j=0;j<num;j++){
//            arrayofString[i]+=' ';
//        }
//    }//create (num+1) x num 2-d array, the fifth row is used to store each combination
//    string temp_string="abcdefghijklmnopqrstuvwxyz";
//    int counter[2]={0};// use the first element to store the number of possible orders, the second element to store the minimum number of stages
//    counter[1]=27;//number of stages won't be larger than 27
//    vector<string> order_vector;
//    kbd_combination(num, num, temp_string, counter, arrayofString, order, layout, final_layout);//find minimum number of stages given by a number of key changes and the final_layout
//    cout << counter[1] << order << endl;
//    kbd_combination2(num, num, temp_string, counter, arrayofString, order_vector, counter[1], layout, final_layout);
//    // use the minimum number obtained above to find all possible orders that generate this minimum number
//    cout << counter[0]<<endl;
}



//void kbd_combination(int num, int rowsize, string& temp_string, int counter[], string array[], string& order, class keyboard layout, class keyboard final_layout){//num is the number of keys, size is the size of each row used, temp_array refers to like "abcdefghijklmnopqrstuvwxyz" which includes all the unique chars needed.
//    if (rowsize>=1){
//        set_content(num-rowsize,num,temp_string,array);//set content for the current row,current row may have different contents depending on the
//        for (int i=0;i<rowsize;i++){
//            char a=array[num-rowsize][i];//num-rowsize is the row_number
//            array[num][num-rowsize]=a;//set the num-th element of the keyboard
//            for (int j=num-rowsize+1;j<num;j++){//used to erase the unused elements in the last row of the arrayofString
//                array[num][j]=' ';
//            }
//            kbd_combination(num, rowsize-1, temp_string, counter, array, order, layout, final_layout);
//        }
//    }
//    else{
//        //cout<<array[num]<<endl;
//        int k = layout.transition_layouts(final_layout, 3, 4, array[num]);// 3 refers to number of key changes 4 refers to the option
//        if(counter[1]>k){
//            counter[1]=k;
//            order = array[num];
//        }
//        counter[0]++;//used to count then umber of keyboard layouts, should be num!
//    }
//}
//
//void set_content(int row, int num, string& temp_string,string array[]){//arraysize is the size of current row, row is the row#, num is the number of keys
//    string temp;
//    //cout << array[num] <<endl;
//    for(int i=0;i<num;i++){
//        if(!is_there(temp_string[i], array[num])){
//            temp+=temp_string[i];
//        }
//    }
//    //cout << temp <<endl;
//    for(int i=0;i<temp.length();i++){
//        array[row][i]=temp[i];
//    }
//}
//
//bool is_there(char cha,string row_string){// row_string means the string of characters of a row
//    for(int i=0;i<row_string.length();i++){
//        if(cha == row_string[i]){
//            return true;
//        }
//    }
//    return false;
//}
//
//
//void kbd_combination2(int num, int rowsize, string& temp_string, int counter[], string array[],vector<string>& order_vector,int k, class keyboard layout, class keyboard final_layout){//used to all orders that is corresponding to k and store them into vector
//
//    if (rowsize>=1){
//        set_content(num-rowsize,num,temp_string,array);//set content for the current row,current row may have different contents depending on the
//        for (int i=0;i<rowsize;i++){
//            char a=array[num-rowsize][i];//num-rowsize is the row_number
//            array[num][num-rowsize]=a;//set the num-th element of the keyboard
//            for (int j=num-rowsize+1;j<num;j++){//used to erase the unused elements in the last row of the arrayofString
//                array[num][j]=' ';
//            }
//            kbd_combination2(num, rowsize-1, temp_string, counter, array, order_vector, k, layout, final_layout);
//        }
//    }
//    else{
//        //cout<<array[num]<<endl;
//        int j = layout.transition_layouts(final_layout, 3, 4, array[num]);// 3 refers to number of key changes 4 refers to the option
//        if(j==k){
//            order_vector.push_back(array[num]);
//        }
//        counter[0]++;//used to count then umber of keyboard layouts, should be num!
//    }
//}
//
//
//
