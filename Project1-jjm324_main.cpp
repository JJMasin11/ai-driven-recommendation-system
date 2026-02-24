//Implemented Option 1

#include "Project1-jjm324_backwardsChaining.cpp"
#include "Project1-jjm324_forwardChaining.cpp"

using namespace std;

int main(int argc, const char * argv[]){
    
    string backward_chain_conclusion = backward_chaining();
    
    if (backward_chain_conclusion == "no"){
        cout<<"Student is not eligible for profession"<<endl;
        return 0;
    }
    else{
        cout<<"Profession = "+backward_chain_conclusion<<endl;
    }
    
    //Add Forward Chain function call below this line
    
    forwardChaining(backward_chain_conclusion);

    return 0;
}


