#include<iostream>
#include<fstream>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include<ctime>

using namespace std;

class Transaction{
private:
    int amount;

    time_t now;
    char dt[40];

    int senderAccountNumber;
    char senderFname[20], senderLname[20];

    int recieverAccountNumber;
    char recieverFname[20], recieverLname[20];

public:
    Transaction(){
        amount=0;
        senderAccountNumber=0;
        recieverAccountNumber=0;
        strcpy(senderFname,"");
        strcpy(senderLname,"");
        strcpy(recieverFname,"");
        strcpy(recieverLname,"");
        strcpy(dt,"");
    }


    int getTransactionData(int amt, int san, char* sfname, char* slname, int ran, char* rfname, char* rlname){
        amount=amt;
        senderAccountNumber=san;
        recieverAccountNumber=ran;
        strcpy(senderFname, sfname);
        strcpy(senderLname, slname);
        strcpy(recieverFname, rfname);
        strcpy(recieverLname, rlname);

        now=time(0);
        strcpy(dt,ctime(&now));
    }

    int storeTransaction();


    void displayTransaction();
    void displayAllTransactions(); //for manager
    int displayMyAllTransactions(int);  //for customer
};

int Transaction::displayMyAllTransactions(int accno){
    ifstream file;
    file.open("Transaction.dat",ios::binary|ios::in);
    if(!file){
        cout<<"Transaction.dat not opened \n";
        return(0);
    }

    file.read((char*)this,sizeof(*this));
    while(!file.eof()){
        if(senderAccountNumber == accno || recieverAccountNumber == accno){
            displayTransaction();
        }
        file.read((char*)this,sizeof(*this));
    }
    file.close();
    return(1);
}

void Transaction::displayAllTransactions(){
    ifstream file;
    file.open("Transaction.dat",ios::binary|ios::in);
    if(!file){
        cout<<"Transaction.dat not opened \n";
        return;
    }

    file.read((char*)this,sizeof(*this));
    while(!file.eof()){
        displayTransaction();
        file.read((char*)this,sizeof(*this));
    }
    file.close();

}

void Transaction::displayTransaction(){
    cout<<"T--------------------------------------------------------------------------------------------T\n";
    cout<<"Transaction done at : "<<dt;
    cout<<"Amount : "<<amount<<"\n";
    cout<<"Sender Name : "<<senderFname<<" "<<senderLname<<"\tSender Account No. :"<<senderAccountNumber<<"\n";
    cout<<"Receiver Name : "<<recieverFname<<" "<<recieverLname<<"\tReceiver Account No. :"<<recieverAccountNumber<<"\n";
    cout<<"T--------------------------------------------------------------------------------------------T\n";
}


int Transaction::storeTransaction(){
    ofstream file;
    file.open("Transaction.dat",ios::binary|ios::app);
    if(!file){
        cout<<"Transaction.dat not opened \n";
        return(0);
    }
    file.write((char*)this,sizeof(*this));
    file.close();
    return(1);
}

class Account{
private:
      int accNumber, accBalance;
      char fname[20], lname[20];
      char accType[20];
      char password[20];

      time_t now;
      char dateOfCreation[40];

public:
    Account(){
        accBalance=0;
        accNumber=0;
        strcpy(fname,"");
        strcpy(lname,"");
        strcpy(accType,"none");
        strcpy(password,"password");
        strcpy(dateOfCreation,"");
    }


    void setAccountDefault(){
        accBalance=0;
        accNumber=0;
        strcpy(fname,"");
        strcpy(lname,"");
        strcpy(accType,"none");
        strcpy(password,"password");
        strcpy(dateOfCreation,"");
    }

    char* returnFirstName(){
        return(fname);
    }
    char* returnLastName(){
        return(lname);
    }
    int returnAccountNumber(){
        return(accNumber);
    }
    char* returnPassword(){
        return(password);
    }

    Account returnAccountByAccNo(int);

    void showData();

    bool isAccountExist(int);

    //store function inside inputAccountData
    int inputAccountData();
    int storeAccountData();

    void viewAllAccount();

    int searchAccountByFirstName(char*);
    int searchAccountByAccNo(int);
    int searchAccount();

    int deleteAccount(int,char*);

    int updateAccountData(int);
    int getAccountUpdateData();

    void currentAccountGuidelines();
    void savingAccountGuidelines();

    int debit(int,int); //goes out, amount deduct
    int credit(int,int); //comes in, amount added

    int changeAccountPassword(int);

};

int Account::changeAccountPassword(int accno){
    cout<<"Welcome to CHANGE ACCOUNT PASSSWORD\n";
    char newPW[20];
    cout<<"Enter new password : ";
    cin.ignore();
    cin.getline(newPW,20);
    strcpy(this->password,newPW);
    int n=0;
    n=updateAccountData(accno);
    return(n);
}

bool Account::isAccountExist(int accno){
    ifstream file;
    Account temp;

    bool exist=false;
    file.open("Account.dat",ios::in|ios::binary);
    if(file){
        file.read((char*)&temp,sizeof(temp));
        while(!file.eof()){
            if(temp.accNumber==accno){
                exist=true;
                break;
            }
            file.read((char*)&temp,sizeof(temp));
        }
        file.close();
    }

    return(exist);
}


void Account::currentAccountGuidelines(){
    cout<<"Guidelines for Current Account : \n";
    cout<<"1. No limits on number of transaction per month. \n";
    cout<<"2. Maximum limit of withdraw in one day will be $25,000 . \n";
    cout<<"3. Maximum limit of deposit in one day will be $50,000 . \n";
    cout<<"4. Minimum balance requirement $5000. \n";
    cout<<"5. Fine on not maintaining minimum balance is $20 per day. \n";
    cout<<"6. If account balance will be NILL or zero for a month, then your account services will be blocked. \n";
}


void Account::savingAccountGuidelines(){
    cout<<"Guidelines for Current Account : \n";
    cout<<"1. No limits on number of transaction per month. \n";
    cout<<"2. Maximum limit of withdraw in one day will be $10,000 . \n";
    cout<<"3. Maximum limit of deposit in one day will be $20,000 . \n";
    cout<<"4. If account balance will be NILL or zero for a year, then your account services will be blocked. \n";
}


int Account::searchAccount(){
    char choice;
    char c;

    again:
    system("cls");
    cout<<"----------Welcome to Search Account Process----------\n";
    cout<<"Press 1 for search by Name \nPress 2 for search by Account Number \nPress any other key for return at main menu"<<endl;
    cin>>choice;
    switch(choice){
    case '1':
        char name[20];
        cout<<"Search By Name----------------------------------------"<<endl;
        cout<<"Please enter name here : ";
        cin.ignore();
        cin.getline(name, 19);
        searchAccountByFirstName(name);

        cout<<"\nPress a to search again or Press any other key for exit search process : ";
        cin>>c;
        if(c=='a'){
            goto again;
        }

        break;

    case '2':
        int acc;
        cout<<"Search By Account Number----------------------------------------"<<endl;
        cout<<"Please enter account number here : ";
        cin>>acc;
        searchAccountByAccNo(acc);

        cout<<"\nPress a to search again or Press any other key for exit search process : ";
        cin>>c;
        if(c=='a'){
            goto again;
        }else{
            goto endOfSearch;
        }

        break;

    default:
        cout<<"You are now redirecting to main menu..............."<<endl;
        getch();
     }

    endOfSearch:
    return 1;

}


int Account::searchAccountByFirstName(char *name){
    ifstream myfile;
    int count=0;

    myfile.open("Account.dat",ios::in|ios::binary);
    if(!myfile){
        cout<<"file not opened"<<endl;
    }
    else{
        myfile.read((char*)this, sizeof(*this));
        while(!myfile.eof()){
            if(!strcmp(name,fname)){
                cout<<"-> record found with First Name : "<<fname<<"\n";
                showData();
                count++;
                break;
            }
            myfile.read((char*)this, sizeof(*this));
        }
        myfile.close();
      }

      if(count==0){
        cout<<"No such record found with First Name : "<<fname<<"\n";
      }

      return(count);
}


int Account::searchAccountByAccNo(int no){
    ifstream myfile;
    int count=0;

    myfile.open("Account.dat",ios::in|ios::binary);
    if(!myfile){
        cout<<"file not opened"<<endl;
    }
    else{
        myfile.read((char*)this, sizeof(*this));
        while(!myfile.eof()){
            if(no == accNumber){
                cout<<"-> Record found with Account Number : "<<no<<"\n";
                showData();
                count++;
                break;
            }
            myfile.read((char*)this, sizeof(*this));
        }
        myfile.close();
    }

    if(count==0){
        cout<<"-> No such record found with Account Number : "<<no<<"\n";
    }

    return(count);
}


Account Account::returnAccountByAccNo(int no){
    Account temp;
    ifstream file;
    bool found=false;

    file.open("Account.dat",ios::in|ios::binary);
    if(!file){
        cout<<"Account.dat file not opened \n";
        return(temp);
    }
    file.read((char*)&temp,sizeof(temp));
    while(!file.eof()){
        if(no == temp.returnAccountNumber()){
            found=true;
            break;
        }
        file.read((char*)&temp,sizeof(temp));
    }
    file.close();

    if(!found){
        temp.setAccountDefault();
    }

    return(temp);
}


void Account::showData(){
  cout<<"$-------------------------------$"<<"\n";
  cout<<"Account No. : "<<accNumber<<"\n";
  cout<<"Name : "<<fname<<" "<<lname<<"\n";
  cout<<"Account Balance : "<<accBalance<<"\n";
  cout<<"Account Type : "<<accType<<"\n";
  cout<<"Account Password : "<<password<<"\n";
  cout<<"Creation Time : "<<dateOfCreation;
  cout<<"$-------------------------------$"<<"\n";
 }


void Account::viewAllAccount(){
  ifstream myFile;

  myFile.open("Account.dat", ios::in|ios::binary);
  if(!myFile)
    cout<<"file not opened"<<endl;
  else{
    myFile.read((char*)this, sizeof(*this));
    while(!myFile.eof()){
        showData();
        myFile.read((char*)this, sizeof(*this));
    }
    myFile.close();
  }
}


int Account::storeAccountData(){
    ofstream file;

    if(accNumber==0 && strcmp(fname,"")==0){
        cout<<"details not provided, So data not stored"<<endl;
        return 0;
    }

    time_t now = time(0);
    strcpy(dateOfCreation,ctime(&now));
    file.open("Account.dat",ios::app|ios::binary);
    file.write((char*)this, sizeof(*this));

    file.close();
    return 1;
}


int Account::inputAccountData(){

    fillInputAgain:

    system("cls");
    cout<<"----------Welcome to Account Creation Process----------"<<endl;

    int ret=0;
    char ch;

    cout<<"Please specify the type of your account below : "<<endl;
    cout<<"Press 1 for CURRENT ACCOUNT \nPress 2 for SAVING ACCOUNT \nPress any other key for cancel account creation \n";
    cin>>ch;
    switch(ch){
    case '1':
        strcpy(accType,"CURRENT ACCOUNT");
        currentAccountGuidelines();
        break;

    case '2':
        strcpy(accType,"SAVING ACCOUNT");
        savingAccountGuidelines();
        break;

    default:
        cout<<"---Account creation is cancelled and now you are redirected to main menu--- \n";
        ret=0;
        goto cancel;
    }

    typeAccountNumberAgain:
    cout<<"Enter Account Number : ";
    cin>>accNumber;


    //check account number function

    if(isAccountExist(accNumber)){
        char ise;
        cout<<"Account with Account Number : "<<accNumber<<" already created. Try another.\nNote - Account Numbers are identicals and no two accounts with same number generated.\n";
        cout<<"Press a for type Account Number Again.\nPress any other key for cancellation of the Account Creation Process \n";
        cin>>ise;
        if(ise=='a'){
            goto typeAccountNumberAgain;
        }else{
            goto cancel;
        }

    }else{

        cin.ignore();

        cout<<"Enter First Name : ";
        cin.getline(fname,20);

        cout<<"Enter Last Name : ";
        cin.getline(lname,20);

        cout<<"Enter Password : ";
        cin.getline(password,20);


        int firstDeposit;
        if(ch=='1'){
            depositCurrentAgain:
            cout<<"Please type deposit the amount of Rs.5000 or above :";
            accBalance=0;
            cin>>firstDeposit;
            if(firstDeposit<5000){
                char c1;
                cout<<"Press d deposit amount again or Press any other key for cancel the process of creating account \n";
                cin>>c1;
                if(c1=='d'){
                    goto depositCurrentAgain;
                }else{
                    ret=0;
                    goto cancel;
                }

            }else{
                accBalance=firstDeposit;
            }
            getch();

        }else if(ch=='2'){
            depositSavingAgain:
            cout<<"Please type deposit amount of Rs.500 or above :";
            accBalance=0;
            cin>>firstDeposit;
            if(firstDeposit<500){
                char c1;
                cout<<"Press d deposit amount again or Press any other key for cancel the process of creating account \n";
                cin>>c1;
                if(c1=='d'){
                    goto depositSavingAgain;
                }else{
                    ret=0;
                    goto cancel;
                }

            }else{
                accBalance=firstDeposit;
            }
            getch();
        }

        cout<<"\nCONFIRMATION MESSAGE : \nCheck the information below : \n";
        showData();

        char c;
        cout<<"Press c for confirm the above information \nPress a for fill info again \nPress any other key for cancelling whole process \n";
        cin>>c;
        switch(c){
        case 'c':
            ret=1;
            break;

        case 'a':
            goto fillInputAgain;
            break;

        default:
            cout<<"account not created \n";
            ret=0;
        }

    }

    cancel:
    return(ret);
}


int Account::deleteAccount(int accno,char* pw){
    ifstream fin;
    ofstream fout;
    int count=0;

    fin.open("Account.dat",ios::in|ios::binary);
    if(!fin){
        cout<<"File not found!!!"<<endl;
        return(0);
    }

    fout.open("tempfile.dat",ios::out|ios::binary|ios::trunc);
    fin.read((char*)this, sizeof(*this));
    while(!fin.eof()){
        if(accno== accNumber && strcmp(pw,password)==0){
            count++;
        }else{
            fout.write((char*)this,sizeof(*this));
        }
        fin.read((char*)this, sizeof(*this));
    }
    fin.close();
    remove("Account.dat");
    fout.close();
    rename("tempfile.dat","Account.dat");


    if(count==0){
        cout<<"Deletion Not Processed.\n";
    }else{
        cout<<"Account Number : "<<accno<<" Deleted \n"<<count<<" records deleted.\n";
    }

    setAccountDefault();
    return(count);
}


int Account::updateAccountData(int accno){
    fstream myfile;
    Account temp;
    int n=0;

    myfile.open("Account.dat",ios::in|ios::out|ios::ate|ios::binary);
    if(!myfile){
        cout<<"Account.dat file not opened"<<endl;
        return(0);
        //means no update
    }

    myfile.seekg(0);
    myfile.read((char*)&temp, sizeof(temp));
    while(!myfile.eof()){
        if(accno == temp.accNumber){
            long pos=myfile.tellp();
            myfile.seekp(pos - sizeof(*this));
            myfile.write((char*)this,sizeof(*this));

            n=1;
            //means updated
            break;
        }
        myfile.read((char*)&temp, sizeof(temp));
    }
    myfile.close();

    return(n);
}


int Account::getAccountUpdateData(){

  char tempFname[20],tempLname[20],tempPassword[20];
  int c=0;

  cout<<"Type if you want to change or leave it if you don't \n";
  cin.ignore();

  cout<<"Enter New First Name : ";
  cin.getline(tempFname,20);

  cout<<"Enter New Last Name : ";
  cin.getline(tempLname,20);

  cout<<"Enter New Password : ";
  cin.getline(tempPassword,20);

  if(strcmp(tempFname,"")!=0){
    strcpy(fname,tempFname);
    c++;
  }
  if(strcmp(tempLname,"")!=0){
    strcpy(lname,tempLname);
    c+=2;
  }
  if(strcmp(tempPassword,"")!=0){
    strcpy(password,tempPassword);
    c+=4;
  }


  switch(c){
  case 0:
    cout<<"Nothing typed. Therefore no updation will take place. \n";
    break;
  case 1:
    cout<<"FirstName changed. Therefore updation will take place. \n";
    break;
  case 2:
    cout<<"LastName changed. Therefore updation will take place. \n";
    break;
  case 3:
    cout<<"FirstName & LastName changed. Therefore updation will take place. \n";
    break;
  case 4:
    cout<<"Password changed. Therefore updation will take place. \n";
    break;
  case 5:
    cout<<"FirstName & Password changed. Therefore updation will take place. \n";
    break;
  case 6:
    cout<<"LastName & Password changed. Therefore updation will take place. \n";
    break;
  case 7:
    cout<<"FirstName, LastName & Password changed. Therefore updation will take place. \n";
    break;
  }

  return(c);
}


int Account::debit(int amt,int accno){
    //amount deduct
    int n = 0;
    accBalance-=amt;

    n=updateAccountData(accno);

    return(n);
}


int Account::credit(int amt, int  accno){
    //amount add
    int n = 0;
    accBalance+=amt;

    n=updateAccountData(accno);

    return(n);
}



class Manager{
char managerPassword[20];

public:
    Manager(){
        strcpy(managerPassword,"");
    }

    void run(){
        if(validManager()){
            cout<<"Correct Password"<<endl;
            showManagerMenu();
        }else{
            cout<<"Wrong Password"<<endl;
        }
    }

    int changeManagerPassword(){
        int n=0;
        cout<<"Welcome to CHANGE MANAGER PASSSWORD\n";
        char newPW[20];
        cout<<"Enter new password : ";
        cin.ignore();
        cin.getline(newPW,20);
        strcpy(this->managerPassword,newPW);

        remove("ManagerData.txt");

        ofstream file;
        file.open("ManagerData.txt",ios::out);
        if(file){
            file<<newPW;
            n++;
            file.close();
        }

        return(n);

    }

    bool validManager(){
        char pw[20];
        bool flag = false;

        cout<<"Enter Manager Password : ";
        cin.ignore();
        cin.getline(pw,20);

        ifstream pwfile;
        pwfile.open("ManagerData.txt",ios::in);
        if(pwfile){
            pwfile.seekg(0, ios::beg);
            pwfile>>managerPassword;
            if(strcmp(pw,managerPassword)==0){
                flag=true;
            }
            pwfile.close();
        }else{
            cout<<"Password Not Verified due to some error.\n";
            flag= false;
        }

        return(flag);

    }

    char managerMenu(){
        char mainChoice;
        cout<<"Enter your choice: \n";
        cout<<"1. View All Accounts \n";
        cout<<"2. Create Account \n";
        cout<<"3. Update Account \n";
        cout<<"4. Search Account \n";
        cout<<"5. Delete Account \n";
        cout<<"6. Change Password \n";
        cout<<"7. Press Any Other Key For Exit \n";
        cin>>mainChoice;
        return(mainChoice);
    }

    void showManagerMenu(){
        Account c;

        while(1){
            cout<<"<-----WELCOME MANAGER TO ABC BANK MENU----->"<<endl;
            switch(managerMenu()){

            case '1':
                //view all account
                system("cls");
                cout<<"<---------------------------------------------->"<<endl;
                c.viewAllAccount();
                cout<<"<---------------------------------------------->"<<endl;
                getch();
                break;

            case '2':
                //store Account data
                if(c.inputAccountData()==1){
                    if(c.storeAccountData()==1){
                        cout<<"ACCOUNT CREATED & INFORMATION STORED SUCCESSFULLY \n";
                    }else{
                        cout<<"Some error occured. Info not stored. \n";
                    }
                }else{
                    cout<<"Input Data not get properly \n";
                }
                getch();
                break;

            case '3':
                //update data
                system("cls");
                cout<<"----------Welcome to Account Data Updation Process----------"<<endl;
                int accno;
                cout<<"Please enter account number : ";
                cin>>accno;
                if(c.isAccountExist(accno)){
                    cout<<"Note : You cannot update your account number. \n";
                    cout<<"Type new data below :- "<<endl;
                    if(c.getAccountUpdateData()){
                        if(c.updateAccountData(accno)){
                            cout<<"Data Updated Successfully \n";
                        }else{
                            cout<<"Data not updated due to some err in updateAccountData() fn.\n";
                        }
                    }
                }else{
                    cout<<"No account exist with Account Number : "<<accno<<"\n";

                }
                cout<<"Press any key to return to main menu \n";
                getch();
                break;

            case '4':
                //search data
                system("cls");
                c.searchAccount();
                getch();
                break;

            case '5':
                //delete data
                system("cls");
                cout<<"----------Welcome to Delete Account Process----------"<<endl;
                int no;
                char pw[20];
                cout<<"Please enter ACCOUNT NUMBER : ";
                cin>>no;
                cin.ignore();
                cout<<"Type ACCOUNT PASSWORD carefully : ";
                cin.getline(pw,19);
                c.deleteAccount(no,pw);
                getch();
                break;


            case '6':
                //change password
                system("cls");
                if(changeManagerPassword()){
                    cout<<"Password Changed ";
                }else{
                    cout<<"Password Not Changed ";
                }
                getch();
                break;


            default:
                cout<<"Thanks for using."<<endl;
                exit(0);

            }

            system("cls");

        }
    }

};



class Customer{
    int customerAccountNumber;
    char customerAccountPassword[20];
    Account ac;
public:

    void viewMyAccount(){
        system("cls");
        ac.showData();
    }

    //transaction file creation
    int sendMoney(){
        int amount, toAcountNumber, fromAccountNo;
        Account to;
        Account *from;

        cout<<"WELCOME TO SEND MONEY SECTION \n";

        cout<<"Type the amount you want to send :";
        cin>>amount;
        cout<<"Type the Account Number to which you want to send money :";
        cin>>toAcountNumber;

        from = &ac;
        fromAccountNo = from->returnAccountNumber();

        to = to.returnAccountByAccNo(toAcountNumber);


        if(to.returnFirstName()=="" && to.returnAccountNumber()==0){
            cout<<"No such user found with account number : "<<toAcountNumber<<" . \n";
        }else{
            char ch;
            cout<<"Press c to confirm \nPress any other key for cancellation \n";
            cin>>ch;
            if(ch=='c'){
                int sent, recieved;

                sent = from->debit(amount, from->returnAccountNumber());
                recieved = to.credit(amount, to.returnAccountNumber());

                if(sent==1 && recieved==1){
                    Transaction t;
                    t.getTransactionData(amount, from->returnAccountNumber(),from->returnFirstName(), from->returnLastName(), to.returnAccountNumber(), to.returnFirstName() , to.returnLastName());
                    t.storeTransaction();

                    return(1);
                }

            }else{
                cout<<"Process Cancelled \n";
            }
        }

        return(0);
    }

    //manager func
    int deposit(){
        int amount=0,depo;

        cout<<"WELCOME TO DEPOSIT MONEY SECTION \n";

        cout<<"Type the amount you want to deposit : ";
        cin>>amount;

        depo = ac.credit(amount, ac.returnAccountNumber());

        if(depo){
            cout<<"The amount of Rs."<<amount<<" id credited in your account successfully. \n";

            ac=ac.returnAccountByAccNo(customerAccountNumber);
            return(1);
        }
        cout<<"Deposit operation failed. Please try again later. \n";
        return(0);

    }

    //manager func
    int withdraw(){
        int amount=0,withd;

        cout<<"WELCOME TO WITHDRAW MONEY SECTION \n";

        cout<<"Type the amount you want to withdraw : ";
        cin>>amount;

        withd = ac.debit(amount, ac.returnAccountNumber());

        if(withd){
            cout<<"The amount of Rs."<<amount<<" id debited from your account successfully. \n";

            ac=ac.returnAccountByAccNo(customerAccountNumber);
            //refresh

            return(1);
        }
        cout<<"Withdraw operation failed. Please try again later. \n";
        return(0);

    }


    int changeMyPassword(){
        system("cls");
        return(ac.changeAccountPassword(ac.returnAccountNumber()));
    }


    void run(){
        cout<<"Enter Account Number : ";
        cin>>customerAccountNumber;
        cout<<"Enter Account Password : ";
        cin.ignore();
        cin.getline(customerAccountPassword,20);

        if(isValidCustomer(customerAccountNumber,customerAccountPassword)){
            showCustomerMenu();
        }else{
            cout<<"No such account exist!!! \n";
        }
    }

    void showTransactions(){
        system("cls");
        Transaction t;
        t.displayMyAllTransactions(ac.returnAccountNumber());
    }

    bool isValidCustomer(int accNo, char* accPw){
        ifstream fin;
        Account temp;
        bool flag=false;
        fin.open("Account.dat",ios::in|ios::binary);
        if(!fin){
            cout<<"Account.dat file not opened \n";
            return(flag);
        }

        fin.read((char*)&temp,sizeof(temp));
        while(!fin.eof()){
            if( accNo == temp.returnAccountNumber() && strcmp(accPw, temp.returnPassword()) == 0){
                flag=true;
                ac = temp;
                break;
            }

            fin.read((char*)&temp,sizeof(temp));
        }
        fin.close();

        return(flag);
    }



    char customerMenu(){
        char mainChoice;
        cout<<"<-----WELCOME "<<ac.returnFirstName()<<" "<<ac.returnLastName()<<" TO ABC BANK's MENU----->"<<endl;
        cout<<"Enter your choice: \n";
        cout<<"1. View My Account \n";
        cout<<"2. Send Money \n";
        cout<<"3. Check Transactions \n";
        cout<<"4. Change Password \n";
        cout<<"5. Press Any Other Key For Exit \n";
        cin>>mainChoice;
        return(mainChoice);
    }


    void showCustomerMenu(){
        while(1){
            switch(customerMenu()){
            case '1':
                //view account case
                viewMyAccount();
                cout<<"Now press any key to return Main Menu \n";
                getch();
                break;

            case '2':
                //send money
                int sent;
                sent = sendMoney();
                if(sent){
                    cout<<"Money transferred successfully \n";
                }else{
                    cout<<"Money transferred failed \n";
                }

                cout<<"Now press any key to return Main Menu \n";
                getch();
                break;

            case '3':
                //check passbook
                showTransactions();
                getch();
                break;

            case '4':
                //change pw
                if(changeMyPassword()){
                    cout<<"Password Changed";
                }else{
                    cout<<"Password Change Failed";
                }
                getch();
                break;

            default:
                cout<<"Thanks "<<ac.returnFirstName()<<" "<<ac.returnLastName()<<" for using our banking app.";
                getch();
                exit(0);

            }

            system("cls");
        }
    }


};




int main(){
    Manager m;
    Customer c;

    char ch;
    for(;;){
        cout<<"WELCOME TO LCOM BANKING MAIN MENU \n";
        cout<<"Choose your module from below : \n";
        cout<<"1. Customer \n2. Manager \nPress any other key for exit.\nType here : ";
        cin>>ch;
        switch(ch){
        case '1':
            system("cls");
            c.run();
            getch();
            break;

        case '2':
            system("cls");
            m.run();
            getch();
            break;

        default:
            cout<<"Thanks for using. Visit again.";
            exit(0);
        }

        system("cls");
    }




    return 0;
}
