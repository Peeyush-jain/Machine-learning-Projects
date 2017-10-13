#include <bits/stdc++.h>

using namespace std;

void readInputFromFile(vector <string> &input ,vector <pair <double , int> > &word  ,string fname , int op){

const char *cstr = fname.c_str();

    ifstream inFile(cstr) ;


    if(inFile.is_open()){
        string line ;
        int index = 0 ;

        while (getline(inFile ,line)){
            if (op == 0){
                input.push_back(line);

            }


            else if (op == 1){
               // word.push_back(make_pair(0.1,line));
                //cout << word[0].second << endl ;
            }
            else if (op == 2) {
                double temp = atof(line.c_str());
                //cout << temp << endl ;
                word.push_back(make_pair(temp,index));
                index++ ;

            }

        }
    }

}

void writeInFile(string fname , vector <string> data){
        const char *wstr = fname.c_str();

        ofstream out(wstr);
        for (int i = 0 ; i < data.size() ; i++){
            string in = data[i] ;
            out << in << "\n" ;
        }

}


void TakeRandomreviews(vector <string> input , vector <string> &pos , vector <string> &neg ){

    int s1 = 0 , s2 = 0 ;
    int k = 0 ;

    while (s1 < 500 && s2 < 500){
        string review = input[k] ;

        if (review[1] != ' '){
            pos[s1] = review ;
            s1 ++ ;
        }
        else {
            if (review[0] - '6' > 0 ){
                pos[s1] = review ;
                s1 ++ ;
            }
            else {
                neg[s2] = review ;
                s2 ++ ;
            }

        }
        k++ ;
    }

    while (s1 < 500){
         string review = input[k] ;
        if (review[1] != ' '){
            pos[s1] = review ;
            s1 ++ ;
        }
        else {
            if (review[0] - '6' > 0 ){
                pos[s1] = review ;
                s1 ++ ;
            }
        }
        k++ ;

    }

      while (s2 < 500){
         string review = input[k] ;
        if (review[1] != ' '){

        }
        else {
            if (review[0] - '6' > 0 ){

            }
            else {
                neg[s2] = review ;
                s2 ++ ;
            }

        }
        k++ ;

    }



}
int myrandom(int j){
    return rand()%j ;
}

int main()
{
    srand(time(NULL));
    vector<string> input ;
    vector <string> testinput ;
    vector <string> validationSet ;
    vector <pair <double , int> > word(89527) ;

    readInputFromFile(input , word ,"labeledBow.feat" , 0);
    readInputFromFile(testinput , word , "test.feat" , 0);
    readInputFromFile(validationSet , word , "labeledBow.feat" , 0);

    random_shuffle(validationSet.begin() , validationSet.end() ,myrandom);
    random_shuffle(testinput.begin() , testinput.end(),myrandom);
    random_shuffle(input.begin() , input.end(),myrandom);

    vector<string> testpos(500);
    vector <string> testneg(500);

    vector<string> pos(500) ;
    vector<string> neg(500) ;

    vector <string> validationPos(500);
    vector <string> validationNeg(500);


    TakeRandomreviews(validationSet , validationPos , validationNeg);
    TakeRandomreviews(testinput , testpos , testneg);
    TakeRandomreviews(input , pos , neg);

    writeInFile("trainingPositive.txt" ,pos);
    writeInFile("trainingNegative.txt" ,neg);

    writeInFile("testPositive.txt" ,testpos);
    writeInFile("testNegative.txt" ,testneg);

    writeInFile("validationPositive.txt" ,validationPos);
    writeInFile("validationNegative.txt" ,validationNeg);

    return 0;
}
