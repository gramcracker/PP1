// basic file operations
#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <sstream>
#include <iomanip>

using namespace std;

class student
{
private:
    vector<float> grades;
    string fname = "";
    string lname = "";
public:
    student(string f, string l)
    {
        fname = f;
        lname = l;
    }
    
    void putGrade(float n){
        grades.push_back(n);
    }

    float getAverage(){
        auto n = grades.size(); 
        float average = 0.0f;
        if ( n != 0) {
            average = std::accumulate( grades.begin(), grades.end(), 0.0) / n; 
        }
        return average;
    }

    float getMax(){
        float max = grades.at(0);
        for(auto i: grades){if(i>max)max = i;}
        return max;
    }

    string getName(){
        return fname+" "+lname;
    }

    char letterGrade(){
        float avg = getAverage();
        return (avg>=90)?('A'):((avg>=80)?('B'):((avg>=70)?('C'):((avg>=60)?('D'):('F')))); 
    }

    string GetTestGrades(){

        ostringstream os;
        for(auto i : grades){
            os<<fixed<<setprecision(2)<<i<<" ";
        }
        return os.str();
    }
};



using namespace std;

int main (int argc, char *argv[]) {
    if (argc <= 1){
        //if no file name then exit.
        cout<<"Must provide file name."<<endl;
        return 0;
    }
    //file handling.
    string fileName = argv[1];
    ifstream infile;
    infile.open (fileName);
    ofstream report;
    report.open("GradeReport.txt");

    //needlessly complicated for the sake of scalability and fun
    vector<student> students;
    int maxStudents = 30;
    int studentNum = 0;
    int numGrades = 5;
    float overallAverage= 0.0;
    float highestGrade= 0.0;
    string studentWithHighestGrade = "";
    vector <float> grades(5, 0.0);
    string fname = "";
    string lname = "";
    string input = "";

    //fill out the vector of students
    while (getline(infile, input))
    {
        istringstream iss(input);
        //create student
        studentNum ++;
        iss>>fname;
        iss>>lname;
        student s(fname, lname);
        //get students grades
        for(int i= 0; i<numGrades; i++){
            if(!iss) {break;}
            float n;
            iss>>n;
            s.putGrade(n);
        }
        //add to vector
        students.push_back(s);
    
    }

    //get the average for every student
    for (auto i : students){
        cout <<left << setw(30) << i.getName() <<" "<<i.GetTestGrades()<<" Average: "<<fixed<<setprecision(2)<<i.getAverage()<<", Letter grade: "<<i.letterGrade()<<endl;
        report<<left << setw(30) << i.getName() <<" "<<i.GetTestGrades()<<" Average: "<<fixed<<setprecision(2)<<i.getAverage()<<", Letter grade: "<<i.letterGrade()<<endl;
    }

    //get the overall average and highest grade
    if ( students.size() != 0) {
        highestGrade = students.at(0).getMax();
        for (auto i : students){
            float n = i.getMax();
            if (n > highestGrade) highestGrade = n;
            overallAverage += i.getAverage();
        }
        overallAverage /= students.size();
    }

    //print out overall average and highest grade
    report<<"Overall Average: "<<overallAverage<<", Highest Grade: "<<highestGrade<<""<<endl;

    infile.close();
    report.close();
    return 0;
}