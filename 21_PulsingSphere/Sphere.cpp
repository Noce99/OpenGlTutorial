/*
    00-01-02-03     
    04-05-06-07
    08-09-10-11
    12-13-14-15
    -----------
    16-17-18-19
    27-//-//-20
    26-//-//-21
    25-24-23-22
    -----------
    28-29-30-31
    39-//-//-32
    38-//-//-33
    37-36-35-34
    -----------
    40-41-42-43
    44-45-46-47
    48-49-50-51
    52-53-54-55
*/

#include <iostream>
#include <cmath>
using namespace std;

void addVertex(double, double, double);
void print();

double edge = 1;//Must be >0
int resolution = 6;//must be in N and not zero
double ledge = edge/(double)(resolution); //little edge
int nov = (resolution+1)*(resolution+1)*2 + (resolution*4)*(resolution-1);//Number of Vertex
double* vertex = new double[nov*3];
int vind = 0; //vertexbuffer index
    
int main(){
    for(int i=0;i<nov*3;i=i+3){
        vertex[i] = 0.0f;
    }
    double x,y,z;
    for(z=edge/2.0f;z>-edge/2.0f;z=z-ledge){
        if (abs(abs(z)-edge/2.0f)<0.0001f){
            for(y=edge/2.0f;y>-edge/2.0f;y=y-ledge){
                for(x=-edge/2.0f;x<edge/2.0f;x=x+ledge){
                    addVertex(x, y, z);
                }
            }
        }else{
            y=edge/2.0f;
            for(x=-edge/2.0f;x<edge/2.0f-0.0001f;x=x+ledge){
                addVertex(x, y, z);
            }
            x=edge/2.0f;
            for(y=edge/2.0f;y>-edge/2.0f+0.0001f;y=y-ledge){
                addVertex(x, y, z);
            }
            y=-edge/2.0f;
            for(x=edge/2.0f;x>-edge/2.0f+0.0001f;x=x-ledge){
                addVertex(x, y, z);
            }
            x=-edge/2.0f;
            for(y=-edge/2.0f;y<edge/2.0f-0.0001f;y=y+ledge){
                addVertex(x, y, z);
            }
        }
    }
    print();
    cout<<"------------------------------------------------"<<endl;
    cout<<"NOV: "<<nov<<" NOV*3: "<<nov*3<<endl; 
}

void addVertex(double x, double y, double z){
    vertex[vind] = x;
    vind++;
    vertex[vind] = y;
    vind++;
    vertex[vind] = z;
    vind++;
}

void print(){
    for(int i=0;i<nov*3;i=i+3){
        cout<<vertex[i]<<"f, "<<vertex[i+1]<<"f, "<<vertex[i+2]<<"f, ";
        if((i/3+1)%(resolution+1)==0){
            cout<<"\n";
        }
    }
}
