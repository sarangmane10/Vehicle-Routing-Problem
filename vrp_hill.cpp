#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<vector>
using namespace std;


int fitness(vector<vector<int>>route,vector<vector<int>> distance_matrix)
    {
        int total_distance = 0;
        for (int i = 0; i < route.size(); i++)
        for (int  j = 0; j < route[i].size()-1; j++)
        {
           total_distance+=distance_matrix[route[i][j]][route[i][j+1]];
        }
        return total_distance;
}

vector<vector<int>> random_Route(vector<vector<int>>rout,int n_Loc,int n_Vehicle)
{
    vector<int>vehicleArr[n_Vehicle];
    srand(static_cast<unsigned int>(time(0)));

        
            vector<int>arr(n_Loc,1);
            int sum=n_Loc;
            for(int i=0;i<n_Vehicle;i++)
            vehicleArr[i].push_back(0);
            while (sum!=0)
            {
                for(int j=0;j<n_Vehicle;j++)
                {
                    int index= rand() % n_Loc;   
                    if(arr[index]!=0)
                    {
                    vehicleArr[j].push_back((index+1));
                    arr[index]=0;
                    }
                    else
                    {
                        for(int k=0;k<n_Loc;k++)
                        {
                            if(arr[k]!=0)
                            {
                            vehicleArr[j].push_back((k+1));
                            arr[k]=0;
                            break;
                            }
                        }
                    }
                    sum=0;
                    for(int k=0;k<n_Loc;k++)  
                    sum+=arr[k];
                    if(sum==0) break;
                }
            }
            for(int j=0;j<n_Vehicle;j++)
            vehicleArr[j].push_back(0);

            for(int j=0;j<n_Vehicle;j++)   
            rout.push_back(vehicleArr[j]);
            
        return rout;
}

void print_Rout(vector<vector<int>>rout,int n_Vehicle)
{
   
        for(int i=0;i<n_Vehicle;i++)
        {
            cout<<"Route of "<<i+1<<" vehical :"<<endl;
            for(int j=0;j<rout[i].size();j++)
            cout<<"->"<<rout[i][j];
            cout<<endl;
        }
        cout<<endl;
}

void modify(int arr[],vector<vector<int>>&rout)
{
    for (int i = 0; i < rout.size()-1; i++)
    {
        swap(rout[i][arr[i]],rout[i+1][arr[i+1]]);
    }
    
}



int main()
{
        int n_Loc=16;
        int n_Vehicle=3;
        int n_itaretion=1000;
        int best_Fitness=INT_MAX;
        vector<vector<int>>best_rout;
        vector<vector<int>>rout;
        vector<vector<int>>distance_Matrix=
        {
        {0, 548, 776, 696, 582, 274, 502, 194, 308, 194, 536, 502, 388, 354, 468,776, 662},
        {548, 0, 684, 308, 194, 502, 730, 354, 696, 742, 1084, 594, 480, 674,1016, 868, 1210},
        {776, 684, 0, 992, 878, 502, 274, 810, 468, 742, 400, 1278, 1164, 1130,788, 1552, 754},
        {696, 308, 992, 0, 114, 650, 878, 502, 844, 890, 1232, 514, 628, 822,1164, 560, 1358},
        {274, 502, 502, 650, 536, 0, 228, 308, 194, 240, 582, 776, 662, 628, 514,1050, 708},
        {502, 730, 274, 878, 764, 228, 0, 536, 194, 468, 354, 1004, 890, 856, 514,1278, 480},
        {582, 194, 878, 114, 0, 536, 764, 388, 730, 776, 1118, 400, 514, 708,1050, 674, 1244},
        {194, 354, 810, 502, 388, 308, 536, 0, 342, 388, 730, 468, 354, 320, 662,742, 856},
        {308, 696, 468, 844, 730, 194, 194, 342, 0, 274, 388, 810, 696, 662, 31084, 514},
        {194, 742, 742, 890, 776, 240, 468, 388, 274, 0, 342, 536, 422, 388, 274,810, 468},
        {536, 1084, 400, 1232, 1118, 582, 354, 730, 388, 342, 0, 878, 764, 730,388, 1152, 354},
        {502, 594, 1278, 514, 400, 776, 1004, 468, 810, 536, 878, 0, 114, 308,650, 274, 844},
        {388, 480, 1164, 628, 514, 662, 890, 354, 696, 422, 764, 114, 0, 194, 536,388, 730},
        {354, 674, 1130, 822, 708, 628, 856, 320, 662, 388, 730, 308, 194, 0, 342,422, 536},
        {468, 1016, 788, 1164, 1050, 514, 514, 662, 320, 274, 388, 650, 536, 342,0, 764, 194},
        {776, 868, 1552, 560, 674, 1050, 1278, 742, 1084, 810, 1152, 274, 388,422, 764, 0, 798},
        {662, 1210, 754, 1358, 1244, 708, 480, 856, 514, 468, 354, 844, 730, 536,194, 798, 0}
        };
      
        rout=random_Route(rout,n_Loc,n_Vehicle);
        print_Rout(rout,n_Vehicle);
        
        for(int i=0;i<n_itaretion;i++)
        {
            int current_Fitness;
            current_Fitness=fitness(rout,distance_Matrix);
            if(current_Fitness<best_Fitness)
            {
                best_rout=rout;
                best_Fitness=current_Fitness;
                if(current_Fitness<0)
                break;
            }
            cout<<"Route in "<<i <<" th iteration : \n\n";
            print_Rout(rout,n_Vehicle);
            cout<<"Current Fitness : "<<current_Fitness<<endl;
            cout<<"Best fitness : "<<best_Fitness<<"\n\n=================================================================================\n";
            rout=best_rout;
            int arr[n_Vehicle];
            for (int i = 0; i < n_Vehicle; i++)
            {
                arr[i]=rand()%(rout[i].size()-1);
                if(arr[i]==0) arr[i]++;
            }
            cout<<endl;
            
            modify(arr,rout);
        }

        cout<<"Best rout is : "<<"\n\n";
        print_Rout(best_rout,n_Vehicle);  
        cout<<"Best Fitness value is : "<<best_Fitness<<"\n\n";
        cout<<"=================================================================================\n";
}