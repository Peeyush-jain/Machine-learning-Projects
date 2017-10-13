#include <bits/stdc++.h>
using namespace std ;
#define MAXWORD 89527
#define att_size 5000
 int frequency_word[MAXWORD][2] ;
vector <pair <int , int> > attribute_count(MAXWORD) ;

class node{
    public :
        int index ;
        node *left ;
        node *right ;
        int majority ;
        node(){
            this->left = NULL ;
            this->right = NULL ;
        }
        node(int index){
            this->index = index ;
            this->left = NULL ;
            this->right = NULL ;
        }


};

int myrandom(int j){
    return rand()%j ;
}

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

void writeIntoFile(string fname , vector <pair <double , int> > word , vector <int> &attribute ){
        const char *wstr = fname.c_str();

        vector <int> choosen(att_size) ;
        int k = 0 ;
        for (int i = 0 ; i < att_size/2 ; i++){

            choosen[k] = word[i].second ;
             attribute[k]  = word[i].second ;
            k++ ;

        }
        for (int i = word.size() -1 ; i > word.size() - att_size/2 ; i--){
            choosen[k] = word[i].second ;
            attribute[k]  = word[i].second ;
            k++ ;
        }

        ofstream output_file(wstr);
        ostream_iterator<int> output_iterator(output_file, "\n");
        copy(choosen.begin(), choosen.end(), output_iterator);




}

void writeInFile(string fname , vector <string> data){
        const char *wstr = fname.c_str();

        ofstream out(wstr);
        for (int i = 0 ; i < data.size() ; i++){
            string in = data[i] ;
            out << in << "\n" ;
        }

}


void print(vector <string> word){
    for (int i = 0 ; i < word.size() ; i++){
        cout << word[i] << endl ;
    }

}

void convertReviewToList(vector<string> input , vector <list <pair <int , int> > > &output){

    for (int i = 0 ; i < 500 ; i++){
        string review = input[i] ;
        string extract = "" ;
        bool first  = true ;
        int wordIndex , wordCount ;
        for (int j = 0 ; j < review.length() ; j++){


            if (review[j] == ' '){
                if(!first){

                    stringstream convert(extract);
                    convert >> wordCount ;


                    output[i].push_back(make_pair(wordIndex , wordCount));

                }
                first = false ;
                extract = "" ;
            }

            else if (review[j] == ':'){
                stringstream convert(extract);
                convert >> wordIndex ;
                extract = "" ;

            }

            else {
                    extract = extract + review[j] ;
            }
        }

        stringstream convert(extract);
        convert >> wordCount ;

        output[i].push_back(make_pair(wordIndex , wordCount));

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

double calculateEntropy(double p_pos , double p_neg){

    if (p_pos != 0 && p_neg != 0){
        double entropy = -1*p_pos*log2(p_pos) + -1*p_neg*log2(p_neg);

        return entropy ;
    }

    return 0.0 ;
}

double informationGain(double totalEntropy , double presentEntropy , double absentEntropy , double totalDatapoints , double presentDatapoint ){

    if (totalDatapoints == 0){
        return 0 ;
    }
    return totalEntropy - ((presentDatapoint/totalDatapoints))*presentEntropy - ((totalDatapoints - presentDatapoint)/totalDatapoints)*absentEntropy  ;
}

int calculateBestAttribute( vector <int> &posList, vector <int> &negList ,list <int> &attribute, vector <list < pair<int , int > > > &storePosReview,vector <list < pair<int , int > > > &storeNegReview ){
     int pos_size = posList.size() ;
     int neg_size = negList.size() ;

     double p_size = double(pos_size);
     double n_size = double (neg_size);
     double p_root_positive = (p_size/(p_size + n_size)) ;
     double p_root_negative = (n_size/(p_size + n_size)) ;

     double totalEntropy = calculateEntropy(p_root_positive , p_root_negative);


     for (int i = 0 ; i < MAXWORD ; i++){
        frequency_word[i][0] = 0 ;
        frequency_word[i][1] = 0 ;
     }

        for (int j = 0 ; j < pos_size ; j++){
            list <pair <int , int> >::iterator it ;
            int threshold = 1 ;
            int i = posList[j] ;
            for (it = storePosReview[i].begin() ; it != storePosReview[i].end() ; it++){
                if ((*it).second >= threshold){
                    frequency_word[(*it).first][0] =  frequency_word[(*it).first][0] + 1 ;
                }
            }
        }

        for (int j = 0 ; j < neg_size ; j++){
            list <pair <int , int> >::iterator it ;
            int threshold = 1 ;
            int i = negList[j] ;
            for (it = storeNegReview[i].begin() ; it != storeNegReview[i].end() ; it++){
                if ((*it).second >= threshold){
                    frequency_word[(*it).first][1] =  frequency_word[(*it).first][1] + 1 ;
                }
            }
        }


        // all matrix has been filled now calculate information gain for each attribute ;
        list<int>::iterator itr ;
        int rootIndex = 0  ;
        double informationG = 0.0 ;

        for (itr = attribute.begin() ; itr != attribute.end() ; itr++){
            int p_present = frequency_word[*itr][0] ;
            int n_present = frequency_word[*itr][1] ;

            double positive_present = double (p_present) ;
            double negative_present = double (n_present) ;


            double entropy_present = 0.0 ;
            if (positive_present != 0 || negative_present != 0){
                double p_pos_present = (positive_present/(positive_present + negative_present)) ;
                double p_neg_present = (negative_present/(positive_present + negative_present)) ;
                entropy_present = calculateEntropy(p_pos_present , p_neg_present);

            }
            int p_absent = p_size - positive_present;
            int n_absent = n_size - negative_present ;

            double positive_absent = double (p_absent) ;
            double negative_absent = double (n_absent) ;


            double entropy_absent = 0.0 ;
            if (positive_absent != 0 || negative_absent != 0){
                double p_pos_absent = (positive_absent/(positive_absent + negative_absent)) ;
                double p_neg_absent = (negative_absent/(positive_absent + negative_absent)) ;
                entropy_absent = calculateEntropy(p_pos_absent , p_neg_absent);
            }
            double totalDatapoints = p_size + n_size ;
            double present_data = positive_present + negative_present ;


            double infoGain = informationGain(totalEntropy , entropy_present , entropy_absent , totalDatapoints , present_data);

            if (informationG < infoGain){
                informationG = infoGain ;
                rootIndex = *itr ;

            }

        }
        if (informationG == 0.0){
            return -1 ;
        }
    return rootIndex ;
}





node * ID3(  vector <int> posList, vector <int> negList ,list <int> attribute ,vector <list < pair<int , int > > > &storePosReview,vector <list < pair<int , int > > > &storeNegReview, int height , int maxHeight ){

    node *root = new node();

    if (posList.size() == 0){
        root->index = -2 ; // -2 represents negative label
        return root ;
    }

    if (negList.size() == 0){
        root->index = -1 ; // -1 represents positive label
        return root ;
    }

    if (attribute.size() == 0){
        if (posList.size() > negList.size()){
            root->index = -1 ;
            return root ;
        }
        else {
            root->index = -2 ;
            return root ;
        }
    }

    int index = calculateBestAttribute(posList ,negList , attribute , storePosReview , storeNegReview);
    // change 1
    if (index == -1|| height > maxHeight){
        if (posList.size() > negList.size()){
            root->index = -1 ;
        }
        else {
            root->index = -2 ;
        }
        return root ;

    }

    root->index = index ;
    attribute_count[index].first  = attribute_count[index].first + 1 ;

    if (posList.size() > negList.size()){
        root->majority = -1 ;
    }
    else {
        root->majority = -2 ;
    }



    vector<int> presentPosList ;
    vector<int> presentNegList ;
    vector<int> absentPosList ;
    vector<int> absentNegList ;

    for (int i = 0 ; i< posList.size() ; i++){
        int index_review = posList[i] ;
        list<pair <int , int> >::iterator finditr ;
        bool present = false ;
        for (finditr = storePosReview[index_review].begin() ; finditr != storePosReview[index_review].end() ; finditr++){
            if ((*finditr).first == index){
                presentPosList.push_back(index_review) ;
                present = true ;
                break ;
            }

        }
        if (!present){
            absentPosList.push_back(index_review);
        }

    }

    for (int i = 0 ; i< negList.size() ; i++){
        int index_review = negList[i] ;
        list<pair <int , int> >::iterator finditr ;
        bool present = false ;
        for (finditr = storeNegReview[index_review].begin() ; finditr != storeNegReview[index_review].end() ; finditr++){
            if ((*finditr).first == index){
                presentNegList.push_back(index_review) ;
                present = true ;
                break ;
            }

        }
        if (!present){
            absentNegList.push_back(index_review);
        }

    }
    // deleting the root index
    list<int>::iterator eraseItr ;
    for (eraseItr = attribute.begin() ; eraseItr != attribute.end() ; eraseItr++){
        if ((*eraseItr) == index){
            break ;
        }
    }
    attribute.erase(eraseItr);

    if (presentPosList.size() == 0 && presentNegList.size() == 0){
        node *t = new node() ;

        if (posList.size() > negList.size()){
            t->index = -1 ;
            root->left = t ;
        }
        else {
             t->index = -2 ;
            root->left = t ;

        }
    }
    else {
         root->left = ID3(presentPosList , presentNegList ,attribute , storePosReview , storeNegReview , height + 1 , maxHeight);
    }

    if (absentPosList.size() == 0 && absentNegList.size() == 0){
        node *t = new node() ;

        if (posList.size() > negList.size()){
            t->index = -1 ;
            root->right = t ;
        }
        else {
             t->index = -2 ;
            root->right = t ;

        }
    }
    else {
            root->right = ID3(absentPosList , absentNegList , attribute , storePosReview , storeNegReview , height + 1 ,maxHeight);
    }

    // now for this index

return root ;


}

int getLabel(int present[] , node *root){

    node *search = root ;


    while (search->left != NULL || search->right != NULL){

        if (present[search->index] == 1){
            search = search->left ;
        }
        else {
            search = search->right ;
        }

    }
    return search->index ;

}


double checkForAccuracy(node *root , vector <list <pair <int ,int> > > &testData , int label){

    double success_test = 0 ;
    double total_test = testData.size() ;
    for (int i = 0 ; i < testData.size() ; i++){
           int present[MAXWORD] = {0} ;
           list<pair <int ,int> >::iterator it ;
           for (it = testData[i].begin() ; it != testData[i].end() ; it++){
                present[(*it).first] = 1 ;
           }
           int testLabel = getLabel(present , root);
           if (testLabel == label){
            success_test++ ;
           }

    }
    double accuracy = (success_test/total_test)*100 ;

    return accuracy ;

}

double getAccuracy_forest(vector <node *> treeNodes , vector <list <pair <int ,int> > > testData , int label){


    double correctLabel = 0 ;
    for (int i = 0 ; i < testData.size() ; i++){

        int positiveLabel = 0 ;
        int negativeLabel = 0 ;
        int finalLabel ;
        int present[MAXWORD] = {0} ;
        list<pair <int ,int> >::iterator it ;
        for (it = testData[i].begin() ; it != testData[i].end() ; it++){
            present[(*it).first] = 1 ;
        }


        for (int j = 0 ; j < treeNodes.size() ; j++){
            node *root = treeNodes[j] ;
            int testLabel = getLabel(present , root);
            if (testLabel == -1){
                positiveLabel++ ;
            }
            else if (testLabel == -2) {
                negativeLabel++ ;
            }

        }
         if (positiveLabel > negativeLabel){
                finalLabel = -1 ;
            }
            else {
                finalLabel = -2 ;
            }
        if (finalLabel == label){
            correctLabel++ ;
        }

    }


    return (correctLabel*100)/testData.size() ;
}

void postOrder(node *root , vector <node *> &storeNodes){

    if (root == NULL){
        return ;
    }
    postOrder(root->left , storeNodes);
    postOrder(root->right , storeNodes);
    if (root->index != -1 && root->index != -2){
        storeNodes.push_back(root);
    }

}

node * pruning(node *root , vector <list <pair <int ,int> > > &validationPos ,  vector <list <pair <int ,int> > > &validationNeg  ){

    vector <node *> storeNodes ;
    postOrder(root ,storeNodes);

    double maxAccuracy = (checkForAccuracy(root ,validationPos , -1) + checkForAccuracy(root , validationNeg , -2))/2 ;
    node * maxNode = root ;

    while (1){
        storeNodes.clear();
        postOrder(root ,storeNodes);
        bool maximum = false ;
        for (int i = 0 ; i < storeNodes.size() ; i++){
            node *removed = storeNodes[i] ;
            int storeIndex = removed->index ;
            node *leftNode = removed->left ;
            node *rightNode = removed->right ;

            removed->index = removed->majority ;
            removed->left = NULL ;
            removed->right = NULL ;
            double accuracy = (checkForAccuracy(root ,validationPos , -1) + checkForAccuracy(root , validationNeg , -2))/2 ;
            //cout << "accuracy = " << accuracy << endl ;
            if (accuracy > maxAccuracy){
                maxAccuracy = accuracy ;
                maxNode = removed ;

                maximum = true ;
            }

            removed->index = storeIndex ;
            removed->left = leftNode ;
            removed->right = rightNode ;
        }

        if (!maximum){

            break ;
        }

        maxNode->index = maxNode->majority ;
        maxNode->left = NULL ;
        maxNode->right = NULL ;



    }

    return root ;

}

void addNoise(vector <int> positveList, vector <int> negativeList ,list <int> attribute,vector <list < pair<int , int > > > &storePosReview,vector <list < pair<int , int > > > &storeNegReview ,vector <list < pair<int , int > > > &testposReview,vector <list < pair<int , int > > > &testnegReview){
    double errorList[] = {0.5 , 1.0, 5.0 ,10.0 , 20.0 , 30.0 , 40.0};
    int errorSize = sizeof(errorList)/sizeof(errorList[0]) ;
    vector <list <pair <int , int> > > errorPos(500) ;

    vector <list <pair <int , int> > > errorNeg(500);

    for (int i = 0 ; i < errorSize ; i++){
        int swap_index = (int)(10*errorList[i]) ;
        errorPos = storePosReview ;
        errorNeg = storeNegReview ;
        for (int j = 0 ; j < swap_index ; j++){
            list <pair <int , int> > temp = errorPos[j];
            errorPos[j] = errorNeg[j];
            errorNeg[j] = temp ;
        }
        int height = 0 ;
        node * tnode1 = ID3(positveList , negativeList ,attribute ,errorPos , errorNeg , height,1000000);
        double accuracy_trainingData = checkForAccuracy(tnode1 , errorNeg , -2);
        double accuracy_testData = checkForAccuracy(tnode1 ,testposReview , -1);

        double accuracy_testNegData = checkForAccuracy(tnode1 , testnegReview , -2);
        cout << "Training Data accuracy  for noise " << errorList[i] << "%  = " << accuracy_trainingData << " %"<< endl ;
        cout << "Test Data accuracy for noise " << errorList[i] << "%  =" << (accuracy_testData + accuracy_testNegData)/2 << " %" << endl ;


        cout << "\n" ;
    }



}

void createRandomForest( vector <int> positveList, vector <int> negativeList ,vector <list < pair<int , int > > > &storePosReview,vector <list < pair<int , int > > > &storeNegReview ,vector <list < pair<int , int > > > &testposReview,vector <list < pair<int , int > > > &testnegReview){ // creating function

    int number_trees[] = {10 , 20 , 30 , 40 , 50,60 , 70 , 80 , 90};
    int size_trees = sizeof(number_trees)/sizeof(number_trees[0]) ;
    int attribute_size = 300 ;
    int size_random_word = 5000;
    vector <int> random_word(size_random_word) ;
    for (int i = 0 ; i < size_random_word ; i++){
        random_word[i] = i;
    }

    for (int i = 0 ; i < size_trees ; i++){

            vector <node *> treeNodes(number_trees[i]) ;
            int k = 0 ;
            for (int j = 0 ; j < number_trees[i] ; j++){

                 list <int> random_attribute ;
                random_shuffle(random_word.begin() , random_word.end() ,myrandom);
                for (int i = 0 ; i < attribute_size ; i++){
                    random_attribute.push_back(random_word[i]) ;
                }
                list<int>::iterator it = random_attribute.begin() ;
                //cout << (*it) << "size is " << random_attribute.size() << endl ;
                node *tnode1 = ID3(positveList , negativeList , random_attribute ,storePosReview , storeNegReview , 0 , 1000000);
                treeNodes[k++] = tnode1 ;
        }

        double accuracy1 = getAccuracy_forest(treeNodes , testposReview , -1);
        double accuracy2 = getAccuracy_forest(treeNodes , testnegReview , -2);

        double training_accuracy1 = getAccuracy_forest(treeNodes , storePosReview , -1);
        double training_accuracy2 = getAccuracy_forest(treeNodes , storeNegReview , -2);
        cout << number_trees[i] << "  " ;
        cout << (training_accuracy1 + training_accuracy2)/2  ;
        cout << " " << (accuracy1 + accuracy2)/2 << endl ;


    }




}

int maximum(int a , int b){
    if (a > b){
        return a ;
    }
    return b ;
}

int calculateHeight(node *root){
    if (root == NULL){
        return 0 ;
    }

    int left = calculateHeight(root->left);
    int right = calculateHeight(root->right);

    return maximum(left,right) + 1 ;



}


int main(int argc , char *argv[])
{
    //srand(time(NULL));

    vector <pair <double , int> > word(89527) ;


    vector<string> testpos ;
    vector <string> testneg ;
    readInputFromFile(testpos , word ,"testPositive.txt" , 0);
    readInputFromFile(testneg , word , "testNegative.txt" , 0);

    vector<string> pos ;
    vector<string> neg ;
    readInputFromFile(pos , word ,"trainingPositive.txt" , 0);
    readInputFromFile(neg , word , "trainingNegative.txt" , 0);

    vector <string> validationPos;
    vector <string> validationNeg;
    readInputFromFile(validationPos , word ,"validationPositive.txt" , 0);
    readInputFromFile(validationNeg , word , "validationNegative.txt" , 0);




    vector <list < pair<int , int > > > storePosReview(500);
    vector <list < pair<int , int > > > storeNegReview(500) ;

    readInputFromFile(testpos,word , "imdbEr.txt",2);
    // choosing first 1000 words
    //sort(word.begin() , word.end());
    list <int> attribute ; // store 5000 words

    // To take 5000 words based on polarity and write into file
    //writeIntoFile("./selected-features-indices.txt" ,word , attribute);
    for (int i = 0 ; i < att_size ; i++){
        attribute.push_back(i);
    }



    //writeFile("./positiveReview" ,pos);
    vector <list <pair <int , int> > > testposReview(500) ;
    vector <list <pair <int , int> > > testnegReview(500) ;
    vector <list <pair <int , int> > > validationPosReview(500) ;
    vector <list <pair <int , int> > > validationNegReview(500) ;

    convertReviewToList(testpos , testposReview );
    convertReviewToList(testneg , testnegReview);
    convertReviewToList(pos , storePosReview) ;
    convertReviewToList(neg, storeNegReview) ;
    convertReviewToList(validationPos , validationPosReview) ;
    convertReviewToList(validationNeg, validationNegReview) ;
   // writeFile("./negativeReview" ,neg);


    for (int i = 0 ; i < MAXWORD ; i++){
        frequency_word[i][0] = 0 ;
        frequency_word[i][1] = 0 ;

    }

    list <pair <int , int> >::iterator itr ;
    list <int>::iterator pr ;
    vector <int> positveList ;
    vector <int> negativeList ;

    for (int i = 0 ; i < 500 ; i++){
        positveList.push_back(i);
        negativeList.push_back(i);
    }


    int height = 0 ;
    
   
        int height_tree[] = {10 , 15 , 20 ,25 ,30 , 10000000} ;
        int number_trees = sizeof(height_tree)/sizeof(height_tree[0]) ;

        node *tnode = ID3(positveList, negativeList,attribute,storePosReview,storeNegReview , 0,10000000 );
        // change 2

           

    if (argv[2][0] == '2'){
    
         for (int i = 0 ; i < number_trees ; i++){
                for (int j = 0 ; j < MAXWORD ; j++){
                    attribute_count[j].first = 0 ;
                    attribute_count[j].second = j ;
                }
                // first represent count and second represent index ;

                node *tnode2 = ID3(positveList, negativeList,attribute,storePosReview,storeNegReview , 0,height_tree[i] );
                double accuracy_trainingData = checkForAccuracy(tnode2 , storeNegReview , -2);
                double accuracy_testData = checkForAccuracy(tnode2 ,testposReview , -1);
                double accuracy_testNegData = checkForAccuracy(tnode2 , testnegReview , -2);
                cout << "Training Data accuracy is " << accuracy_trainingData << " %"<< endl ;
                cout << "Test Data accuracy is " << (accuracy_testData + accuracy_testNegData)/2 << " %" << endl ;
                vector <node * > storeNodes ;
                postOrder(tnode2 , storeNodes);
                cout << "Number of nodes in height " << height_tree[i] << "  are = " << storeNodes.size() << endl ;
                cout << "\n" ;

        }
        node * tnode2 = ID3(positveList, negativeList,attribute,storePosReview,storeNegReview , 0,10000000 );
        vector <node *> storeNodes ;
        postOrder(tnode2 ,storeNodes);
        for (int j = 0 ; j < MAXWORD ; j++){
            attribute_count[j].first = 0 ;
            attribute_count[j].second = j ;
        }

        for (int i = 0 ; i < storeNodes.size() ; i++){
            node * k = storeNodes[i] ;
            attribute_count[k->index].first ++ ;

        }

        sort(attribute_count.begin() , attribute_count.end());
        for (int i = 0 ; i < 10 ; i++){
            cout << attribute_count[MAXWORD-1-i].second << "  " << attribute_count[MAXWORD-1-i].first << endl ;
        }


    }

    else if (argv[2][0] == '3'){
        if (tnode == NULL){
            cout << "Please run experiment 2 first to create tree" << endl ;
        }
        else {
            cout << "\n" << "Adding Noise ....." << endl ;
            addNoise(positveList,negativeList,attribute,storePosReview,storeNegReview,testposReview,testnegReview);
        }

    }
    else if (argv[2][0] == '4'){
        if (tnode == NULL){
            cout << "Please run experiment 2 first to create tree" << endl ;
        }
        else {
            cout << "\n" << "Pruning the tree .... " << endl ;
            cout << "root attribute is " << tnode->index << endl ;
            cout << "Height of a Original tree is " << calculateHeight(tnode) << endl ;

            node *t = pruning(tnode,validationPosReview,validationNegReview);
            vector <node *> storeNodes ;
            postOrder(t,storeNodes);
            cout << "Number of nodes in Prune tree is = " << storeNodes.size() << endl ;
            cout << "root attribute is " << t->index << endl ;
            cout << "Height of a Prune tree is " << calculateHeight(t) << endl ;
            cout << "Accuracy on test Data " << (checkForAccuracy(t , testposReview , -1) + checkForAccuracy(t , testnegReview , -2))/2 << endl ;
        }
         //random forest creating ;
    }
    else if (argv[2][0] == '5'){
        cout << "\n" << "Creating Random Forest ...." << endl ;
        createRandomForest(positveList , negativeList,storePosReview,storeNegReview,testposReview , testnegReview);
    }
    else {
        cout << "Enter Valid Input" << endl ;
    }



    return 0;
}
