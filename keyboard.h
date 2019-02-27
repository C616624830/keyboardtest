//
//  keyboard.h
//  Keyboard_layout_algo
//
//  Created by LeOOON on 2/13/19.
//  Copyright © 2019 LeOOON. All rights reserved.
//
#include <iostream>
#include <string>
#include <fstream> // contains file stream processing types
#include <cstdlib> // exit function prototype
using namespace std;
#ifndef keyboard_h
#define keyboard_h
class keyboard{
public:
    class key_pos{
    public:
        key_pos(int Row=0,int Col=0){
            row=Row;
            col=Col;
        }
        int row;
        int col;
        void set_pos(int Row,int Col){
            row = Row;
            col = Col;
        }
    };
    
    keyboard(string row1="qwertyuiop",string row2=" asdfghjkl",string row3="  zxcvbnm "){
            layout[0]=row1;
            layout[1]=row2;
            layout[2]=row3;
    }
    
    
    int transition_layouts(keyboard final_layout,int num,int option, string order){
        int k = 1;
        if (option==1){
            for(int i=0; i<3;i++){
                for (int j=0; j<10; j++){
                    if (this->layout[i][j] != final_layout.layout[i][j]){
                        int counter = 0;
                        char char1 = layout[i][j];
                        char char2 = final_layout.layout[i][j];
                        key_pos ref1{i,j};
                        cout<<"keyboard_layout_set_"+to_string(k)+": \n";
                        replacement(num,counter,char1,char2,ref1,final_layout);
                        file_create(k);
                        k++;
                        print_layout();
                    }
                }
            }
        }
        else if (option==2){
            most_frequent_keys(final_layout,num);
        }
        else if (option==3){
            vowel_consonant(final_layout,num);
        }
        else {
            return combination_order(final_layout,num,order);
        }
        return k-1;
    }
    
    void vowel_consonant(keyboard final_layout,int num);
    void most_frequent_keys(keyboard final_layout,int num);
    void find_mismatch2(keyboard final_layout,int num);
    void find_mismatch3(keyboard final_layout,int num);
    void replacement2(int num,int counter,char char1,char char2,key_pos ref1,keyboard final_layout);
    void replacement3(int num,int counter,char char1,char char2,key_pos ref1,keyboard final_layout);
    
    int combination_order(keyboard final_layout,int num, string order);
    void find_mismatch4(keyboard final_layout,int num, string order);
    void replacement4(int num,int counter,char char1,char char2,key_pos ref1,keyboard final_layout,string order);
    
    void find_mismatch(keyboard final_layout,int num){
        for(int i=0; i<3;i++){
            for (int j=0; j<10; j++){
                if (this->layout[i][j] != final_layout.layout[i][j]){
                    int counter = 0;
                    char char1 = layout[i][j];
                    char char2 = final_layout.layout[i][j];
                    key_pos ref1{i,j};
                    replacement(num,counter,char1,char2,ref1,final_layout);
                    return;
                }
            }
        }
    }
    
    void replacement(int num,int counter,char char1,char char2,key_pos ref1,keyboard final_layout){
        char *array_char = new char[num];
        array_char[0]=char1;
        array_char[1]=char2;
        key_pos *array_pos = new key_pos[num+1];
        array_pos[0]=ref1;
        for (int i=0;i<num-1;i++){
            findpos(array_pos[i+1],array_char[i+1]);
            array_char[i+2]=final_layout.layout[array_pos[i+1].row][array_pos[i+1].col];
            counter++;//number of key replaced in one part = number of ref_pos found in this loop + 1
            if (array_char[i+2]==char1){
                break;
            }
        }
        
        cout << layout[array_pos[1].row][array_pos[1].col] << "-->"<< layout[array_pos[0].row][array_pos[0].col] << " ";
        
        cout << layout[array_pos[0].row][array_pos[0].col] << "-->"<< layout[array_pos[counter].row][array_pos[counter].col] << " ";
        
        for (int i=counter;i>0;i--){
            if ((i-1)>0){
                cout<<layout[array_pos[counter].row][array_pos[counter].col]<<"-->"<<layout[array_pos[i-1].row][array_pos[i-1].col]<<" ";
            }
            swap(array_pos[counter],array_pos[i-1]);
        }
        cout << endl;
        int num2 = num-counter-1;
        if (num2>1){
            find_mismatch(final_layout,num2);
        }
        delete[] array_char;
        delete[] array_pos;
    }
    
    
    void swap(key_pos pos1,key_pos pos2){
        char temp_char = layout[pos1.row][pos1.col];
        layout[pos1.row][pos1.col]=layout[pos2.row][pos2.col];
        layout[pos2.row][pos2.col]=temp_char;
    }
    
    
    void findpos(key_pos &pos,char ref_char){
        for (int i=0;i<3;i++){
            for (int j=0;j<10;j++){
                if (layout[i][j]==ref_char){
                    pos.row=i;
                    pos.col=j;
                    return;
                }
            }
        }
    }
    
    void findpos_final(key_pos &pos,keyboard final_layout,char ref_char){
        for (int i=0;i<3;i++){
            for (int j=0;j<10;j++){
                if (final_layout.layout[i][j]==ref_char){
                    pos.row=i;
                    pos.col=j;
                    return;
                }
            }
        }
    }
    
    void print_layout(){
        cout<<endl;
        for (int i=0;i<3;i++){
            for (int j=0;j<10;j++){
                cout<<layout[i][j]<<' ';
            }
            cout << endl;
        }
        cout << endl;
    }
    
    void file_create(int k){
        
        //On windows a path needs to be like this, "\\" is needed instead of one "\"
        // Note to change the "\" before "res" to "\\"
        ofstream outFile1,outFile2,outFile3,outFile4,outFile5,outFile6;
        //Windows directory of LatinIMEv2
        //string path="C:\\LatinIMEv2\\keyboard\\src\\main\\res\\xml\\";
        
        //Mac directory:
        string path="/Users/lieyangchen/Desktop/xmls/";
        
        //Windows directory:
        //string path="C:\\Users\\LeOOnN\\Desktop\\New folder\\";
        // keyboard_layout_set_#
        outFile1.open(path+"keyboard_layout_set_"+to_string(k)+".xml");
        outFile1<<"<?xml version=\"1.0\" encoding=\"utf-8\"?>"<<endl;
        outFile1<<"<KeyboardLayoutSet"<<endl;
        outFile1<<"    xmlns:latin=\"http://schemas.android.com/apk/res-auto\">"<<endl;
        outFile1<< "    <Element\n        latin:elementName=\"alphabet\"\n        latin:elementKeyboard=\"@xml/kbd_"+to_string(k)+"\"\n        latin:enableProximityCharsCorrection=\"true\" />"<<endl;
        outFile1<< "    <Element\n        latin:elementName=\"symbols\"\n        latin:elementKeyboard=\"@xml/kbd_symbols\" />"<<endl;
        outFile1<< "    <Element\n        latin:elementName=\"symbolsShifted\"\n        latin:elementKeyboard=\"@xml/kbd_symbols_shift\" />"<<endl;
        outFile1<< "    <Element\n        latin:elementName=\"phone\"\n        latin:elementKeyboard=\"@xml/kbd_phone\" />"<<endl;
        outFile1<< "    <Element\n        latin:elementName=\"phoneSymbols\"\n        latin:elementKeyboard=\"@xml/kbd_phone_symbols\" />"<<endl;
        outFile1<< "    <Element\n        latin:elementName=\"number\"\n        latin:elementKeyboard=\"@xml/kbd_number\" />\n</KeyboardLayoutSet>"<<endl;
        outFile1.close();
        
        //kbd_#
        outFile2.open(path+"kbd_"+to_string(k)+".xml");
        outFile2<<"<?xml version=\"1.0\" encoding=\"utf-8\"?>"<<endl;
        outFile2<<"<Keyboard\n    xmlns:latin=\"http://schemas.android.com/apk/res-auto\"\n>\n    <include\n        latin:keyboardLayout=\"@xml/rows_"+to_string(k)+"\" />\n</Keyboard>"<<endl;
        outFile2.close();
        
        //rows_#
        outFile3.open(path+"rows_"+to_string(k)+".xml");
        outFile3<<"<?xml version=\"1.0\" encoding=\"utf-8\"?>"<<endl;
        outFile3<<"<merge"<<endl;
        outFile3<<"    xmlns:latin=\"http://schemas.android.com/apk/res-auto\""<<endl;
        outFile3<<">"<<endl;
        outFile3<<"    <include"<<endl;
        outFile3<<"        latin:keyboardLayout=\"@xml/key_styles_common\" />"<<endl;
        outFile3<<"    <Row"<<endl;
        outFile3<<"        latin:keyWidth=\"10%p\""<<endl;
        outFile3<<"    >"<<endl;
        outFile3<<"        <include"<<endl;
        outFile3<<"            latin:keyboardLayout=\"@xml/rowkeys_"+to_string(k)+"_row1\" />"<<endl;
        outFile3<<"    </Row>"<<endl;
        outFile3<<"    <Row"<<endl;
        outFile3<<"        latin:keyWidth=\"10%p\""<<endl;
        outFile3<<"    >"<<endl;
        outFile3<<"        <include"<<endl;
        outFile3<<"            latin:keyboardLayout=\"@xml/rowkeys_"+to_string(k)+"_row2\""<<endl;
        outFile3<<"            latin:keyXPos=\"5%p\" />"<<endl;
        outFile3<<"    </Row>"<<endl;
        outFile3<<"    <Row"<<endl;
        outFile3<<"        latin:keyWidth=\"10%p\""<<endl;
        outFile3<<"    >"<<endl;
        outFile3<<"        <Key"<<endl;
        outFile3<<"            latin:keyStyle=\"shiftKeyStyle\""<<endl;
        outFile3<<"            latin:keyWidth=\"15%p\""<<endl;
        outFile3<<"            latin:visualInsetsRight=\"1%p\" />"<<endl;
        outFile3<<"        <include"<<endl;
        outFile3<<"            latin:keyboardLayout=\"@xml/rowkeys_"+to_string(k)+"_row3\" />"<<endl;
        outFile3<<"        <Key"<<endl;
        outFile3<<"            latin:keyStyle=\"deleteKeyStyle\""<<endl;
        outFile3<<"            latin:keyWidth=\"fillRight\""<<endl;
        outFile3<<"            latin:visualInsetsLeft=\"1%p\" />"<<endl;
        outFile3<<"    </Row>"<<endl;
        outFile3<<"   <include"<<endl;
        outFile3<<"        latin:keyboardLayout=\"@xml/row_qwerty4\" />"<<endl;
        outFile3<<"</merge>"<<endl;
        outFile3.close();
        
        //rowkeys_#_row1
        {outFile4.open(path+"rowkeys_"+to_string(k)+"_row1.xml");
            outFile4<<"<?xml version=\"1.0\" encoding=\"utf-8\"?>"<<endl;
            outFile4<<"<merge"<<endl;
            outFile4<<"    xmlns:latin=\"http://schemas.android.com/apk/res-auto\""<<endl;
            outFile4<<">"<<endl;
            for (int i=0;i<9;i++){
                string key2(1,layout[0][i]);
                outFile4<<"    <Key"<<endl;
                outFile4<<"        latin:keySpec=\""+key2+"\""<<endl;
                outFile4<<"        latin:keyHintLabel=\""+to_string(i+1)+"\""<<endl;
                outFile4<<"        latin:additionalMoreKeys=\""+to_string(i+1)+"\"/>"<<endl;
            }
            string key3(1,layout[0][9]);
            outFile4<<"    <Key"<<endl;
            outFile4<<"        latin:keySpec=\""+key3+"\""<<endl;
            outFile4<<"        latin:keyHintLabel=\""+to_string(0)+"\""<<endl;
            outFile4<<"        latin:additionalMoreKeys=\""+to_string(0)+"\"/>"<<endl;
            outFile4<<"</merge>"<<endl;
            outFile4.close();}
        
        
        
        //rowkeys_#_row2
        {outFile5.open(path+"rowkeys_"+to_string(k)+"_row2.xml");
            outFile5<<"<?xml version=\"1.0\" encoding=\"utf-8\"?>"<<endl;
            outFile5<<"<merge"<<endl;
            outFile5<<"    xmlns:latin=\"http://schemas.android.com/apk/res-auto\""<<endl;
            outFile5<<">"<<endl;
            for (int i=1;i<10;i++){
                string key2(1,layout[1][i]);
                outFile5<<"    <Key"<<endl;
                outFile5<<"        latin:keySpec=\""+key2+"\"/>"<<endl;
            }
            outFile5<<"</merge>"<<endl;
            outFile5.close();}
        
        
        //rowkeys_#_row3
        {outFile6.open(path+"rowkeys_"+to_string(k)+"_row3.xml");
            outFile6<<"<?xml version=\"1.0\" encoding=\"utf-8\"?>"<<endl;
            outFile6<<"<merge"<<endl;
            outFile6<<"    xmlns:latin=\"http://schemas.android.com/apk/res-auto\""<<endl;
            outFile6<<">"<<endl;
            for (int i=2;i<9;i++){
                string key3(1,layout[2][i]);
                outFile6<<"    <Key"<<endl;
                outFile6<<"        latin:keySpec=\""+key3+"\"/>"<<endl;
            }
            outFile6<<"</merge>"<<endl;
            outFile6.close();}
    }
    
    string layout[3] = {"qwertyuiop"," asdfghjkl","  zxcvbnm "};
};

#endif /* keyboard_h */




