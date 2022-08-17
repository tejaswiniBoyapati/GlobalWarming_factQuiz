//--------------------Libraries--------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//------------------------------------------------------------GLOBAL VARIABLES, DATATYPES------------------------------------------------------------

//=============IMP variables=============
int i,j,k;//loop variables
char choice;
int intChoice;//do while variable
int teachoice;//do while variable in teacher's menu
int n;//no. of students
int excellent;//excellent count
int male=0,female=0;//count of male and female
char tName[10],tRoll[5]="";

//=============Structures=============
int m=0,y=0;
struct topics
{
    char *question[15]; //to store questions by storing base addresss of first letter of long string
    char *answer[15]; //to store correct answers
    char *option[15][4]; //to store option of each question for Topic 1(Multiple Choice)
}topic1,topic2; //structure variables for topic 1(MCQ) and topic 2(One Word type subjective questions) quiz resp.

struct students
{
    struct generalinfo // structure for storing general info of students
    {
        char name[20];
        int rollno[5];
        char gender[2];
    };
    int *t1inp; //t1 wrong/correct answers
    int *t2inp; //for inputting correct and wrong answers given by the user in Topic 2 Quiz
    int t1marks,t2marks,total; //for storing the marks
    int remark;
};

struct generalinfo *details; //structure variable for stroing details for each student

//=============BST Somil variables=============

int sorted[50],inc=0;
int n;

struct node {
    int key;
    int c;
    struct node *left, *right;
};

//------------------------------------------------------------FUNCTION PROTOTYPES------------------------------------------------------------

void quizMain (void);
struct generalinfo info (struct generalinfo *details, int i);
struct students takeQuiz(struct students student[], int i);
void detailedQuiz (int,int,int);

struct node* insert(struct node* node, int key);
void inorder(struct node* root, struct students student[], int n);
struct node* newNode(int item);
int gcdrec(int a , int b);
void teachersmenu (struct students student[],struct generalinfo *details, int n);


//------------------------------------------------------------INT MAIN()------------------------------------------------------------

int main()
{
    quizMain();
    
    printf("\nEnter total number of quiz attendees : ");
    scanf("%d",&n);

    struct students student[n]; //structure variable for storing details for each student
    
    details=(struct generalinfo*)malloc(n*sizeof(struct generalinfo)); //memory allocation

    for(i=0;i<n;i++) //MAIN LOOP
    {
        do 
        {
            printf("\n#student-%d details",i+1);
            printf("\nEnter your details !");
            info(details,i);
            printf("Do you want to re-enter your details?(y/n)\n");
            scanf(" %c",&choice);
        }while(choice=='y' || choice=='Y');

        student[i] = takeQuiz(student,i);
    }
    
    struct node* root = NULL;
    root = insert(root,student[(n/2)].total);
    for(i=0;i<n;i++)
    {
        if(i!=n/2)
        insert(root,student[i].total);
    }

    inorder(root,student,n);

    teachersmenu(student,details,n);
    
}
  
//------------------------------------------------------------Fucntion Definitions------------------------------------------------------------

/*=========================================================================Teacher's Menu===============================================*/

void teachersmenu (struct students student[], struct generalinfo *details,int n)
{
    struct students temp;
    struct generalinfo tempinfo;
    int exitpw,t=0;
    int attempts=3;
    do
    {
        
        int pass;
        // pass=321
        printf("\nEnter password to access the teacher's menu:");
        scanf("%d",&pass);
        if(pass==321)
        {
            exitpw=1;
            do
            {
                printf("\n================================================================");
                printf("\nTeacher's Menu\nEnter 1 to get the number of students who got EXCELLENT as remark\nEnter 2 to get the male to female ratio of the candidates who took the quiz\nEnter 3 to get the SORTED MARKSHEET\nEnter 4 to check marks scored by a particular candidate\nEnter 5 to exit the menu");
                printf("\n================================================================");

                printf("\nEnter your choice(1,2,3,4,5) : ");
                scanf("%d",&teachoice);
                
                switch (teachoice)
                {
                case 1: {
                    printf("\nNumber of students who got EXCELLENT as remark are: %d",excellent);
                }
                break;
                case 2: {
                
                    printf("\nRatio = %d:%d",(male/gcdrec(male,female)),(female/gcdrec(male,female)));

                }
                break;
                case 3: {   

                    //to print the sorted markseet
                    int p=-1;
                    for(i=y;i<n;i++)
                    {
                        for(int j=0;j<n;j++)
                        {
                            if(sorted[i]==student[j].total && p!=j)
                            {
                                temp=student[i];
                                student[i]=student[j];
                                student[j]=temp;
                                tempinfo=*(details+i);
                                *(details+i)=*(details+j);
                                *(details+j)=tempinfo;
                                p=j;
                                y=y+1;
                                break;
                            }
                        }
                    }
                    
                    for(i=0;i<n;i++)
                    {
                        printf("\n%s         ",(details+i)->name);
                        for(int j=0;j<5;j++) //use this loop for printing the roll no.
                        printf("%d",(details+i)->rollno[j]);
                        
                        for(int k=0;k<1;k++) //this for printing the gender
                        printf("           %c          ",(details+i)->gender[k]);
                        printf("%d",student[i].total);
                    }
                        }
                        break;

                case 4:
                {
                    int itsok;
                    int roll[5];
                    printf("Enter the Roll No. of required candidate\n");
                    for (j = 0; j < 5; j++)
                    {
                        scanf("%1d",&roll[j]);
                    }
                    itsok=6;
                    for(int h=0;h<n;h++)
                    {
                    for(j=0;j<5;j++)
                    {
                        if((details+h)->rollno[j]!=roll[j])
                        {
                        itsok=5;
                        }
                        else{
                        itsok=6;
                        }
                    }
                        if(itsok==6)
                        {
                                printf("\n%s\t",(details+h)->name);
                                for(int j=0;j<5;j++) //use this loop for printing the roll no.
                                printf("%d",(details+h)->rollno[j]);
                                
                                for(int k=0;k<1;k++) //this for printing the gender
                                printf("\t%c\t",(details+h)->gender[k]);
                                printf("%d",student[h].total);
                            break;
                        }
                        else{printf("\nRoll no. doesn't exist");}
                    }

                }
                break;

                case 5:{
                    printf("\nExiting...");
                    printf("\n~Thank You~");
                    t=1;
                    
                }
                break;

                default: {
                    printf("\nWrong input, try again.");
                    break;
                }
                }
                if(t!=1){
                printf("\nDo you want to repeat Teacher's menu?(y/n)");
                scanf(" %c",&choice);}
            }while((choice=='y' || choice=='Y') && t==0);
        }
        else
        {
            attempts=attempts-1;
            printf("\nInvalid password! Try again");
            printf("\nNo. of attempts left: %d",attempts);
            if(attempts==0)
            {
                printf("\nNo. of attempts exceeded,Access Denied");
                exitpw=1;
            }
            else
            {
                exitpw=0;
            }
        }
    }while(exitpw!=1);
    

    
    printf("\n=====================END OF GLOBAL WARMING QUIZ=====================");
}
//=============Arav-Abi Fucntions=============

void quizMain (void)//to assign questions, options, answers.
{
    //assigning questions for Topic 1 Quiz
    topic1.question[0]="Which one of these increases the level of carbon dioxide in our atmosphere?";
    topic1.question[1]="What is an extreme event?";
    topic1.question[2]="What does EPA stand for?";
    topic1.question[3]="In the 10,000 years before the Industrial Revolution in 1751, carbon dioxide levels in the air rose by less than 10 percent. Since then they’ve risen by:";
    topic1.question[4]="How can we reduce global warming?";

    topic1.question[5]="Which of the following are ozone depleting substances?";
    topic1.question[6]="What is an ozone molecule formed from?";
    topic1.question[7]="What is the name of the international agreement committing parties to phasing out ozone depleting substances and phasing down hydrofluorocarbons (HFCs)?";
    topic1.question[8]="What is global warming potential (GWP)?";
    topic1.question[9]="What is the (approximate) global warming potential (GWP) of hydrofluorocarbon HFC-134a?";

    topic1.question[10]="Which of the following have ozone depleting substances and synthetic greenhouse gases commonly been used for?";
    topic1.question[11]="What is the difference between synthetic greenhouse gases and other greenhouse gases?";
    topic1.question[12]="How much ozone can one kilogram of halon 1211 destroy?";
    topic1.question[13]="The main cause of ozone depletion and the ozone hole is";
    topic1.question[14]="Ozone can be destroyed by the following free radical(s)";

    //Topic 1 answers
    topic1.answer[0]="4";
    topic1.answer[1]="4";
    topic1.answer[2]="3";
    topic1.answer[3]="2";
    topic1.answer[4]="4";

    topic1.answer[5]="1";
    topic1.answer[6]="1";
    topic1.answer[7]="2";
    topic1.answer[8]="4";
    topic1.answer[9]="3";

    topic1.answer[10]="4";
    topic1.answer[11]="2";
    topic1.answer[12]="4";
    topic1.answer[13]="4";
    topic1.answer[14]="4";

    //Topic 1 options
    topic1.option[0][0]="Driving a car";
    topic1.option[0][1]="Traveling by plane";
    topic1.option[0][2]="Cutting down trees";
    topic1.option[0][3]="All of the above";

    topic1.option[1][0]="Any event that ranks among the highest or lowest among all observations of its kind";
    topic1.option[1][1]="By how far removed the event is from the long-term average of all observations of that kind of event at that location";
    topic1.option[1][2]="By describing the event’s probability of occurrence in a given time span.";
    topic1.option[1][3]="All of the above";

    topic1.option[2][0]="Electronic Pollution Agency";
    topic1.option[2][1]="Environment Protocol Agency ";
    topic1.option[2][2]="Environmental Protection Agency";
    topic1.option[2][3]="Earth Protection Agency";

    topic1.option[3][0]="21 percent";
    topic1.option[3][1]="46 percent";
    topic1.option[3][2]="62 percent";
    topic1.option[3][3]="98 percent";

    topic1.option[4][0]="Reduce water waste";
    topic1.option[4][1]="Power your home with renewable energy";
    topic1.option[4][2]="Drive a fuel-efficient vehicle";
    topic1.option[4][3]="All of the above";

    topic1.option[5][0]="Chlorofluorocarbons (CFCs)";
    topic1.option[5][1]="Hydrofluorocarbons (HFCs)";
    topic1.option[5][2]="Hydrochlorofluorocarbons (HCFCs)";
    topic1.option[5][3]="Carbon dioxide (CO2)";

    topic1.option[6][0]="3 oxygen atoms";
    topic1.option[6][1]="3 carbon dioxide atoms";
    topic1.option[6][2]="2 carbon dioxide atoms";
    topic1.option[6][3]="2 hydrogen atoms and 1 oxygen atom";

    topic1.option[7][0]="Vienna Protocol";
    topic1.option[7][1]="Montreal Protocol";
    topic1.option[7][2]="Paris Agreement";
    topic1.option[7][3]="Antarctic Convention";

    topic1.option[8][0]="The effectiveness of an air conditioning system. The higher the global warming potential, the better the system at heating a room but the worse at cooling a room.";
    topic1.option[8][1]=" A measure of the amount of heat trapped in the atmosphere by a certain mass of gas compared to the amount of heat";
    topic1.option[8][2]="The net contribution of Antarctic wildlife to synthetic greenhouse gas emissions.";
    topic1.option[8][3]="The global temperature rise scientists predict would occur without the phase-down of synthetic greenhouse gases.";

    topic1.option[9][0]="130";
    topic1.option[9][1]="2200";
    topic1.option[9][2]="1430";
    topic1.option[9][3]="HFC-134a does not have a global warming potential.";


    topic1.option[10][0]="Asthma puffers";
    topic1.option[10][1]="Refrigerators and air conditioners";
    topic1.option[10][2]="Propellants in aerosol products";
    topic1.option[10][3]="All of the above";

    topic1.option[11][0]="Greenhouse gases are found in greenhouses, synthetic greenhouse gases are not.";
    topic1.option[11][1]="Greenhouse gases occur naturally and through human activity, synthetic greenhouse gases only occur through human activity.";
    topic1.option[11][2]="Synthetic greenhouse gases all contain silicon, other greenhouse gases do not.";
    topic1.option[11][3]="Both a. and b.";

    topic1.option[12][0]="1 kilogram";
    topic1.option[12][1]="100 tonnes";
    topic1.option[12][2]="50 kilograms";
    topic1.option[12][3]="50 tonnes";

    topic1.option[13][0]="halocarbon refrigerants";
    topic1.option[13][1]="propellants";
    topic1.option[13][2]="foam-blowing agents";
    topic1.option[13][3]="all of the above";

    topic1.option[14][0]="hydroxyl radicals (OH)";
    topic1.option[14][1]="nitric oxide radical (NO)";
    topic1.option[14][2]="chlorine radical (Cl)";
    topic1.option[14][3]="All of the above";
    //Topic 2 questions
    topic2.question[0]="Which of these countries have NOT vowed to use only 100%% renewable energy by 2050? ";
    topic2.question[1]="Which country has not run completely on renewable energy?";
    topic2.question[2]="In 2016, about how much of the United State’s energy consumption derived from renewable sources?(in percent)";
    topic2.question[3]="In the United States, which is one of the fastest growing renewable energy sectors?";
    topic2.question[4]="According to scientists, how many countries could run entirely on wind, solar, and water power by 2050?";

    topic2.question[5]="The Ozone hole is a much larger springtime decrease in ___ ozone around Erath’s polar regions.";
    topic2.question[6]="Following are referred to as ozone-depleting substances (ODs).";
    topic2.question[7]="The ozone hole occurs during the Antarctic";
    topic2.question[8]="The process by which the clouds remove NO2 from the stratosphere by converting it to nitric acid in the PSC particles, which then are lost by sedimentation is called";
    topic2.question[9]="Ozone depletion would magnify production of which vitamin?";

    topic2.question[10]="Montreal Protocol was signed in";
    topic2.question[11]="Following is used as refrigerant in automobile";
    topic2.question[12]="International Day for the Preservation of the Ozone Layer” or “World Ozone Day” falls in which month?";
    topic2.question[13]="Which atom released when CFCs molecules are broken from UV radiations?";
    topic2.question[14]="Which compound which is used in fire extinguishers cause ozone layer depletion?";
    //Topic 2 answers
    topic2.answer[0]="canada";
    topic2.answer[1]="usa";
    topic2.answer[2]="10";
    topic2.answer[3]="solar";
    topic2.answer[4]="140";

    topic2.answer[5]="Stratospheric";
    topic2.answer[6]="All";
    topic2.answer[7]="Spring";
    topic2.answer[8]="Denitrification";
    topic2.answer[9]="D";

    topic2.answer[10]="1987";
    topic2.answer[11]="R-134a";
    topic2.answer[12]="September";
    topic2.answer[13]="Chlorine";
    topic2.answer[14]="Halons";
}

struct students takeQuiz(struct students student[], int i)
{
    // variables local to function 
    int topicNo;
    int inp,occ1,occ2,retest=2,bestOf=0;
    int *re;
    int *inpt1[3], *inpt2[3];
    int ansFlag,inpIndex;
    int *t1mks[3],*t2mks[3];
    int *t1rand[3],*t2rand[3];
    int rd,rflag=0,flag=0;
    int t2atp;
    

    
    
    //char inp;
    
    // student[i].t1inp=(int *)calloc(5,sizeof(int));
    printf("\nWelcome to Quiz !");
    printf("\nInstructions for Quiz \nContains 2 TOPICS one with 5 MCQs and other with one word answer \n Each MCQ carries 2 points  \nTotal Marks for entire quiz 20 \nEach topic can be visited only once \nEach candidate can have only two retests for the quiz");
    printf("\n================================================================");
    

    re = (int*) malloc(3*sizeof(int));//so that default is 0, but malloc is more productive.
    do{
        inpt1[bestOf]=(int*)calloc(5,sizeof(int));//bestOf goes from 0 to 2
        inpt2[bestOf]=(int*)calloc(5,sizeof(int));
        t1mks[bestOf]=(int*)calloc(1,sizeof(int));//bestOf goes from 0 to 2
        t2mks[bestOf]=(int*)calloc(1,sizeof(int));

        t1rand[bestOf]=(int*)calloc(5,sizeof(int));//bestOf goes from 0 to 2
        t2rand[bestOf]=(int*)calloc(5,sizeof(int));
        
        printf("\nAttempt No. : %d/3",bestOf+1);
        occ1=0;
        occ2=0;
        do{
            printf("\nEnter your choice of Topic(1/2) : ");
            do{//scanf simplicity
                flag=1;
                scanf("%d",&topicNo);
                if(topicNo==1)
                {
                    if(occ1==0){
                        flag=0;
                        occ1++;
                    }else{
                        printf("\nTopic 1 already taken\nRe-Enter Topic choice\n");
                    }
                } else if(topicNo==2){
                    if(occ2==0){
                        flag=0;
                        occ2++;
                    }else{
                        printf("\nTopic 2 already taken\nRe-Enter Topic choice\n");
                    }
                } else {
                    printf("\nWrong Choice\nRe-Enter Topic choice\n");
                }
            }while(flag);

            switch(topicNo)
            {
                case 1:
                {
                    student[i].t1marks=0;
                    printf("\nTest 1-MCQs");
                    j=0;
                    while(j<5)
                    {
                        do {
                            rflag=0;
                            rd=rand()%15;
                            *(t1rand[bestOf]+j)=rd;
                            if(j!=0){
                                for(k=0;k<j;k++){
                                    if(rd==*(t1rand[bestOf]+k))
                                    {
                                        rflag=1;
                                        break;
                                    }
                                }
                            }
                        }while(rflag);//if rflag==0 then it exits
                                            
                        printf("\n================================================================");
                        printf("\nQ. %s",topic1.question[rd]);
                        for(int k=0;k<4;k++)
                        {
                            printf("\n%d. %s",k+1,topic1.option[rd][k]);
                        }
                        printf("\nYour Answer : ");
                        scanf("%d",&inp);
                        // *((student[i].t1inp)+j)=inp;
                        *(inpt1[bestOf]+j)=inp;

                        if(inp>=1&&inp<=4)
                        {
                            //if(inp == *(topic1.answer[j])) - somil was wrong
                            if(inp==((int)(*(topic1.answer[rd])))-48)
                            {
                                printf("Correct Answer!");
                                // student[i].t1marks+=2;
                                *t1mks[bestOf]+=2;
                            } else {
                                printf("Wrong Answer!");
                            }
                            j++;
                        } else{
                            printf("\nIncorrect input, try again with possible inputs");
                        }
                    } 
                    break;           
                }
                case 2:
                {
                    student[i].t2marks=0;
                    printf("\nTest 2-Subjective Type");
                    j=0;
                    while(j<5)
                    {

                        do {
                            rflag=0;
                            rd=rand()%15;
                            *(t2rand[bestOf]+j)=rd;
                            if(j!=0){
                                for(k=0;k<j;k++){
                                    if(rd==*(t2rand[bestOf]+k))
                                    {
                                        rflag=1;
                                        break;
                                    }
                                }
                            }
                        }while(rflag);//if rflag==0 then it exits


                        
                        // scanf("%[^\n]",&inpC);
                        //fflush(stdin);
                        // fgets(inpC)

                        // *((student[i].t1inp)+j)=inp;
                        // *(inpt2[bestOf]+j)=inpC;

                        t2atp=0;
                        do {
                            printf("\n================================================================");
                            printf("\nQ. %s",topic2.question[rd]);
                            printf("\nYour Answer : ");
                            scanf("%s",(inpt2[bestOf]+j));//takes inp even if it is an integer pointer  


                            if(strcmpi((inpt2[bestOf]+j),topic2.answer[rd]) == 0)//can't do it later, cuz input is continuous
                            {
                                printf("Correct Answer!");
                                ansFlag = 1;
                            } else {
                                printf("Wrong Answer!");
                                ansFlag = 0;
                            }


                            if(ansFlag==1)
                            {
                                // student[i].t2marks+=2;//sums up
                                *t2mks[bestOf]+=2;
                                choice = 'n';
                            }else if(t2atp<2){
                                t2atp++;
                                printf("\nRe-do Attempt/s left: %d",2-t2atp);// 1,0
                                printf("\nDo you want to redo the question?(y/n)");
                                scanf(" %c",&choice);
                                // choice=getchar();
                            }else{
                                choice='n';
                                printf("\nNo of Re-do Attempts Exceeded!");
                            }
                            
                            // if(choice!='y' || choice!='Y'){j++;}// re-check ,dk what the problem is -_-
                        } while (choice=='y' || choice=='Y');         
                        j++;    
                    }
                    break;
                }
                default://can never be reached 
                {
                    printf("Wrong Input for Topic Choice");
                }
                
            }
        }while(!(occ1==1&&occ2==1));
        // student[i].total = student[i].t1marks + student[i].t2marks;//adds both marks up
        *(re+bestOf) = *t1mks[bestOf] + *t2mks[bestOf];

        printf("\n================================================================");
        printf("\nNo. of retests attempts left : %d",retest);
        if(retest==0){printf("\nYou can't take anymoere retests.");break;}
        --retest;
        ++bestOf;
        printf("\nDo you want to take a retest?(y/n)");
        scanf(" %c",&choice);

    }while (choice=='y' || choice=='Y');
    
    //Best of given no. of attempts - wrt total score
    printf("\n================================================================");
    static int max;
    max = 0;
    printf("\nCalculating best of %d test/s",bestOf);//gg
    for (j = 0; j < bestOf; j++)
    {
        printf("\nScore in %d attempt : %d",j+1,*(re+j));
        if(*(re+j) >= max){
            max = *(re+j);
            inpIndex = j;
        }
    }

    // reassigned to main indexes 
    student[i].total = max;
    student[i].t1marks = *t1mks[inpIndex];
    student[i].t2marks = *t2mks[inpIndex];

    if(student[i].total==20)
        excellent++;

    // printf("\n%d",student[i].total);
    // printf("\n%d",student[i].t1marks);
    // printf("\n%d",student[i].t2marks);

    

    printf("\nBest of %d tests : %d",bestOf,max);
    printf("\n================================================================");

    //check-imp
    // for(int i = 0;i<5;i++)
    //     printf("\n%d",*(inpt1[inpIndex]+i));

    // for(int i = 0;i<5;i++)
    //     printf("\n%s",(inpt2[inpIndex]+i));//gg not pointer value, but base address
   
    do
    {
        printf("\n================================================================");
        printf("\nResult Menu \n1.For Remark \n2.For Detailed Analysis - Topicwise and overall \n3.To output incorrect question and answer along with your input \n(It is good to learn from your mistakes) \n4.To exit");
        printf("\n================================================================");

        printf("\nEnter your choice(1,2,3,4) : ");
        scanf("%d",&intChoice);
        
        switch (intChoice)
        {
        case 1: {
            do
            {
                (student[i].total >= 20)?printf("Excellent"):((student[i].total >= 16)?printf("Very Good"):printf("\nTime to brush up on your knowledge of global warming"));
                printf("\nDo you want to repeat Remark Analysis?(y/n)");
                scanf(" %c",&choice);
            } while (choice=='y' || choice=='Y');
            
            break;
        }
        case 2: {
            do
            {
                printf("\n================================================================");
                printf("\nDetailed Analysis Menu \n1.For Topic 1\n2.For Topic 2\n3.For overall analysis\n4.To exit");
                printf("\n================================================================");

                printf("\nEnter your choice(1,2,3,4) : ");
                scanf("%d",&intChoice);

                switch (intChoice)
                {
                case 1: {
                    printf("\n================================================================");
                    printf("\nAnalysis for Topic 1");
                    detailedQuiz((student[i].t1marks)/2,5-((student[i].t1marks)/2),5);
                    printf("\n================================================================");
                    break;
                }
                case 2: {
                    printf("\n================================================================");
                    printf("\nAnalysis for Topic 2");
                    detailedQuiz((student[i].t2marks)/2,5-((student[i].t2marks)/2),5);
                    printf("\n================================================================");
                    break;
                }
                case 3: {
                    printf("\n================================================================");
                    printf("\nOverall Analysis");
                    detailedQuiz((student[i].total)/2,10-((student[i].total)/2),10);
                    printf("\n================================================================");
                    break;
                }
                case 4: {
                    printf("\nExiting...");
                    flag = 1;
                    break;
                }
                default: {
                    printf("\nWrong input, try again.");
                    break;
                }
                }
                if(flag==1){break;}
                printf("\nDo you want to repeat Detailed Analysis?(y/n)");
                scanf(" %c",&choice);

            } while (choice=='y' || choice=='Y');
            break;
        }
        case 3: {
            printf("\nInccorrectly Attempted Analysis");
            do
            {
                printf("\n================================================================");
                printf("\nIncorrectly Attempted Questions Menu \n1.For topic 1 \n2.For topic 2 \n3.To exit");
                printf("\n================================================================");

                printf("\nEnter your choice(1,2,3) : ");
                scanf("%d",&intChoice);

                switch (intChoice)
                {
                case 1: {
                    printf("\n================================================================");
                    printf("\nIncorrectly Attempted Questions from Topic 1");
                    for(i = 0; i < 5;i++)
                    {
                        rd=*(t1rand[inpIndex]+i);
                        if(*(inpt1[inpIndex]+i) != ((int)(*(topic1.answer[rd]))-48)) {
                            printf("\nQ. %s",topic1.question[rd]);
                            for(int k=0;k<4;k++)
                            {
                                printf("\n%d. %s",k+1,topic1.option[rd][k]);
                            }
                            printf("\nYour Input : %d",*(inpt1[inpIndex]+i));
                            printf("\nCorrect Answer : %d",((int)(*(topic1.answer[rd])))-48);
                            printf("\n================================================================");
                        }
                    }
                    printf("\nDo you want a feedback copy? (y/n)");
                    scanf(" %c",&choice);
                    static int x=0;

                    if(choice=='y' || choice=='Y')
                    {
                        printf("\nCreating file...");
                        FILE *fptr;
                        static char fname[5];
                        static char filename[50];
                        sprintf(filename,"%s-Topic1.txt",tName);
                        fptr=fopen(filename,"w+");
                        for(i = 0; i < 5;i++)
                        {
                            rd=*(t1rand[inpIndex]+i);
                            if(*(inpt1[inpIndex]+i) != ((int)(*(topic1.answer[rd]))-48)) {
                                fprintf(fptr,"\nQ. %s",topic1.question[rd]);
                                for(int k=0;k<4;k++)
                                {
                                    fprintf(fptr,"\n%d.%s",k+1,topic1.option[rd][k]);
                                }
                                fprintf(fptr,"\nYour Input : %d",*(inpt1[inpIndex]+i));
                                fprintf(fptr,"\nCorrect Answer : %d",((int)(*(topic1.answer[rd])))-48);
                                fprintf(fptr,"\n================================================================");
                            }
                        }
                        fclose(fptr);
                        x++;
                        
                    }
                    
                    
                    break;
                }
                case 2: {
                    printf("\n================================================================");
                    printf("\nIncorrectly Attempted Questions from Topic 2");
                    for(i = 0; i < 5;i++)
                    {
                        rd=*(t2rand[inpIndex]+i);
                        if(strcmpi((inpt2[inpIndex]+i),topic2.answer[rd]) != 0) {
                            printf("\nQ. %s",topic2.question[rd]);
                            printf("\nYour Answer : %s",(inpt2[inpIndex]+i));//works just with base address, no need of value
                            printf("\nCorrect Answer : %s",topic2.answer[rd]); 
                            printf("\n================================================================");
                        }
                    }
                    printf("\nDo you want a feedback copy? (y/n)");
                    scanf(" %c",&choice);
                    if(choice=='y' || choice=='Y'){
                        FILE *fptr;
                        static char filename[50];
                        sprintf(filename,"%s-Topic2.txt",tName);
                        fptr=fopen(filename,"w+");
                        for(i = 0; i < 5;i++)
                        {
                            rd=*(t2rand[inpIndex]+i);
                            if(strcmpi((inpt2[inpIndex]+i),topic2.answer[rd]) != 0) {
                                fprintf(fptr,"\nQ. %s",topic2.question[rd]);
                                fprintf(fptr,"\nYour Answer : %s",(inpt2[inpIndex]+i));//works just with base address, no need of value
                                fprintf(fptr,"\nCorrect Answer : %s",topic2.answer[rd]);
                                fprintf(fptr,"\n================================================================");
                            }
                        }
                    fclose(fptr);
                    }
                    
                    break;
                }
                case 3: {
                    printf("\nExiting...");
                    flag = 1;
                    break;
                }
                default: {
                    printf("\nWrong input, try again.");
                    break;
                }
                }

                if(flag==1){break;}
                printf("\nDo you want to repeat Incorrectly Attempted Analysis?(y/n)");
                scanf(" %c",&choice);

            } while (choice=='y' || choice=='Y');
            break;
        }
        case 4:{
            printf("\nExiting...");
            rflag=1;
            break;
        }
        default: {
            printf("\nWrong input, try again.");
            break;
        }
        }

        if(rflag==1){break;}
        printf("\nDo you want to repeat Results menu?(y/n)");
        scanf(" %c",&choice);
    }while(choice=='y' || choice=='Y');


    for(j=0;j<3;j++)
    {
        free(inpt1[j]);
        free(inpt2[j]);
        free(t1mks[j]);
        free(t2mks[j]);
        free(t1rand[j]);
        free(t2rand[j]);
    }
     
    free(re);

    return student[i] ;
}

int gcdrec(int a , int b)
{
    return(b!=0 ? gcdrec(b,a%b) :a);
}

void detailedQuiz (int c,int w,int o)
{
    printf("\nNumber of correct answers : %d/%d",c,o);
    printf("\nNumber of wrong answers : %d/%d",w,o);

    printf("\nPercentage of correct answers : %d%%",(c*100)/5);
    printf("\nPercentage of wrong answers : %d%%",(w*100)/5);

    printf("\nTotal Marks scored : %d/%d",c*2,o*2);
    printf("\nTotal Percentage : %d%%",(c*100)/5);

}

//===================================================
struct generalinfo info (struct generalinfo *details, int i)
{
    printf("\nEnter your name :");
    scanf("%s",(details+i)->name);

    strcpy(tName,(details+i)->name); //for naming the file

    int count,j,x,l;
    do
    {
        printf("\nEnter your 5 digit roll no. : ");
        fflush(stdin);
        
        count = 5;
        for (j = 0; j < 5; j++)
        {
            scanf("%1d",&(details+i)->rollno[j]);
            // strcat(tRoll,(details+i)->rollno[j]);
        }
        //  fflush(stdin);
        if(i>0)
        {
           count=6;
            for(int l=0;l<i;l++)
            {
              for(j=0;j<5;j++)
              {
                 if((details+l)->rollno[j]!=(details+i)->rollno[j])
                {
                  count=5;
                }
                else{
                  count=6;
                }
              }
                if(count==6)
                break;
            }
        }
        (count!=5)?printf("Re-enter your Roll No."):printf("Correct Roll No. !");
                
    } while (count!=5);

    do
    {
        printf("\nEnter gender?(m/f)");
        fflush(stdin);
        fgets((details+i)->gender,2,stdin);
        fflush(stdin);
    } while (*((details+i)->gender)!='M'&&*((details+i)->gender)!='m'&&*((details+i)->gender)!='F'&&*((details+i)->gender)!='f');

    if(*((details+i)->gender)=='M' || *((details+i)->gender)=='m')
    male++;
    if(*((details+i)->gender)=='F' || *((details+i)->gender)=='f')
    female++;
}


//=============BST Fucntions=============

void inorder(struct node* root, struct students student[], int n) // Function to do inorder traversal of BST
{   
    if (root != NULL)
    {
        inorder(root->left,student,n);
        if(root->c==1)
        {
           
            sorted[inc]= root->key;
            inc=inc+1;
            
        }

        if(root->c!=1)
        {
            int k;
            for(k=1;k<= root->c;k++)
            {
           
            sorted[inc]= root->key;
            inc=inc+1;
            
            }
        }
        inorder(root->right,student,n);
    }
}
 
struct node* insert(struct node* node, int key) // Function to insert a new node with given key in BST
{
    /* If the tree is empty, return a new node */
    if (node == NULL)
        return newNode(key);
    
    if (key == node->key)
    {
       (node->c)++;
        return node;
    }

    /* Otherwise, recur down the tree */
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
 
    /* return the (unchanged) node pointer */
    return node;
}

struct node* newNode(int item) // Function to create a new BST node
{
    struct node* temp
        = (struct node*)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = NULL;
    temp->c=1;
    return temp;
}
