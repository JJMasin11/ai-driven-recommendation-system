#include <iostream>
#include <cctype>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

struct Variable {
    string name;
    string value;
};

//forwards chaining variables
vector<string> derivedConclusionList;
queue<Variable> conclusionVariableQueue;
Variable variableList[30] = {{"profession",""}, {"math", ""}, {"term", ""}, {"leadership", ""}, {"scope", ""}, 
                            {"high_pressure_m", ""}, {"organ", ""}, {"high_pressure_hc", ""}, {"patients", ""}, {"recover", ""}, {"art", ""},
                            {"music_or_theater", ""}, {"drive", ""}, {"job_base", ""}, {"history", ""}, {"abstract", ""}, 
                            {"law", ""}, {"writing", ""}, {"law_relationship", ""}, {"reporting", ""}, {"explanation", ""}, 
                            {"conflict", ""}, {"design", ""}, {"living_things", ""}, {"world", ""}, {"learn", ""}, 
                            {"human", ""}, {"energy", ""}, {"chemical_process", ""}, {"device", ""}};

string clauseList[185] = {"profession", "math", "term", "", "",
        "profession", "math", "term", "", "",
        "profession", "math", "leadership", "", "",
        "profession", "math", "leadership", "", "",
        "profession", "scope", "high_pressure_m", "", "",
        "profession", "scope", "high_pressure_m", "", "",
        "profession", "scope", "organ", "", "",
        "profession", "scope", "organ", "", "",
        "profession", "high_pressure_hc", "", "", "",
        "profession", "high_pressure_hc", "patients", "", "",
        "profession", "high_pressure_hc", "patients", "recover", "",
        "profession", "high_pressure_hc", "patients", "recover", "",
        "profession", "art", "", "", "",
        "profession", "art", "drive", "", "",
        "profession", "art", "drive", "music_or_theater", "",
        "profession", "art", "drive", "music_or_theater", "",
        "profession", "job_base", "law", "law_relationship", "",
        "profession", "job_base", "law", "law_relationship", "",
        "profession", "job_base", "law", "writing", "",
        "profession", "job_base", "law", "writing", "",
        "profession", "job_base", "history", "", "",
        "profession", "job_base", "history", "abstract", "",
        "profession", "job_base", "history", "abstract", "",
        "profession", "reporting", "", "", "",
        "profession", "reporting", "explanation", "conflict", "",
        "profession", "reporting", "explanation", "conflict", "",
        "profession", "reporting", "explanation", "design", "",
        "profession", "reporting", "explanation", "design", "",
        "profession", "living_things", "learn", "", "",
        "profession", "living_things", "learn", "", "",
        "profession", "living_things", "world", "human", "",
        "profession", "living_things", "world", "human", "",
        "profession", "living_things", "world", "", "",
        "profession", "energy", "device", "", "",
        "profession", "energy", "device", "", "",
        "profession", "energy", "chemical_process", "", "",
        "profession", "energy", "chemical_process", "", ""}; //5 slots for each rule

string questionList[29] = {
        "Are you good at math? [Yes][No]",
        "Are you more interested in short-term or long-term goals? [Short-term][Long-term]",
        "Do you have good leadership skills? [Yes][No]",
        "Do you want to be specialized or more general? [Specialized][General]",
        "Are you comfortable in high pressure situations? [Yes][No]",
        "Are you more interested in the brain or the heart? [Brain][Heart]",
        "Are you able to work in stressful situations? [Yes][No]",
        "Are you interested in working with patients? [Yes][No]",
        "Are you interested in helping a patient recover from an injury or surgery? [Yes][No]",
        "Are you interested in art? [Yes][No]",
        "Are you more interested in music or theater? [Music][Theater]",
        "Do you have the drive to become a top performer? [Yes][No]",
        "Would you enjoy a job more based in the academic or the real world? [Academic][Real-world]",
        "Do you enjoy discussing history? [Yes][No]",
        "Do you enjoy thinking about things on a more conceptual level and discussing abstract ideas? [Yes][No]",
        "Do you have an interest in law or policy? [Yes][No]",
        "Do you enjoy writing or literature? [Yes][No]",
        "Would you rather advise or enforce the law? [Advise][Enforce]",
        "Do you like telling stories and bringing attention to topics through reporting? [Yes][No]",
        "Are you good at explaining complex ideas in a way people can easily understand? [Yes][No]",
        "Are you good at understanding and resolving conflicts with others? [Yes][No]",
        "Are you better at writing or design? [Writing][Design]",
        "Are you interested in the study of living things? [Yes][No]",
        "Are you interested in the natural world? [Yes][No]",
        "Would you rather learn about computers or space? [Computers][Space]",
        "What is more important? Humans as individuals or humans in a society? [Individuals][Society]",
        "Are you passionate about solving the energy crisis? [Yes][No]",
        "Are you interested in chemical processes? [Yes][No]",
        "Do you like tinkering with devices? [Yes][No]"};

string answerList[58] = {
        "yes", "no",
        "short-term", "long-term",
        "yes", "no",
        "specialized", "general",
        "yes", "no",
        "brain", "heart",
        "yes", "no",
        "yes", "no",
        "yes", "no",
        "yes", "no",
        "music", "theater",
        "yes", "no",
        "academic", "real-world",
        "yes", "no",
        "yes", "no",
        "yes", "no",
        "yes", "no",
        "advise", "enforce",
        "yes", "no",
        "yes", "no",
        "yes", "no",
        "writing", "design",
        "yes", "no",
        "yes", "no",
        "computers", "space",
        "individuals", "society",
        "yes", "no",
        "yes", "no",
        "yes", "no"};

string ruleList[37][5] = {
    {"business", "yes", "short-term", "accounting"},
    {"business", "yes", "long-term", "finance"},
    {"business", "no", "yes", "management"},
    {"business", "no", "no", "marketing"},
    {"medical", "general", "yes", "surgeon"},
    {"medical", "general", "no", "general practitioner"},
    {"medical", "specialized", "brain", "neurologist"},
    {"medical", "specialized", "heart", "cardiologist"},
    {"health care", "yes", "paramedic"},
    {"health care", "no", "no", "pharmacist"},
    {"health care", "no", "yes", "yes", "physical therapist"},
    {"health care", "no", "yes", "no", "dietitian"},
    {"fine arts", "yes", "artist"},
    {"fine arts", "no", "no", "fine arts education"},
    {"fine arts", "no", "yes", "music", "musician"},
    {"fine arts", "no", "yes", "theater", "actor"},
    {"liberal arts", "real-world", "yes", "enforce", "lawyer"},
    {"liberal arts", "real-world", "yes", "advise", "political studies"},
    {"liberal arts", "real-world", "no", "yes", "english"},
    {"liberal arts", "real-world", "no", "no", "liberal arts education"},
    {"liberal arts", "academic", "yes", "historian"},
    {"liberal arts", "academic", "no", "yes", "philosophy"},
    {"liberal arts", "academic", "no", "no", "social studies"},
    {"communication", "yes", "journalist"},
    {"communication", "no", "no", "no", "public relations"},
    {"communication", "no", "no", "yes", "human resources"},
    {"communication", "no", "yes", "design", "graphic design"},
    {"communication", "no", "yes", "writing", "technical writing"},
    {"science", "no", "computers", "computer science"},
    {"science", "no", "space", "astronomy"},
    {"science", "yes", "no", "individuals", "psychology"},
    {"science", "yes", "no", "society", "sociology"},
    {"science", "yes", "yes", "biology"},
    {"engineering", "no", "yes", "mechanical engineer"},
    {"engineering", "no", "no", "civil engineer"},
    {"engineering", "yes", "yes", "chemical engineer"},
    {"engineering", "yes", "no", "electrical engineer"}
}; 

//function prototypes
int search_cvl(string variable);   //searches clause varaible list for entry matching input, returns clause #
int clause_to_rule(int variable);  //converts clause # to corresponding rule #
void update_VL(int variable);      //take clause #, check if variable is in the list or not; if it's not, ask the user
bool validate_Ri(int variable);    //check if the rule's clauses are valid with the contents of the variable list.
//    If so, add conclusion to derived conclusion list & conclusion queue
void processF(string variable); //instantiate value of variable in variable list
void forwardChaining(string variable); //run forward chaining

int search_cvl(string variable){
    int Ci = 0;

    int size = sizeof(clauseList)/sizeof(clauseList[0]);
    for(int i = 0; i < size; i++) {
        if(clauseList[i] == variable) {
            Ci = i;
            update_VL(Ci);
            int Ri = clause_to_rule(Ci);
            if(validate_Ri(Ri)){
                break;
            }
        }
    }

    return Ci;
}

int clause_to_rule(int variable){   //i'm assuming 5 slots per rule; change it if you need more jack
    int Ri = ((variable/5) + 1) * 10;
    return Ri;
}

void update_VL(int variable){
    string variableToCheck;
    string answer;

    for(int i = variable; i < variable + 4; i++) {
        if(clauseList[i] != "") {
            variableToCheck = clauseList[i];

            for(int j = 0; j < sizeof(variableList)/sizeof(variableList[0]); j++) {
                if(variableList[j].name == variableToCheck && variableList[j].value == "") {
                    //ask question from question list
                    cout << questionList[j - 1] << endl;
                    
                    do {
                        cin >> answer;
                        
                        transform(answer.begin(), answer.end(), answer.begin(), ::tolower);

                        if(answer != answerList[2*(j-1)] && answer != answerList[2*(j-1) + 1]) {
                            cout << "Please enter one of the listed answers." << endl;
                        }
                    } while (answer != answerList[2*(j-1)] && answer != answerList[2*(j-1) + 1]);

                    variableList[j].value = answer;
                }
            }
        }
    }
}

bool validate_Ri(int variable){
    string ruleToCheck[5] = {};
    //hack because it won't let me directly asign an array
    for(int i = 0; i < 5; i++){
        ruleToCheck[i] = ruleList[(variable/10) - 1][i];
    }

    int clauseNumber = ((variable / 10) * 5) - 5;
    //iterate over clauses in rule
    for(int i = 0; i < 4; i++) {
        //search variable list for matching name
        for(int j = 0; j < sizeof(variableList)/sizeof(variableList[0]); j++) {
            if(clauseList[i + clauseNumber] == ""){
                break;
            }
            if(variableList[j].name == clauseList[i + clauseNumber]) {
                //variable name match; check whether value is correct
                if(variableList[j].value != ruleToCheck[i]){
                    return false;
                }
                break;
            }
        }
    }

    //get conclusion from rule
    string conclusion = "";
    for(int i = 4; i >= 0; i--){
        if(ruleToCheck[i] != ""){
            conclusion = ruleToCheck[i];
            break;
        }
    }
    derivedConclusionList.push_back(conclusion);

    Variable area;
    area.name = "Area";
    area.value = conclusion;
    conclusionVariableQueue.push(area);

    return true;
}

void processF(string variable, string value){   //i'm just using this overload for the main function to avoid asking the user what the system just told them
    //look for variable in list, instantiate value
    for(int i = 0; i < 29; i++){
        if(variable == variableList[i].name){
            variableList[i].value = value;
            break;
        }
    }
    //call search_cvl
    search_cvl(variable);
}

void processF(string variable){
    search_cvl(variable);
}

void forwardChaining(string variable){
    if (variable != "no"){
        processF("profession", variable);
        while(!derivedConclusionList.empty()){
            processF(derivedConclusionList.back());
            derivedConclusionList.pop_back();
        }
    }
    while(!conclusionVariableQueue.empty()){
        Variable conVar = conclusionVariableQueue.front();
        cout << conVar.name + " = " + conVar.value;
        conclusionVariableQueue.pop();
    }
}
