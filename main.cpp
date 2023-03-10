#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struct Profile
{
    string full_name;
    bool sex;
    int group;
    int id;
    int grades[8];
    string date;
};

int countStudents(Profile students[]){
    int count = 0;
    for(int i = 0; i < 40; i++){
        if ((students[i].full_name).length()>1){
            count +=1;
        }
        else{
            return count;
        }
    }
}
void addProfile(Profile* students){
    Profile student;
    cout << "Enter name of student:\n";
    cin.get();
    getline(cin, student.full_name);
//    cin.get();
    cin.clear();
    cout << "Enter gender(0 - Female 1 - Male):\n";
    cin >> student.sex;

    cout << "Enter number of group:\n";
    cin >> student.group;
    cout << "Enter student id:\n";
    cin >> student.id;
    cout << "Enter grades of student:\n";
    for (int i=0; i<8;i++){
        cin >> student.grades[i];
        if (student.grades[i] == 2){
            cout << '\n' << "This student will be expelled. The profile will not be saved in the database.";
            return;
        }
    }
    cin.clear();
    time_t now = time(0);
    char* dt = ctime(&now);
    student.date = dt;
    students[countStudents(students)] = student;
}
void saveData(Profile student[]){
        ofstream database; // Создаем поток записи в файл
    database.open("C:\\Users\\vvlad\\CLionProjects\\practice2_1\\student.txt");
    if (!database.is_open()) {
        cout << '\n' << "Saving error!";
    }
    else
    {
        for(int i = 0; i< countStudents(student);i++) {
            database << student[i].full_name << ' ';
            database << student[i].sex << ' ' << student[i].group << ' ' << student[i].id << ' ';
            for (int g = 0; g < 8; g++)
                database << student[i].grades[g];
            database << endl;
        }
        cin.clear();
        database.close();
    }
}
void getStudentInfo(Profile S){
    cout << "Name:" <<S.full_name << endl;
    if(S.sex){
        cout <<"Male\n";
    }
    else{
        cout <<"Female\n";
    }
    cout << "Group number:" <<S.group << endl;
    cout << "Student id:" <<S.id << endl;
    cout << "Grades of student:\n";
    for (int i=0; i<8;i++){
        cout <<  S.grades[i] << " ";
    }
    cout << "\nRecord added " <<S.date;

}
void readDatabase(Profile* students){
    int k = 0;
    ifstream database;
database.open("C:\\Users\\vvlad\\CLionProjects\\practice2_1\\student.txt");
    if (!database.is_open()) {
        cout << '\n' << "Error! File isn't open";}
    else{
        string data;
        while (getline(database, data)) {
            Profile student;
            string sex, group, grades, id;
            int i = 0;
            int countSpace = 0;

             while (countSpace<3){
                 if (data[i]== ' '){
                     student.full_name += data[i];
                     countSpace += 1;
                     i += 1;

                 }
                 else {
                     student.full_name += data[i];
                     i += 1;
                 }
            }
             student.full_name.erase((student.full_name).length()-1);
            while (countSpace == 3){
                if (data[i]== ' '){
                    countSpace += 1;
                    i += 1;

                }
                else {
                    sex = data[i];
                    student.sex = stoi(sex);
                    i += 1;
                }
            }
            while (countSpace==4){
                if (data[i]== ' '){
                    countSpace += 1;
                    i += 1;
                }
                else {
                        group += data[i];
                        i += 1;

                }
            }
            if (group.length()==4){
                student.group = stoi(group);
            }
            while (countSpace==5) {
                if (data[i]== ' '){
                    countSpace += 1;
                    i += 1;
                }
                else {
                    id += data[i];
                    student.id = stoi(id);
                    i += 1;
                }
            }
            while (countSpace==6 && grades.length() !=8) {
                grades +=data[i];
                i+=1;
            }
            if (grades.length()==8){
                for(int g = 0; g < 8; g++){
                    student.grades[g] = stoi(string(1,grades[g]));
                }
            }
            time_t now = time(0);
            char* dt = ctime(&now);
            student.date = dt;

            students[k]=student;
            k+=1;
        }

        }
        cin.clear();
        database.close();

    }


void getStudents(Profile students[]){
    for(int i=0;i < countStudents(students);i++){
        getStudentInfo(students[i]);
        cout << "---------------------------------------\n";
    }
}
void getStudentsFromGroup(Profile students[]){
    int userNumberGroup;
    cout << "Enter number of group:\n";
    cin >> userNumberGroup;
    cout << "Students from " << userNumberGroup << " group:\n";
    cout << "---------------------------\n";
    for (int i = 0; i < 40; i++){
        if (students[i].group == userNumberGroup){
            getStudentInfo(students[i]);
            cout << "---------------------------\n";
        }
    }
}
void editProfile(Profile* students){
    int userChoice;
    int userNumberGroup;
    int userNumberId;
    cout << "Enter number of group:\n";
    cin >> userNumberGroup;
    cout << "---------------------------------------\n";
    cout << "Students from " << userNumberGroup << " group:\n";
    cout << "---------------------------------------\n";
    for (int i = 0; i < 40; i++){
        if (students[i].group == userNumberGroup){
            cout << students[i].id << ". " << students[i].full_name << "\n";
        }
    }
    cout << "---------------------------------------\n";
    cout << "Enter id of student:\n";
    cin >> userNumberId;
    int studentGlobalId;
    for (int i = 0; i < 40; i++){
        if ((students[i].group == userNumberGroup) && (students[i].id==userNumberId)){
            studentGlobalId = i;
            break;
        }
    }
    getStudentInfo(students[studentGlobalId]);
    while(true){
        cout << "---------------------------------------\n";
        cout << "Choose info to edit:\n0 - Stop editing\n1 - Full name\n2 - Sex\n3 - Group\n4 - Id\n5 - Grades\n";
        cin >> userChoice;
        switch(userChoice){
            case 0:
                cout << "---------------------------------------\n";
                getStudentInfo(students[studentGlobalId]);
                cout << "---------------------------------------\n";
                return;
            case 1:
                cout << "Enter new data:\n";
                cin.get();
                getline(cin, students[studentGlobalId].full_name);
                cin.clear();
                break;
            case 2:
                cout << "Enter new data:\n";
                cin >> students[studentGlobalId].sex;
                break;
            case 3:
                cout << "Enter new data:\n";
                cin >> students[studentGlobalId].group;
                break;
            case 4:
                cout << "Enter new data:\n";
                cin >> students[studentGlobalId].id;
                break;
            case 5:
                cout << "Enter new data:\n";
                for (int i=0; i<8;i++){
                    cin >> students[studentGlobalId].grades[i];
                }
                break;
        }
    }
}
float averageGrades(Profile student){
    float summMarks = 0;
    for (int j = 0; j < 8; j++){
        summMarks += student.grades[j];
    }
    return summMarks/8;
}

void sortAvg(Profile students[]){
    Profile studentsForSort[40];
    for(int i = 0; i< countStudents(students);i++){
        studentsForSort[i] = students[i];
    }
//    memcpy(studentsForSort,students, sizeof(studentsForSort));
//    memcpy(studentsForSort,students, countStudents(students)*sizeof(Profile));
    for (int i = 1; i <= countStudents(studentsForSort)-1; i++){
        for (int j = i; j > 0;j--){
            if (averageGrades(studentsForSort[j])< averageGrades(studentsForSort[j-1])){
                swap(studentsForSort[j-1], studentsForSort[j]);
            } else {
                continue;
            }
        }
    }
    cout << "\n---------------------------------------------";
    cout << "\nBest students by average value of marks:";
    cout << "\n---------------------------------------------\n";
    for (int i = countStudents(studentsForSort) - 1; i >= 0; i--){
        cout << (countStudents(studentsForSort)-i) << "." << " "<< studentsForSort[i].full_name <<" "<< averageGrades(studentsForSort[i]);
        cout << "\n---------------------------------------------\n";
    }
}
void getStudentId(Profile students[]){
    int userNumber;
    cout << "\n---------------------------------------------";
    cout << "\nEnter student id:";
    cout << "\n---------------------------------------------\n";
    cin >> userNumber;
    for(int i = 0; i< countStudents(students);i++){
        if (students[i].id==userNumber){
            getStudentInfo(students[i]);
            cout << "\n---------------------------------------------\n";
        }
    }
}
void countSex(Profile students[]){
    int countMale = 0;
    int countFemale = 0;
    for (int i = 0; i < countStudents(students); i++){
        if (students[i].sex) countMale+=1;
        else countFemale +=1;
    }
    cout << "\n---------------------------------------------";
    cout << "\nCount of male students: " <<countMale;
    cout << "\nCount of female students: " <<countFemale;
    cout << "\n---------------------------------------------\n";



}
void rateStudents(Profile students[]){
    Profile studentsGreat[countStudents(students)];
    Profile studentsGood[countStudents(students)];
    Profile studentsWell[countStudents(students)];
    int k = 0,f = 0,l = 0;
    for (int i = 0; i< countStudents(students);i++){
        bool flagGood = false;
        bool flagWell = false;
        for(int j = 0;j<8;j++){
            if (students[i].grades[j]==3) {
                studentsWell[k] = students[i];
                k+=1;
                flagWell = true;
                break;
            }
            if (students[i].grades[j]==4) flagGood = true;
        }
        if(flagGood && !flagWell){studentsGood[f] = students[i];f++;}
        if(!flagGood && !flagWell){studentsGreat[l] = students[i]; l++;}
    }
    cout << "---------------------------------------------\n";
    cout << "Students with great marks:\n";
    cout << "---------------------------------------------\n";
    for (int i = 0;i<l;i++) {
        cout << studentsGreat[i].full_name << " ";

        for (int j = 0; j < 8; j++) {
            cout << studentsGreat[i].grades[j] << " ";
        }
        cout << "\n";

    }
    cout << "---------------------------------------------\n";
    cout << "Students with good marks:\n";
    cout << "---------------------------------------------\n";

    for (int i = 0;i<f;i++) {
        cout << studentsGood[i].full_name << " ";

        for (int j = 0; j < 8; j++) {
            cout << studentsGood[i].grades[j] << " ";
        }
        cout << "\n";
    }
    cout << "---------------------------------------------\n";
    cout << "Students with well marks:\n";
    cout << "---------------------------------------------\n";
    for (int i = 0;i<k;i++) {
        cout << studentsWell[i].full_name << " ";

        for (int j = 0; j < 8; j++) {
            cout << studentsWell[i].grades[j] << " ";
        }
        cout << "\n";
    }
    cout << "---------------------------------------\n";

}
int main() {
    Profile students[40];
    readDatabase(students);
    int userChoice;
    while(true){
        cout <<"Choose the action:\n0 - Save and exit\n1 - Show all students\n2 - Add new record\n3 - Edit record\n4 - Get students of group"
               "\n5 - Show students ranking by marks\n6 - Show count of male/female students\n7 - Show separation by great/good/well marks\n8 - Show students by group id\n";
    cin >> userChoice;
    if(userChoice==0){
        saveData(students);
        break;
    }
        switch (userChoice) {
        case 1:
            getStudents(students);
            break;
        case 2:
            addProfile(students);
            break;
        case 3:
            editProfile(students);
            break;
        case 4:
            getStudentsFromGroup(students);
            break;
        case 5:
            sortAvg(students);
            break;
        case 6:
            countSex(students);
            break;
        case 7:
            rateStudents(students);
            break;
        case 8:
            getStudentId(students);
            break;
        default:
            cout <<"\nUnknown command!\n";
        }
    }
    system("pause");
}
