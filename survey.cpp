#include <iostream>
#include <string>
#include <fstream>
#include <algorithm> 
using namespace std;
// Function that will write survey

void processSurvey(string party, string surveyData[][2]) {

    cout << "Your party is: " << party;
    //Check is file already exists
    fstream surveyFile;
    surveyFile.open(party + ".txt", ios::app);
    //Write data
    for (int i = 0; i < 8; i++) {
    surveyFile << surveyData[i][0] << surveyData[i][1];
    };
    //Close file
    surveyFile.close();

}

//for validation input
bool isValid(string answer) {

    string letters[8] = { "a", "b", "c", "d", "A", "B", "C", "D" };
    bool valid = false;
    int sizeOfArray = sizeof(letters) / sizeof(letters[0]);
    for(int i = 0; i < sizeOfArray; i++) {
        if (answer == letters[i]) {
            valid = true;
            break;
        }
    }

    return valid;
}

//Find frequent letter

string* letterMode(string arr[]) {

    int parties[] = { 0,0,0,0 };
    int maxPointsOption = 0;

    //Calculate points

    for (int i = 0; i < 7; i++) {

        if (arr[i] == "a" || arr[i] == "A") {
            parties[0] += 1;
        }
        else if (arr[i] == "b" || arr[i] == "B") {
            parties[1] += 1;
        }
        else if (arr[i] == "c" || arr[i] == "C") {
            parties[2] += 1;
        }
        else if (arr[i] == "d" || arr[i] == "D") {
            parties[3] += 1;
        }

    }

    // Find the highest number of points

    for (int i = 0; i < 4; i++) {
        if (parties[i] == *max_element(parties, parties + 4))
        {
            maxPointsOption = i;
            break;
        }
    }

     string * data = new string[2];

     if (maxPointsOption == 0) {
         data[0] = "Republican";
         data[1] = "a";
    }
    else if (maxPointsOption == 1) {
         data[0] = "Democrat";
         data[1]= "b";
     
    }
    else if (maxPointsOption == 2) {
         data[0] = "Independent",
         data[1]=  "c";
    }
    else {
         data[0] = "Green";
         data[1] = "d" ;
    }

    return data;
}


int main(){

    //Create the survey structure with 2D array
    string surveyAnswers[8][2] = {
        {"\n1. Where do you get your political news?\n a. Fox News; \n b. CNN; \n c. BBC or other independent media; \n d. I don't read political news or my preferences are not listed\n Answer: ", ""},
        {"\n2. What help government should provide to poor people?\n a.No help, this is the responsibility of people themselves; \n b.Increase financial spending to provide equal opportunities; \n c.Maybe provide some finances of healthcare coverage for the very poor; \n d.Some help, but concentration on the environment;\n Answer: ", ""},
        {"\n3. What is your opinion about abortion?\n a. This is a murder, should be banned; \n b. This is woman choice, should be allowed; \n c. Allowed with some limitations, like no later than 10 - 12 weeks ; \n d. Should be available;\n Answer: ",""},
        {"\n4. What goverment should do about gun control?\n a. No guns control, this is a free country; \n b. We should restrict usage as much as possible, this is not civilised; \n c. Apply restrictions, but keep small guns, like revolvers, or not a deadly ones.; \n d. Thoughtful, carefully considered gun control such as is contained in the Brady Bill \n Answer: ", ""},
        {"\n5. What actions should be done about drugs such as Cannabis?\n a. Should be illegal; \n b. Decrimilize possesion of it; \n c. Everywhere there should be a measure, leave some states with legalization and the rest without it. \n d. Cannabis/Hemp is to be legalized, regulated and controlled like cigarettes and alcohol. \n Answer: ", ""},
        {"\n6. What do you think about illegal immigration?\n a. We should keep our coubntry closed for uninvited foreigners \n b. More diversity can improve our society, and we need to protect them from employer exploitation; \n c. Eliminate all restrictions on immigration \n d. Undocumented immigrants should be granted a legal status which includes the chance to become US citizens\n Answer: ", ""},
        {"\n7. What is your opinion about taxes?\n a. We need lower taxes for businesses; \n b. We need increase taxes for wealthy people; \n c. Increase taxes for reach, but keep it reasonable \n d. We need a new approach such a environmental taxes\n Answer:", ""},
        {"\n8. What is your political party?\n a. Republican; \n b. Democrat; \n c. Independent \n d. Green \n Answer: ", ""},
    };

    string answersForProcessing[7];

    int arraySize = (sizeof surveyAnswers / sizeof surveyAnswers[0]);
    cout << "Welcome to the political survey! We have 8 questions for you about your political views. For each question type the answer number, such as a, b, c or d. Each question is supposed to have only one answer.\n";

    //Display all questions and inputs
    for (int i = 0; i < arraySize-1; i++) {

        cout << surveyAnswers[i][0];
        cin >> surveyAnswers[i][1];

        //Validate input

        while (isValid(surveyAnswers[i][1]) != true) {
            cout << "Wrong input! You should enter only one letter from the choice";
            cout << surveyAnswers[i][0];
            cin >> surveyAnswers[i][1];
        }

        //Add answers to an array for further processing
        answersForProcessing[i] = surveyAnswers[i][1];

    }


    //Before asking user about their party, the programm will try to make a guess

    string* calculatedData;
    calculatedData = letterMode(answersForProcessing);

    string guess = calculatedData[0];
    string answer = calculatedData[1];
    char isRight; // is guess correct

    //Making a guess

    cout << "\n Based on you previous answers, you might be a " << guess << "\n Press Y or y if it is correct, and n or N if guess is wrong: ";
    cin >> isRight;

    if (isRight == 'Y' || isRight == 'y') {
        cout << "\nThank you for participation!\n";
        surveyAnswers[7][1] = answer;
        processSurvey(guess, surveyAnswers);
    }

    else {
        cout << surveyAnswers[7][0];
        cin >> surveyAnswers[7][1];

        //Write survey data to file based on answer of last question

        if (surveyAnswers[7][1] == "a") {
            processSurvey("Republican", surveyAnswers);
        }
        else if (surveyAnswers[7][1] == "b") {
            processSurvey("Democrat", surveyAnswers);
        }

        else if (surveyAnswers[7][1] == "c") {
            processSurvey("Independent", surveyAnswers);
        }

        else {
            processSurvey("Green", surveyAnswers);
        }

    }

}




