#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
void input(int);
void allotperiod(int,int);
int checkperiod(int,int,int,int,int);
void allotlab(int,int);
int checklab(int,int,int);
int checkperiod_in_day(int,int,int);
int checkstaff(char*);
int total_staff;
struct inputx
{
    int number_of_subject;
    int number_of_theory;
    int number_of_lab;
    char semester[25];
    char lab[200][100];
    char theory[200][100];
    char lab_staff[200][100];
    char theory_staff[200][100];
    int lfrequency[200];
    int tfrequency[200];
    char timetable[5][7][100];
    char name[25];
    int number_of_periods;
}x[100];
struct staff_tt
{
    char name[100];
    char staff_timetable[5][7][100];
}s[100];
void input(int noc)                                                                 //getting input
{   
    for(int j=0;j<noc;j++)
    {   
        int count=0;
        printf("------------------------------Input for class %d-----------------------------\n",j+1);
        printf("Enter semester:");
        // gets(x[j].semester);
        scanf("%s",x[j].semester);
        printf("Enter Class:");
        scanf("%s",&x[j].name);
        printf("ENTER THE NUMBER OF THEORY CLASS:\t");
        scanf("%d",&x[j].number_of_theory);
        printf("ENTER NUMBER OF LAB CLASS:\t");
        scanf("%d",&x[j].number_of_lab);
        x[j].number_of_subject=x[j].number_of_lab+x[j].number_of_theory;
        for(int i=0;i<x[j].number_of_theory;i++)
        {
            printf("Enter theory subject %d:",i+1);
            scanf("%s",x[j].theory[i]);
            printf("Enter faculty for %s theory:",x[j].theory[i]);
            scanf("%s",x[j].theory_staff[i]);
        }
        for(int i=0;i<x[j].number_of_lab;i++)
        {
            printf("Enter lab subject %d :",i+1);
            scanf("%s",x[j].lab[i]);
            printf("Enter faculty for %s lab:",x[j].lab[i]);
            scanf("%s",x[j].lab_staff[i]);
        }
        printf("*****Enter number of periods per weeks*****\n");
        for(int i=0;i<x[j].number_of_theory;i++)
        {
            printf("Enter number of period for %s:",x[j].theory[i]);
            scanf("%d:",&x[j].tfrequency[i]);
        }
        for(int i=0;i<x[j].number_of_lab;i++)
        {
            printf("Enter number of period for %s lab:",x[j].lab[i]);
            scanf("%d:",&x[j].lfrequency[i]);
        }
        printf("--------------------------------------------------------------------\n");
    }
}
void staff_count(int noc)
{
    int sum=0;
    for(int i=0;i<noc;i++)
    {
        sum+=x[i].number_of_subject;
    }
    total_staff=sum;
    int j=0;
    while(j<total_staff)
    {
        for(int k=0;k<noc;k++)
        {
            for(int i=0;i<x[k].number_of_theory;i++)
            {
                if(checkstaff(x[k].theory_staff[i])==0)
                {
                    strcpy(s[j].name,x[k].theory_staff[i]);
                    j++;
                }
            }
            for(int i=0;i<x[k].number_of_lab;i++)
            {
                if(checkstaff(x[k].lab_staff[i])==0)
                {
                    strcpy(s[j].name,x[k].lab_staff[i]);
                    j++;
                }
            }
        }
        total_staff=j;
        break;
    }
}
int checkstaff(char* name)
{
    int flag=0;
    for(int i=0;i<total_staff;i++)
    {
        if(strcmp(s[i].name,name)==0)
        {
            flag+=1;
            break;
        }
    }
    if(flag==0)
    {
        return 0;
    }
    return 1;
}
void allotperiod(int n,int h)
{
    int day,period,flag=0,iflag=0,oflag=0;
    day=rand()%5;
    period=rand()%7;
    if(strcmp(x[h].timetable[day][2],"BREAK")!=0)
        strcpy(x[h].timetable[day][4],"BREAK");
    if(strlen(x[h].timetable[day][period])==0)
    {
        if(h==0)
        {
            if(strlen(x[h].timetable[day][0])==0)
            {
                strcpy(x[h].timetable[day][0],x[h].theory[n]);
                for(int i=0;i<total_staff;i++)
                {
                    if(strcmp(s[i].name,x[h].theory_staff[n])==0)
                    {
                        strcpy(s[i].staff_timetable[day][0],x[h].name);
                         return;
                    }
                }
            }
            if(checkperiod_in_day(h,n,day)==0)
            {
                strcpy(x[h].timetable[day][period],x[h].theory[n]);
                for(int i=0;i<total_staff;i++)
                {
                    if(strcmp(s[i].name,x[h].theory_staff[n])==0)
                    {
                        strcpy(s[i].staff_timetable[day][period],x[h].name);
                        return;
                    }
                }
            }
            else
                allotperiod(n,h);
        }
        else
        {
            for(int i=1;i!=h;i++)
            {
                for(int j=0;j<x[h-i].number_of_theory;j++)
                {
                    if(checkperiod(h,h-i,n,day,0)==1)
                    {
                        oflag+=1;
                    }
                    if(checkperiod(h,h-i,n,day,period)==1)
                    {
                        iflag+=1;
                    }
                }   
            }
            if(oflag==0 && strlen(x[h].timetable[day][0])==0)
            {
                if(checkperiod_in_day(h,n,day)==0)
                {
                    strcpy(x[h].timetable[day][0],x[h].theory[n]);
                    for(int i=0;i<total_staff;i++)
                    {
                        if(strcmp(s[i].name,x[h].theory_staff[n])==0)
                        {
                            strcpy(s[i].staff_timetable[day][0],x[h].name);
                        }
                    }
                }
                else
                {
                    allotperiod(n,h);
                }
            }
            else if(iflag==0)
            {
                if(checkperiod_in_day(h,n,day)==0)
                {
                    strcpy(x[h].timetable[day][period],x[h].theory[n]);
                    for(int i=0;i<total_staff;i++)
                    {
                        if(strcmp(s[i].name,x[h].theory_staff[n])==0)
                        {
                            strcpy(s[i].staff_timetable[day][period],x[h].name);
                        }
                    }
                }
                else
                {
                    allotperiod(n,h);
                }
            }
            
            else
                allotperiod(n,h);
        }
    }
    else
        allotperiod(n,h);  
}
int checkperiod(int l,int m,int n,int d,int p)
{
    int pos,flag=0;
    for(int i=0;i<x[m].number_of_theory;i++)
    {
        if(strcmp(x[l].theory_staff[n],x[m].theory_staff[i])==0)
        {
            if(strcmp(x[l].timetable[d][p],x[m].theory[i])==0)
            {
                flag+=1;
                break;
            }
        }
    }
    if(flag==0)
        return 0;
    return 1;
}
int checkperiod_in_day(int h,int n,int d)
{
    int flag=0;
    for(int i=0;i<7;i++)
    {
        if(strcmp(x[h].timetable[d][i],x[h].theory[n])==0)
        {
            flag+=1;
            break;
        }
    }
    if(flag==0)
        return 0;
    return 1;
}
void allotlab(int n,int h)                                          //to allot lab
{
    int lflag=0;
    int d=rand()%5;
    int p=rand()%7;
    for(int i=0;i<3;i++)
    {
        if(strlen(x[h].timetable[d][p+i])==0)
        {
            lflag+=1;
        }
    }
    if(lflag==3 && (p==1 || p==3))
    {
        for(int i=0;i<3;i++)
        {
            strcpy(x[h].timetable[d][p+i],x[h].lab[n]);
            for(int j=0;j<total_staff;j++)
            {
                if(strcmp(s[j].name,x[h].lab_staff[n])==0)
                {
                    strcpy(s[j].staff_timetable[d][p+i],x[h].name);
                }
            }
        }
        if(p==3)
        {
            strcpy(x[h].timetable[d][2],"BREAK");
            return;
        }
    }
    else
        allotlab(n,h);
}
int main()
{ 
    int number_of_class;
    printf("ENTER NUMBER OF CLASS:");
    scanf("%d",&number_of_class);
    input(number_of_class);
    srand(time(NULL));
    staff_count(number_of_class);
    for(int k=0;k<number_of_class;k++)
    {
        for(int i=0;i<x[k].number_of_lab;i++)
        {
            for(int j=0;j<x[k].lfrequency[i];j++)
            {
                allotlab(i,k);
            }
        }
        for(int m=0;m<x[k].number_of_theory;m++)
        {
            for(int n=0;n<x[k].tfrequency[m];n++)
            {
                allotperiod(m,k);
            }
        }
    }   
    for(int k=0;k<number_of_class;k++)
    {
        for(int i=0;i<5;i++)
        {
            for(int j=0;j<7;j++)
            {
                printf("%s\t",x[k].timetable[i][j]);
            }
        printf("\n");
        }
        printf("-------------------------------------------------\n");
    }
    for(int k=0;k<total_staff;k++)
    {   
        printf("%s:\n",s[k].name);
        for(int i=0;i<5;i++)
        {
            for(int j=0;j<7;j++)
            {
                printf("%s\t",s[k].staff_timetable[i][j]);
            }
        printf("\n");
        }
        printf("-------------------------------------------------\n");
    }
    
}
