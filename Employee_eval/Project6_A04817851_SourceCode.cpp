/*
Matthew Hebert
A04817851
Project 6
*/

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

const int n = 3, numsem = 9, numyear = 3;

struct address
{
    string street;
    string city;
    string state;
    string zip;
};

struct semeval
{
    double eval[9];
};

struct comp_eval
{
    double compeval[3];
    double total;
    double average;
};

struct Employee
{
    string header[2];
    string e_name;
    string s_name;
    string e_id;
    string e_tele;
    address address;
    semeval e_evals;
    comp_eval comp_e_evals;
    double salary;
    double salraise;
    double salraiseindoll;
    double newsal;
    string letter[2];
    string note[2];
};


int inputData(ifstream &, ofstream &, int, Employee []);
int validateData(ofstream &, int, Employee []);
void FWE(int, Employee []);
void TAFWE(int, Employee []);
void SRinPercent(int, Employee []);
void Salary(int, Employee []);
void letter(ofstream &, int, Employee []);
void report(ofstream &, int, Employee []);

int main()
{
    ifstream fin;
    ofstream fout;
    fin.open("Project6_A04817851_inputfile.txt");
    fout.open("Project6_A04817851_outputfile.txt");
    Employee emp[n];
    int validatenum;

    for (int r = 0; r < n; r++)
    {
        validatenum = inputData(fin, fout, r, emp);
        if (validatenum == 1)
            continue;
        else if (validatenum == 2)
            break;
        FWE(r, emp);
        TAFWE(r, emp);
        SRinPercent(r, emp);
        Salary(r, emp);
        report(fout, r, emp);
    }
    fin.close();
    fout.close();
}


int inputData(ifstream &fin, ofstream &fout, int r, Employee emp[])
{
    int validate;

//get employee string info
    if(r == 0)
    {
        getline(fin, emp[r].letter[0]);
        getline(fin, emp[r].letter[1]);
    }

    getline(fin, emp[r].header[0]);
    getline(fin, emp[r].header[1]);
    getline(fin, emp[r].e_name);
    getline(fin, emp[r].s_name);
    getline(fin, emp[r].e_id);
    getline(fin, emp[r].e_tele);
    getline(fin, emp[r].address.street, ',');
    getline(fin, emp[r].address.city, ',');
    getline(fin, emp[r].address.state, ',');
    getline(fin, emp[r].address.zip);

//get employee evaluations
    for(int e = 0; e < numsem; e++)
    {
        fin >> emp[r].e_evals.eval[e];
    }

//get salary
    fin >> emp[r].salary;

//get discrepancy notes
    fin.ignore();
    getline(fin, emp[r].note[0]);
    getline(fin, emp[r].note[1]);

//validate data
    validate = validateData(fout, r, emp);
    if (validate == 1)
        return 1;
    else if (validate == 2)
        return 2;
}

int validateData(ofstream &fout, int r, Employee emp[])
{
//test warning length
    if (!(emp[0].letter[0].length() == 39))
    {
        cout << "ERROR. ";
        fout << "ERROR. PLEASE DO NOT EDIT WARNING MESSAGES." << endl;
        return 1;
    }

//test congrats length
    if (!(emp[0].letter[1].length() == 42))
    {
        cout << "ERROR. ";
        fout << "ERROR. PLEASE DO NOT EDIT CONGRATS MESSAGE." << endl;
        return 1;
    }

//test header lengths
    if (!(emp[r].header[0].length() == 34))
    {
        cout << "ERROR. ";
        fout << "ERROR. PLEASE DO NOT EDIT HEADERS." << endl;
        return 1;
    }

    if (!(emp[r].header[1].length() == 66))
    {
        cout << "ERROR. ";
        fout << "ERROR. PLEASE DO NOT EDIT HEADERS." << endl;
        return 1;
    }

//test user info lengths
    if (!(emp[r].e_name.length() > 1 && emp[r].e_name.length() < 50))
    {
        cout << "ERROR. ";
        fout << "ERROR. PLEASE ENTER A VALID EMPLOYEE NAME." << endl;
        return 1;
    }

    if (!(emp[r].s_name.length() > 1 && emp[r].s_name.length() < 50))
    {
        cout << "ERROR. ";
        fout << "ERROR. PLEASE ENTER A VALID SUPERVISOR NAME." << endl;
        return 1;
    }

    if (!(emp[r].e_id.length() > 1 && emp[r].e_id.length() < 20))
    {
        cout << "ERROR. ";
        fout << "ERROR. PLEASE ENTER A VALID EMPLOYEE ID." << endl;
        return 1;
    }

    if (!(emp[r].e_tele.length() > 1 && emp[r].e_tele.length() < 20))
    {
        cout << "ERROR. ";
        fout << "ERROR. PLEASE ENTER A VALID EMPLOYEE TELEPHONE NUMBER." << endl;
        return 1;
    }

    if (!(emp[r].address.street.length() > 1 && emp[r].address.street.length() < 33))
    {
        cout << "ERROR. ";
        fout << "ERROR. PLEASE ENTER A VALID STREET." << endl;
        return 1;
    }

    if (!(emp[r].address.city.length() > 1 && emp[r].address.city.length() < 20))
    {
        cout << "ERROR. ";
        fout << "ERROR. PLEASE ENTER A VALID CITY." << endl;
        return 1;
    }

    if (!(emp[r].address.state.length() > 1 && emp[r].address.state.length() < 15))
    {
        cout << "ERROR. ";
        fout << "ERROR. PLEASE ENTER A VALID STATE." << endl;
        return 1;
    }

    if (!(emp[r].address.zip.length() > 1 && emp[r].address.zip.length() < 10))
    {
        cout << "ERROR. ";
        fout << "ERROR. PLEASE ENTER A VALID ZIP." << endl;
        return 1;
    }

//test evaluation values
    for(int g = 0; g < numsem; g++)
    {
        if (!(emp[r].e_evals.eval[g] > 0 && emp[r].e_evals.eval[g] < 150))
        {
            cout << "ERROR. ";
            fout << "ERROR. PLEASE ENTER A VALID GRADE FOR SEMESTER " << g+1;
            return 2;
        }
    }

//test salary values
    if(emp[r].salary < 0)
    {
        cout << "ERROR. ";
        fout << "ERROR. PLEASE ENTER A VALID SALARY.";
        return 2;
    }

//test discrepancy note lengths
    if(!(emp[r].note[0].length() > 85 && emp[r].note[0].length() < 150))
    {
        cout << "ERROR. ";
        fout << "ERROR. PLEASE VALIDATE THE DISCREPANCY NOTE.";
        return 1;
    }
    if(!(emp[r].note[1].length() > 59 && emp[r].note[1].length() < 125))
    {
        cout << "ERROR. ";
        fout << "ERROR. PLEASE VALIDATE THE DISCREPANCY NOTE.";
        return 1;
    }
}

void FWE(int r, Employee emp[])
{
// declare weights
    const double fallw = 0.39, springw = 0.37, summerw = 0.24;

//calculate final weighted evaluations
    emp[r].comp_e_evals.compeval[0] = (emp[r].e_evals.eval[0]*springw)
                                     +(emp[r].e_evals.eval[1]*summerw)
                                     +(emp[r].e_evals.eval[2]*fallw);

    emp[r].comp_e_evals.compeval[1] = (emp[r].e_evals.eval[3]*springw)
                                     +(emp[r].e_evals.eval[4]*summerw)
                                     +(emp[r].e_evals.eval[5]*fallw);

    emp[r].comp_e_evals.compeval[2] = (emp[r].e_evals.eval[6]*springw)
                                     +(emp[r].e_evals.eval[7]*summerw)
                                     +(emp[r].e_evals.eval[8]*fallw);


}

void TAFWE(int r, Employee emp[])
{
//calculate tfwe
    emp[r].comp_e_evals.total = emp[r].comp_e_evals.compeval[0]
                               +emp[r].comp_e_evals.compeval[1]
                               +emp[r].comp_e_evals.compeval[2];
//calculate afwe
    emp[r].comp_e_evals.average = emp[r].comp_e_evals.total/3;

}

void SRinPercent(int r, Employee emp[])
{
//calculate sr in percent
    if (emp[r].comp_e_evals.average < 75)
        emp[r].salraise = 0;
    else if (emp[r].comp_e_evals.average > 75 && emp[r].comp_e_evals.average <= 80)
        emp[r].salraise = 1;
    else if (emp[r].comp_e_evals.average > 80 && emp[r].comp_e_evals.average <= 90)
        emp[r].salraise = 3;
    else if (emp[r].comp_e_evals.average > 90 && emp[r].comp_e_evals.average <= 100)
        emp[r].salraise = 5;
    else
        emp[r].salraise = 10;
}

void Salary(int r, Employee emp[])
{
//calculate sr in dollars
    emp[r].salraiseindoll = (emp[r].salraise * 0.01) * emp[r].salary;

//calculate salary with raise
    emp[r].newsal = emp[r].salraiseindoll + emp[r].salary;

}

void letter(ofstream &fout, int r, Employee emp[])
{
//write warning / congrats messages
    if (emp[r].comp_e_evals.average < 70)
        fout << endl << emp[0].letter[0] << endl;
    else if (emp[r].comp_e_evals.average >= 95)
        fout << endl << emp[0].letter[1] << endl;
}

void report(ofstream &fout, int r, Employee emp[])
{
    fout << setw(50) << emp[r].header[0] << endl;
    fout << emp[r].header[1] << endl << endl;
    fout << setw(34) << "Name of the Employee:" << setw(9) << " " << emp[r].e_name << endl;
    fout << setw(34) << "Name of the Supervisor:" << setw(9) << " " << emp[r].s_name << endl;
    fout << setw(34) << "Employee ID:" << setw(9) << " " << emp[r].e_id << endl;
    fout << setw(34) << "Telephone Number:" << setw(9) << " " << emp[r].e_tele << endl;
    fout << setw(34) << "Address:" << setw(9) << " " << emp[r].address.street << ", " << emp[r].address.city << ", " << emp[r].address.state << ", " << emp[r].address.zip << endl;

//write evaluations
    for (int o = 0; o < numyear; o++)
    {
        if (o == 0)
        {
            fout << setw(34) << "Spring Semester Evaluation, 2011:" << setw(9) << " " << setprecision(2) << fixed << emp[r].e_evals.eval[0] << endl;
            fout << setw(34) << "Summer Semester Evaluation, 2011:" << setw(9) << " " << emp[r].e_evals.eval[1] << endl;
            fout << setw(34) << "Fall Semester Evaluation, 2011:" << setw(9) << " " << emp[r].e_evals.eval[2] << endl;
        }
        else if (o == 1)
        {
            fout << setw(34) << "Spring Semester Evaluation, 2012:" << setw(9) << " " << emp[r].e_evals.eval[3] << endl;
            fout << setw(34) << "Summer Semester Evaluation, 2012:" << setw(9) << " " << emp[r].e_evals.eval[4] << endl;
            fout << setw(34) << "Fall Semester Evaluation, 2012:" << setw(9) << " " << emp[r].e_evals.eval[5] << endl;
        }
        else if (o == 2)
        {
            fout << setw(34) << "Spring Semester Evaluation, 2013:" << setw(9) << " " << emp[r].e_evals.eval[6] << endl;
            fout << setw(34) << "Summer Semester Evaluation, 2013:" << setw(9) << " " << emp[r].e_evals.eval[7] << endl;
            fout << setw(34) << "Fall Semester Evaluation, 2013:" << setw(9) << " " << emp[r].e_evals.eval[8] << endl;
        }
    }

//write computed evaluations
    fout << setw(34) << "Final Weighted Evaluation, 2011:" << setw(9) << " " << emp[r].comp_e_evals.compeval[0] << endl;
    fout << setw(34) << "Final Weighted Evaluation, 2012:" << setw(9) << " " << emp[r].comp_e_evals.compeval[1] << endl;
    fout << setw(34) << "Final Weighted Evaluation, 2013:" << setw(9) << " " << emp[r].comp_e_evals.compeval[2] << endl;
    fout << setw(34) << "Total Final Weighted Evaluation:" << setw(9) << " " << emp[r].comp_e_evals.total << endl;
    fout << setw(34) << "Average Final Weighted Evaluation:" << setw(9) << " " << emp[r].comp_e_evals.average << endl;
    fout << setw(34) << "Current Salary:" << setw(9) << " " << "$" << emp[r].salary << endl;
    fout << setw(34) << "Salary Raise in %:" << setw(9) << " " << emp[r].salraise << "%" << endl;
    fout << setw(34) << "Salary Raise in Dollars:" << setw(9) << " " << "$" << emp[r].salraiseindoll << endl;
    fout << setw(34) << "Salary in Dollars with Raise:" << setw(9) << " " << "$" << emp[r].newsal << endl;

//write warning/congrats message
    letter(fout, r, emp);

//write discrepancy note
    fout << endl << emp[r].note[0] << endl;
    fout << "\t" << emp[r].note[1] << endl << endl << endl;
}
