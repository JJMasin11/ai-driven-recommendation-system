#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <vector>

using namespace std;

string conclusion_list[10] = {"profession","qualify","profession","profession","profession","profession","profession","profession","profession","profession"};
bool processed[10] = {false,false,false,false,false,false,false,false,false,false};
string variable_list[8] = {"diploma",
                                    "security",
                                    "art",
                                    "journalism",
                                    "helping",
                                    "care_type",
                                    "study_physical",
                                    "theoretical"};
string clause_variable_list[170] = {"diploma","","","","","","",
            "diploma","","","","","","",
            "qualify","security","art","","","","",
            "qualify","security","art","","","","",
            "qualify","security","journalism","","","","",
            "qualify","security","journalism","helping","care_type","","",
            "qualify","security","journalism","helping","care_type","","",
            "qualify","security","journalism","helping","study_physical","","",
            "qualify","security","journalism","helping","study_physical","theoretical","",
            "qualify","security","journalism","helping","study_physical","theoretical",""};

unordered_map<string,string> edit_variable_map= {{"diploma",""},
    {"qualify",""},
    {"security",""},
    {"art",""},
    {"journalism",""},
    {"helping",""},
    {"care_type",""},
    {"study_physical",""},
    {"theoretical",""}};

unordered_map<string,string> ask_question_map={
    {"diploma","Do you have High School Diploma? [yes][no]"},
    {"security","Is job security more important than following your passion? [yes][no]"},
    {"art","Are you passionate about creating art, music or theater? [yes][no]"},
    {"journalism","Are you good at conveying complex ideas or interested in journalism? [yes][no]"},
    {"helping","Are you interested in helping others? [yes][no]"},
    {"care_type","Are you interested in preventive care or treatment? [preventive][treatment]"},
    {"study_physical","Are you interested in studying the physical world? [yes][no]"},
    {"theoretical","Do you like the theoretical or practical part? [theoretical][practical]"}};

unordered_map<string, vector<string>> answer_map = {
    {"diploma",{"yes","no"}},
    {"security",{"yes","no"}},
    {"art",{"yes","no"}},
    {"journalism",{"yes","no"}},
    {"helping",{"yes","no"}},
    {"care_type",{"preventive","treatment"}},
    {"study_physical",{"yes","no"}},
    {"theoretical",{"theoretical","practical"}}};

string conclusion_variable = "";

string rule10[2]= {"no","no"};

string rule20[2]= {"yes","yes"};

string rule30[4]= {"yes","no","yes","fine arts"};

string rule40[4]= {"yes","no","no","liberal arts"};

string rule50[4]= {"yes","yes","yes","communication"};

string rule60[6]= {"yes","yes","no","yes","preventive","health care"};

string rule70[6]= {"yes","yes","no","yes","treatment","medical"};

string rule80[6]= {"yes","yes","no","no","no","business"};

string rule90[7]= {"yes","yes","no","no","yes","theoretical","science"};

string rule100[7]= {"yes","yes","no","no","yes","practical","engineering"};


//function prototypes
int search_con(string variable);
int rule_to_clause(int variable);
void update_variable(int variable);
void validate_rule(int variable, string conclusion);
void process(string variable);
bool check_variable_in_list(string variable);
string backward_chaining();

//Function Implementation below this line

string backward_chaining(){
    
    string goal = "profession";
    process(goal);
    return conclusion_variable;
}

int search_con(string variable){
    int rule_number=0;
    int conclusion_listlength = sizeof(conclusion_list)/sizeof(conclusion_list[0]);

    for (int i=0;i<conclusion_listlength;i++){
        if ((variable == conclusion_list[i]) && (processed[i]==false)){
            rule_number = (i+1) * 10;
            processed[i] = true;
            break;
        }
    }

    return rule_number;
}

int rule_to_clause(int variable){
    int clause_number;
    clause_number = 7 * ((variable/10) - 1) + 1;

    return clause_number;
}

void update_variable(int variable){
    int adjusted_clause = variable - 1;
    int end_clause = adjusted_clause + 7;

    while (adjusted_clause<end_clause){
        string current_var = clause_variable_list[adjusted_clause];
        if ( (check_variable_in_list(current_var)) && edit_variable_map.count(current_var) > 0 ){
            
            string getValue = edit_variable_map[current_var];
            if (getValue == ""){
                string input;
                vector<string> answers = answer_map[current_var];
                cout<<ask_question_map[current_var]<<endl;
                
                do{
                    cin>>input;
                   transform(input.begin(), input.end(), input.begin(), ::tolower);
                    
                    if ((answers[0] != input) && (answers[1] != input))
                        cout << "Please enter one of the listed answers." << endl;
                    
                }while((answers[0] != input) && (answers[1] != input));
                edit_variable_map[current_var] = input;
            }
        }
        else{
            if ((current_var != "") && (edit_variable_map[current_var] == "")){
                process(current_var);
            }
        }
        adjusted_clause++;
    }
    return;
}

void validate_rule(int variable, string conclusion){
    int clause = rule_to_clause(variable);
    int adjusted_clause = clause - 1;
    string* select_rule = nullptr;
    int array_size = 0;
    switch(variable){
        case 10:
            select_rule = rule10;
            array_size = 2;
            break;
        case 20:
            select_rule = rule20;
            array_size = 2;
            break;
        case 30:
            select_rule = rule30;
            array_size = 4;
            break;
        case 40:
            select_rule = rule40;
            array_size = 4;
            break;
        case 50:
            select_rule = rule50;
            array_size = 4;
            break;
        case 60:
            select_rule = rule60;
            array_size = 6;
            break;
        case 70:
            select_rule = rule70;
            array_size = 6;
            break;
        case 80:
            select_rule = rule80;
            array_size = 6;
            break;
        case 90:
            select_rule = rule90;
            array_size = 7;
            break;
        case 100:
            select_rule = rule100;
            array_size = 7;
            break;
    }
    for (int i=0;i<array_size;i++,adjusted_clause++){
        string var_name = clause_variable_list[adjusted_clause];
        if (var_name == ""){
            break;
        }
        string mapping = edit_variable_map[var_name];
        if (mapping != *(select_rule+i)){
            conclusion_variable = "";
            return;
        }
    }
    conclusion_variable = select_rule[array_size-1];
    return;
}

void process(string variable){

    int conclusion_listlength = sizeof(conclusion_list)/sizeof(conclusion_list[0]);
    
    for (int i = 0;i<conclusion_listlength;i++){
        int rule_number = search_con(variable);

        int clause_number = rule_to_clause(rule_number);

        update_variable(clause_number);

        validate_rule(rule_number,"");
        
        if (edit_variable_map.count(variable)>0){
            edit_variable_map[variable] = conclusion_variable;
            return;
        }
        if (conclusion_variable == ""){
            continue;
        }
        else
            break;
    }
    return;
}

bool check_variable_in_list(string variable){
    for (int i = 0;i<8;i++){
        if (variable == variable_list[i]){
            return true;
        }
    }
    return false;
}

