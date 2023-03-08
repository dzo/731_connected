#include <iostream>
#include <opencv2/opencv.hpp>

#include <unordered_set>

using namespace cv;
using namespace std;

typedef pair<int, int> pairs;

int main(int argc, char** argv) {
    (void)argv[argc - 1];
    srand(100);
    Mat_<Vec3b> binary;
    binary=imread("../../Binary1.jpg");
    Mat_<uint8_t> i;
    cvtColor(binary,i,COLOR_BGR2GRAY);
    imshow("input", i);
    vector<set<pairs>> sets;
    vector<Vec3b> colours;
    int counter=-1;
    int s1,s2;
    Mat_<int> A(i.rows,i.cols);
    A=-1;
    for(int y=1;y<A.rows;y++) {
      cout<<y<<endl;
      for(int x=1;x<A.cols;x++) {
        if(i(y,x)>128) {
          if (i(y,x-1)>128 || i(y-1,x)>128){
            s1=A(y,x-1);
            s2=A(y-1,x);
            if(s1!=-1) {
              sets[s1].insert(pair(y,x));
              A(y,x)=s1;
            }
            if(s2!=-1) {
              sets[s2].insert(pair(y,x));
              A(y,x)=s2;
            }
            if(s1!=s2 && s1!=-1 && s2!=-1) {
              for(set<pairs>::iterator it=sets[s2].begin();it!= sets[s2].end();it++) {
                sets[s1].insert(*it);
                A(it->first,it->second)=s1;
              }
              sets[s2].clear();
            }
          } else {
            counter++;
            set<pairs> ns;
            sets.push_back(ns);
            sets[counter].insert(pair(y,x));
            colours.push_back(Vec3b(rand()%220+35,rand()%220+35,rand()%220+35));
            A(y,x)=counter;
          }
        }
      }
    }
    cout<<counter<<endl;
    imwrite("op.png",A);
    Mat_<Vec3b> c(i.rows,i.cols);
    for(int y=0;y<i.rows;y++) {
      for(int x=0;x<i.cols;x++)
        c(y,x)=colours[A(y,x)];
    }
    imwrite("opc.png",c);
    imshow("output",c);

    waitKey(0);

}
